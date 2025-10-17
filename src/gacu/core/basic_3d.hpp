#ifndef BASIC_3D_HPP
#define BASIC_3D_HPP

#include <gacu/internal/shader_program.hpp>

namespace gacu {

    class BasicMesh3d {
        private:
            unsigned int m_gl_vao_handle;    
            unsigned int m_gl_vbo_handle;
            unsigned int m_gl_ebo_handle;
            unsigned int m_vertex_count;
        public:
            BasicMesh3d(float *data, unsigned int data_length, unsigned int *indices,
                unsigned int indices_length);
            ~BasicMesh3d();
            void Activate();
            void Deactivate();
            void DrawCall();
    };

    class BasicTexture {
        private:
            unsigned int m_gl_texture_id;
        public:
            BasicTexture(unsigned char* data = 0, size_t width = 0, size_t height = 0);
            ~BasicTexture();
            void Activate();
            void Deactivate();
    };

    BasicTexture *LoadTexture(std::string path);

    class BasicObjectRenderer3d {
        private:
            ShaderProgram *m_shader_program;
            unsigned int m_texture_upload_location;
            unsigned int m_use_texture_upload_location;
            unsigned int m_color_upload_location;
        public:
            BasicObjectRenderer3d();
            ~BasicObjectRenderer3d();
            void RenderObjectTextured(BasicMesh3d *mesh, BasicTexture *texture);
            void RenderObjectColored(BasicMesh3d *mesh, float red, float green, float blue);
    };
}

#endif