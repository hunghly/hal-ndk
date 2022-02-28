#include <iostream>
#include <hardware/hardware.h>
#include <hardware/audio.h>
#include "hal-ndk.h"
#include <dlfcn.h>

int main()
{
    const hw_module_t* MODULE;
    const char* module_id = "audio";

    load_hw(module_id,&MODULE);
    return 0;
}

int load_hw(const char* module_id, const struct hw_module_t** hw_module) {

    std::cout << "Attempting to load libhardware" << std::endl;
    const char* LIBHARDWARE_DIR = "/system/lib/libhardware.so\0";
    const char* HW_GET_MODULE = "hw_get_module";

    // declare ptr to function called hw_get_module with two params
    typedef int (*hw_get_module_t) (const char*, const struct hw_module_t**); 

    // void* lib_hardware = dlopen(LIBHARDWARE_DIR, RTLD_NOW);
    // void* libaudio = dlopen("/system/lib/hw/audio.primary.default.so", RTLD_GLOBAL);

    // std::cout << "Printing LibHardware: "<< lib_hardware << std::endl;

    // if (!lib_hardware) {
    //     std::cout << "Error opening libhardware.so" << std::endl;
    //     return 1;
    // }
    // if (!libaudio) {
    //     std::cout << "Error opening audio.primary.default.so" << std::endl;
    //     return 1;
    // }

    // load cutils
    // void* lib_cutils = dlopen("/system/lib/libcutils.so", RTLD_GLOBAL);
    // typedef int (*property_get_t) (const char *key, char *value, const char *default_value);
    // property_get_t property_get = (property_get_t) dlsym(lib_cutils, "property_get");

    // hw_get_module_t hw_get_module = (hw_get_module_t) dlsym(lib_hardware, HW_GET_MODULE);
    int status = hw_get_module(module_id, hw_module);
    // std::cout << "Libhardware loaded. Gathering HW_GET_MODULE Function." << std::endl;
    // hw_get_module_t hw_get_module = (hw_get_module_t) dlsym(lib_hardware, HW_GET_MODULE);
    // std::cout << "Printing hw_get_module: " << hw_get_module << std::endl;
    // if (!hw_get_module) {
    //     std::cout << "Error getting funcs" << std::endl;
    //     dlclose(lib_hardware);
    //     return 1;
    // }
    std::cout << "Functions gathered. Gathering module " << module_id << std::endl;
    // int status = hw_get_module("gps", hw_module);
    std::cout << "hw_module:" << *hw_module << std::endl;
    std::cout << "hw_module tag:" << (*hw_module)->tag << std::endl;
    std::cout << "hw_module Module API Version: " << (*hw_module)->module_api_version << std::endl;
    std::cout << "hw_module HAL API Version: " << (*hw_module)->hal_api_version << std::endl;
    std::cout << "hw_module id:" << (*hw_module)->id << std::endl;
    std::cout << "hw_module name:" << (*hw_module)->name << std::endl;
    std::cout << "hw_module author:" << (*hw_module)->author << std::endl;
    std::cout << "hw_module name:" << (*hw_module)->name << std::endl;
    std::cout << "hw_module dso:" << (*hw_module)->dso << std::endl;
    // hw_device_t* device_open;
    // std::cout << "hw_module methods:" << (*hw_module)->init_check(device_open) << std::endl;
    
    // hw_device_t** device_open;
    // std::cout << "hw_module opening?:" << (*hw_module)->methods->open(*hw_module, AUDIO_HARDWARE_INTERFACE, device_open) << std::endl;


    std::cout << "Status:" << status << std::endl;
    if (status != 0) {
        std::cout << "Error getting module" << std::endl;
        // dlclose(lib_hardware);
        return 1;
    }

    hw_device_t* device;
    status = (*hw_module)->methods->open(*hw_module, AUDIO_HARDWARE_INTERFACE, &device);
    if (status != 0) {
        std::cout << "Error opening interface" << std::endl;
        // dlclose(lib_hardware);
        return 1;
    }
    audio_hw_device_t* audio_device_itf = (audio_hw_device_t*)device;

    status = audio_device_itf->init_check(audio_device_itf);
    if (status != 0) {
        std::cout << "Audio Interface was not initiated." << status << std::endl;
        return 0;
    }

    std::cout << "Success: Audio Interface initiated." << std::endl;
    std::cout << "audio_device_itf:" << audio_device_itf << std::endl;
    std::cout << "audio_device_itf tag:" << ((hw_device_t*) audio_device_itf)->tag << std::endl;
    std::cout << "audio_device_itf version:" << ((hw_device_t*) audio_device_itf)->version << std::endl;
    // std::cout << "audio_device_itf Module API Version: " << (*audio_device_itf)->module_api_version << std::endl;
    // std::cout << "audio_device_itf HAL API Version: " << (*audio_device_itf)->hal_api_version << std::endl;
    // std::cout << "audio_device_itf id:" << (*audio_device_itf)->id << std::endl;
    // std::cout << "audio_device_itf name:" << (*audio_device_itf)->name << std::endl;
    // std::cout << "audio_device_itf author:" << (*audio_device_itf)->author << std::endl;
    // std::cout << "audio_device_itf name:" << (*audio_device_itf)->name << std::endl;
    // std::cout << "audio_device_itf dso:" << (*audio_device_itf)->dso << std::endl;
    // Try to get the audio supported devices
    std::cout << "Searching for supported devices." << std::endl;
    // int sup_devices = audio_device_itf->get_supported_devices(audio_device_itf);
    // std::cout << "Support devices int: " << sup_devices << std::endl;


    float myvolume = 0.0;
    float* vol = &myvolume;
    bool mystate = true;
    
    // std::cout << "Initial Error" << status << std::endl;
    // std::cout << "Audio Volume Before myvolume=" << myvolume << " volptr=" << *vol << std::endl;
    // status = audio_device_itf->get_master_volume(audio_device_itf, vol);
    // std::cout << "Getting Audio Volume Error? " << status << std::endl;
    // std::cout << "Audio Volume myvolume=" << myvolume << " volptr=" << *vol << std::endl;










/*
    hw_module_t** audio_module; 
    *audio_module = (struct hw_module_t *) dlsym(libaudio, HAL_MODULE_INFO_SYM_AS_STR);

    // Print Hardware information
    std::cout << "\n==== Hardware Information ====:" << std::endl;
    std::cout << "Module API Version: " << (*audio_module)->module_api_version << std::endl;
    std::cout << "HAL API Version: " << (*audio_module)->hal_api_version << std::endl;

    // Print audio module information
    std::cout << "\n==== Audio Information ====:" << std::endl;
    std::cout << "audio_module:" << *audio_module << std::endl;
    std::cout << "audio_module name:" << (*audio_module)->name << std::endl;
    std::cout << "audio_module id:" << (*audio_module)->id << std::endl;
    std::cout << "audio_module author:" << (*audio_module)->author << std::endl;
    std::cout << "audio_module dso:" << (*audio_module)->dso << std::endl;
*/

/*
    // Attempt to get the device methods and do some work**update later**

    int err;
    hw_device_t* device;
    float myvolume = 0.0;
    float* vol = &myvolume;
    bool mystate = true;
    

    std::cout << "Opening Audio Device" << std::endl;
    err = (*audio_module)->methods->open(*audio_module, AUDIO_HARDWARE_INTERFACE, &device);
    if (!err) {
        std::cout << "Device Opened. Retrieving Interface" << std::endl;
        audio_hw_device_t* audio_device_itf = (audio_hw_device_t*)device;
        if (audio_device_itf) {
            std::cout << "Audio Interface retrieved. Checking if hardware interface is initiated" << std::endl;
            err = audio_device_itf->init_check(audio_device_itf);
            if (err) {
                std::cout << "Audio Interface was not initiated." << err << std::endl;
                return 0;
            }
            std::cout << "Success: Audio Interface initiated." << std::endl;

            // Try to get the audio supported devices
            std::cout << "Searching for supported devices." << std::endl;
            // int sup_devices = audio_device_itf->get_supported_devices(audio_device_itf);
            // std::cout << "Support devices int: " << sup_devices << std::endl;

            // std::cout << "Initial Error" << err << std::endl;
            // std::cout << "Audio Volume Before myvolume=" << myvolume << " volptr=" << *vol << std::endl;
            // err = audio_device_itf->get_master_volume(audio_device_itf, vol);
            // std::cout << "Getting Audio Volume Error? " << err << std::endl;
            // std::cout << "Audio Volume myvolume=" << myvolume << " volptr=" << *vol << std::endl;

            // err = audio_device_itf->set_master_mute(audio_device_itf, mystate);
            // std::cout << "Error getting state?? " << err << std::endl;
            // std::cout << "State is " << mystate << std::endl;

            // std::cout << "tag" << audio_device_itf->common.tag << std::endl;



            // close the interface/device
            std::cout << "Closing interface and device" << std::endl;
            err = audio_device_itf->common.close(device);
            std::cout << "Error closing? " << err << std::endl;
        }
    } else {
        std::cout << "Error while opening module" << err << std::endl;
    }
*/

    std::cout << "Complete getting module" << std::endl;

    // dlclose(lib_hardware);

    return 0;
}