#pragma once


#include <array>
#include <functional>
#include <vector>

#include <vulkan/vulkan.h>
#include <glslang/glslang_c_interface.h>



struct ShaderModule {
	std::vector<unsigned int> SPIRV; // SPIRV Shader Storage
	VkShaderModule shaderModule; 
};

void SetDefaultTResources(glslang_resource_t& Resources);


size_t compileShader(glslang_stage_t stage, const char* shaderResource, ShaderModule& shaderModule);

//! Get STAGE from FileName
glslang_stage_t glslangShaderStageFromFileName(const char* fileName);

size_t compileShaderFile(const char* file, ShaderModule& shaderModule);
