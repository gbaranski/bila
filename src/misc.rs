use glam::Vec2;

pub type Position = Vec2;
pub type Velocity = Vec2;
pub type Acceleration = Vec2;

#[derive(Clone, Copy, Debug, PartialEq)]
pub enum Side {
    Left,
    Right,
    Up,
    Down,
}
