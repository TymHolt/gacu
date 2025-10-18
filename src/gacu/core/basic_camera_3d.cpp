#include <gacu/core/basic_3d.hpp>
#include <gacu/core/core.hpp>

gacu::BasicCamera3d::BasicCamera3d(float x, float y, float z, float fov, float aspect, float near, 
    float far) {
    
    m_x = x;
    m_y = y;
    m_z = z;
    m_fov = fov;
    m_aspect = aspect;
    m_near = near;
    m_far = far;

    m_transform = glm::mat4(1.0f);
    m_recalculate_matrices = true;
}

void gacu::BasicCamera3d::RecalculateMatrices() {
    m_transform = glm::perspective(glm::radians(m_fov), m_aspect, m_near, m_far);
    m_transform = glm::translate(m_transform, glm::vec3(-m_x, -m_y, -m_z));
}

glm::mat4 gacu::BasicCamera3d::GetTransformMatrix() {
    if (m_recalculate_matrices) {
        m_recalculate_matrices = false;
        RecalculateMatrices();
    }

    return m_transform;
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

void gacu::BasicCamera3d::setZ(float z) {
    m_z = z;
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

void gacu::BasicCamera3d::setNearClip(float near) {
    m_near = near;
    m_recalculate_matrices = true;
}

void gacu::BasicCamera3d::setFarClip(float far) {
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

float gacu::BasicCamera3d::GetFov() {
    return m_fov;
}

float gacu::BasicCamera3d::GetAspect() {
    return m_aspect;
}

float gacu::BasicCamera3d::getNearClip() {
    return m_near;
}

float gacu::BasicCamera3d::GetFarClip() {
    return m_far;
}