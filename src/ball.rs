use crate::Position;
use crate::Velocity;

#[derive(Clone, Copy, Debug, PartialEq)]
pub struct Ball {
    pub position: Position,
    pub velocity: Velocity,
}
