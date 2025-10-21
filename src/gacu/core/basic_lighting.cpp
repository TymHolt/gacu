#include <gacu/core/basic_3d.hpp>

gacu::BasicIllumination3d::BasicIllumination3d() {
    m_ambient_color = glm::vec3(1.0f, 1.0f, 1.0f);
    m_ambient_strength = 0.1f;
    m_sun_color = glm::vec3(1.0f, 1.0f, 1.0f);
    m_sun_direction = glm::vec3(0.0f, -1.0f, -1.0f);
    m_sun_strength = 0.9f;
}

void gacu::BasicIllumination3d::SetAmbient(glm::vec3 color, float strength) {
    m_ambient_color = color;
    m_ambient_strength = strength;
}

void gacu::BasicIllumination3d::SetSun(glm::vec3 direction, glm::vec3 color, float strength) {
    m_sun_direction = direction;
    m_sun_color = color;
    m_sun_strength = strength;
}

glm::vec3 gacu::BasicIllumination3d::GetAmbientColor() {
    return m_ambient_color;
}

float gacu::BasicIllumination3d::GetAmbientStrength() {
    return m_ambient_strength;
}

glm::vec3 gacu::BasicIllumination3d::GetSunColor() {
    return m_sun_color;
}

glm::vec3 gacu::BasicIllumination3d::GetSunDirection() {
    return m_sun_direction;
}

float gacu::BasicIllumination3d::GetSunStrength() {
    return m_sun_strength;
}