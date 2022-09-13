#include "UtilsVulkan.h"

#include "Utils/Utils.h"

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