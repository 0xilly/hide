/* 
 * Copyright (c) Anthony Anderson
 * SPDX-License-Identifier: MPL-2.0
 */

#pragma once

#include <vulkan/vulkan.h>

struct VkManager {
    VkApplicationInfo appinfo{};
    VkInstance instance;
    VkSurfaceKHR surface;
 
    auto setup() -> void;
    auto cleanup() -> void;
};
