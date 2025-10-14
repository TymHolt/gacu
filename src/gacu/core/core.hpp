#ifndef GACU_CORE_HPP
#define GACU_CORE_HPP

namespace gacu {
    
    void Init(int width, int height, const char *title);
    bool Update(float *delta_time);
    void Terminate();
};

#endif