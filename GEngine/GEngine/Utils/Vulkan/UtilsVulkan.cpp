#include "UtilsVulkan.h"

#include "Utils/Utils.h"
#include <cassert>



void SetDefaultTResources(glslang_resource_t& Resources)
{
    Resources.max_lights = 32;
    Resources.max_clip_planes = 6;
    Resources.max_texture_units = 32;
    Resources.max_texture_coords = 32;
    Resources.max_vertex_attribs = 64;
    Resources.max_vertex_uniform_components = 4096;
    Resources.max_varying_floats = 64;
    Resources.max_vertex_texture_image_units = 32;
    Resources.max_combined_texture_image_units = 80;
    Resources.max_texture_image_units = 32;
    Resources.max_fragment_uniform_components = 4096;
    Resources.max_draw_buffers = 32;
    Resources.max_vertex_uniform_vectors = 128;
    Resources.max_varying_vectors = 8;
    Resources.max_fragment_uniform_vectors = 16;
    Resources.max_vertex_output_vectors = 16;
    Resources.max_fragment_input_vectors = 15;
    Resources.min_program_texel_offset = -8;
    Resources.max_program_texel_offset = 7;
    Resources.max_clip_distances = 8;
    Resources.max_compute_work_group_count_x = 65535;
    Resources.max_compute_work_group_count_y = 65535;
    Resources.max_compute_work_group_count_z = 65535;
    Resources.max_compute_work_group_size_x = 1024;
    Resources.max_compute_work_group_size_y = 1024;
    Resources.max_compute_work_group_size_z = 64;
    Resources.max_compute_uniform_components = 1024;
    Resources.max_compute_texture_image_units = 16;
    Resources.max_compute_image_uniforms = 8;
    Resources.max_compute_atomic_counters = 8;
    Resources.max_compute_atomic_counter_buffers = 1;
    Resources.max_varying_components = 60;
    Resources.max_vertex_output_components = 64;
    Resources.max_geometry_input_components = 64;
    Resources.max_geometry_output_components = 128;
    Resources.max_fragment_input_components = 128;
    Resources.max_image_units = 8;
    Resources.max_combined_image_units_and_fragment_outputs = 8;
    Resources.max_combined_shader_output_resources = 8;
    Resources.max_image_samples = 0;
    Resources.max_vertex_image_uniforms = 0;
    Resources.max_tess_control_image_uniforms = 0;
    Resources.max_tess_evaluation_image_uniforms = 0;
    Resources.max_geometry_image_uniforms = 0;
    Resources.max_fragment_image_uniforms = 8;
    Resources.max_combined_image_uniforms = 8;
    Resources.max_geometry_texture_image_units = 16;
    Resources.max_geometry_output_vertices = 256;
    Resources.max_geometry_total_output_components = 1024;
    Resources.max_geometry_uniform_components = 1024;
    Resources.max_geometry_varying_components = 64;
    Resources.max_tess_control_input_components = 128;
    Resources.max_tess_control_output_components = 128;
    Resources.max_tess_control_texture_image_units = 16;
    Resources.max_tess_control_uniform_components = 1024;
    Resources.max_tess_control_total_output_components = 4096;
    Resources.max_tess_evaluation_input_components = 128;
    Resources.max_tess_evaluation_output_components = 128;
    Resources.max_tess_evaluation_texture_image_units = 16;
    Resources.max_tess_evaluation_uniform_components = 1024;
    Resources.max_tess_patch_components = 120;
    Resources.max_patch_vertices = 32;
    Resources.max_tess_gen_level = 64;
    Resources.max_viewports = 16;
    Resources.max_vertex_atomic_counters = 0;
    Resources.max_tess_control_atomic_counters = 0;
    Resources.max_tess_evaluation_atomic_counters = 0;
    Resources.max_geometry_atomic_counters = 0;
    Resources.max_fragment_atomic_counters = 8;
    Resources.max_combined_atomic_counters = 8;
    Resources.max_atomic_counter_bindings = 1;
    Resources.max_vertex_atomic_counter_buffers = 0;
    Resources.max_tess_control_atomic_counter_buffers = 0;
    Resources.max_tess_evaluation_atomic_counter_buffers = 0;
    Resources.max_geometry_atomic_counter_buffers = 0;
    Resources.max_fragment_atomic_counter_buffers = 1;
    Resources.max_combined_atomic_counter_buffers = 1;
    Resources.max_atomic_counter_buffer_size = 16384;
    Resources.max_transform_feedback_buffers = 4;
    Resources.max_transform_feedback_interleaved_components = 64;
    Resources.max_cull_distances = 8;
    Resources.max_combined_clip_and_cull_distances = 8;
    Resources.max_samples = 4;
    Resources.max_mesh_output_vertices_nv = 256;
    Resources.max_mesh_output_primitives_nv = 512;
    Resources.max_mesh_work_group_size_x_nv = 32;
    Resources.max_mesh_work_group_size_y_nv = 1;
    Resources.max_mesh_work_group_size_z_nv = 1;
    Resources.max_task_work_group_size_x_nv = 32;
    Resources.max_task_work_group_size_y_nv = 1;
    Resources.max_task_work_group_size_z_nv = 1;
    Resources.max_mesh_view_count_nv = 4;

    Resources.limits.non_inductive_for_loops = 1;
    Resources.limits.while_loops = 1;
    Resources.limits.do_while_loops = 1;
    Resources.limits.general_uniform_indexing = 1;
    Resources.limits.general_attribute_matrix_vector_indexing = 1;
    Resources.limits.general_varying_indexing = 1;
    Resources.limits.general_sampler_indexing = 1;
    Resources.limits.general_variable_indexing = 1;
    Resources.limits.general_constant_matrix_vector_indexing = 1;

}

