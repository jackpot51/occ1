use cosmic::{
    app::{Core, Task},
    executor,
    iced::{ContentFit, Length},
    widget, Element,
};

#[derive(Clone, Debug)]
pub enum Message {}

pub struct App {
    core: Core,
    image: widget::image::Handle,
}

impl cosmic::Application for App {
    type Executor = executor::Default;
    type Flags = widget::image::Handle;
    type Message = Message;
    const APP_ID: &'static str = "dev.soller.OCC1Viewer";

    fn core(&self) -> &Core {
        &self.core
    }

    fn core_mut(&mut self) -> &mut Core {
        &mut self.core
    }

    fn init(core: Core, image: Self::Flags) -> (Self, Task<Self::Message>) {
        (App { core, image }, Task::none())
    }

    fn update(&mut self, _message: Self::Message) -> Task<Self::Message> {
        Task::none()
    }

    fn view(&self) -> Element<Self::Message> {
        widget::image::viewer(self.image.clone())
            .content_fit(ContentFit::None)
            .filter_method(widget::image::FilterMethod::Nearest)
            .min_scale(1.0)
            .scale_step(1.0)
            .width(Length::Fill)
            .height(Length::Fill)
            .into()
    }
}
