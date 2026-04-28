class LibARM64 {
    constructor(wasmPath, libMaliInstance) {
        this.wasmPath = wasmPath;
        this.mali = libMaliInstance;
        this.instance = null;
    }

    async init() {
        const response = await fetch(this.wasmPath);
        const bytes = await response.arrayBuffer();
        
        const imports = {
            env: {
                ...this.mali.getBridge(),
                memory: new WebAssembly.Memory({ initial: 256, maximum: 4096 }),
                abort: () => console.error("WASM Aborted")
            }
        };

        const { instance } = await WebAssembly.instantiate(bytes, imports);
        this.instance = instance;

        const ptr = this.instance.exports.get_wasm_memory_ptr();
        this.mali.linkMemory(this.instance.exports.memory);

        this.instance.exports.vertex_boot();
        console.log("LibARM64: Sistema iniciado y vinculado a libMALI.");
    }

    step(cycles = 1000) {
        this.instance.exports.vertex_run_frame(cycles);
    }
}

window.LibARM64 = LibARM64;