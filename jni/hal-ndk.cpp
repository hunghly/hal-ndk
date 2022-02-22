#include <iostream>
#include <hardware/hardware.h>
#include "hal-ndk.h"
#include <dlfcn.h>

int main()
{
    const hw_module_t* MODULE;
    const char* module_id = "gps";

    std::cout << "Hello World!" << std::endl;
    load_hw(module_id,&MODULE);
    return 0;
}

int load_hw(const char* module_id, const struct hw_module_t** hw_module) {

    std::cout << "Attempting to load libhardware" << std::endl;
    const char* LIBHARDWARE_DIR = "/system/lib64/libhardware.so\0";
    const char* HW_GET_MODULE = "hw_get_module";

    // declare ptr to function called hw_get_module with two params
    typedef int (*hw_get_module_t) (const char*, const struct hw_module_t**); 

    void* lib_hardware = dlopen(LIBHARDWARE_DIR, RTLD_NOW);

    std::cout << "printing: "<< lib_hardware << std::endl;

    if (!lib_hardware) {
        std::cout << "Error opening libhardware.so" << std::endl;
        return 1;
    }

    std::cout << "Libhardware loaded. Gathering Funcs" << std::endl;
    hw_get_module_t hw_get_module = (hw_get_module_t) dlsym(lib_hardware, HW_GET_MODULE);
    // int (*module1) (const char*, const struct hw_module_t**);
    
//    module1 = (int*) dlsym(lib_hardware, HW_GET_MODULE);

    // if (!module1) {
    if (!hw_get_module) {
        std::cout << "Error getting funcs" << std::endl;
        dlclose(lib_hardware);
        return 1;
    }

    // std::cout << "Address location of HW_GET_MODULE:" << module1 << std::endl;
    std::cout << "Funcs gathered. gathering modules" << std::endl;

    int status = hw_get_module("audio_policy", hw_module);
    // int status = module1(module_id, hw_module);
    // hw_module_methods_t test;

    std::cout << "status:" << status << std::endl;
    if (status != 0) {
        std::cout << "Error getting module" << std::endl;
        dlclose(lib_hardware);
        return 1;
    }

    std::cout << "Complete getting module" << std::endl;
    // std::cout << "Testing Audio Header Echo" << AUDIO_PARAMETER_VALUE_HAC_ON << std::endl;

    dlclose(lib_hardware);

    return 0;
}