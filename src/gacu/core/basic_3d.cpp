#include <stdexcept>
#include <gacu/core/basic_3d.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <gacu/libs/stb/stb_image.h>
#include <gacu/libs/glad/glad.h>

gacu::BasicMesh3d::BasicMesh3d(float *data, unsigned int data_length, unsigned int *indices,
    unsigned int indices_length) {
    
    m_vertex_count = indices_length;
    
    glGenVertexArrays(1, &m_gl_vao_handle);  
    glBindVertexArray(m_gl_vao_handle);

    glGenBuffers(1, &m_gl_vbo_handle);
    glBindBuffer(GL_ARRAY_BUFFER, m_gl_vbo_handle);
    glBufferData(GL_ARRAY_BUFFER, data_length * sizeof(float), data, GL_STATIC_DRAW);

    glGenBuffers(1, &m_gl_ebo_handle);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_gl_ebo_handle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_length * sizeof(unsigned int), indices,
        GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    // Position data attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);
    
    // Material data attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float),
        (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Normal data attribute
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float),
        (void *) (6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

}

gacu::BasicMesh3d::~BasicMesh3d() {
    glDeleteVertexArrays(1, &m_gl_vao_handle);
    glDeleteBuffers(1, &m_gl_vbo_handle);
    glDeleteBuffers(1, &m_gl_ebo_handle);
}

void gacu::BasicMesh3d::Activate() {
    glBindVertexArray(m_gl_vao_handle);
}

void gacu::BasicMesh3d::Deactivate() {
    glBindVertexArray(0);
}

void gacu::BasicMesh3d::DrawCall() {
    glDrawElements(GL_TRIANGLES, m_vertex_count, GL_UNSIGNED_INT, 0);
}


gacu::BasicTexture::BasicTexture(unsigned char* data, size_t width, size_t height) {
    glGenTextures(1, &m_gl_texture_id);
    glBindTexture(GL_TEXTURE_2D, m_gl_texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
}
 
gacu::BasicTexture::~BasicTexture() {
    glDeleteTextures(1, &m_gl_texture_id);
}

void gacu::BasicTexture::Activate() {
    glBindTexture(GL_TEXTURE_2D, m_gl_texture_id);
}

void gacu::BasicTexture::Deactivate() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

gacu::BasicTexture *gacu::LoadTexture(std::string path) {
    stbi_set_flip_vertically_on_load(true);

    const char *path_c_string = path.c_str();
    int width;
    int height;
    int nr_channels;
    unsigned char *data = stbi_load(path_c_string, &width, &height, &nr_channels, 4);

    if (!data) {
        stbi_image_free(data);
        throw std::runtime_error(std::string("Failed to load texture " + path));
    }

    BasicTexture *texture = new BasicTexture(data, width, height);
    stbi_image_free(data);
    return texture;
}

gacu::BasicObjectRenderer3d::BasicObjectRenderer3d() {
    std::string vertex_shader_source =
        "#version 330 core\n"
        "\n"
        "layout (location = 0) in vec3 a_position;\n"
        "layout (location = 1) in vec3 a_material;\n"
        "layout (location = 2) in vec3 a_normal;\n"
        "\n"
        "uniform mat4 u_camera_transform;\n"
        "uniform mat4 u_object_transform;\n"
        "uniform mat3 u_object_rotation;\n"
        "\n"
        "out vec3 p_position;\n"
        "out vec3 p_material;\n"
        "out vec3 p_normal;\n"
        "\n"
        "void main() {\n"
        "   vec4 position = u_camera_transform * u_object_transform * vec4(a_position, 1.0);\n"
        "\n"
        "   p_position = position.xyz;\n"
        "   p_material = a_material;\n"
        "   p_normal = u_object_rotation * a_normal;\n"
        "\n"
        "   gl_Position = position;\n"
        "}\n";

    std::string fragment_shader_source =
        "#version 330 core\n"
        "\n"
        "in vec3 p_position;\n"
        "in vec3 p_material;\n"
        "in vec3 p_normal;\n"
        "\n"
        "uniform float u_use_texture;\n"
        "uniform sampler2D u_texture;\n"
        "uniform float u_use_vertex_color;\n"
        "uniform vec3 u_color;\n"
        "\n"
        "uniform vec3 u_ambient_color;\n"
        "uniform float u_ambient_strength;\n"
        "uniform vec3 u_sun_direction;\n"
        "uniform vec3 u_sun_color;\n"
        "uniform float u_sun_strength;\n"
        "\n"
        "out vec4 o_color;\n"
        "\n"
        "void main() {\n"
        "    vec4 texture_color_raw = texture(u_texture, vec2(p_material.x, p_material.y));\n"
        "    vec3 texture_color = texture_color_raw.xyz;\n"
        "    vec3 base_color = u_color * (1.0f - u_use_vertex_color) + p_material * u_use_vertex_color;\n"
        "    vec3 color = base_color * (1.0f - u_use_texture) + texture_color * u_use_texture;\n"
        "\n"
        "    vec3 normal = normalize(p_normal);\n"
        "    vec3 sun_direction = normalize(u_sun_direction);\n"
        "    float sun_strength = max(dot(normal, -sun_direction), 0.0f);\n"
        "    vec3 diffuse = u_sun_strength * sun_strength * u_sun_color;\n"
        "    vec3 ambient = u_ambient_color * u_ambient_strength;\n"
        "\n"
        "    vec3 shaded_color = color * (ambient + diffuse);\n"
        "\n"
        "    vec3 keepv = vec3(0.0f, 0.0f, 0.001f) * p_normal;\n"
        "    o_color = vec4(shaded_color + keepv, 1.0f);\n"
        "}\n";
        
    m_shader_program = new ShaderProgram(vertex_shader_source, fragment_shader_source);

    m_texture_location = m_shader_program->GetGLUploadLocation("u_texture");
    m_use_texture_location = m_shader_program->GetGLUploadLocation("u_use_texture");
    m_color_location = m_shader_program->GetGLUploadLocation("u_color");
    m_camera_transform_location = m_shader_program->GetGLUploadLocation("u_camera_transform");
    m_object_transform_location = m_shader_program->GetGLUploadLocation("u_object_transform");
    m_object_rotation_location = m_shader_program->GetGLUploadLocation("u_object_rotation");
    m_use_vertex_color_location = m_shader_program->GetGLUploadLocation("u_use_vertex_color");
    m_ambient_color_location = m_shader_program->GetGLUploadLocation("u_ambient_color");
    m_ambient_strength_location = m_shader_program->GetGLUploadLocation("u_ambient_strength");
    m_sun_color_location = m_shader_program->GetGLUploadLocation("u_sun_color");
    m_sun_direction_location = m_shader_program->GetGLUploadLocation("u_sun_direction");
    m_sun_strength_location = m_shader_program->GetGLUploadLocation("u_sun_strength");
}

gacu::BasicObjectRenderer3d::~BasicObjectRenderer3d() {
    delete m_shader_program;
}

void gacu::BasicObjectRenderer3d::Before() {
    glEnable(GL_DEPTH_TEST);
    m_shader_program->Activate();
    m_shader_program->UploadMatrix4(m_camera_transform_location, m_camera.GetTransformMatrix());
    
    glm::vec3 ambient_color = m_illumination.GetAmbientColor();
    m_shader_program->UploadFloat3(m_ambient_color_location, ambient_color.r, ambient_color.g,
        ambient_color.b);
    m_shader_program->UploadFloat(m_ambient_strength_location, m_illumination.GetAmbientStrength());
    
    glm::vec3 sun_color = m_illumination.GetSunColor();
    m_shader_program->UploadFloat3(m_sun_color_location, sun_color.r, sun_color.g,
        sun_color.b);
    glm::vec3 sun_direction = m_illumination.GetSunDirection();
    m_shader_program->UploadFloat3(m_sun_direction_location, sun_direction.r, sun_direction.g,
        sun_direction.b);
    m_shader_program->UploadFloat(m_sun_strength_location, m_illumination.GetSunStrength());
}

void gacu::BasicObjectRenderer3d::After() {
    m_shader_program->Deactivate();
    glDisable(GL_DEPTH_TEST);
}

void gacu::BasicObjectRenderer3d::UploadTransform(BasicObjectTransform3d *transform) {
    m_shader_program->UploadMatrix3(m_object_rotation_location, transform->GetRotationMatrix());
    m_shader_program->UploadMatrix4(m_object_transform_location, transform->GetTransformMatrix());
}

void gacu::BasicObjectRenderer3d::SetCamera(BasicCamera3d camera) {
    m_camera = camera;
}

void gacu::BasicObjectRenderer3d::SetIllumination(BasicIllumination3d illumination) {
    m_illumination = illumination;
}

void gacu::BasicObjectRenderer3d::RenderObjectTextured(BasicMesh3d *mesh,
    BasicObjectTransform3d *transform, BasicTexture *texture) {
    
    Before();
    mesh->Activate();

    UploadTransform(transform);
    m_shader_program->UploadInt(m_texture_location, 0);
    m_shader_program->UploadFloat(m_use_texture_location, 1.0f);

    texture->Activate();

    mesh->DrawCall();

    texture->Deactivate();
    mesh->Deactivate();
    After();
}

void gacu::BasicObjectRenderer3d::RenderObjectColored(BasicMesh3d *mesh,
    BasicObjectTransform3d *transform, float red, float green, float blue) {
    
    Before();
    mesh->Activate();

    UploadTransform(transform);
    m_shader_program->UploadFloat(m_use_texture_location, 0.0f);
    m_shader_program->UploadFloat(m_use_vertex_color_location, 0.0f);
    m_shader_program->UploadFloat3(m_color_location, red, green, blue);

    mesh->DrawCall();

    mesh->Deactivate();
    After();
}

void gacu::BasicObjectRenderer3d::RenderObjectVertexColored(BasicMesh3d *mesh,
    BasicObjectTransform3d *transform) {
    
    Before();
    mesh->Activate();

    UploadTransform(transform);
    m_shader_program->UploadFloat(m_use_texture_location, 0.0f);
    m_shader_program->UploadFloat(m_use_vertex_color_location, 1.0f);

    mesh->DrawCall();

    mesh->Deactivate();
    After();        
}
   