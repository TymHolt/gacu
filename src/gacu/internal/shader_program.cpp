#include <stdexcept>
#include <gacu/libs/glad/glad.h>
#include <gacu/internal/shader_program.hpp>

bool LoadShader(int gl_type, std::string source, unsigned int *gl_shader_handle) {
    *gl_shader_handle = glCreateShader(gl_type);
    const char *source_c_string = source.c_str();
    glShaderSource(*gl_shader_handle, 1, &source_c_string, NULL);
    glCompileShader(*gl_shader_handle);

    int compile_status;
    glGetShaderiv(*gl_shader_handle, GL_COMPILE_STATUS, &compile_status);
    return compile_status;
}

gacu::ShaderProgram::ShaderProgram(std::string vertex_shader_source,
    std::string fragment_shader_source) {
    
    char info_log[512];

    unsigned int gl_vertex_shader_handle;
    if (!LoadShader(GL_VERTEX_SHADER, vertex_shader_source, &gl_vertex_shader_handle)) {
        glGetShaderInfoLog(gl_vertex_shader_handle, sizeof(info_log), NULL, info_log);
        glDeleteShader(gl_vertex_shader_handle);
        throw std::runtime_error(std::string(info_log));
    }

    unsigned int gl_fragment_shader_handle;
    if (!LoadShader(GL_FRAGMENT_SHADER, fragment_shader_source, &gl_fragment_shader_handle)) {
        glGetShaderInfoLog(gl_fragment_shader_handle, sizeof(info_log), NULL, info_log);
        glDeleteShader(gl_vertex_shader_handle);
        glDeleteShader(gl_fragment_shader_handle);
        throw std::runtime_error(std::string(info_log));
    }

    m_gl_program_handle = glCreateProgram();
    glAttachShader(m_gl_program_handle, gl_vertex_shader_handle);
    glAttachShader(m_gl_program_handle, gl_fragment_shader_handle);
    glLinkProgram(m_gl_program_handle);

    int link_status;
    glGetProgramiv(m_gl_program_handle, GL_LINK_STATUS, &link_status);
    if(!link_status) {
        glGetProgramInfoLog(m_gl_program_handle, sizeof(info_log), NULL, info_log);
        glDeleteShader(gl_vertex_shader_handle);
        glDeleteShader(gl_fragment_shader_handle);
        glDeleteProgram(m_gl_program_handle);
        throw std::runtime_error(std::string(info_log));
    }

    glDeleteShader(gl_vertex_shader_handle);
    glDeleteShader(gl_fragment_shader_handle);
}

gacu::ShaderProgram::~ShaderProgram() {
    glDeleteProgram(m_gl_program_handle);
}

void gacu::ShaderProgram::Activate() {
    glUseProgram(m_gl_program_handle);
}

void gacu::ShaderProgram::Deactivate() {
    glUseProgram(0);
}

unsigned int gacu::ShaderProgram::GetGLUploadLocation(std::string name) {
    const char *name_c_string = name.c_str();
    return glGetUniformLocation(m_gl_program_handle, name_c_string);
}


void gacu::ShaderProgram::UploadMatrix4(unsigned int gl_upload_location, glm::mat4 matrix) {
    glUniformMatrix4fv(gl_upload_location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void gacu::ShaderProgram::UploadFloat(unsigned int gl_upload_location, float f) {
    glUniform1f(gl_upload_location, f);
}

void gacu::ShaderProgram::UploadFloat3(unsigned int gl_upload_location, float x, float y, float z) {
    glUniform3f(gl_upload_location, x, y, z);
}

void gacu::ShaderProgram::UploadInt(unsigned int gl_upload_location, int i) {
    glUniform1i(gl_upload_location, i);
}