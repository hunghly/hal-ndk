#include <iostream>
#include <hardware.h>
#include "hal-ndk.h"
#include <dlfcn.h>

int main()
{
    const hw_module_t* MODULE;
    const char* module_id = "audio";

    std::cout << "Hello World!" << std::endl;
    load_hw(module_id,&MODULE);
    return 0;
}

int load_hw(const char* module_id, const struct hw_module_t** hw_module) {

    std::cout << "Executing LOAD_HW" << std::endl;
    std::cout << "Attempting to load libhardware" << std::endl;

    void* lib_hardware = dlopen("/system/lib/libhardware.so", RTLD_NOW);
    if (!lib_hardware) {
        std::cout << "Error opening libhardware.so" << std::endl;
        return 1;
    }

    return 0;
}