class LibMali {
    constructor(canvasElement) {
        if (!(canvasElement instanceof HTMLCanvasElement)) {
            throw new Error("libMALI: Valid HTMLCanvasElement required.");
        }

        this.canvas = canvasElement;
        const glOptions = {
            alpha: false,
            depth: true,
            stencil: true,
            antialias: true,
            premultipliedAlpha: false,
            preserveDrawingBuffer: false,
            powerPreference: "high-performance",
            failIfMajorPerformanceCaveat: false
        };

        this.gl = this.canvas.getContext("webgl2", glOptions);
        if (!this.gl) {
            throw new Error("libMALI: WebGL2 context (GLES 3.0) could not be initialized.");
        }

        
        this.memory = null;
        this.resources = {
            buffers: new Map(),
            textures: new Map(),
            programs: new Map(),
            shaders: new Map(),
            vaos: new Map(),
            framebuffers: new Map(),
            renderbuffers: new Map(),
            queries: new Map(),
            samplers: new Map(),
            syncs: new Map(),
            transformFeedbacks: new Map()
        };

        this._nextId = 1;
        console.log("libMALI: Driver initialized. Targeting OpenGL ES 3.0+");
    }

    linkMemory(wasmMemory) {
        this.memory = wasmMemory;
    }

    _view(ptr, length, type = Uint8Array) {
        return new type(this.memory.buffer, ptr, length);
    }

    _genId() {
        return this._nextId++;
    }

    getBridge() {
        const gl = this.gl;
        const r = this.resources;

        return {
            
            mali_gl_clear: (mask) => gl.clear(mask),
            mali_gl_clear_color: (r, g, b, a) => gl.clearColor(r, g, b, a),
            mali_gl_viewport: (x, y, w, h) => gl.viewport(x, y, w, h),

            
            mali_gl_create_buffer: () => {
                const id = this._genId();
                r.buffers.set(id, gl.createBuffer());
                return id;
            },
            mali_gl_bind_buffer: (target, id) => {
                gl.bindBuffer(target, id ? r.buffers.get(id) : null);
            },
            mali_gl_buffer_data: (target, size, dataPtr, usage) => {
                const data = dataPtr ? this._view(dataPtr, size) : size;
                gl.bufferData(target, data, usage);
            },
            mali_gl_buffer_sub_data: (target, offset, size, dataPtr) => {
                gl.bufferSubData(target, offset, this._view(dataPtr, size));
            },

            mali_gl_create_shader: (type) => {
                const id = this._genId();
                r.shaders.set(id, gl.createShader(type));
                return id;
            },
            mali_gl_shader_source: (id, sourcePtr, length) => {
                const source = new TextDecoder().decode(this._view(sourcePtr, length));
                gl.shaderSource(r.shaders.get(id), source);
            },
            mali_gl_compile_shader: (id) => gl.compileShader(r.shaders.get(id)),
            mali_gl_create_program: () => {
                const id = this._genId();
                r.programs.set(id, gl.createProgram());
                return id;
            },
            mali_gl_attach_shader: (progId, shaderId) => {
                gl.attachShader(r.programs.get(progId), r.shaders.get(shaderId));
            },
            mali_gl_link_program: (id) => gl.linkProgram(r.programs.get(id)),
            mali_gl_use_program: (id) => gl.useProgram(id ? r.programs.get(id) : null),

            mali_gl_create_texture: () => {
                const id = this._genId();
                r.textures.set(id, gl.createTexture());
                return id;
            },
            mali_gl_bind_texture: (target, id) => {
                gl.bindTexture(target, id ? r.textures.get(id) : null);
            },
            mali_gl_tex_image_2d: (target, level, internalformat, width, height, border, format, type, dataPtr) => {
                const data = dataPtr ? this._view(dataPtr, 0) : null;
                gl.texImage2D(target, level, internalformat, width, height, border, format, type, data);
            },

            mali_gl_gen_vertex_arrays: () => {
                const id = this._genId();
                r.vaos.set(id, gl.createVertexArray());
                return id;
            },
            mali_gl_bind_vertex_array: (id) => {
                gl.bindVertexArray(id ? r.vaos.get(id) : null);
            },

            mali_gl_draw_arrays: (mode, first, count) => {
                gl.drawArrays(mode, first, count);
            },
            mali_gl_draw_elements: (mode, count, type, offset) => {
                gl.drawElements(mode, count, type, offset);
            },
            mali_gl_draw_arrays_instanced: (mode, first, count, instanceCount) => {
                gl.drawArraysInstanced(mode, first, count, instanceCount);
            },
            mali_gl_draw_elements_instanced: (mode, count, type, offset, instanceCount) => {
                gl.drawElementsInstanced(mode, count, type, offset, instanceCount);
            },

            mali_gl_get_uniform_location: (progId, namePtr, nameLen) => {
                const name = new TextDecoder().decode(this._view(namePtr, nameLen));
                const loc = gl.getUniformLocation(r.programs.get(progId), name);
                if (!loc) return -1;
                const id = this._genId();
                this.resources.queries.set(id, loc); 
                return id;
            },
            mali_gl_uniform_matrix_4fv: (locId, transpose, dataPtr) => {
                gl.uniformMatrix4fv(this.resources.queries.get(locId), transpose, this._view(dataPtr, 16, Float32Array));
            },

            mali_gl_finish: () => gl.finish(),
            mali_gl_flush: () => gl.flush(),
        };
    }
}

window.LibMali = LibMali;