size_t compileShader(glslang_stage_t stage, const char* shaderSource, ShaderModule& shaderModule)
{
    glslang_resource_t resources;

    SetDefaultTResources(resources);

	const glslang_input_t input =
	{
		.language = GLSLANG_SOURCE_GLSL,
		.stage = stage,
		.client = GLSLANG_CLIENT_VULKAN,
		.client_version = GLSLANG_TARGET_VULKAN_1_1,
		.target_language = GLSLANG_TARGET_SPV,
		.target_language_version = GLSLANG_TARGET_SPV_1_3,
		.code = shaderSource,
		.default_version = 100,
		.default_profile = GLSLANG_NO_PROFILE,
		.force_default_version_and_profile = false,
		.forward_compatible = false,
		.messages = GLSLANG_MSG_DEFAULT_BIT,
		.resource = &resources
	};

    //! Creating a shader
    glslang_shader_t* shd = glslang_shader_create(&input);


    //! Check shader is valid
    if (!glslang_shader_preprocess(shd, &input))
    {
        //! There is an error in shader log to fprintf
        
        fprintf(stderr, "GLSL preprocessing failed\n");
        fprintf(stderr, "\n%s",glslang_shader_get_info_log(shd));
        fprintf(stderr, "\n%s", glslang_shader_get_info_debug_log(shd));
        fprintf(stderr, "code:\n%s", input.code);
        return 0;
    }

    //! Check shader can be parsed
    if (!glslang_shader_parse(shd, &input))
    {
        //! Cannot parse shader
        fprintf(stderr, "GLSL parsing failed\n");
        fprintf(stderr, "\n%s", glslang_shader_get_info_log(shd));
        fprintf(stderr, "\n%s", glslang_shader_get_info_debug_log(shd));
        fprintf(stderr, "%s",glslang_shader_get_preprocessed_code(shd));
        fprintf(stderr, "code:\n%s", input.code);
        return 0;
    }

    //! Creating program pipeline

    glslang_program_t* program = glslang_program_create();
    glslang_program_add_shader(program, shd);

    //! Specify link messages
    
    auto msgs = GLSLANG_MSG_SPV_RULES_BIT | GLSLANG_MSG_VULKAN_RULES_BIT;

    //! Check shader and program can linked
    if (!glslang_program_link(program, msgs))
    {
        //! Cannot parse shader
        fprintf(stderr, "GLSL program linking failed\n");
        fprintf(stderr, "\n%s", glslang_program_get_info_log(program));
        fprintf(stderr, "\n%s", glslang_program_get_info_debug_log(program));
        fprintf(stderr, "code:\n%s", input.code);   
        return 0;
    }

    glslang_program_SPIRV_generate(program, stage);

    //! Resizing vector as same as SPIRV CODE SIZE
    shaderModule.SPIRV.resize(glslang_program_SPIRV_get_size(program));
    glslang_program_SPIRV_get(program, shaderModule.SPIRV.data());

    //! Check Messages
    const char* spirv_messages = glslang_program_SPIRV_get_messages(program);
    if (spirv_messages)
        fprintf(stderr, "%s", spirv_messages);
    
    //! Delete Program And Shader Because We get what we want
    glslang_program_delete(program);
    glslang_shader_delete(shd);

    //! Return Size of Vector
    return shaderModule.SPIRV.size();
}

