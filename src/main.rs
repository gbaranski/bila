mod ball;
mod fonts;
mod misc;
mod world;

use ball::Ball;
use misc::Acceleration;
use misc::Position;
use misc::Side;
use misc::Velocity;
use world::World;

#[macroquad::main("bila")]
async fn main() {
    let font = {
        let font = macroquad::text::load_ttf_font_from_bytes(fonts::SOURCE_CODE_PRO_LIGHT)
            .expect("couldn't load font");
        font
    };

    let mut world = World::new(font);

    for i in 0.. {
        world.update(i).await;
    }
}
