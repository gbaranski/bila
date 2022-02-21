mod ball;
mod fonts;
mod misc;
mod world;

use ball::Ball;
use misc::Acceleration;
use misc::Position;
use misc::Velocity;
use world::World;

fn window_configuration() -> macroquad::window::Conf {
    macroquad::window::Conf {
        window_title: "Bila".to_string(),
        window_width: 1280,
        window_height: 720,
        ..Default::default()
    }
}

#[macroquad::main(window_configuration)]
async fn main() {
    let font = macroquad::text::load_ttf_font_from_bytes(fonts::SOURCE_CODE_PRO_LIGHT)
        .expect("couldn't load font");

    let mut world = World::new(font);

    for i in 0.. {
        macroquad_profiler::profiler(Default::default());
        world.update(i).await;
    }
}