glslang_stage_t glslangShaderStageFromFileName(const char* fileName)
{
    if (endsWith(fileName, ".vert"))
        return GLSLANG_STAGE_VERTEX;

    if (endsWith(fileName, ".frag"))
        return GLSLANG_STAGE_FRAGMENT;

    if (endsWith(fileName, ".geom"))
        return GLSLANG_STAGE_GEOMETRY;

    if (endsWith(fileName, ".comp"))
        return GLSLANG_STAGE_COMPUTE;

    if (endsWith(fileName, ".tesc"))
        return GLSLANG_STAGE_TESSCONTROL;

    if (endsWith(fileName, ".tese"))
        return GLSLANG_STAGE_TESSEVALUATION;

    return GLSLANG_STAGE_VERTEX;
}


size_t compileShaderFile(const char* file, ShaderModule& shaderModule)
{
    if (auto shaderSource = readShaderFile(file); !shaderSource.empty())
        return compileShader(glslangShaderStageFromFileName(file), shaderSource.c_str(), shaderModule);

    return 0;
}

void CHECK(bool check, const char* fileName, int lineNumber)
{
    if (!check)
    {
        printf("CHECK() failed at %s:%i\n", fileName, lineNumber);
        assert(false);
        exit(EXIT_FAILURE);
    }
}

void createInstance(VkInstance* instance)
{
    // https://vulkan.lunarg.com/doc/view/1.1.108.0/windows/validation_layers.html
    //! Debugging Layers
    const std::vector<const char*> ValidationLayers =
    {
        "VK_LAYER_KHRONOS_validation",
        "VK_LAYER_LUNARG_object_tracker"
    };

    const std::vector<const char*> exts =
    {
        "VK_KHR_surface",
#if defined (_WIN32)
        "VK_KHR_win32_surface"
#endif
#if defined (__APPLE__)
        "VK_MVK_macos_surface"
#endif
#if defined (__linux__)
        "VK_KHR_xcb_surface"
#endif
        , VK_EXT_DEBUG_UTILS_EXTENSION_NAME
        , VK_EXT_DEBUG_REPORT_EXTENSION_NAME
        /* for indexed textures */
        , VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME
    };

    const VkApplicationInfo appinfo =
    {
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pNext = nullptr,
        .pApplicationName = "Vulkan",
        .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
        .pEngineName = "No Engine",
        .engineVersion = VK_MAKE_VERSION(1, 0, 0),
        .apiVersion = VK_API_VERSION_1_1
    };

    const VkInstanceCreateInfo createInfo =
    {
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0,
        .pApplicationInfo = &appinfo,
        .enabledLayerCount = static_cast<uint32_t>(ValidationLayers.size()),
        .ppEnabledLayerNames = ValidationLayers.data(),
        .enabledExtensionCount = static_cast<uint32_t>(exts.size()),
        .ppEnabledExtensionNames = exts.data()
    };

    VK_CHECK(vkCreateInstance(&createInfo, nullptr, instance));

    volkLoadInstance(*instance);
}

