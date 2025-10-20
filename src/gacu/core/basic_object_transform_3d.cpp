#include <gacu/core/basic_3d.hpp>

gacu::BasicObjectTransform3d::BasicObjectTransform3d() {
    m_x = 0.0f;
    m_y = 0.0f;
    m_z = 0.0f;
    m_pitch = 0.0f;
    m_yaw = 0.0f;
    m_roll = 0.0f;
    m_scale_x = 1.0f;
    m_scale_y = 1.0f;
    m_scale_z = 1.0f;

    m_transform = glm::mat4(1.0f);
    m_recalculate_matrices = true;
}

void gacu::BasicObjectTransform3d::RecalculateMatrices() {
    m_transform = glm::mat4(1.0f);
    m_transform = glm::translate(m_transform, glm::vec3(m_x, m_y, m_z));
    m_transform = glm::scale(m_transform, glm::vec3(m_scale_x, m_scale_y, m_scale_z));
    m_transform = glm::rotate(m_transform, glm::radians(m_yaw), glm::vec3(0.0f, 1.0f, 0.0f));
    m_transform = glm::rotate(m_transform, glm::radians(m_pitch), glm::vec3(1.0f, 0.0f, 0.0f));
    m_transform = glm::rotate(m_transform, glm::radians(m_roll), glm::vec3(0.0f, 0.0f, 1.0f));
}

glm::mat4 gacu::BasicObjectTransform3d::GetTransformMatrix() {
    if (m_recalculate_matrices) {
        m_recalculate_matrices = false;
        RecalculateMatrices();
    }

    return m_transform;
}

void gacu::BasicObjectTransform3d::SetX(float x) {
    m_x = x;
    m_recalculate_matrices = true;
}

void gacu::BasicObjectTransform3d::SetY(float y) {
    m_y = y;
    m_recalculate_matrices = true;
}

void gacu::BasicObjectTransform3d::SetZ(float z) {
    m_z = z;
    m_recalculate_matrices = true;
}

void gacu::BasicObjectTransform3d::SetPitch(float pitch) {
    m_pitch = pitch;
    m_recalculate_matrices = true;
}

void gacu::BasicObjectTransform3d::SetYaw(float yaw) {
    m_yaw = yaw;
    m_recalculate_matrices = true;
}

void gacu::BasicObjectTransform3d::SetRoll(float roll) {
    m_roll = m_roll;
    m_recalculate_matrices = true;
}

void gacu::BasicObjectTransform3d::SetScaleX(float scale_x) {
    m_scale_x = scale_x;
    m_recalculate_matrices = true;
}

void gacu::BasicObjectTransform3d::SetScaleY(float scale_y) {
    m_scale_y = scale_y;
    m_recalculate_matrices = true;
}

void gacu::BasicObjectTransform3d::SetScaleZ(float scale_z) {
    m_scale_z = scale_z;
    m_recalculate_matrices = true;
}

float gacu::BasicObjectTransform3d::GetX() {
    return m_x;
}

float gacu::BasicObjectTransform3d::GetY() {
    return m_y;
}

float gacu::BasicObjectTransform3d::GetZ() {
    return m_z;
}

float gacu::BasicObjectTransform3d::GetPitch() {
    return m_pitch;
}

float gacu::BasicObjectTransform3d::GetYaw() {
    return m_yaw;
}

float gacu::BasicObjectTransform3d::GetRoll() {
    return m_roll;
}


float gacu::BasicObjectTransform3d::GetScaleX() {
    return m_scale_x;
}


float gacu::BasicObjectTransform3d::GetScaleY() {
    return m_scale_y;
}

float gacu::BasicObjectTransform3d::GetScaleZ() {
    return m_scale_z;
}