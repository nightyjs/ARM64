#include "gpu.h"
#include <stdio.h>
#include <stdint.h>
#include <emscripten.h>

EM_JS(void, js_mali_gl_clear, (uint32_t mask), {
  if (typeof gpu !== 'undefined') gpu.mali_gl_clear(mask);
});

EM_JS(void, js_mali_gl_finish, (), {
  if (typeof gpu !== 'undefined') gpu.mali_gl_finish();
});

EM_JS(void, js_mali_gl_flush, (), {
  if (typeof gpu !== 'undefined') gpu.mali_gl_flush();
});

EM_JS(void, js_mali_gl_use_program, (int id), {
  if (typeof gpu !== 'undefined') gpu.mali_gl_use_program(id);
});

EM_JS(void, js_mali_gl_bind_vertex_array, (int id), {
  if (typeof gpu !== 'undefined') gpu.mali_gl_bind_vertex_array(id);
});

EM_JS(void, js_mali_gl_draw_arrays, (uint32_t mode, int first, int count), {
  if (typeof gpu !== 'undefined') gpu.mali_gl_draw_arrays(mode, first, count);
});

EM_JS(void, js_mali_gl_viewport, (int x, int y, int w, int h), {
  if (typeof gpu !== 'undefined') gpu.mali_gl_viewport(x, y, w, h);
});

EM_JS(void, js_mali_gl_clear_color, (float r, float g, float b, float a), {
  if (typeof gpu !== 'undefined') gpu.mali_gl_clear_color(r, g, b, a);
});

// --- LÓGICA DE ESCRITURA MMIO ---

void gpu_mmio_write(uint32_t offset, uint32_t value) {
    switch (offset) {
        case 0x00: js_mali_gl_clear(value); break;
        case 0x04: js_mali_gl_finish(); break;
        case 0x08: js_mali_gl_flush(); break;
        case 0x0C: js_mali_gl_use_program(value); break;
        case 0x10: js_mali_gl_bind_vertex_array(value); break;
        
        case 0x14: {
            uint32_t* params = (uint32_t*)(uintptr_t)value;
            js_mali_gl_draw_arrays(params[0], params[1], params[2]);
            break;
        }
        case 0x18: {
            int* v = (int*)(uintptr_t)value;
            js_mali_gl_viewport(v[0], v[1], v[2], v[3]);
            break;
        }
        case 0x1C: {
            float* c = (float*)(uintptr_t)value;
            js_mali_gl_clear_color(c[0], c[1], c[2], c[3]);
            break;
        }
    }
}

void gpu_init() {
    js_mali_gl_finish();
}