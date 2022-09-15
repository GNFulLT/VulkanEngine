#pragma once


#include <array>
#include <functional>
#include <vector>

#include "volk/volk.h"
#include "Utils/glslang_wrapper.h"

#define VK_CHECK(value) CHECK(value == VK_SUCCESS, __FILE__, __LINE__);
#define VK_CHECK_RET(value) if ( value != VK_SUCCESS ) { CHECK(false, __FILE__, __LINE__); return value; }

//! Check Results same as ThrowIfFailed() with a difference it exits immediately
void CHECK(bool check, const char* fileName, int lineNumber);

struct ShaderModule {
	std::vector<unsigned int> SPIRV; // SPIRV Shader Storage
	VkShaderModule shaderModule; 
};


struct VulkanInstance {
	VkInstance instance;
	VkSurfaceKHR surface;
	VkDebugUtilsMessengerEXT messenger;
	VkDebugReportCallbackEXT reportCallback;
};


struct VulkanRenderDevice {
	
	uint32_t framebufferWidth;
	uint32_t framebufferHeight;

	VkDevice device;
	VkQueue graphicsQueue;
	VkPhysicalDevice physicalDevice;
	uint32_t graphicsFamily;
	VkSemaphore semaphore;
	VkSemaphore renderSemaphore;
	VkSwapchainKHR swapchain;
	std::vector<VkImage> swapchainImages;
	std::vector<VkImageView> swapchainImageViews;
	VkCommandPool commandPool;
	std::vector<VkCommandBuffer> commandBuffers;
};


void SetDefaultTResources(glslang_resource_t& Resources);


size_t compileShader(glslang_stage_t stage, const char* shaderResource, ShaderModule& shaderModule);

//! Get STAGE from FileName
glslang_stage_t glslangShaderStageFromFileName(const char* fileName);

size_t compileShaderFile(const char* file, ShaderModule& shaderModule);



//! Vulkan Things
//! 
//# -------------------------------------------------------

bool createImage(VkDevice device, VkPhysicalDevice physicalDevice, uint32_t width, uint32_t height, VkFormat format,
	VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory, VkImageCreateFlags flags, uint32_t mipLevels);

void copyBuffer(VulkanRenderDevice& vkDev, VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

bool createBuffer(VkDevice device, VkPhysicalDevice physicalDevice,
	VkDeviceSize size, VkBufferUsageFlags usage,VkMemoryPropertyFlags properties,VkBuffer& buffer, VkDeviceMemory& bufferMemory);

uint32_t findMemoryType(VkPhysicalDevice device, uint32_t typeFilter, VkMemoryPropertyFlags properties);

//bool fillCommandBuffers(size_t i);

void destroyVulkanInstance(VulkanInstance& vk);

void destroyVulkanRenderDevice(VulkanRenderDevice& vkDev);

bool initVulkanRenderDevice(VulkanInstance& vk, VulkanRenderDevice& vkDev,uint32_t width, uint32_t height,std::function<bool(VkPhysicalDevice)> selector,VkPhysicalDeviceFeatures deviceFeatures);


//! For Sync
VkResult createSemaphore(VkDevice device, VkSemaphore* outSemaphore);

//! For Creating Swap Chain, Stores necessary infos

struct SwapchainSupportDetails final
{
	VkSurfaceCapabilitiesKHR capabilities = {};
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};

//! Set Debug Callbacks
bool setupDebugCallbacks(VkInstance instance,VkDebugUtilsMessengerEXT* messenger,VkDebugReportCallbackEXT* reportCallback);

//! Create Image View
bool createImageView(VkDevice device, VkImage image,VkFormat format, VkImageAspectFlags aspectFlags,VkImageView* imageView);

//! Get Actual Images from swap chain
size_t createSwapchainImages(VkDevice device, VkSwapchainKHR swapchain,std::vector<VkImage>& swapchainImages,std::vector<VkImageView>& swapchainImageViews);

//! Create Swap Chain
VkResult createSwapchain(VkDevice device, VkPhysicalDevice physicalDevice,VkSurfaceKHR surface,uint32_t graphicsFamily,uint32_t width, uint32_t height,VkSwapchainKHR* swapchain);

//! Swap Chain Image Count
uint32_t chooseSwapImageCount(const VkSurfaceCapabilitiesKHR& caps);

//! Present mode for swapchain
VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);

//! Get R8G8B8A8 Format
VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>&availableFormats);


//! Get SwapChainSupportDetails by physical device and selected surface
SwapchainSupportDetails querySwapchainSupport(VkPhysicalDevice device, VkSurfaceKHR surface);

//! Create Vulkan Instance
void createInstance(VkInstance* instance);


//! Check physical devices
VkResult findSuitablePhysicalDevice(VkInstance instance, std::function<bool(VkPhysicalDevice)> selector, VkPhysicalDevice* physicalDevice);

//! Find Queue Families of founded physical device
uint32_t findQueueFamilies(VkPhysicalDevice device, VkQueueFlags desiredFlags);

//! Create Logical Device from physical device , features and queue family
VkResult createDevice(VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures deviceFeatures, uint32_t graphicsFamily, VkDevice* device);
