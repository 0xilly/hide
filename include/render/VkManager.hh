#pragma once

#include <vulkan/vulkan.h>

struct VkManager {
    VkApplicationInfo appinfo{};
    VkInstance instance;
 
    auto setup() -> void;
    auto cleanup() -> void;
};
