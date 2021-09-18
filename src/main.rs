mod ball;
mod fonts;
mod misc;

use ball::Ball;
use misc::Acceleration;
use misc::Position;
use misc::Side;
use misc::Velocity;

use macroquad::prelude::*;

const BALLS_COUNT: usize = 8;
const BALL_SIZE: f32 = 32.0;
const BALL_TEXT_FONT_SIZE: u16 = 64;
const BALL_TEXT_FONT_SCALE: f32 = 1.0;
const PRIMARY_BALL_COLOR: Color = RED;
const PRIMARY_TEXT_COLOR: Color = BLUE;
const SECONDARY_BALL_COLOR: Color = BLUE;
const SECONDARY_TEXT_COLOR: Color = RED;

#[macroquad::main("bila")]
async fn main() {
    let font = {
        let font =
            load_ttf_font_from_bytes(fonts::SOURCE_CODE_PRO_LIGHT).expect("couldn't load font");
        font
    };

    let mut balls = (0..BALLS_COUNT)
        .map(|n| {
            Ball::new(
                screen_width() * (n as f32 / BALLS_COUNT as f32) as f32,
                screen_height() / 2.0,
            )
        })
        .collect::<Vec<_>>();

    loop {
        clear_background(BLACK);

        for (i, ball) in balls.iter().enumerate() {
            let (ball_color, text_color) = if i == 0 {
                (PRIMARY_BALL_COLOR, PRIMARY_TEXT_COLOR)
            } else {
                (SECONDARY_BALL_COLOR, SECONDARY_TEXT_COLOR)
            };

            let text = i.to_string();
            let size = measure_text(&text, Some(font), BALL_TEXT_FONT_SIZE, BALL_TEXT_FONT_SCALE);
            let position = ball.position();
            draw_circle(position.x, position.y, BALL_SIZE, ball_color);
            draw_text_ex(
                &text,
                position.x - (size.width / 2.0),
                position.y + (size.height / 2.0),
                TextParams {
                    font,
                    font_size: BALL_TEXT_FONT_SIZE,
                    font_scale: BALL_TEXT_FONT_SCALE,
                    font_scale_aspect: 1.0,
                    color: text_color,
                },
            );
        }

        if is_key_pressed(KeyCode::Escape) {
            return;
        }

        const KEYMAP: &[(&[KeyCode], Side)] = &[
            (&[KeyCode::Left, KeyCode::A], Side::Left),
            (&[KeyCode::Right, KeyCode::D], Side::Right),
            (&[KeyCode::Up, KeyCode::W], Side::Up),
            (&[KeyCode::Down, KeyCode::S], Side::Down),
        ];

        let primary_ball = &mut balls[0];
        for (keys, side) in KEYMAP {
            if keys.into_iter().any(|key| is_key_down(key.to_owned())) {
                primary_ball.push(side.to_owned());
            }
        }

        primary_ball.update();

        next_frame().await;
    }
}
