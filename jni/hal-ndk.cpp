#include <iostream>
#include <hardware/hardware.h>
#include <hardware/audio.h>
#include "hal-ndk.h"
#include <dlfcn.h>

int main()
{
    const hw_module_t* MODULE;
    const char* module_id = "audio.primary";

    load_hw(module_id,&MODULE);
    return 0;
}

int load_hw(const char* module_id, const struct hw_module_t** hw_module) {

    std::cout << "Attempting to load libhardware" << std::endl;
    const char* LIBHARDWARE_DIR = "/system/lib/libhardware.so\0";
    const char* HW_GET_MODULE = "hw_get_module";

    // declare ptr to function called hw_get_module with two params
    typedef int (*hw_get_module_t) (const char*, const struct hw_module_t**); 

    void* lib_hardware = dlopen(LIBHARDWARE_DIR, RTLD_NOW);
    void* libaudio = dlopen("/system/lib/hw/audio.primary.default.so", RTLD_GLOBAL);

    std::cout << "Printing LibHardware: "<< lib_hardware << std::endl;

    if (!lib_hardware) {
        std::cout << "Error opening libhardware.so" << std::endl;
        return 1;
    }
    if (!libaudio) {
        std::cout << "Error opening audio.primary.default.so" << std::endl;
        return 1;
    }

    *hw_module = (struct hw_module_t *) dlsym(libaudio, HAL_MODULE_INFO_SYM_AS_STR);

    std::cout << "hw_module:" << *hw_module << std::endl;
    std::cout << "hw_module name:" << (*hw_module)->name << std::endl;
    std::cout << "hw_module id:" << (*hw_module)->id << std::endl;
    
    // std::cout << "Status:" << status << std::endl;

    // std::cout << "Libhardware loaded. Gathering HW_GET_MODULE Function." << std::endl;
    // hw_get_module_t hw_get_module = (hw_get_module_t) dlsym(lib_hardware, HW_GET_MODULE);
    // std::cout << "Printing hw_get_module: " << hw_get_module << std::endl;
    // if (!hw_get_module) {
    //     std::cout << "Error getting funcs" << std::endl;
    //     dlclose(lib_hardware);
    //     return 1;
    // }
    // std::cout << "Functions gathered. Gathering module " << module_id << std::endl;
    // int status = hw_get_module(module_id, hw_module);
    // std::cout << "hw_module:" << *hw_module << std::endl;
    // std::cout << "hw_module name:" << (*hw_module)->name << std::endl;
    // std::cout << "hw_module id:" << (*hw_module)->id << std::endl;
    // std::cout << "Status:" << status << std::endl;
    // if (status != 0) {
    //     std::cout << "Error getting module" << std::endl;
    //     dlclose(lib_hardware);
    //     return 1;
    // }

    std::cout << "Complete getting module" << std::endl;

    dlclose(lib_hardware);

    return 0;
}