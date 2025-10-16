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

    class BasicObjectRenderer3d {
        private:
            ShaderProgram *m_shader_program;
            unsigned int m_texture_upload_location;
            unsigned int m_use_texture_upload_location;
        public:
            BasicObjectRenderer3d();
            ~BasicObjectRenderer3d();
            void RenderObject(BasicMesh3d *mesh);
    };
}

#endif