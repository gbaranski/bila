use crate::ball;
use crate::Ball;
use crate::Position;
use crate::Side;

use macroquad::prelude::*;
use std::convert::TryInto;

const BALL_COUNT: usize = 8;

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
                let position = if n == 0 {
                    Position::new(screen_width() / 2.0, screen_height() / 4.0)
                } else {
                    Position::new(
                        screen_width() * (n as f32 / BALL_COUNT as f32) as f32,
                        screen_height() / 2.0,
                    )
                };
                Ball::new(n, position)
            })
            .collect::<Vec<_>>();

        Self {
            font,
            balls: balls.try_into().unwrap(),
        }
    }

    // TODO: Consider moving that to ball.rs
    fn draw_ball(&self, ball: &Ball) {
        let text = (ball.index() + 1).to_string();
        let size = measure_text(
            &text,
            Some(self.font),
            ball::TEXT_FONT_SIZE,
            ball::TEXT_FONT_SCALE,
        );
        let position = ball.position();
        draw_circle(position.x, position.y, ball::RADIUS, *ball.color());
        draw_text_ex(
            &text,
            position.x - (size.width / 2.0),
            position.y + (size.height / 2.0),
            TextParams {
                font: self.font,
                font_size: ball::TEXT_FONT_SIZE,
                font_scale: ball::TEXT_FONT_SCALE,
                font_scale_aspect: 1.0,
                color: *ball.text_color(),
            },
        );
    }

    fn draw_arrow(&self, cursor: Vec2) {
        let primary_ball = self.primary_ball();
        draw_line(
            primary_ball.position().x,
            primary_ball.position().y,
            cursor.x,
            cursor.y,
            5.0,
            Color::new(255.0, 0.0, 0.0, 0.8),
        );
    }

    #[inline]
    fn primary_ball(&self) -> &Ball {
        &self.balls[0]
    }

    #[inline]
    fn primary_ball_mut(&mut self) -> &mut Ball {
        &mut self.balls[0]
    }

    fn draw_stats(&self, tick: usize) {
        let mut current_y = 0.0;
        let mut draw_line = |s: &str| {
            let size = measure_text(&s, Some(self.font), STATS_FONT_SIZE, STATS_FONT_SCALE);
            draw_text_ex(
                &s,
                screen_width() - size.width,
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
        let collisions = self.ball_collisions(&primary_ball);
        let position = primary_ball.position();
        let acceleration = primary_ball.acceleration();
        let velocity = primary_ball.velocity();
        draw_line(&format!("tick: {}", tick));
        draw_line(&format!("fps: {}", get_fps()));
        draw_line(&format!("pos: ({}, {})", position.x, position.y));
        draw_line(&format!("acc: ({} {})", acceleration.x, acceleration.y));
        draw_line(&format!("vel: ({} {})", velocity.x, velocity.y));
        draw_line(&format!(
            "collisions: {}",
            collisions
                .iter()
                .map(|v| (v + 1).to_string())
                .collect::<Vec<_>>()
                .join(", ")
        ));
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

        let sides = BALL_KEYMAP
            .iter()
            .filter(|(keys, _)| keys.into_iter().any(|key| is_key_down(key.to_owned())))
            .map(|(_, side)| side);

        self.primary_ball_mut().reset_acceleration();
        for side in sides {
            self.primary_ball_mut().push(side.to_owned());
        }
    }

    /// Returns all collisions for the ball
    fn ball_collisions(&self, ball: &Ball) -> Vec<ball::Index> {
        self.balls
            .iter()
            .filter(|other| other.index() != ball.index())
            .filter(|other| ball.does_collide(other))
            .map(|other| other.index().clone())
            .collect()
    }

    /// Returns all collifions from all balls
    fn all_collisions(&self) -> Vec<(ball::Index, Vec<ball::Index>)> {
        self.balls
            .iter()
            .map(|ball| (ball.index().clone(), self.ball_collisions(ball)))
            .collect::<Vec<_>>()
    }

    pub async fn update(&mut self, tick: usize) {
        // let aspect_ratio = macroquad::window::screen_width() / macroquad::window::screen_height();
        // let camera = Camera2D::from_display_rect(Rect {
        //     x: -aspect_ratio,
        //     y: -1.0,
        //     w: aspect_ratio * 2.0,
        //     h: 2.0,
        // });
        // set_camera(&camera);
        // let mouse_position = camera.screen_to_world(macroquad::input::mouse_position().into());
        let mouse_position = macroquad::input::mouse_position().into();
        for ball in &mut self.balls {
            ball.set_default_colors();
        }

        for (a, collisions) in self.all_collisions() {
            for b in collisions {
                let mut f = |a, b| {
                    let other = self.balls[a];
                    let ball: &mut Ball = &mut self.balls[b];
                    ball.handle_collision(&other);
                    ball.highlight();
                };
                f(a, b);
                f(b, a);
            }
        }

        for ball in &self.balls {
            self.draw_ball(ball);
        }

        self.handle_keys();
        self.primary_ball_mut()
            .update(Position::new(screen_width(), screen_height()));
        self.draw_arrow(mouse_position);
        self.draw_stats(tick);

        next_frame().await;
    }
}
