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

    std::cout << "Attempting to load libhardware" << std::endl;
    const char* LIBHARDWARE_DIR = "/system/lib64/libhardware.so\0";
    const char* HW_GET_MODULE = "hw_get_module";

    // declare ptr to function called hw_get_module_t with two params
    typedef int (*hw_get_module_t) (const char*, const struct hw_module_t**); 

    void* lib_hardware = dlopen(LIBHARDWARE_DIR, RTLD_NOW);

    std::cout << "printing: "<< lib_hardware << std::endl;

    if (!lib_hardware) {
        std::cout << "Error opening libhardware.so" << std::endl;
        return 1;
    }

    std::cout << "Libhardware loaded. Gathering Funcs" << std::endl;
    hw_get_module_t hw_get_module = (hw_get_module_t) dlsym(lib_hardware, HW_GET_MODULE);

    if (!hw_get_module) {
        std::cout << "Error getting funcs" << std::endl;
        dlclose(lib_hardware);
        return 1;
    }
    std::cout << "Funcs gathered. gathering modules" << std::endl;

    int status = hw_get_module(module_id, hw_module);

    if (status != 0) {
        std::cout << "Error getting module" << std::endl;
        dlclose(lib_hardware);
        return 1;
    }

    std::cout << "Complete getting module" << std::endl;
    dlclose(lib_hardware);

    return 0;
}