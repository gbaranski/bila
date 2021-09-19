use crate::Acceleration;
use crate::Position;
use crate::Side;
use crate::Velocity;
use macroquad::color::Color;

pub const RADIUS: f32 = 32.0;
pub const FRICTION: f32 = 0.5;
pub const PUSH_FACTOR: f32 = 1.0;
pub const MAX_SPEED: f32 = 10.0;

pub const TEXT_FONT_SIZE: u16 = 64;
pub const TEXT_FONT_SCALE: f32 = 1.0;

pub type Index = usize;

#[derive(Clone, Copy, Debug, PartialEq)]
pub struct Ball {
    index: Index,
    color: Color,
    text_color: Color,
    position: Position,
    velocity: Velocity,
    acceleration: Acceleration,
}

impl Ball {
    pub fn new(index: Index, x: f32, y: f32) -> Self {
        let (color, text_color) = Self::default_colors(index);
        Self {
            index,
            color,
            text_color,
            position: Position::new(x, y),
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

        distance < (RADIUS + RADIUS).powi(2)
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

    pub fn handle_collision(&mut self, (other_position, other_velocity): (Position, Velocity)) {
        let position_delta = other_position - self.position;
        let distance = position_delta.length();
        let norm = distance.powi(2);
        let velocity_delta = other_velocity - self.velocity;

        self.velocity += ((velocity_delta).dot(position_delta) / norm) * position_delta;
        self.position -= position_delta / distance * (RADIUS * 2.0 - distance) * 0.5;
    }

    pub fn reset_acceleration(&mut self) {
        self.acceleration.x = 0.0;
        self.acceleration.y = 0.0;
    }

    pub fn update(&mut self) {
        // Apply acceleration
        {
            self.velocity.x += self.acceleration.x;
            self.velocity.y += self.acceleration.y;
        }

        // Apply friction
        {
            if self.velocity.x > 0.0 {
                self.velocity.x += -FRICTION;
            } else if self.velocity.x < 0.0 {
                self.velocity.x += FRICTION;
            }

            if self.velocity.y > 0.0 {
                self.velocity.y += -FRICTION;
            } else if self.velocity.y < 0.0 {
                self.velocity.y += FRICTION;
            }
        }

        // Limit the velocity
        {
            self.velocity.x = self.velocity.x.clamp(-MAX_SPEED, MAX_SPEED);
            self.velocity.y = self.velocity.y.clamp(-MAX_SPEED, MAX_SPEED);
        }

        // Update position
        {
            self.position.x += self.velocity.x;
            self.position.y += self.velocity.y;
        }
    }

    pub fn push(&mut self, side: Side) {
        match side {
            Side::Left => self.acceleration.x -= PUSH_FACTOR,
            Side::Right => self.acceleration.x += PUSH_FACTOR,
            Side::Up => self.acceleration.y -= PUSH_FACTOR,
            Side::Down => self.acceleration.y += PUSH_FACTOR,
        };
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
