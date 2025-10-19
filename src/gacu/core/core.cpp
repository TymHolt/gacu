#include <gacu/libs/glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <gacu/core/core.hpp>

GLFWwindow *glfw_window_handle;
double last_update_time;

void gacu::Init(int width, int height, const char *title) {
    if (!glfwInit())
        throw std::runtime_error(std::string("GLFW failed to initialize"));
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfw_window_handle = glfwCreateWindow(width, height, title, NULL, NULL);

    if (glfw_window_handle == NULL) {
        glfwTerminate();
        throw std::runtime_error(std::string("GLFW window failed to create"));
    }

    glfwMakeContextCurrent(glfw_window_handle);
    
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        glfwTerminate();
        throw std::runtime_error(std::string("GLAD failed to load"));
    }

    last_update_time = (float) glfwGetTime();
}

void gacu::GetSize(int *width, int *height) {
    glfwGetFramebufferSize(glfw_window_handle, width, height);
}

bool gacu::Update(float *delta_time) {
    glfwSwapBuffers(glfw_window_handle);
    glfwPollEvents();
        
    double current_update_time = glfwGetTime();
    *delta_time = (float) (current_update_time - last_update_time);
    last_update_time = current_update_time;

    int framebuffer_width;
    int frame_buffer_height;
    glfwGetFramebufferSize(glfw_window_handle, &framebuffer_width, &frame_buffer_height);
    glViewport(0, 0, framebuffer_width, frame_buffer_height);

    glClearColor(34.0f / 255.0f, 40.0f / 255.0f, 49.0f / 255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    return !glfwWindowShouldClose(glfw_window_handle);
}

void gacu::Terminate() {
    glfwTerminate();
}

bool gacu::IsKeyPressed(int glfw_key) {
    return glfwGetKey(glfw_window_handle, glfw_key) == GLFW_PRESS;
}