mergeInto(LibraryManager.library, {
    mali_gl_clear: function(mask) { mali.mali_gl_clear(mask); },
    mali_gl_clear_color: function(r, g, b, a) { mali.mali_gl_clear_color(r, g, b, a); },
    mali_gl_viewport: function(x, y, w, h) { mali.mali_gl_viewport(x, y, w, h); },
    mali_gl_use_program: function(id) { mali.mali_gl_use_program(id); },
    mali_gl_bind_vertex_array: function(id) { mali.mali_gl_bind_vertex_array(id); },
    mali_gl_draw_arrays: function(mode, first, count) { mali.mali_gl_draw_arrays(mode, first, count); },
    mali_gl_finish: function() { mali.mali_gl_finish(); },
    mali_gl_flush: function() { mali.mali_gl_flush(); },
});