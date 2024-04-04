use std::{collections, env, fmt::Write, fs};

fn print_byte(byte: u8) {
    for col in 0..8 {
        if (byte & (0x80 >> col)) != 0 {
            print!("█");
        } else {
            print!("_");
        }
    }
}

fn print_string(string: &str, char_rom: &[u8]) {
    for row in 0..10 {
        for c in string.chars() {
            let byte = char_rom[row * 128 + c as usize];
            print_byte(byte);
        }
        println!();
    }
}

fn main() {
    let char_rom_path = "../roms/osborne1/7a3007-00.ud15";
    let char_rom = fs::read(&char_rom_path).expect("failed to read character ROM");

    let mut patterns = vec![collections::BTreeSet::new(); 10 * 256];

    for c in 0u8..128u8 {
        println!("0x{:02X}: {:?}", c, c as char);
        for row in 0..10 {
            let byte = char_rom[row * 128 + c as usize];
            print_byte(byte);
            println!();
            patterns[row * 256 + byte as usize].insert(c as char);
        }
    }

    for row in 0..10 {
        println!("Row {}", row);
        for byte in 0..256 {
            let chars = &patterns[row * 256 + byte];
            if ! chars.is_empty() {
                println!("0x{:02X}: {:?}", byte, chars);
                print_byte(byte as u8);
                println!();
            }
        }
    }

    println!("Printing string");
    print_string("Hello", &char_rom);

    use image::{self, imageops::*, GenericImageView, Luma};
    const COLS: usize = 17; // 52 is maximum, adjust for cycles
    const ROWS: usize = 17; // 24 is maximum
    const CELL_WIDTH: usize = 8;
    const CELL_HEIGHT: usize = 10;
    const SCALE_X: usize = 1; // 4 to remove artifacts, 1 to increase apparent resolution
    const SCALE_Y: usize = 1; // Multiply this by 256 cycles for character swapping time
    const WIDTH: usize = COLS * CELL_WIDTH / SCALE_X;
    const HEIGHT: usize = ROWS * CELL_HEIGHT / SCALE_Y;
    let img_path = env::args().nth(1).unwrap_or("icon.png".to_string());
    let img = image::open(img_path).unwrap();
    let img = img.resize_exact(WIDTH as u32, HEIGHT as u32, FilterType::Nearest);
    let mut img = img.grayscale();
    let mut img = img.as_mut_luma8().unwrap();
    //dither(&mut img, &BiLevel);

    let mut image = [[false; WIDTH * SCALE_X]; HEIGHT * SCALE_Y];
    for y in 0..img.height() {
        for x in 0..img.width() {
            let value = match img.get_pixel(x, y) {
                Luma([luma]) => {
                    *luma < 128
                },
                other_pixel => {
                    panic!("unsupported pixel {:?}", other_pixel)
                },
            };
            for off_y in 0..SCALE_Y {
                for off_x in 0..SCALE_X {
                    image[y as usize * SCALE_Y + off_y][x as usize * SCALE_X + off_x] = !value;
                }
            }
        }
    }

    let mut asm = String::new();

    let mut matched = image.clone();
    for (row, line) in image.iter().enumerate() {
        let mut cycles = 0;

        writeln!(asm, "ld hl, #0x{:04X} // cycle {}", 0xF000 + (row / 10) * 128, cycles);
        cycles += 10;

        for (group_i, group) in line.chunks(8).enumerate() {
            let mut byte = 0;
            for (col, value) in group.iter().enumerate() {
                if *value {
                    byte |= (0x80 >> col);
                }
            }

            let pattern_offset = (row % 10) * 256;
            if patterns[pattern_offset + byte].is_empty() {
                let mut closest_opt = None;
                for other_byte in 0..256 {
                    if !patterns[pattern_offset + other_byte].is_empty() {
                        //TODO: difference should be smarter than just comparing bits
                        let mut diff = 0;
                        for col in 0..8 {
                            if ((byte >> col) & 1) != ((other_byte >> col) & 1) {
                                diff += 1;
                            }
                        }

                        /*
                        // Do not allow empty parts
                        if byte > 0 && other_byte == 0 {
                            diff = 256;
                        }
                        */

                        closest_opt = Some(match closest_opt.take() {
                            Some((prev_byte, prev_diff)) => if diff < prev_diff {
                                (other_byte, diff)
                            } else {
                                (prev_byte, prev_diff)
                            },
                            None => (other_byte, diff)
                        });
                    }
                }
                byte = closest_opt.unwrap().0;
            }

            // This prefers characters like ' ' with lots of blank lines on unused lines
            // This helps with adjusting timing.
            let mut blankest_opt = None;
            for c in patterns[pattern_offset + byte].iter() {
                let mut blank_rows = 0;
                for row in 0..10 {
                    let row_byte = char_rom[row * 128 + *c as usize];
                    if row_byte == 0 {
                        blank_rows += 1;
                    }
                }

                blankest_opt = Some(match blankest_opt.take() {
                    Some((prev_c, prev_blank_rows)) => if blank_rows > prev_blank_rows {
                        (c, blank_rows)
                    } else {
                        (prev_c, prev_blank_rows)
                    },
                    None => (c, blank_rows)
                });
            }

            let c = blankest_opt.unwrap().0;
            println!("{}, {}: 0x{:02X} = {:?}", row, group_i, byte, c);

            writeln!(asm, "ld (hl), #0x{:02X} // cycle {}", *c as u8, cycles);
            cycles += 10;
            writeln!(asm, "inc l // cycle {}", cycles);
            cycles += 4;

            for col in 0..8 {
                matched[row][group_i * 8 + col] = byte & (0x80 >> col) != 0;
            }
        }

        while cycles <= 256 - 4 {
            writeln!(asm, "nop // cycles {}", cycles);
            cycles += 4;
        }

        assert_eq!(cycles, 256);
        writeln!(asm, "// total cycles {}", cycles);
    }

    fs::write("program.asm", asm).unwrap();

    use std::num::NonZeroU32;
    use winit::event::{Event, WindowEvent};
    use winit::event_loop::{ControlFlow, EventLoop};
    use winit::window::WindowBuilder;
    let event_loop = EventLoop::new();
    let window = WindowBuilder::new().build(&event_loop).unwrap();
    let context = unsafe { softbuffer::Context::new(&window) }.unwrap();
    let mut surface = unsafe { softbuffer::Surface::new(&context, &window) }.unwrap();
    event_loop.run(move |event, _, control_flow| {
        *control_flow = ControlFlow::Wait;

        match event {
            Event::RedrawRequested(window_id) if window_id == window.id() => {
                let (width, height) = {
                    let size = window.inner_size();
                    (size.width, size.height)
                };

                surface
                    .resize(
                        NonZeroU32::new(width).unwrap(),
                        NonZeroU32::new(height).unwrap(),
                    )
                    .unwrap();

                let mut buffer = surface.buffer_mut().unwrap();
                for y in 0..height {
                    for x in 0..width {
                        let mut value = 0;

                        let max_x = 52 * 8;
                        let max_y = 24 * 10;
                        if x < max_x && y < max_y {
                            value = 0x202020;
                        }

                        if y < (HEIGHT * SCALE_Y) as u32 && x < (WIDTH * SCALE_X) as u32 {
                            if matched[y as usize][x as usize] {
                                value = 0x00FF00
                            }
                        }

                        let index = y as usize * width as usize + x as usize;
                        buffer[index] = value;
                    }
                }

                buffer.present().unwrap();
            }
            Event::WindowEvent {
                event: WindowEvent::CloseRequested,
                window_id,
            } if window_id == window.id() => {
                *control_flow = ControlFlow::Exit;
            }
            _ => {}
        }
    });
}
