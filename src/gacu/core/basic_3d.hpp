#ifndef BASIC_3D_HPP
#define BASIC_3D_HPP

#include <gacu/internal/shader_program.hpp>
#include <gacu/libs/math.hpp>

namespace gacu {

    class BasicCamera3d {
        private:
            bool m_recalculate_matrices;
            glm::mat4 m_transform;
            float m_x;
            float m_y;
            float m_z;
            float m_fov;
            float m_aspect;
            float m_near;
            float m_far;
            
            void RecalculateMatrices();
        public:
            BasicCamera3d(float x = 0.0f, float y = 0.0f, float z = 0.0f, float fov = 0.0f, 
                float aspect = 0.0f, float near = 0.0f, float far = 0.0f);
            glm::mat4 GetTransformMatrix();
            void ApplyGlobalAspect();
            void SetX(float x);
            void SetY(float y);
            void setZ(float z);
            void SetFov(float fov);
            void SetAspect(float aspect);
            void setNearClip(float near);
            void setFarClip(float far);
            float GetX();
            float GetY();
            float GetZ();
            float GetFov();
            float GetAspect();
            float getNearClip();
            float GetFarClip();
    };

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
            unsigned int m_camera_transform_location;
            unsigned int m_texture_upload_location;
            unsigned int m_use_texture_upload_location;
            unsigned int m_color_upload_location;

            void Before(BasicCamera3d *camera);
            void After();
        public:
            BasicObjectRenderer3d();
            ~BasicObjectRenderer3d();
            void RenderObjectTextured(BasicMesh3d *mesh, BasicCamera3d *camera, BasicTexture *texture);
            void RenderObjectColored(BasicMesh3d *mesh, BasicCamera3d *camera, float red, float green,
                float blue);
    };
}

#endif