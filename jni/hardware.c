/*
 * Copyright (C) 2008 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <hardware/hardware.h>

#include <cutils/properties.h>

#include <stdio.h>
#include <dlfcn.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>
#include <limits.h>
#include <unistd.h>

#define LOG_TAG "HAL"
// #include <utils/Log.h>

/** Base path of the hal modules */
#define HAL_LIBRARY_PATH1 "/system/lib/hw"
#define HAL_LIBRARY_PATH2 "/vendor/lib/hw"

/**
 * There are a set of variant filename for modules. The form of the filename
 * is "<MODULE_ID>.variant.so" so for the led module the Dream variants 
 * of base "ro.product.board", "ro.board.platform" and "ro.arch" would be:
 *
 * led.trout.so
 * led.msm7k.so
 * led.ARMV6.so
 * led.default.so
 */

static const char *variant_keys[] = {
    "ro.hardware",  /* This goes first so that it can pick up a different
                       file on the emulator. */
    "ro.product.board",
    "ro.board.platform",
    "ro.arch"
};

static const int HAL_VARIANT_KEYS_COUNT =
    (sizeof(variant_keys)/sizeof(variant_keys[0]));

/**
 * Load the file defined by the variant and if successful
 * return the dlopen handle and the hmi.
 * @return 0 = success, !0 = failure.
 */
static int load(const char *id,
        const char *path,
        const struct hw_module_t **pHmi)
{
    int status;
    void *handle;
    struct hw_module_t *hmi;

    /*
     * load the symbols resolving undefined symbols before
     * dlopen returns. Since RTLD_GLOBAL is not or'd in with
     * RTLD_NOW the external symbols will not be global
     */
    printf("Path inside load: %s\n", path);
    handle = dlopen(path, RTLD_NOW);
    if (handle == NULL) {
        char const *err_str = dlerror();
        status = -EINVAL;
        printf("Error found: %s | status: %d", err_str, status);

        goto done;
    }
    printf("Loaded Module. Attempting to get address");
    /* Get the address of the struct hal_module_info. */
    const char *sym = HAL_MODULE_INFO_SYM_AS_STR;
    printf("Sym is: %s\n", sym);
    hmi = (struct hw_module_t *)dlsym(handle, sym);
    if (hmi == NULL) {
        status = -EINVAL;
        printf("Error found in HMI: status: %d\n", status);
        goto done;
    }

    printf("Comparing id with hmi->id: %s | %s\n", id, hmi->id);
    /* Check that the id matches */
    // if (strcmp(id, hmi->id) != 0) {
    //     status = -EINVAL;
    //     goto done;
    // }

    hmi->dso = handle;

    /* success */
    status = 0;

    done:
    if (status != 0) {
        hmi = NULL;
        if (handle != NULL) {
            dlclose(handle);
            handle = NULL;
        }
    } else {
        // ALOGV("loaded HAL id=%s path=%s hmi=%p handle=%p",
        //         id, path, *pHmi, handle);
        printf("loaded HAL id=%s path=%s hmi=%p handle=%p\n",
                id, path, *pHmi, handle);
    }

    *pHmi = hmi;

    return status;
}

int hw_get_module_by_class(const char *class_id, const char *inst,
                           const struct hw_module_t **module)
{
    int status;
    int i;
    const struct hw_module_t *hmi = NULL;
    char prop[PATH_MAX];
    char path[PATH_MAX];
    char name[PATH_MAX];

    if (inst)
        snprintf(name, PATH_MAX, "%s.%s", class_id, inst);
    else
        strlcpy(name, class_id, PATH_MAX);

    printf("Inside of HW Get Module. Name is: %s\n", name);
    void* lib_cutils = dlopen("/system/lib/libcutils.so", RTLD_GLOBAL);
    typedef int (*property_get_t) (const char *key, char *value, const char *default_value);
    property_get_t property_get = (property_get_t) dlsym(lib_cutils, "property_get");


    /*
     * Here we rely on the fact that calling dlopen multiple times on
     * the same .so will simply increment a refcount (and not load
     * a new copy of the library).
     * We also assume that dlopen() is thread-safe.
     */

    /* Loop through the configuration variants looking for a module */
    for (i=0 ; i<HAL_VARIANT_KEYS_COUNT+1 ; i++) {
        if (i < HAL_VARIANT_KEYS_COUNT) {
            if (property_get(variant_keys[i], prop, NULL) == 0) {
                continue;
            }
            printf("Found property! KEY: %s | VALUE: %s\n", variant_keys[i], prop);

            snprintf(path, sizeof(path), "%s/%s.%s.so",
                     HAL_LIBRARY_PATH2, name, prop);
            printf("VProp is: %s\n", prop);
            printf("VPath is: %s\n", path);
            if (access(path, R_OK) == 0) {
                printf("Found\n");
                break;
            }
            snprintf(path, sizeof(path), "%s/%s.%s.so",
                     HAL_LIBRARY_PATH1, name, prop);
            printf("SProp is: %s\n", prop);
            printf("SPath is: %s\n", path);
            if (access(path, R_OK) == 0) {
                printf("Found\n");
                break;
            }
        } else {
            snprintf(path, sizeof(path), "%s/%s.default.so",
                     HAL_LIBRARY_PATH1, name);
            printf("\nDefault Prop is: %s\n", prop);
            printf("Default Path is: %s\n", path);
            if (access(path, R_OK) == 0) {
                printf("Found\n");
                break;
            }
            // Try with primary added to path
            snprintf(path, sizeof(path), "%s/%s.primary.default.so",
                     HAL_LIBRARY_PATH1, name);
            printf("\nDefault Primary Prop is: %s\n", prop);
            printf("Default Primary Path is: %s\n", path);

            if (access(path, R_OK) == 0) {
                printf("Found\n");
                break;
            }

            snprintf(path, sizeof(path), "%s/%s.primary.default.so",
                    HAL_LIBRARY_PATH2, name);
            printf("\nDefault Primary VProp is: %s\n", prop);
            printf("Default Primary VPath is: %s\n", path);
            if (access(path, R_OK) == 0) {
                printf("Found\n");
                break;
            }
        }
    }

    status = -ENOENT;
    if (i < HAL_VARIANT_KEYS_COUNT+1) {
        /* load the module, if this fails, we're doomed, and we should not try
         * to load a different variant. */
        status = load(class_id, path, module);
        printf("File Found Status at: %s is %d\n", path, status);
    }

    return status;
}

int hw_get_module(const char *id, const struct hw_module_t **module)
{
    return hw_get_module_by_class(id, NULL, module);
}