VkResult createDevice(VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures deviceFeatures, uint32_t graphicsFamily, VkDevice* device)
{
    //! The Extensions that Device must support
    const std::vector<const char*> extensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

    //!  Device Queue
    const float queuePriority = 1.0f;
    const VkDeviceQueueCreateInfo qci = {
      .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO, // Always VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO
      .pNext = nullptr,                                    // Always nullptr
      .flags = 0,                                          // Always 0
      .queueFamilyIndex = graphicsFamily,                  // vkGetPhysicalDeviceQueueFamilyProperties()    
      .queueCount = 1,
      .pQueuePriorities = &queuePriority
    };

    const VkDeviceCreateInfo ci = {
    .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,  // Always VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO
    .pNext = nullptr,                               // Always nullptr 
    .flags = 0,                                     // Always 0
    .queueCreateInfoCount = 1,                      // Number of queue create infp
    .pQueueCreateInfos = &qci,                      // List of queue create info
    .enabledLayerCount = 0,                         // Layer Count 
    .ppEnabledLayerNames = nullptr,                 // List of layer names
    .enabledExtensionCount = static_cast<uint32_t>(extensions.size()), // Extension Count
  .ppEnabledExtensionNames = extensions.data(),                        // List of extension names
  .pEnabledFeatures = &deviceFeatures                                  // Enabled Futures VkPhysicalDeviceFeatures can be get vkGetPhysicalDeviceFeatures()
    };
    return vkCreateDevice(
        physicalDevice, &ci, nullptr, device);
}

VkResult findSuitablePhysicalDevice(VkInstance instance, std::function<bool(VkPhysicalDevice)> selector, VkPhysicalDevice* physicalDevice)
{
    uint32_t deviceCount = 0;
    //! Get Device Counts
     
    VK_CHECK_RET(vkEnumeratePhysicalDevices(instance,&deviceCount, nullptr));
    
    //! If there is no suitable device, return error initialization failed
    
    if (!deviceCount)
        return VK_ERROR_INITIALIZATION_FAILED;
    
    //! List of all physical device
    std::vector<VkPhysicalDevice> devices(deviceCount);

    //! Fill the list
    VK_CHECK_RET(vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data()));
    
    //! Pass device as a argument to the parameter function that returns bool, select the first that returns true 
    for (const auto& device : devices)
        if (selector(device)) {
            *physicalDevice = device;
            return VK_SUCCESS;
        }
    return VK_ERROR_INITIALIZATION_FAILED;
}

uint32_t findQueueFamilies(VkPhysicalDevice device, VkQueueFlags desiredFlags)
{
    uint32_t familyCount;

    //! Get All Queue Families from physical device firstly check there is any family supported
    vkGetPhysicalDeviceQueueFamilyProperties(device, &familyCount, nullptr);
   
    if (!familyCount)
        return 0;


    std::vector<VkQueueFamilyProperties>families(familyCount);
    
    //! At least there is one queue family so fill the vector with these
    vkGetPhysicalDeviceQueueFamilyProperties(device, &familyCount, families.data());

    //! Check all families if there is one that provide the requirements, desired flags and return it's index
    for (uint32_t i = 0; i != families.size(); i++)
        if (families[i].queueCount &&
            (families[i].queueFlags & desiredFlags))
            return i;
    return 0;
}


SwapchainSupportDetails querySwapchainSupport(VkPhysicalDevice device, VkSurfaceKHR surface)
{
    //! Get details surface capabilities
    SwapchainSupportDetails details;
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

    //! Check there is any format of surface that physical device support
    uint32_t formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);
    
    //! If it is fill details.formats
    if (formatCount) {
        details.formats.resize(formatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount,details.formats.data());
    }


    //! Check Surface Presentetion 
    uint32_t presentModeCnt;
    vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCnt, nullptr);
    if (presentModeCnt) {
        details.presentModes.resize(presentModeCnt);
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCnt,details.presentModes.data());
    }

    return details;
}

VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
{
    return
    { VK_FORMAT_B8G8R8A8_UNORM,VK_COLOR_SPACE_SRGB_NONLINEAR_KHR };
}

VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes)
{
    //! If it supports VK_PRESENT_MODE_MAILBOX_KHR return it if not return VK_PRESENT_MODE_FIFO_KHR
    for (const auto mode : availablePresentModes)
        if (mode == VK_PRESENT_MODE_MAILBOX_KHR)
            return mode;
    return VK_PRESENT_MODE_FIFO_KHR;
}

uint32_t chooseSwapImageCount(
    const VkSurfaceCapabilitiesKHR& caps)
{
    const uint32_t imageCount = caps.minImageCount + 1;
    const bool imageCountExceeded = caps.maxImageCount && imageCount > caps.maxImageCount;
    return imageCountExceeded ?caps.maxImageCount : imageCount;
}


VkResult createSwapchain(
    VkDevice device, VkPhysicalDevice physicalDevice,
    VkSurfaceKHR surface,
    uint32_t graphicsFamily,
    uint32_t width, uint32_t height,
    VkSwapchainKHR* swapchain)
{
    auto swapchainSupport = querySwapchainSupport(physicalDevice, surface);

    auto surfaceFormat = chooseSwapSurfaceFormat(swapchainSupport.formats);
    
    auto presentMode = chooseSwapPresentMode(swapchainSupport.presentModes);

    const VkSwapchainCreateInfoKHR ci = {
       .sType =VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
       .flags = 0,
       .surface = surface,
       .minImageCount = chooseSwapImageCount(swapchainSupport.capabilities),
       .imageFormat = surfaceFormat.format,
       .imageColorSpace = surfaceFormat.colorSpace,
       .imageExtent = {.width = width, .height = height },
       .imageArrayLayers = 1,
       .imageUsage =
       VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT |
       VK_IMAGE_USAGE_TRANSFER_DST_BIT,
      .imageSharingMode = VK_SHARING_MODE_EXCLUSIVE,
      .queueFamilyIndexCount = 1,
      .pQueueFamilyIndices = &graphicsFamily,
      .preTransform =
      swapchainSupport.capabilities.currentTransform,
      .compositeAlpha =
      VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
      .presentMode = presentMode,
      .clipped = VK_TRUE,
      .oldSwapchain = VK_NULL_HANDLE
    };
    return vkCreateSwapchainKHR(device, &ci, nullptr, swapchain);
}

size_t createSwapchainImages(VkDevice device, VkSwapchainKHR swapchain,std::vector<VkImage>& swapchainImages,std::vector<VkImageView>& swapchainImageViews)
{
    uint32_t imageCount = 0;

    VK_CHECK(vkGetSwapchainImagesKHR(device, swapchain,&imageCount, nullptr) == VK_SUCCESS);
    
    swapchainImages.resize(imageCount);
    
    swapchainImageViews.resize(imageCount);

    VK_CHECK(vkGetSwapchainImagesKHR(device, swapchain,&imageCount, swapchainImages.data()) ==VK_SUCCESS);

    for (unsigned i = 0; i < imageCount; i++)
        if (!createImageView(device, swapchainImages[i],VK_FORMAT_B8G8R8A8_UNORM,VK_IMAGE_ASPECT_COLOR_BIT,&swapchainImageViews[i]))
            exit(EXIT_FAILURE);

    return imageCount;
}

