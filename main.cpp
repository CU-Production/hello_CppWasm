#include "wasm3_cpp.h"
#include <iostream>
#include <fstream>

int sum(int a, int b)
{
    return a + b;
}

void * ext_memcpy (void* dst, const void* arg, int32_t size)
{
    return memcpy(dst, arg, (size_t) size);
}


int main() {
    std::cout << "Loading WebAssembly..." << std::endl;

    wasm3::environment env;
    wasm3::runtime runtime = env.new_runtime(8*1024);
    const char* file_name = "wasm/test_prog.wasm";
    std::ifstream wasm_file(file_name, std::ios::binary | std::ios::in);
    if (!wasm_file.is_open())
    {
        std::cout << "Failed to open wasm file!" << std::endl;
        return EXIT_FAILURE;
    }
    wasm3::module wasm_module = env.parse_module(wasm_file);
    runtime.load(wasm_module);

    wasm_module.link("*", "sum", sum);

    {
        wasm3::function test_fn = runtime.find_function("test");
        auto res = test_fn.call<int>(20, 10);
        std::cout << "result: " << res << std::endl;
    }

    /**
         * Calling functions that modify an internal state, with mixed argument / return types
         */
    {
        wasm3::function counter_get_fn = runtime.find_function("test_counter_get");
        wasm3::function counter_inc_fn = runtime.find_function("test_counter_inc");
        wasm3::function counter_add_fn = runtime.find_function("test_counter_add");

        // call with no arguments and a return value
        auto value = counter_get_fn.call<int32_t>();
        std::cout << "counter: " << value << std::endl;

        // call with no arguments and no return value
        counter_inc_fn.call();
        value = counter_get_fn.call<int32_t>();
        std::cout << "counter after increment: " << value << std::endl;

        // call with one argument and no return value
        counter_add_fn.call(42);
        value = counter_get_fn.call<int32_t>();
        std::cout << "counter after adding value: " << value << std::endl;
    }
    {
        wasm3::function test_add = runtime.find_function("test_add");
        int value = test_add.call<int32_t>(4, 5);
        std::cout << "test_add(4, 5): " << value << std::endl;
    }
    {
        wasm3::function test_mul = runtime.find_function("test_mul");
        int value = test_mul.call<int32_t>(4, 5);
        std::cout << "test_mul(4, 5): " << value << std::endl;
    }

    return 0;
}
