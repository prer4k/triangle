use glam::{Mat4, Vec3};
use glfw::{Action, Key, Window};

pub struct Camera {
    pub position: Vec3,
    pub fov: f32,
    pub near_plane: f32,
    pub far_plane: f32,
    pub yaw: f32,
    pub pitch: f32,
    aspect: f32,
}

impl Camera {
    pub fn new(aspect: f32) -> Self {
        Self {
            position: Vec3::new(0.0, 0.0, 5.0),
            fov: 45.0_f32.to_radians(),
            near_plane: 0.1,
            far_plane: 100.0,
            yaw: -90.0,
            pitch: 0.0,
            aspect,
        }
    }

    pub fn set_aspect(&mut self, aspect: f32) {
        self.aspect = aspect;
    }

    pub fn front(&self) -> Vec3 {
        let yaw = self.yaw.to_radians();
        let pitch = self.pitch.to_radians();
        Vec3::new(
            yaw.cos() * pitch.cos(),
            pitch.sin(),
            yaw.sin() * pitch.cos(),
        )
        .normalize()
    }

    pub fn view_matrix(&self) -> Mat4 {
        let dir = self.front();
        Mat4::look_at_rh(self.position, self.position + dir, Vec3::Y)
    }

    pub fn projection_matrix(&self) -> Mat4 {
        Mat4::perspective_rh_gl(self.fov, self.aspect, self.near_plane, self.far_plane)
    }
}

/// First-person fly camera (WASD, QE, mouse look).
pub struct FlyCamera {
    move_speed: f32,
    sensitivity: f32,
    enabled: bool,
    first_mouse: bool,
    last_x: f64,
    last_y: f64,
}

impl Default for FlyCamera {
    fn default() -> Self {
        Self {
            move_speed: 2.5,
            sensitivity: 0.1,
            enabled: false,
            first_mouse: true,
            last_x: 0.0,
            last_y: 0.0,
        }
    }
}

impl FlyCamera {
    pub fn set_enabled(&mut self, enabled: bool) {
        self.enabled = enabled;
    }

    pub fn reset_mouse(&mut self) {
        self.first_mouse = true;
    }

    pub fn update(&mut self, camera: &mut Camera, window: &Window, dt: f32) {
        if !self.enabled {
            return;
        }

        let fast = window.get_key(Key::LeftShift) == Action::Press
            || window.get_key(Key::RightShift) == Action::Press;
        let speed = self.move_speed * if fast { 3.0 } else { 1.0 };

        let front = camera.front();
        let right = front.cross(Vec3::Y).normalize();

        if window.get_key(Key::W) == Action::Press {
            camera.position += front * speed * dt;
        }
        if window.get_key(Key::S) == Action::Press {
            camera.position -= front * speed * dt;
        }
        if window.get_key(Key::A) == Action::Press {
            camera.position -= right * speed * dt;
        }
        if window.get_key(Key::D) == Action::Press {
            camera.position += right * speed * dt;
        }
        if window.get_key(Key::E) == Action::Press {
            camera.position += Vec3::Y * speed * dt;
        }
        if window.get_key(Key::Q) == Action::Press {
            camera.position -= Vec3::Y * speed * dt;
        }

        let (x, y) = window.get_cursor_pos();
        if self.first_mouse {
            self.last_x = x;
            self.last_y = y;
            self.first_mouse = false;
        }

        let dx = x - self.last_x;
        let dy = self.last_y - y;
        self.last_x = x;
        self.last_y = y;

        camera.yaw += dx as f32 * self.sensitivity;
        camera.pitch += dy as f32 * self.sensitivity;
        camera.pitch = camera.pitch.clamp(-89.0, 89.0);
    }
}
