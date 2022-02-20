use crate::Acceleration;
use crate::Position;
use crate::Velocity;
use macroquad::color::Color;
use macroquad::prelude::Vec2;

pub const RADIUS: f32 = 32.0;
pub const MAX_SPEED: f32 = 15.0;

pub const TEXT_FONT_SIZE: u16 = 64;
pub const TEXT_FONT_SCALE: f32 = 1.0;

pub type Index = usize;

#[derive(Clone, Copy, Debug, PartialEq)]
pub struct Ball {
    index: Index,
    color: Color,
    text_color: Color,
    radius: f32,
    position: Position,
    velocity: Velocity,
    acceleration: Acceleration,
}

impl Ball {
    pub fn new(index: Index, position: Position) -> Self {
        let (color, text_color) = Self::default_colors(index);
        Self {
            index,
            color,
            text_color,
            radius: RADIUS,
            position,
            velocity: Velocity::new(0.0, 0.0),
            acceleration: Acceleration::new(0.0, 0.0),
        }
    }

    fn default_colors(index: Index) -> (Color, Color) {
        if index == 0 {
            (colors::ball::PRIMARY, colors::text::PRIMARY)
        } else {
            (colors::ball::SECONDARY, colors::text::SECONDARY)
        }
    }

    #[inline]
    pub fn index(&self) -> &Index {
        &self.index
    }

    #[inline]
    pub fn color(&self) -> &Color {
        &self.color
    }

    #[inline]
    pub fn text_color(&self) -> &Color {
        &self.text_color
    }

    #[inline]
    pub fn position(&self) -> &Position {
        &self.position
    }

    #[inline]
    pub fn velocity(&self) -> &Velocity {
        &self.velocity
    }

    #[inline]
    pub fn acceleration(&self) -> &Acceleration {
        &self.acceleration
    }

    pub fn does_collide(&self, other: &Self) -> bool {
        let distance = (self.position.x - other.position.x).powi(2)
            + (self.position.y - other.position.y).powi(2);

        distance < (self.radius + other.radius).powi(2)
    }

    pub fn highlight(&mut self) {
        self.color = colors::ball::HIGHLIGHT;
        self.text_color = colors::text::HIGHLIGHT;
    }

    pub fn set_default_colors(&mut self) {
        let (color, text_color) = Self::default_colors(self.index);
        self.color = color;
        self.text_color = text_color;
    }

    pub fn handle_collision(&mut self, other: &Self) {
        let position_delta = other.position - self.position;
        let distance = position_delta.length();
        let norm = distance.powi(2);
        let velocity_delta = other.velocity - self.velocity;

        self.velocity += ((velocity_delta).dot(position_delta) / norm) * position_delta;
        self.position -= position_delta / distance * (self.radius + other.radius - distance) * 0.5;
    }

    fn round_numbers(&mut self) {

        // Limit the velocity
        // rounding friction to N decimal places
        let digits = 4;
        let ten_to_n = 10_f32.powi(digits);
        self.velocity.x = (self.velocity.x * ten_to_n).round() / ten_to_n;
        self.velocity.y = (self.velocity.y * ten_to_n).round() / ten_to_n;
        if self.velocity.x.abs() <= 16.0 / (ten_to_n) {
            self.velocity.x = 0f32;
        }
        if self.velocity.y.abs() <= 16.0 / (ten_to_n) {
            self.velocity.y = 0f32;
        }
        self.position.x = (self.position.x * ten_to_n).round() / ten_to_n;
        self.position.y = (self.position.y * ten_to_n).round() / ten_to_n;
    }

    pub fn update(&mut self, wall: Position) {
        // Apply friction
        {
            let drag: f32 = 0.97;
            self.velocity *= drag;
        }

        // Update position
        {
            self.position.x =
                (self.position.x + self.velocity.x).clamp(self.radius, wall.x - self.radius);
            self.position.y =
                (self.position.y + self.velocity.y).clamp(self.radius, wall.y - self.radius);
        }
        self.round_numbers();
    }

    pub fn push(&mut self, v: Vec2) {
        self.velocity = v;
    }
}

mod colors {
    use macroquad::color::Color;
    use macroquad::color::BLUE;
    use macroquad::color::RED;
    use macroquad::color::YELLOW;

    pub mod ball {
        use super::*;

        pub const PRIMARY: Color = RED;
        pub const SECONDARY: Color = BLUE;
        pub const HIGHLIGHT: Color = YELLOW;
    }

    pub mod text {
        use super::*;

        pub const PRIMARY: Color = BLUE;
        pub const SECONDARY: Color = RED;
        pub const HIGHLIGHT: Color = BLUE;
    }
}