bool createImageView(VkDevice device, VkImage image,
    VkFormat format, VkImageAspectFlags aspectFlags,
    VkImageView* imageView)
{
    const VkImageViewCreateInfo viewInfo = {
      .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
      .pNext = nullptr,
      .flags = 0,
      .image = image,
      .viewType = VK_IMAGE_VIEW_TYPE_2D,
      .format = format,
      .subresourceRange = {
      .aspectMask = aspectFlags,
      .baseMipLevel = 0,
      .levelCount = 1,
      .baseArrayLayer = 0,
      .layerCount = 1
     }
    };

    VK_CHECK(vkCreateImageView(device, &viewInfo,nullptr, imageView));
    return true;
}


//# ----------------------------------------------------------------------

bool setVkObjectName(VulkanRenderDevice& vkDev, void* object, VkObjectType objType, const char* name)
{
    VkDebugUtilsObjectNameInfoEXT nameInfo = {
        .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
        .pNext = nullptr,
        .objectType = objType,
        .objectHandle = (uint64_t)object,
        .pObjectName = name
    };

    return (vkSetDebugUtilsObjectNameEXT(vkDev.device, &nameInfo) == VK_SUCCESS);
}

//! VK DEBUG CALLS
//# ----------------------------------------------------------------------

//! Print all debug messages to the console
static VKAPI_ATTR VkBool32 VKAPI_CALL vulkanDebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT Severity,
    VkDebugUtilsMessageTypeFlagsEXT Type,const VkDebugUtilsMessengerCallbackDataEXT* CallbackData, void* UserData)
{
    printf("Validation layer: %s\n",CallbackData->pMessage);
    return VK_FALSE;
}

//! Print all warnings to the console
static VKAPI_ATTR VkBool32 VKAPI_CALL vulkanDebugReportCallback(
    VkDebugReportFlagsEXT flags,
    VkDebugReportObjectTypeEXT objectType,
    uint64_t object, size_t location,
    int32_t messageCode,
    const char* pLayerPrefix,
    const char* pMessage, void* UserData)
{
    //! Dont Write performance warning
    if (flags & VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT)
        return VK_FALSE;


   
    printf("Debug callback (%s): %s\n",pLayerPrefix, pMessage);return VK_FALSE;
}

//# ----------------------------------------------------------------------

//# ----------------------------------------------------------------------


bool setupDebugCallbacks(
    VkInstance instance,
    VkDebugUtilsMessengerEXT* messenger,
    VkDebugReportCallbackEXT* reportCallback)
{
    const VkDebugUtilsMessengerCreateInfoEXT ci1 = {
      .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
      .messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
      .messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
      .pfnUserCallback = &vulkanDebugCallback,
      .pUserData = nullptr
    };

    VK_CHECK(vkCreateDebugUtilsMessengerEXT(instance, &ci1, nullptr, messenger));

    const VkDebugReportCallbackCreateInfoEXT ci2 = {
      .sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT,
      .pNext = nullptr,
      .flags =
        VK_DEBUG_REPORT_WARNING_BIT_EXT |
        VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT |
        VK_DEBUG_REPORT_ERROR_BIT_EXT |
        VK_DEBUG_REPORT_DEBUG_BIT_EXT,
      .pfnCallback = &vulkanDebugReportCallback,
      .pUserData = nullptr
    };

    VK_CHECK(vkCreateDebugReportCallbackEXT(instance,&ci2, nullptr, reportCallback));

    return true;
}

VkResult createSemaphore(VkDevice device, VkSemaphore* outSemaphore)
{
    const VkSemaphoreCreateInfo ci = {.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO };
    return vkCreateSemaphore(device, &ci, nullptr, outSemaphore);
}

