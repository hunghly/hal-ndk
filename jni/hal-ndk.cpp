#include <iostream>
#include <hardware/hardware.h>
#include <hardware/audio.h>
#include <system/audio.h>
#include "hal-ndk.h"
#include <dlfcn.h>
#include <ostream>


int main()
{
    const hw_module_t* MODULE;
    const char* module_id = "audio";
    int status;

    load_module(module_id,&MODULE);


    hw_device_t* device;    
    status = MODULE->methods->open(MODULE, AUDIO_HARDWARE_INTERFACE, &device);
    if (status != 0) {
        std::cout << "Error opening interface" << std::endl;
        // dlclose(lib_hardware);
        return 0;
    }
    std::cout << "Device opened. Checking initiation." << std::endl;

    audio_hw_device_t* audio_device_itf = (audio_hw_device_t*)device;

    if (audio_device_itf) {
        status = audio_device_itf->init_check(audio_device_itf);
        if (status != 0) {
            std::cout << "Audio Interface was not initiated." << status << std::endl;
            return 0;
        } else {
            std::cout << "Success: Audio Interface initiated." << std::endl;
        }
    }


    // Try to get the audio supported devices
    /* Example: 3222405119 converts to:
        1100 0000 0001 0001 1111 1111 1111 1111
        All AUDIO_DEVICE_OUT and the default reserved bits
        Use check_bit() to see if a particular device is supported.
        For example, AUDIO_DEVICE_OUT_BLUETOOTH_SCO is 0x10 i.e. 5th bit
    */
    audio_devices_t supported_devices = audio_device_itf->get_supported_devices(audio_device_itf);
    if (!supported_devices) {
        std::cout << "Error getting supported devices" << status << std::endl;
        return 0;
    } else {
        std::cout << "Retrieved supported devices." << supported_devices << std::endl;
        std::cout << "Support devices" << supported_devices << std::endl;
        // int n = supported_devices >> 1;
        // std::cout << "AUDIO_DEVICE_OUT_EARPIECE: " << checkBit(supported_devices, 1) << std::endl;
        // std::cout << "AUDIO_DEVICE_OUT_BLUETOOTH_A2DP_SPEAKER: " << checkBit(supported_devices, 4) << std::endl;
    }

    // audio_config
    // struct audio_config {
    //     uint32_t sample_rate;
    //     audio_channel_mask_t channel_mask;
    //     audio_format_t  format;
    // };

    audio_config_t config {
        .sample_rate = 10,
        .channel_mask = AUDIO_CHANNEL_OUT_STEREO,
        .format = AUDIO_FORMAT_PCM_16_BIT,
    };

    audio_stream_out_t** out_stream;

    std::cout << config.format << std::endl;

    status = audio_device_itf->open_output_stream(audio_device_itf, 1, supported_devices, AUDIO_OUTPUT_FLAG_NONE, &config, out_stream);
    if (status != 0) {
        std::cout << "Error opening output stream." << status << std::endl;
        return 0;
    } else {
        std::cout << "Stream opened." << status << std::endl;
        audio_device_itf->close_output_stream(audio_device_itf, *out_stream);
        // if (status != 0) {
        //     std::cout << "Error closing output stream." << status << std::endl;
        // } else {
        std::cout << "Output stream closed." << status << std::endl;
        // }
    }


    // Try to set mode
    /*
    typedef enum {
        AUDIO_MODE_INVALID          = -2,
        AUDIO_MODE_CURRENT          = -1,
        AUDIO_MODE_NORMAL           = 0,
        AUDIO_MODE_RINGTONE         = 1,
        AUDIO_MODE_IN_CALL          = 2,
        AUDIO_MODE_IN_COMMUNICATION = 3,

        AUDIO_MODE_CNT,
        AUDIO_MODE_MAX              = AUDIO_MODE_CNT - 1,
    } audio_mode_t;
    */
    // status = audio_device_itf->set_mode(audio_device_itf, (audio_mode_t) 0);
    // if (status != 0) {
    //     std::cout << "Error setting mode." << status << std::endl;
    //     return 0;
    // } else {
    //     std::cout << "Mode updated." << status << std::endl;
    // }


    // Try to open output stream
    // status = audio_device_itf->open_output_stream(audio_device_itf, 1, );
    // if (status != 0) {
    //     std::cout << "Error setting Master volume." << status << std::endl;
    //     return 0;
    // } else {
    //     std::cout << "Master volume updated." << status << std::endl;
    // }


    // Try to set audio volume
    // status = audio_device_itf->set_master_volume(audio_device_itf, .9);
    // if (status != 0) {
    //     std::cout << "Error setting Master volume." << status << std::endl;
    //     return 0;
    // } else {
    //     std::cout << "Master volume updated." << status << std::endl;
    // }

    // Try to mute volume
    // status = audio_device_itf->set_master_mute(audio_device_itf, 1);
    // if (status != 0) {
    //     std::cout << "Error muting volume." << status << std::endl;
    //     return 0;
    // } else {
    //     std::cout << "Master mute updated." << status << std::endl;
    // }

    // Close the audio device
    status = audio_device_itf->common.close(device);
    if (status != 0) {
        std::cout << "Error closing audio device." << status << std::endl;
        return 0;
    } else {
        std::cout << "Audio device closed." << status << std::endl;
    }
  
    std::cout << "Complete getting module" << std::endl;

    return 0;
}

