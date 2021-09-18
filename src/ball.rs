use crate::Acceleration;
use crate::Position;
use crate::Side;
use crate::Velocity;

const FRICTION: f32 = 0.5;
const PUSH_FACTOR: f32 = 1.0;
const MAX_SPEED: f32 = 10.0;

#[derive(Clone, Copy, Debug, PartialEq)]
pub struct Ball {
    pub id: usize,
    position: Position,
    velocity: Velocity,
    acceleration: Acceleration,
}

impl Ball {
    pub fn new(id: usize, x: f32, y: f32) -> Self {
        Self {
            id,
            position: Position { x, y },
            velocity: Velocity { x: 0.0, y: 0.0 },
            acceleration: Acceleration { x: 0.0, y: 0.0 },
        }
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
