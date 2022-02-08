APP_OPTIM := debug    # Build the target in debug mode. 
APP_ABI := all # Define the target architecture to be ARM.
APP_STL := c++_shared
APP_CPPFLAGS := -frtti -fexceptions \
-std=c++17   # This is the place you enable exception.
APP_PLATFORM := android-19 # Define the target Android version of the native application.