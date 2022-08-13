#include "pb.h"

// initializes the entire engine
int init_pb()
{
    GLFWwindow *pb_window = init_window();
    init_vulkan();

    while (!glfwWindowShouldClose(pb_window))
    {
        glfwPollEvents();
    }
    return 1;
}