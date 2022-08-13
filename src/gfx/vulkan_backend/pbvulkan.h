#ifndef PB_GFX_VULKAN_H
#define PB_GFX_VULKAN_H
#include <pb.h>
#include <vulkan/vulkan.h>

int init_vulkan();
VkPhysicalDevice getPhysicalDevice(VkInstance *instance);
uint32_t findQueueFamilies(VkPhysicalDevice physicalDevice);
VkDeviceCreateInfo createLogicalDevice(VkPhysicalDeviceFeatures *deviceFeatures, VkDeviceQueueCreateInfo  deviceCreateInfo);

#endif