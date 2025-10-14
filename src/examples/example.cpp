#include <gacu/core/core.hpp>

int main() {
    gacu::Init(1280, 720, "GACU Example");

    float delta_time;
    while (gacu::Update(&delta_time));

    gacu::Terminate();
}