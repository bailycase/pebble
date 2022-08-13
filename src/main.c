#include <stdio.h>
#include "main.h"

void error_callback(int error, const char *description)
{
    fprintf(stderr, "Error: %s\n", description);
}

int main()
{

    if (!glfwInit())
    {
        printf("Failed to initialize GLFW\n");
        return -1;
    }

    if (!glfwVulkanSupported())
    {
        printf("Vulkan is not supported\n");
        return -1;
    }

    // glfwSetErrorCallback(error_callback);

    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    // GLFWwindow *window = glfwCreateWindow(800, 600, "Vulkan", NULL, NULL);

    // if (!window)
    // {
    //     printf("Failed to create GLFW window\n");
    //     glfwTerminate();
    //     return -1;
    // }

    // glfwMakeContextCurrent(window);

    // while (!glfwWindowShouldClose(window))
    // {
    //     glfwPollEvents();
    //     glfwSwapBuffers(window);
    // }

    return 0;
}