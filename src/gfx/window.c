#include "window.h"

void error_callback(int error, const char *description)
{
    fprintf(stderr, "Error: %s\n", description);
}

// Initialize the window to be used for rendering and attach a rendering instance
GLFWwindow *init_window()
{
    GLFWwindow *pb_window = NULL;
    // attempt to initialize GLFW
    if (!glfwInit())
    {
        printf("Failed to initialize GLFW\n");
        return pb_window;
    }

    if (!glfwVulkanSupported())
    {
        printf("Vulkan is not supported");
        return pb_window;
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    pb_window = glfwCreateWindow(800, 600, "Vulkan", NULL, NULL);

    return pb_window;
}
