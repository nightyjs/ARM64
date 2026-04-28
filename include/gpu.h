#ifndef GPU_H
#define GPU_H

#include <stdint.h>

//libMALI.js configuration
extern void mali_gl_clear(uint32_t mask);
extern void mali_gl_clear_color(float r, float g, float b, float a);
extern void mali_gl_viewport(int x, int y, int w, int h);
extern int  mali_gl_create_buffer();
extern void mali_gl_bind_buffer(uint32_t target, int id);
extern void mali_gl_buffer_data(uint32_t target, int size, int dataPtr, uint32_t usage);
extern void mali_gl_buffer_sub_data(uint32_t target, int offset, int size, int dataPtr);
extern int  mali_gl_create_shader(uint32_t type);
extern void mali_gl_shader_source(int id, int sourcePtr, int length);
extern void mali_gl_compile_shader(int id);
extern int  mali_gl_create_program();
extern void mali_gl_attach_shader(int progId, int shaderId);
extern void mali_gl_link_program(int id);
extern void mali_gl_use_program(int id);
extern int  mali_gl_create_texture();
extern void mali_gl_bind_texture(uint32_t target, int id);
extern void mali_gl_tex_image_2d(uint32_t target, int level, int internalformat, int width, int height, int border, uint32_t format, uint32_t type, int dataPtr);
extern int  mali_gl_gen_vertex_arrays();
extern void mali_gl_bind_vertex_array(int id);
extern void mali_gl_draw_arrays(uint32_t mode, int first, int count);
extern void mali_gl_draw_elements(uint32_t mode, int count, uint32_t type, int offset);
extern int  mali_gl_get_uniform_location(int progId, int namePtr, int nameLen);
extern void mali_gl_uniform_matrix_4fv(int locId, int transpose, int dataPtr);
extern void mali_gl_finish();
extern void mali_gl_flush();

void gpu_init();
void gpu_mmio_write(uint32_t offset, uint32_t value);

#endif