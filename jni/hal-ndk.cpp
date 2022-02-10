#include <iostream>
#include <hardware.h>
#include "hal-ndk.h"

int main()
{
    std::cout << "Hello World!" << std::endl;
    return 0;
}

int load_hw(const char* module_id, const struct hw_module_t** hw_module) {

    std::cout << "Executing LOAD_HW" << std::endl;
    
    return 0;
}