#include <gacu/core/basic_3d.hpp>
#include <gacu/core/core.hpp>

gacu::BasicCamera3d::BasicCamera3d(float fov, float aspect, float near, float far) {
    m_x = 0.0f;
    m_y = 0.0f;
    m_z = 0.0f;
    m_pitch = 0.0f;
    m_yaw = 0.0f;
    m_fov = fov;
    m_aspect = aspect;
    m_near = near;
    m_far = far;

    m_transform = glm::mat4(1.0f);
    m_rotation = glm::mat4(1.0f);
    m_recalculate_matrices = true;
}

void gacu::BasicCamera3d::RecalculateMatrices() {
    m_rotation = glm::mat4(1.0f);
    m_rotation = glm::rotate(m_rotation, glm::radians(360.0f - m_pitch),
        glm::vec3(1.0f, 0.0f, 0.0f));
    m_rotation = glm::rotate(m_rotation, glm::radians(360.0f - m_yaw),
        glm::vec3(0.0f, 1.0f, 0.0f));

    m_transform = glm::perspective(glm::radians(m_fov), m_aspect, m_near, m_far);
    m_transform = m_transform * m_rotation;
    m_transform = glm::translate(m_transform, glm::vec3(-m_x, -m_y, -m_z));
}

glm::mat4 gacu::BasicCamera3d::GetTransformMatrix() {
    if (m_recalculate_matrices) {
        m_recalculate_matrices = false;
        RecalculateMatrices();
    }

    return m_transform;
}

glm::mat4 gacu::BasicCamera3d::GetRotationMatrix() {
    if (m_recalculate_matrices) {
        m_recalculate_matrices = false;
        RecalculateMatrices();
    }

    return m_rotation;
}

void gacu::BasicCamera3d::MoveTransformed(glm::vec3 move_vector) {
    glm::mat4 move_rotation = glm::mat4(1.0f);
    move_rotation = glm::rotate(move_rotation, glm::radians(m_yaw),
        glm::vec3(0.0f, 1.0f, 0.0f));  
    move_rotation = glm::rotate(move_rotation, glm::radians(m_pitch),
        glm::vec3(1.0f, 0.0f, 0.0f));

    glm::vec4 move_delta = move_rotation * glm::vec4(move_vector, 0.0f);
    m_x += move_delta.x;
    m_y += move_delta.y;
    m_z += move_delta.z;
}

void gacu::BasicCamera3d::ApplyGlobalAspect() {
    int width;
    int height;
    gacu::GetSize(&width, &height);
    SetAspect((float) width / (float) height);
}

void gacu::BasicCamera3d::SetX(float x) {
    m_x = x;
    m_recalculate_matrices = true;
}

void gacu::BasicCamera3d::SetY(float y) {
    m_y = y;
    m_recalculate_matrices = true;
}

void gacu::BasicCamera3d::SetZ(float z) {
    m_z = z;
    m_recalculate_matrices = true;
}

void gacu::BasicCamera3d::SetPitch(float pitch) {
    m_pitch = pitch;
    m_recalculate_matrices = true;
}

void gacu::BasicCamera3d::SetYaw(float yaw) {
    m_yaw = yaw;
    m_recalculate_matrices = true;
}

void gacu::BasicCamera3d::SetFov(float fov) {
    m_fov = fov;
    m_recalculate_matrices = true;
}

void gacu::BasicCamera3d::SetAspect(float aspect) {
    m_aspect = aspect;
    m_recalculate_matrices = true;
}

void gacu::BasicCamera3d::SetNearClip(float near) {
    m_near = near;
    m_recalculate_matrices = true;
}

void gacu::BasicCamera3d::SetFarClip(float far) {
    m_far = far;
    m_recalculate_matrices = true;
}

float gacu::BasicCamera3d::GetX() {
    return m_x;
}

float gacu::BasicCamera3d::GetY() {
    return m_y;
}

float gacu::BasicCamera3d::GetZ() {
    return m_z;
}

float gacu::BasicCamera3d::GetPitch() {
    return m_pitch;
}

float gacu::BasicCamera3d::GetYaw() {
    return m_yaw;
}

float gacu::BasicCamera3d::GetFov() {
    return m_fov;
}

float gacu::BasicCamera3d::GetAspect() {
    return m_aspect;
}

float gacu::BasicCamera3d::GetNearClip() {
    return m_near;
}

float gacu::BasicCamera3d::GetFarClip() {
    return m_far;
}