bool initVulkanRenderDevice(VulkanInstance& vk, VulkanRenderDevice& vkDev, uint32_t width, uint32_t height, std::function<bool(VkPhysicalDevice)> selector, VkPhysicalDeviceFeatures deviceFeatures)
{
    vkDev.framebufferWidth = width;
    vkDev.framebufferHeight = height;

    VK_CHECK(findSuitablePhysicalDevice(vk.instance, selector, &vkDev.physicalDevice));
    vkDev.graphicsFamily = findQueueFamilies(vkDev.physicalDevice, VK_QUEUE_GRAPHICS_BIT);
    VK_CHECK(createDevice(vkDev.physicalDevice, deviceFeatures, vkDev.graphicsFamily, &vkDev.device));

    vkGetDeviceQueue(vkDev.device, vkDev.graphicsFamily, 0, &vkDev.graphicsQueue);
    if (vkDev.graphicsQueue == nullptr)
        exit(EXIT_FAILURE);

    VkBool32 presentSupported = 0;
    vkGetPhysicalDeviceSurfaceSupportKHR(vkDev.physicalDevice, vkDev.graphicsFamily, vk.surface, &presentSupported);
    if (!presentSupported)
        exit(EXIT_FAILURE);

    VK_CHECK(createSwapchain(vkDev.device, vkDev.physicalDevice, vk.surface, vkDev.graphicsFamily, width, height, &vkDev.swapchain));
    const size_t imageCount = createSwapchainImages(vkDev.device, vkDev.swapchain, vkDev.swapchainImages, vkDev.swapchainImageViews);
    vkDev.commandBuffers.resize(imageCount);

    VK_CHECK(createSemaphore(vkDev.device, &vkDev.semaphore));
    VK_CHECK(createSemaphore(vkDev.device, &vkDev.renderSemaphore));

    const VkCommandPoolCreateInfo cpi =
    {
        .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
        .flags = 0,
        .queueFamilyIndex = vkDev.graphicsFamily
    };

    VK_CHECK(vkCreateCommandPool(vkDev.device, &cpi, nullptr, &vkDev.commandPool));

    const VkCommandBufferAllocateInfo ai =
    {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
        .pNext = nullptr,
        .commandPool = vkDev.commandPool,
        .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
        .commandBufferCount = static_cast<uint32_t>(vkDev.swapchainImages.size()),
    };

    VK_CHECK(vkAllocateCommandBuffers(vkDev.device, &ai, &vkDev.commandBuffers[0]));
    return true;
}

void destroyVulkanRenderDevice(
    VulkanRenderDevice& vkDev)
{
    for (size_t i = 0; i < vkDev.swapchainImages.size();
        i++)
        vkDestroyImageView(vkDev.device,
            vkDev.swapchainImageViews[i], nullptr);
    vkDestroySwapchainKHR(
        vkDev.device, vkDev.swapchain, nullptr);
    vkDestroyCommandPool(vkDev.device,
        vkDev.commandPool, nullptr);
    vkDestroySemaphore(vkDev.device, vkDev.semaphore,
        nullptr);
    vkDestroySemaphore(vkDev.device,
        vkDev.renderSemaphore, nullptr);
    vkDestroyDevice(vkDev.device, nullptr);
}


void destroyVulkanInstance(VulkanInstance& vk)
{
    vkDestroySurfaceKHR(
        vk.instance, vk.surface, nullptr);
    vkDestroyDebugReportCallbackEXT(vk.instance,
        vk.reportCallback, nullptr);
    vkDestroyDebugUtilsMessengerEXT(vk.instance,
        vk.messenger, nullptr);
    vkDestroyInstance(vk.instance, nullptr);
}

uint32_t findMemoryType(VkPhysicalDevice device,uint32_t typeFilter,VkMemoryPropertyFlags properties)
{
  VkPhysicalDeviceMemoryProperties memProperties;
	vkGetPhysicalDeviceMemoryProperties(device, &memProperties);

	for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
		if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
			return i;
		}
	}

	return 0xFFFFFFFF;
}

