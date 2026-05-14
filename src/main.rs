mod assets;
mod camera;
mod engine;
mod geometry;
mod material;
mod mesh;
mod renderer;
mod scene;
mod shader;
mod texture;
mod transform;

mod game;

use engine::Engine;
use game::DemoGame;

fn main() {
    Engine::new(800, 600, "engine").run(DemoGame);
}
