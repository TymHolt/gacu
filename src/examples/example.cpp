#include <gacu/core/core.hpp>
#include <gacu/core/basic_3d.hpp>

int main() {
    gacu::Init(1280, 720, "GACU Example");

    float vertices[] = {
        0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,  0.0f, 0.0f, -1.0f, 
        0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,  0.0f, 0.0f, -1.0f, 
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f, -1.0f, 
        -0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, -1.0f
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    gacu::BasicMesh3d *mesh = new gacu::BasicMesh3d(vertices, 4 * 9, indices, 6);
    gacu::BasicObjectRenderer3d *renderer = new gacu::BasicObjectRenderer3d();
    gacu::BasicCamera3d camera(0.0f, 0.0f, 3.0f, 90.0f, 1.0f, 0.1f, 1024.0f);

    float delta_time;
    while (gacu::Update(&delta_time)) {
        camera.ApplyGlobalAspect();
        renderer->RenderObjectColored(mesh, &camera, 1.0f, 0.0f, 0.0f);
    }

    delete mesh;
    delete renderer;

    gacu::Terminate();
    return 0;
}