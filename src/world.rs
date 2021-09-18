use crate::Ball;

use crate::Side;
use macroquad::prelude::*;
use std::convert::TryInto;

const BALL_COUNT: usize = 8;
const BALL_SIZE: f32 = 32.0;
const BALL_TEXT_FONT_SIZE: u16 = 64;
const BALL_TEXT_FONT_SCALE: f32 = 1.0;
const PRIMARY_BALL_COLOR: Color = RED;
const PRIMARY_TEXT_COLOR: Color = BLUE;
const SECONDARY_BALL_COLOR: Color = BLUE;
const SECONDARY_TEXT_COLOR: Color = RED;

const STATS_LINE_SPACING: f32 = 10.0;
const STATS_FONT_SIZE: u16 = 24;
const STATS_FONT_COLOR: Color = WHITE;
const STATS_FONT_SCALE: f32 = 1.0;

pub struct World {
    font: Font,
    balls: [Ball; BALL_COUNT],
}

impl World {
    pub fn new(font: Font) -> Self {
        let balls = (0..BALL_COUNT)
            .map(|n| {
                Ball::new(
                    n,
                    screen_width() * (n as f32 / BALL_COUNT as f32) as f32,
                    screen_height() / 2.0,
                )
            })
            .collect::<Vec<_>>();

        Self {
            font,
            balls: balls.try_into().unwrap(),
        }
    }

    // TODO: Consider moving that to ball.rs
    fn draw_ball(&self, ball: &Ball) {
        let (ball_color, text_color) = if ball.id == 0 {
            (PRIMARY_BALL_COLOR, PRIMARY_TEXT_COLOR)
        } else {
            (SECONDARY_BALL_COLOR, SECONDARY_TEXT_COLOR)
        };

        let text = ball.id.to_string();
        let size = measure_text(
            &text,
            Some(self.font),
            BALL_TEXT_FONT_SIZE,
            BALL_TEXT_FONT_SCALE,
        );
        let position = ball.position();
        draw_circle(position.x, position.y, BALL_SIZE, ball_color);
        draw_text_ex(
            &text,
            position.x - (size.width / 2.0),
            position.y + (size.height / 2.0),
            TextParams {
                font: self.font,
                font_size: BALL_TEXT_FONT_SIZE,
                font_scale: BALL_TEXT_FONT_SCALE,
                font_scale_aspect: 1.0,
                color: text_color,
            },
        );
    }

    fn primary_ball(&self) -> &Ball {
        &self.balls[0]
    }

    fn primary_ball_mut(&mut self) -> &mut Ball {
        &mut self.balls[0]
    }

    fn draw_stats(&self, tick: usize) {
        let mut current_y = 0.0;
        let mut draw_line = |s: &str| {
            let size = measure_text(&s, Some(self.font), STATS_FONT_SIZE, STATS_FONT_SCALE);
            draw_text_ex(
                &s,
                0.0,
                current_y + size.height,
                TextParams {
                    font: self.font,
                    font_size: STATS_FONT_SIZE,
                    font_scale: STATS_FONT_SCALE,
                    font_scale_aspect: 1.0,
                    color: STATS_FONT_COLOR,
                },
            );
            current_y += size.height + STATS_LINE_SPACING;
        };
        let primary_ball = self.primary_ball();
        let position = primary_ball.position();
        let acceleration = primary_ball.acceleration();
        let velocity = primary_ball.velocity();
        draw_line(&format!("tick: {}", tick));
        draw_line(&format!("pos: ({}, {})", position.x, position.y));
        draw_line(&format!("acc: ({} {})", acceleration.x, acceleration.y));
        draw_line(&format!("vel: ({} {})", velocity.x, velocity.y));
    }

    fn handle_keys(&mut self) {
        if is_key_pressed(KeyCode::Escape) {
            std::process::exit(0);
        }

        const BALL_KEYMAP: &[(&[KeyCode], Side)] = &[
            (&[KeyCode::Left, KeyCode::A], Side::Left),
            (&[KeyCode::Right, KeyCode::D], Side::Right),
            (&[KeyCode::Up, KeyCode::W], Side::Up),
            (&[KeyCode::Down, KeyCode::S], Side::Down),
        ];

        for (keys, side) in BALL_KEYMAP {
            if keys.into_iter().any(|key| is_key_down(key.to_owned())) {
                self.primary_ball_mut().push(side.to_owned());
            }
        }
    }

    pub async fn update(&mut self, tick: usize) {
        clear_background(BLACK);

        for ball in self.balls.iter() {
            self.draw_ball(ball);
        }

        self.handle_keys();
        self.primary_ball_mut().update();
        self.draw_stats(tick);

        next_frame().await;
    }
}
