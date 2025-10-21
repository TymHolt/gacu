#ifndef SHADER_PROGRAM_HPP
#define SHADER_PROGRAM_HPP

#include <string>
#include <gacu/libs/math.hpp>

namespace gacu {

    class ShaderProgram {
        private:
            unsigned int m_gl_program_handle;
        public:
            ShaderProgram(std::string vertex_shader_source = "",
                std::string fragment_shader_source = "");
            ~ShaderProgram();
            void Activate();
            void Deactivate();
            unsigned int GetGLUploadLocation(std::string name);
            void UploadMatrix3(unsigned int gl_upload_location, glm::mat3 matrix);
            void UploadMatrix4(unsigned int gl_upload_location, glm::mat4 matrix);
            void UploadFloat(unsigned int gl_upload_location, float f);
            void UploadFloat3(unsigned int gl_upload_location, float x, float y, float z);
            void UploadInt(unsigned int gl_upload_location, int i);
    };
}

#endif