bool createBuffer(
    VkDevice device, VkPhysicalDevice physicalDevice,
    VkDeviceSize size, VkBufferUsageFlags usage,
    VkMemoryPropertyFlags properties,
    VkBuffer& buffer, VkDeviceMemory& bufferMemory)
{
    const VkBufferCreateInfo bufferInfo = {
      .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
      .pNext = nullptr,
      .flags = 0,
      .size = size,
      .usage = usage,
      .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
      .queueFamilyIndexCount = 0,
      .pQueueFamilyIndices = nullptr
    };
    VK_CHECK(vkCreateBuffer(
        device, &bufferInfo, nullptr, &buffer));
    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(device, buffer,
        &memRequirements);
    const VkMemoryAllocateInfo ai = {
      .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
      .pNext = nullptr,
      .allocationSize = memRequirements.size,
      .memoryTypeIndex = findMemoryType(physicalDevice,
        memRequirements.memoryTypeBits, properties)
    };
    VK_CHECK(vkAllocateMemory(
        device, &ai, nullptr, &bufferMemory));
    vkBindBufferMemory(device, buffer, bufferMemory, 0);
    return true;
}

VkCommandBuffer beginSingleTimeCommands(VulkanRenderDevice& vkDev)
{
    VkCommandBuffer commandBuffer;

    const VkCommandBufferAllocateInfo allocInfo = {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
        .pNext = nullptr,
        .commandPool = vkDev.commandPool,
        .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
        .commandBufferCount = 1
    };

    vkAllocateCommandBuffers(vkDev.device, &allocInfo, &commandBuffer);

    const VkCommandBufferBeginInfo beginInfo = {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
        .pNext = nullptr,
        .flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
        .pInheritanceInfo = nullptr
    };

    vkBeginCommandBuffer(commandBuffer, &beginInfo);

    return commandBuffer;
}

void endSingleTimeCommands(VulkanRenderDevice& vkDev, VkCommandBuffer commandBuffer)
{
    vkEndCommandBuffer(commandBuffer);

    const VkSubmitInfo submitInfo = {
        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
        .pNext = nullptr,
        .waitSemaphoreCount = 0,
        .pWaitSemaphores = nullptr,
        .pWaitDstStageMask = nullptr,
        .commandBufferCount = 1,
        .pCommandBuffers = &commandBuffer,
        .signalSemaphoreCount = 0,
        .pSignalSemaphores = nullptr
    };

    vkQueueSubmit(vkDev.graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
    vkQueueWaitIdle(vkDev.graphicsQueue);

    vkFreeCommandBuffers(vkDev.device, vkDev.commandPool, 1, &commandBuffer);
}

void copyBuffer(VulkanRenderDevice& vkDev, VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size)
{
    VkCommandBuffer commandBuffer = beginSingleTimeCommands(vkDev);

    const VkBufferCopy copyRegion = {
        .srcOffset = 0,
        .dstOffset = 0,
        .size = size
    };

    vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

    endSingleTimeCommands(vkDev, commandBuffer);
}

bool createImage(VkDevice device, VkPhysicalDevice physicalDevice, uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory, VkImageCreateFlags flags, uint32_t mipLevels) {
    const VkImageCreateInfo imageInfo = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
        .pNext = nullptr,
        .flags = flags,
        .imageType = VK_IMAGE_TYPE_2D,
        .format = format,
        .extent = VkExtent3D {.width = width, .height = height, .depth = 1 },
        .mipLevels = mipLevels,
        .arrayLayers = (uint32_t)((flags == VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT) ? 6 : 1),
        .samples = VK_SAMPLE_COUNT_1_BIT,
        .tiling = tiling,
        .usage = usage,
        .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
        .queueFamilyIndexCount = 0,
        .pQueueFamilyIndices = nullptr,
        .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED
    };

    VK_CHECK(vkCreateImage(device, &imageInfo, nullptr, &image));

    VkMemoryRequirements memRequirements;
    vkGetImageMemoryRequirements(device, image, &memRequirements);

    const VkMemoryAllocateInfo allocInfo = {
        .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        .pNext = nullptr,
        .allocationSize = memRequirements.size,
        .memoryTypeIndex = findMemoryType(physicalDevice, memRequirements.memoryTypeBits, properties)
    };

    VK_CHECK(vkAllocateMemory(device, &allocInfo, nullptr, &imageMemory));

    vkBindImageMemory(device, image, imageMemory, 0);
    return true;
}