#include <cstdio>
#include <render/VkManager.hh>

auto VkManager::setup() -> void {
  appinfo.sType               = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  appinfo.pApplicationName    = "Hide";
  appinfo.applicationVersion  = VK_MAKE_VERSION(0,0,1);
  appinfo.pEngineName         = "Nia Edit";
  appinfo.engineVersion       = VK_MAKE_VERSION(0,0,1);
  appinfo.apiVersion          = VK_API_VERSION_1_3;

  VkInstanceCreateInfo create_instance{};
  create_instance.sType             = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  create_instance.pApplicationInfo  = &appinfo;

  VkResult result = vkCreateInstance(&create_instance, nullptr, &instance);
  if (result != VK_SUCCESS) {
    std::printf("Unable to make vulkan instance");
  }
  
}
