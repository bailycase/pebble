#include "pbvulkan.h"

// creates a new vulkan instance
int init_vulkan()
{
    VkInstance instance = NULL;
    // specify the application info
    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Pebble Engine";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;
    appInfo.pNext = NULL;

    // specify the create info
    VkInstanceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    // assign the glfw extensions to the create info
    uint32_t glfwExtensionCount = 0;
    const char **requiredExtensions;
    const char **glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    requiredExtensions = malloc((glfwExtensionCount + 1) * sizeof(const char *));

    for (uint32_t i = 0; i < glfwExtensionCount; i++)
    {
        requiredExtensions[i] = glfwExtensions[i];
    }

    requiredExtensions[sizeof(requiredExtensions) / sizeof(const char *) + 1] = VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME;

    createInfo.enabledExtensionCount = glfwExtensionCount + 1;
    createInfo.ppEnabledExtensionNames = requiredExtensions;
    createInfo.flags = VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;

    VkResult result = vkCreateInstance(&createInfo, NULL, &instance);

    if (result != VK_SUCCESS)
    {
        printf("Failed to create vulkan instance\n");
        return -1;
    }
    else
    {
        printf("Vulkan instance created\n");
    }

    // TODO: check for extension support

    // TODO: add validation layers

    // vkDestroyInstance(instance, NULL);

    VkPhysicalDevice physicalDevice = getPhysicalDevice(&instance);
    uint32_t queueFamily = findQueueFamilies(physicalDevice);

    VkDeviceQueueCreateInfo queueCreateInfo = {};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = queueFamily;
    queueCreateInfo.queueCount = 1;
    float queuePriority = 1.0f;
    queueCreateInfo.pQueuePriorities = &queuePriority;

    VkPhysicalDeviceFeatures deviceFeatures = {};

    createLogicalDevice(&deviceFeatures, queueCreateInfo);

    return 1;
}

VkPhysicalDevice getPhysicalDevice(VkInstance *instance)
{
    VkPhysicalDevice physicalDevice = NULL;
    uint32_t physicalDeviceCount = 0;
    vkEnumeratePhysicalDevices(*instance, &physicalDeviceCount, NULL);
    VkPhysicalDevice *physicalDevices = malloc(physicalDeviceCount * sizeof(VkPhysicalDevice));
    vkEnumeratePhysicalDevices(*instance, &physicalDeviceCount, physicalDevices);

    // TODO: add some sort of scoring system to select the best physical device

    physicalDevice = physicalDevices[0];
    free(physicalDevices);
    return physicalDevice;
}

uint32_t findQueueFamilies(VkPhysicalDevice physicalDevice)
{
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, NULL);
    VkQueueFamilyProperties *queueFamilies = malloc(queueFamilyCount * sizeof(VkQueueFamilyProperties));
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies);
    uint32_t graphicsFamily = UINT32_MAX;
    uint32_t presentFamily = UINT32_MAX;
    for (uint32_t i = 0; i < queueFamilyCount; i++)
    {
        if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            graphicsFamily = i;
        }
        VkBool32 presentSupport = 0;
        // vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, surface, &presentSupport);
        if (presentSupport)
        {
            presentFamily = i;
        }
    }
    free(queueFamilies);
    return graphicsFamily;
}

VkDeviceCreateInfo createLogicalDevice(VkPhysicalDeviceFeatures *deviceFeatures, VkDeviceQueueCreateInfo  queueCreateInfo) {
    VkDeviceCreateInfo createInfo = {};

    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.pQueueCreateInfos = &queueCreateInfo;
    createInfo.queueCreateInfoCount = 1;

    // createInfo.pEnabledFeatures = &deviceFeatures;
    return createInfo;
}