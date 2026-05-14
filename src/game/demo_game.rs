use glam::Vec3;
use rand::Rng;
use std::rc::Rc;

use crate::engine::{Engine, Game};
use crate::geometry;
use crate::material::Material;

pub struct DemoGame;

fn random_position(rng: &mut impl Rng) -> Vec3 {
    Vec3::new(
        rng.gen_range(-5..=4) as f32,
        rng.gen_range(-5..=4) as f32,
        rng.gen_range(-5..=4) as f32,
    )
}

impl Game for DemoGame {
    fn init(&mut self, engine: &mut Engine) {
        let (cube_mesh, sphere_mesh, cube_mat, sphere_mat) = {
            let assets = engine.assets();
            let cube_mesh = assets.mesh("cube", &geometry::cube());
            let sphere_mesh = assets.mesh("sphere", &geometry::uv_sphere(16, 32));

            let basic = assets.shader("basic");
            let toon = assets.shader("toon");
            let cat = assets.texture("cat", "assets/image.JPG");

            let cube_mat = Rc::new(Material::new(basic).with_texture(cat));
            let sphere_mat = Rc::new(
                Material::new(toon)
                    .with_color(Vec3::new(0.35, 0.7, 1.0))
                    .with_toon_steps(4.0),
            );

            (cube_mesh, sphere_mesh, cube_mat, sphere_mat)
        };

        let mut rng = rand::thread_rng();

        for _ in 0..12 {
            engine.spawn(
                cube_mesh.clone(),
                cube_mat.clone(),
                random_position(&mut rng),
                |t, time, _dt| t.rotation.y = time,
            );
        }

        for _ in 0..8 {
            engine.spawn(
                sphere_mesh.clone(),
                sphere_mat.clone(),
                random_position(&mut rng),
                |t, time, _dt| {
                    t.position.y += time.sin() * 0.0025;
                    t.rotation.x = time * 0.5;
                },
            );
        }
    }
}
