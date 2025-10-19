#ifndef GACU_CORE_HPP
#define GACU_CORE_HPP

namespace gacu {
    
    void Init(int width, int height, const char *title);
    void GetSize(int *width, int *height);
    bool Update(float *delta_time);
    void Terminate();
    bool IsKeyPressed(int glfw_key);
};

#endif