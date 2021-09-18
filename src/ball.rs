use crate::Acceleration;
use crate::Position;
use crate::Side;
use crate::Velocity;

const FRICTION: f32 = 0.1;
const MASS: f32 = 10.0;
const PUSH_FACTOR: f32 = 90.0;
const MAX_VELOCITY: f32 = 10.0;

#[derive(Clone, Copy, Debug, PartialEq)]
pub struct Ball {
    position: Position,
    velocity: Velocity,
    acceleration: Acceleration,
}

impl Ball {
    pub fn new(x: f32, y: f32) -> Self {
        Self {
            position: Position { x, y },
            velocity: Velocity { x: 0.0, y: 0.0 },
            acceleration: Acceleration { x: 0.0, y: 0.0 },
        }
    }

    #[inline]
    pub fn position(&self) -> &Position {
        &self.position
    }

    pub fn update(&mut self) {
        // Apply acceleration
        self.velocity.x += self.acceleration.x;
        self.velocity.y += self.acceleration.y;

        // Apply friction
        if self.velocity.x > 0.0 {
            self.velocity.x = (self.velocity.x - FRICTION).max(0.0)
        } else if self.velocity.x < 0.0 {
            self.velocity.x = (self.velocity.x + FRICTION).max(0.0)
        }

        if self.velocity.y > 0.0 {
            self.velocity.y = (self.velocity.y - FRICTION).max(0.0)
        } else if self.velocity.y < 0.0 {
            self.velocity.y = (self.velocity.y + FRICTION).max(0.0)
        }

        // Slow down if velocity exceeds MAX_VELOCITY
        if self.velocity.x > MAX_VELOCITY {
            self.velocity.x = MAX_VELOCITY;
        } else if self.velocity.x < -MAX_VELOCITY {
            self.velocity.x = -MAX_VELOCITY;
        }

        if self.velocity.y > MAX_VELOCITY {
            self.velocity.y = MAX_VELOCITY;
        } else if self.velocity.y < -MAX_VELOCITY {
            self.velocity.y = -MAX_VELOCITY;
        }

        // Update position
        self.position.x += self.velocity.x;
        self.position.y += self.velocity.y;
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
