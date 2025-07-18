use std::{env, error::Error, fs, io::Write, thread, time};

pub struct Command {
    pub command_bits: u8,
    pub value_mask: u8,
}

impl Command {
    pub const fn new(command_bits: u8, value_mask: u8) -> Self {
        //TODO: assert_eq!(command_bits & value_mask, 0);
        Self { command_bits, value_mask }
    }

    pub fn compile(&self, value: u8) -> Option<u8> {
        assert_eq!(self.command_bits & self.value_mask, 0);
        if value & self.value_mask == value {
            Some(self.command_bits | value)
        } else {
            None
        }
    }
}

// 0b000xxxxx: 32 values for repeat
static REPEAT: Command = Command::new(0x00, 0x1F);
// 0b0xxxxxxx: 128 values for ASCII characters (ignore lower 32 for repeat)
static CHAR: Command = Command::new(0x00, 0x7F);
// 0b100xxxxx: 32 values for delay
static DELAY: Command = Command::new(0x80, 0x1F);
// 0b101xxxxx: 32 values for Y
static SETY: Command = Command::new(0xA0, 0x1F);
// 0b11xxxxxx: 64 values for X
static SETX: Command = Command::new(0xC0, 0x3F);

fn main() -> Result<(), Box<dyn Error>> {
    let input_path = env::args()
        .nth(1)
        .ok_or_else(|| format!("no argument provided"))?;
    let input = fs::read_to_string(&input_path)?;

    let mut output_opt = match env::args().nth(2) {
        Some(output_path) => Some(
            fs::OpenOptions::new()
                .create(true)
                .truncate(true)
                .write(true)
                .open(output_path)?,
        ),
        None => None,
    };

    // Centered on osborne screen
    let xoff = -7isize;
    let fb_w = 52;
    let fb_h = 24;
    let mut fb_x = 0;
    let mut fb_y = 0;
    let mut fb_c = b' ';
    let mut fb = vec![fb_c; fb_w * fb_h];
    let mut data = Vec::new();
    let mut frames = 0;
    let mut display = move |frame: &str, mut count: u8, flush: bool| -> Result<(), Box<dyn Error>> {
        if frame.is_empty() {
            return Ok(());
        }

        if let Some(ref mut output) = output_opt {
            let change_based = true;
            if change_based {
                // Simple change-based algorithm
                let mut new = vec![b' '; fb_w * fb_h];
                let mut x = xoff;
                let mut y = 0;
                for &byte in frame.as_bytes() {
                    if byte == b'\n' {
                        x = xoff;
                        y += 1;
                    } else {
                        if x >= 0 && x < fb_w as isize && y < fb_h {
                            let i = y * fb_w + x as usize;
                            new[i] = byte;
                        }
                        x += 1;
                    }
                }

                for y in 0..fb_h {
                    for x in 0..fb_w {
                        let i = y * fb_w + x as usize;
                        let byte = new[i];
                        if fb[i] != byte {
                            if fb_y != y {
                                data.push(SETY.compile(y as u8).unwrap());
                                fb_y = y;
                                fb_x = 0;
                            }
                            if fb_x != x {
                                data.push(SETX.compile(x as u8).unwrap());
                                fb_x = x;
                            }
                            // Lower 32 values for repeating
                            assert!(byte >= 0x20);
                            if byte == fb_c {
                                if let Some(count) = data.pop_if(|x| *x < 0x1F) {
                                    data.push(REPEAT.compile(count + 1).unwrap());
                                } else {
                                    data.push(REPEAT.compile(1).unwrap());
                                }
                            } else {
                                data.push(CHAR.compile(byte).unwrap());
                            }
                            fb[i] = byte;
                            fb_c = byte;
                            fb_x += 1;
                        }
                    }
                }

                while count >= 0x1F {
                    data.push(DELAY.compile(0x1F).unwrap());
                    count -= 0x1F;
                }
                data.push(DELAY.compile(count).unwrap());
                fb_x = 0;
                fb_y = 0;

                if flush {
                    //TODO: fit whole file on single floppy
                    println!("original size {}", data.len());
                    data.truncate(176 * 1024);
                    println!("truncated to {}", data.len());
                    output.write(&data)?;
                    data.clear();
                }
            } else {
                // Algorithm for zx compression of full frame data
                data.push(0u8);
                data.push(count);
                data.extend_from_slice(frame.as_bytes());
                frames += 1;
                if frames >= 30 || data.len() >= 24 * 1024 || flush {
                    // ZX0 compression
                    let compressed = zx0::compress(&data);

                    println!("{} frames {} => {}", frames, data.len(), compressed.len());
                    
                    let len = u16::try_from(compressed.len()).expect("compressed length out of bounds");
                    output.write(&len.to_le_bytes())?;
                    output.write(&compressed)?;

                    data.clear();
                    frames = 0;
                }
            }
        } else {
            for _ in 0..count {
                print!("\x1Bc{}", frame);
                thread::sleep(time::Duration::from_secs_f64(1.0 / 15.0));
            }
        }

        Ok(())
    };

    let mut count = 1;
    let mut frame = String::new();
    for line in input.split('\n') {
        if let Ok(new_count) = line.parse::<u8>() {
            display(&frame, count, false)?;
            frame.clear();
            count = new_count;
        } else {
            frame.push_str(line);
            frame.push('\n');
        }
    }
    display(&frame, count, true)?;

    Ok(())
}
