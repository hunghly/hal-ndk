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
    const char* LIBHARDWARE_DIR = "/system/lib64/libhardware.so\0";

    std::cout << LIBHARDWARE_DIR << std::endl;

    void* lib_hardware = dlopen(LIBHARDWARE_DIR, RTLD_NOW);

    std::cout << "printing: "<< lib_hardware << std::endl;

    if (!lib_hardware) {
        std::cout << "Error opening libhardware.so" << std::endl;
        return 1;
    }

    std::cout << "Libhardware loaded" << std::endl;

    return 0;
}