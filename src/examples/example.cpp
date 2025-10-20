#include <GLFW/glfw3.h>
#include <gacu/core/core.hpp>
#include <gacu/core/basic_3d.hpp>

void UpdateCamera(gacu::BasicCamera3d *camera, float delta_time);
void UpdateObject(gacu::BasicObjectTransform3d *transform, float delta_time);

int main() {
    // Init gacu window and OpenGL context
    gacu::Init(1280, 720, "GACU Example");

    // Define quad
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

    // Init all objects needed
    gacu::BasicMesh3d *mesh = new gacu::BasicMesh3d(vertices, 4 * 9, indices, 6);
    gacu::BasicObjectRenderer3d *renderer = new gacu::BasicObjectRenderer3d();
    gacu::BasicCamera3d camera(90.0f, 1.0f, 0.1f, 1024.0f);
    gacu::BasicObjectTransform3d transform;

    // Update + render loop
    float delta_time;
    while (gacu::Update(&delta_time)) {
        UpdateObject(&transform, delta_time);
        UpdateCamera(&camera, delta_time);
        renderer->RenderObjectColored(mesh, &transform, &camera, 1.0f, 0.0f, 0.0f);
    }

    // Clean up
    delete mesh;
    delete renderer;

    gacu::Terminate();
    return 0;
}

void UpdateCamera(gacu::BasicCamera3d *camera, float delta_time) {
    camera->ApplyGlobalAspect();

    if (gacu::IsKeyPressed(GLFW_KEY_SPACE))
        return;

    float delta_rotate = 180.0f * delta_time;
    float pitch = camera->GetPitch();
    float yaw = camera->GetYaw();
    
    if (gacu::IsKeyPressed(GLFW_KEY_UP))
        pitch += delta_rotate;
    if (gacu::IsKeyPressed(GLFW_KEY_DOWN))
        pitch -= delta_rotate;
    if (gacu::IsKeyPressed(GLFW_KEY_RIGHT))
        yaw -= delta_rotate;
    if (gacu::IsKeyPressed(GLFW_KEY_LEFT))
        yaw += delta_rotate;

    camera->SetPitch(pitch);
    camera->SetYaw(yaw);

    float move_x = 0.0f;
    float move_z = 0.0f;
        
    if (gacu::IsKeyPressed(GLFW_KEY_W))
        move_z--;
    if (gacu::IsKeyPressed(GLFW_KEY_S))
        move_z++;
    if (gacu::IsKeyPressed(GLFW_KEY_A))
        move_x--;
    if (gacu::IsKeyPressed(GLFW_KEY_D))
        move_x++;

    glm::vec3 move_vector = glm::vec3(move_x, 0.0f, move_z);
    if (glm::length(move_vector) != 0.0f) { // Prevent NaN
        move_vector = glm::normalize(move_vector) * 2.0f * delta_time;
        camera->MoveTransformed(move_vector);
    }
}

void UpdateObject(gacu::BasicObjectTransform3d *transform, float delta_time) {
    if (!gacu::IsKeyPressed(GLFW_KEY_SPACE))
        return;

    float delta_rotate = 180.0f * delta_time;
    float pitch = transform->GetPitch();
    float yaw = transform->GetYaw();
    
    if (gacu::IsKeyPressed(GLFW_KEY_UP))
        pitch -= delta_rotate;
    if (gacu::IsKeyPressed(GLFW_KEY_DOWN))
        pitch += delta_rotate;
    if (gacu::IsKeyPressed(GLFW_KEY_RIGHT))
        yaw -= delta_rotate;
    if (gacu::IsKeyPressed(GLFW_KEY_LEFT))
        yaw += delta_rotate;

    transform->SetPitch(pitch);
    transform->SetYaw(yaw);

    float move_x = 0.0f;
    float move_z = 0.0f;
        
    if (gacu::IsKeyPressed(GLFW_KEY_W))
        move_z--;
    if (gacu::IsKeyPressed(GLFW_KEY_S))
        move_z++;
    if (gacu::IsKeyPressed(GLFW_KEY_A))
        move_x--;
    if (gacu::IsKeyPressed(GLFW_KEY_D))
        move_x++;

    move_x *=  2.0f * delta_time;
    move_z *=  2.0f * delta_time;

    transform->SetX(transform->GetX() + move_x);
    transform->SetZ(transform->GetZ() + move_z);
}