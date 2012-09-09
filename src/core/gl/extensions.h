/*!The Graphic 2D Box Library
 * 
 * GBox2 is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 * 
 * GBox2 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with GBox2; 
 * If not, see <a href="http://www.gnu.org/licenses/"> http://www.gnu.org/licenses/</a>
 * 
 * Copyright (C) 2009 - 2012, ruki All rights reserved.
 *
 * @author		ruki
 * @file		extensions.h
 *
 */
#ifndef G2_CORE_GL_EXTENSIONS_H
#define G2_CORE_GL_EXTENSIONS_H

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * types
 */

// the gl extensions type
typedef enum __g2_gl_extensions_t
{
	G2_GL_EXT_ARB_base_instance 						= 0
,	G2_GL_EXT_ARB_blend_func_extended
,	G2_GL_EXT_ARB_color_buffer_float
,	G2_GL_EXT_ARB_compatibility
,	G2_GL_EXT_ARB_compressed_texture_pixel_storage
,	G2_GL_EXT_ARB_conservative_depth
,	G2_GL_EXT_ARB_copy_buffer
,	G2_GL_EXT_ARB_depth_buffer_float
,	G2_GL_EXT_ARB_depth_clamp
,	G2_GL_EXT_ARB_depth_texture
,	G2_GL_EXT_ARB_draw_buffers
,	G2_GL_EXT_ARB_draw_elements_base_vertex
,	G2_GL_EXT_ARB_draw_instanced
,	G2_GL_EXT_ARB_ES2_compatibility
,	G2_GL_EXT_ARB_explicit_attrib_location
,	G2_GL_EXT_ARB_fragment_coord_conventions
,	G2_GL_EXT_ARB_fragment_program
,	G2_GL_EXT_ARB_fragment_program_shadow
,	G2_GL_EXT_ARB_fragment_shader
,	G2_GL_EXT_ARB_framebuffer_object
,	G2_GL_EXT_ARB_framebuffer_sRGB
,	G2_GL_EXT_ARB_geometry_shader4
,	G2_GL_EXT_ARB_get_program_binary
,	G2_GL_EXT_ARB_half_float_pixel
,	G2_GL_EXT_ARB_half_float_vertex
,	G2_GL_EXT_ARB_imaging
,	G2_GL_EXT_ARB_instanced_arrays
,	G2_GL_EXT_ARB_internalformat_query
,	G2_GL_EXT_ARB_map_buffer_alignment
,	G2_GL_EXT_ARB_map_buffer_range
,	G2_GL_EXT_ARB_multisample
,	G2_GL_EXT_ARB_multitexture
,	G2_GL_EXT_ARB_occlusion_query
,	G2_GL_EXT_ARB_occlusion_query2
,	G2_GL_EXT_ARB_pixel_buffer_object
,	G2_GL_EXT_ARB_point_parameters
,	G2_GL_EXT_ARB_point_sprite
,	G2_GL_EXT_ARB_provoking_vertex
,	G2_GL_EXT_ARB_robustness
,	G2_GL_EXT_ARB_sampler_objects
,	G2_GL_EXT_ARB_seamless_cube_map
,	G2_GL_EXT_ARB_separate_shader_objects
,	G2_GL_EXT_ARB_shader_bit_encoding
,	G2_GL_EXT_ARB_shader_objects
,	G2_GL_EXT_ARB_shading_language_100
,	G2_GL_EXT_ARB_shading_language_420pack
,	G2_GL_EXT_ARB_shading_language_include
,	G2_GL_EXT_ARB_shading_language_packing
,	G2_GL_EXT_ARB_shadow
,	G2_GL_EXT_ARB_sync
,	G2_GL_EXT_ARB_texture_border_clamp
,	G2_GL_EXT_ARB_texture_buffer_object
,	G2_GL_EXT_ARB_texture_compression
,	G2_GL_EXT_ARB_texture_compression_rgtc
,	G2_GL_EXT_ARB_texture_cube_map
,	G2_GL_EXT_ARB_texture_env_add
,	G2_GL_EXT_ARB_texture_env_combine
,	G2_GL_EXT_ARB_texture_env_crossbar
,	G2_GL_EXT_ARB_texture_env_dot3
,	G2_GL_EXT_ARB_texture_float
,	G2_GL_EXT_ARB_texture_mirrored_repeat
,	G2_GL_EXT_ARB_texture_multisample
,	G2_GL_EXT_ARB_texture_non_power_of_two
,	G2_GL_EXT_ARB_texture_rectangle
,	G2_GL_EXT_ARB_texture_rg
,	G2_GL_EXT_ARB_texture_rgb10_a2ui
,	G2_GL_EXT_ARB_texture_storage
,	G2_GL_EXT_ARB_texture_swizzle
,	G2_GL_EXT_ARB_timer_query
,	G2_GL_EXT_ARB_transform_feedback2
,	G2_GL_EXT_ARB_transform_feedback_instanced
,	G2_GL_EXT_ARB_transpose_matrix
,	G2_GL_EXT_ARB_uniform_buffer_object
,	G2_GL_EXT_ARB_vertex_array_bgra
,	G2_GL_EXT_ARB_vertex_array_object
,	G2_GL_EXT_ARB_vertex_buffer_object
,	G2_GL_EXT_ARB_vertex_program
,	G2_GL_EXT_ARB_vertex_shader
,	G2_GL_EXT_ARB_vertex_type_2_10_10_10_rev
,	G2_GL_EXT_ARB_viewport_array
,	G2_GL_EXT_ARB_window_pos
,	G2_GL_EXT_ATI_draw_buffers
,	G2_GL_EXT_ATI_texture_float
,	G2_GL_EXT_ATI_texture_mirror_once
,	G2_GL_EXT_S3_s3tc
,	G2_GL_EXT_EXT_texture_env_add
,	G2_GL_EXT_EXT_abgr
,	G2_GL_EXT_EXT_bgra
,	G2_GL_EXT_EXT_bindable_uniform
,	G2_GL_EXT_EXT_blend_color
,	G2_GL_EXT_EXT_blend_equation_separate
,	G2_GL_EXT_EXT_blend_func_separate
,	G2_GL_EXT_EXT_blend_minmax
,	G2_GL_EXT_EXT_blend_subtract
,	G2_GL_EXT_EXT_compiled_vertex_array
,	G2_GL_EXT_EXT_Cg_shader
,	G2_GL_EXT_EXT_depth_bounds_test
,	G2_GL_EXT_EXT_direct_state_access
,	G2_GL_EXT_EXT_draw_buffers2
,	G2_GL_EXT_EXT_draw_instanced
,	G2_GL_EXT_EXT_draw_range_elements
,	G2_GL_EXT_EXT_fog_coord
,	G2_GL_EXT_EXT_framebuffer_blit
,	G2_GL_EXT_EXT_framebuffer_multisample
,	G2_GL_EXT_EXTX_framebuffer_mixed_formats
,	G2_GL_EXT_EXT_framebuffer_object
,	G2_GL_EXT_EXT_framebuffer_sRGB
,	G2_GL_EXT_EXT_geometry_shader4
,	G2_GL_EXT_EXT_gpu_program_parameters
,	G2_GL_EXT_EXT_gpu_shader4
,	G2_GL_EXT_EXT_multi_draw_arrays
,	G2_GL_EXT_EXT_packed_depth_stencil
,	G2_GL_EXT_EXT_packed_float
,	G2_GL_EXT_EXT_packed_pixels
,	G2_GL_EXT_EXT_pixel_buffer_object
,	G2_GL_EXT_EXT_point_parameters
,	G2_GL_EXT_EXT_provoking_vertex
,	G2_GL_EXT_EXT_rescale_normal
,	G2_GL_EXT_EXT_secondary_color
,	G2_GL_EXT_EXT_separate_shader_objects
,	G2_GL_EXT_EXT_separate_specular_color
,	G2_GL_EXT_EXT_shadow_funcs
,	G2_GL_EXT_EXT_stencil_two_side
,	G2_GL_EXT_EXT_stencil_wrap
,	G2_GL_EXT_EXT_texture3D
,	G2_GL_EXT_EXT_texture_array
,	G2_GL_EXT_EXT_texture_buffer_object
,	G2_GL_EXT_EXT_texture_compression_dxt1
,	G2_GL_EXT_EXT_texture_compression_latc
,	G2_GL_EXT_EXT_texture_compression_rgtc
,	G2_GL_EXT_EXT_texture_compression_s3tc
,	G2_GL_EXT_EXT_texture_cube_map
,	G2_GL_EXT_EXT_texture_edge_clamp
,	G2_GL_EXT_EXT_texture_env_combine
,	G2_GL_EXT_EXT_texture_env_dot3
,	G2_GL_EXT_EXT_texture_filter_anisotropic
,	G2_GL_EXT_EXT_texture_format_BGRA8888
,	G2_GL_EXT_EXT_texture_integer
,	G2_GL_EXT_EXT_texture_lod
,	G2_GL_EXT_EXT_texture_lod_bias
,	G2_GL_EXT_EXT_texture_mirror_clamp
,	G2_GL_EXT_EXT_texture_object
,	G2_GL_EXT_EXT_texture_shared_exponent
,	G2_GL_EXT_EXT_texture_sRGB
,	G2_GL_EXT_EXT_texture_sRGB_decode
,	G2_GL_EXT_EXT_texture_storage
,	G2_GL_EXT_EXT_texture_swizzle
,	G2_GL_EXT_EXT_texture_type_2_10_10_10_REV
,	G2_GL_EXT_EXT_timer_query
,	G2_GL_EXT_EXT_transform_feedback2
,	G2_GL_EXT_EXT_vertex_array
,	G2_GL_EXT_EXT_vertex_array_bgra
,	G2_GL_EXT_EXT_x11_sync_object
,	G2_GL_EXT_EXT_import_sync_object
,	G2_GL_EXT_IBM_rasterpos_clip
,	G2_GL_EXT_IBM_texture_mirrored_repeat
,	G2_GL_EXT_KTX_buffer_region
,	G2_GL_EXT_NV_alpha_test
,	G2_GL_EXT_NV_blend_minmax
,	G2_GL_EXT_NV_blend_square
,	G2_GL_EXT_NV_complex_primitives
,	G2_GL_EXT_NV_conditional_render
,	G2_GL_EXT_NV_copy_depth_to_color
,	G2_GL_EXT_NV_copy_image
,	G2_GL_EXT_NV_depth_buffer_float
,	G2_GL_EXT_NV_depth_clamp
,	G2_GL_EXT_NV_explicit_multisample
,	G2_GL_EXT_NV_fbo_color_attachments
,	G2_GL_EXT_NV_fence
,	G2_GL_EXT_NV_float_buffer
,	G2_GL_EXT_NV_fog_distance
,	G2_GL_EXT_NV_fragdepth
,	G2_GL_EXT_NV_fragment_program
,	G2_GL_EXT_NV_fragment_program_option
,	G2_GL_EXT_NV_fragment_program2
,	G2_GL_EXT_NV_framebuffer_multisample_coverage
,	G2_GL_EXT_NV_geometry_shader4
,	G2_GL_EXT_NV_gpu_program4
,	G2_GL_EXT_NV_half_float
,	G2_GL_EXT_NV_light_max_exponent
,	G2_GL_EXT_NV_multisample_coverage
,	G2_GL_EXT_NV_multisample_filter_hint
,	G2_GL_EXT_NV_occlusion_query
,	G2_GL_EXT_NV_packed_depth_stencil
,	G2_GL_EXT_NV_parameter_buffer_object
,	G2_GL_EXT_NV_parameter_buffer_object2
,	G2_GL_EXT_NV_path_rendering
,	G2_GL_EXT_NV_pixel_data_range
,	G2_GL_EXT_NV_point_sprite
,	G2_GL_EXT_NV_primitive_restart
,	G2_GL_EXT_NV_register_combiners
,	G2_GL_EXT_NV_register_combiners2
,	G2_GL_EXT_NV_shader_buffer_load
,	G2_GL_EXT_NV_texgen_reflection
,	G2_GL_EXT_NV_texture_barrier
,	G2_GL_EXT_NV_texture_compression_vtc
,	G2_GL_EXT_NV_texture_env_combine4
,	G2_GL_EXT_NV_texture_expand_normal
,	G2_GL_EXT_NV_texture_lod_clamp
,	G2_GL_EXT_NV_texture_multisample
,	G2_GL_EXT_NV_texture_rectangle
,	G2_GL_EXT_NV_texture_shader
,	G2_GL_EXT_NV_texture_shader2
,	G2_GL_EXT_NV_texture_shader3
,	G2_GL_EXT_NV_transform_feedback
,	G2_GL_EXT_NV_transform_feedback2
,	G2_GL_EXT_NV_vdpau_interop
,	G2_GL_EXT_NV_vertex_array_range
,	G2_GL_EXT_NV_vertex_array_range2
,	G2_GL_EXT_NV_vertex_buffer_unified_memory
,	G2_GL_EXT_NV_vertex_program
,	G2_GL_EXT_NV_vertex_program1_1
,	G2_GL_EXT_NV_vertex_program2
,	G2_GL_EXT_NV_vertex_program2_option
,	G2_GL_EXT_NV_vertex_program3
,	G2_GL_EXT_NVX_conditional_render
,	G2_GL_EXT_NVX_gpu_memory_info
,	G2_GL_EXT_OES_depth24
,	G2_GL_EXT_OES_depth32
,	G2_GL_EXT_OES_depth_texture
,	G2_GL_EXT_OES_element_index_uint
,	G2_GL_EXT_OES_fbo_render_mipmap
,	G2_GL_EXT_OES_get_program_binary
,	G2_GL_EXT_OES_mapbuffer
,	G2_GL_EXT_OES_packed_depth_stencil
,	G2_GL_EXT_OES_rgb8_rgba8
,	G2_GL_EXT_OES_standard_derivatives
,	G2_GL_EXT_OES_texture_3D
,	G2_GL_EXT_OES_texture_float
,	G2_GL_EXT_OES_texture_float_linear
,	G2_GL_EXT_OES_texture_half_float
,	G2_GL_EXT_OES_texture_half_float_linear
,	G2_GL_EXT_OES_texture_npot
,	G2_GL_EXT_OES_vertex_array_object
,	G2_GL_EXT_OES_vertex_half_float
,	G2_GL_EXT_SGIS_generate_mipmap
,	G2_GL_EXT_SGIS_texture_lod
,	G2_GL_EXT_SGIX_depth_texture
,	G2_GL_EXT_SGIX_shadow
,	G2_GL_EXT_SUN_slice_accum
,	G2_GL_EXT_MAXN

}g2_gl_extensions_t;

#endif