int load_module(const char* module_id, const struct hw_module_t** hw_module) {


    int status = hw_get_module(module_id, hw_module);

    if (status != 0) {
        std::cout << "Error getting module" << std::endl;
        return -1;
    }

    print_module_info(&(*hw_module));
    return 0;
}

/* Checks k-th bit to see if it is set, returns non-zero value if bit is set
*/
int check_bit(uint32_t n, int k) {
    int temp = 1 << (k-1);
    int set = n & temp;
    if (set != 0) {
        std::cout << "Set for bit at K: " << k << std::endl;
    } else {
        std::cout << "Unset for bit at K: " << k << std::endl;
    }
    return set;
}

void print_module_info(const struct hw_module_t** hw_module) {
        std::cout << "\nHW_MODULE INFORMATION" << std::endl;
        std::cout << "----------------------------" << std::endl;
        std::cout << "hw_module address location:" << *hw_module << std::endl;
        std::cout << "hw_module tag:" << (*hw_module)->tag << std::endl;
        std::cout << "hw_module Module API Version: " << (*hw_module)->module_api_version << std::endl;
        std::cout << "hw_module HAL API Version: " << (*hw_module)->hal_api_version << std::endl;
        std::cout << "hw_module id:" << (*hw_module)->id << std::endl;
        std::cout << "hw_module name:" << (*hw_module)->name << std::endl;
        std::cout << "hw_module author:" << (*hw_module)->author << std::endl;
        std::cout << "hw_module name:" << (*hw_module)->name << std::endl;
        std::cout << "hw_module dso:" << (*hw_module)->dso << std::endl;
}



    // std::cout << "Attempting to load libhardware" << std::endl;
    // const char* LIBHARDWARE_DIR = "/system/lib/libhardware.so\0";
    // const char* HW_GET_MODULE = "hw_get_module";

    // declare ptr to function called hw_get_module with two params
    // typedef int (*hw_get_module_t) (const char*, const struct hw_module_t**); 

    // void* lib_hardware = dlopen(LIBHARDWARE_DIR, RTLD_NOW);

    // if (!lib_hardware) {
    //     std::cout << "Error opening libhardware.so" << std::endl;
    //     return 1;
    // }

    // load cutils
    // void* lib_cutils = dlopen("/system/lib/libcutils.so", RTLD_GLOBAL);
    // typedef int (*property_get_t) (const char *key, char *value, const char *default_value);
    // property_get_t property_get = (property_get_t) dlsym(lib_cutils, "property_get");

    // hw_get_module_t hw_get_module = (hw_get_module_t) dlsym(lib_hardware, HW_GET_MODULE);


        // std::cout << "Libhardware loaded. Gathering HW_GET_MODULE Function." << std::endl;
    // hw_get_module_t hw_get_module = (hw_get_module_t) dlsym(lib_hardware, HW_GET_MODULE);
    // std::cout << "Printing hw_get_module: " << hw_get_module << std::endl;
    // if (!hw_get_module) {
    //     std::cout << "Error getting funcs" << std::endl;
    //     dlclose(lib_hardware);
    //     return 1;
    // }

            // dlclose(lib_hardware);


  // audio_device_itf->get_devices_for_stream(audio_device_itf, AUDIO_STREAM_SYSTEM);


    // std::cout << "audio_device_itf:" << audio_device_itf << std::endl;
    // std::cout << "audio_device_itf tag:" << ((hw_device_t*) audio_device_itf)->tag << std::endl;
    // std::cout << "audio_device_itf version:" << ((hw_device_t*) audio_device_itf)->version << std::endl;
    // std::cout << "audio_device_itf tag2:" << audio_device_itf->common.tag << std::endl;
    // std::cout << "audio_device_itf version2:" << audio_device_itf->common.version << std::endl;


    // float myvolume = 0;
    // float* vol = &myvolume;
    // bool mystate = true;
    
    // std::cout << "Initial Error" << status << std::endl;
    // std::cout << "Audio Volume Before myvolume=" << myvolume << " volptr=" << *vol << std::endl;
    // status = audio_device_itf->set_master_volume(audio_device_itf, 0);
    // std::cout << "Getting Audio Volume Error? " << status << std::endl;
    // std::cout << "Audio Volume myvolume=" << myvolume << " volptr=" << *vol << std::endl;



    // status = audio_device_itf->common.close(device);
    // std::cout << "Error closing? " << status << std::endl;



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
