
#define LOG_TAG "CameraWrapper"
#include <cutils/log.h>
#include <cutils/native_handle.h>
#include <utils/threads.h>
#include <utils/String8.h>
#include <sensor/SensorManager.h>
#include <hardware/hardware.h>
#include <hardware/camera.h>
#include <camera/Camera.h>
#include <camera/CameraParameters.h>
#include <media/hardware/HardwareAPI.h> // For VideoNativeHandleMetadata
#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>



static int load(
        camera_module_t **pCamera)
{
    int status = -EINVAL;
    void *handle = NULL;
    struct hw_module_t *hmi = NULL;

    handle = dlopen("/system/lib/hw/camera.msm8996.so", RTLD_NOW);

   /* Get the address of the struct hal_module_info. */
    const char *sym = HAL_MODULE_INFO_SYM_AS_STR;
    *pCamera = (camera_module_t *)dlsym(handle, sym);
    if (pCamera == NULL){
	return -EINVAL;
    }
    return 0;
}

int main(int argc,char **argv){
    camera_module_t *cModule;
    if (0 != load(&cModule)){
	printf("Failed to load module\n");
	return 1;
    }
    printf("There are actually %d camera\n", cModule->get_number_of_cameras());
    struct camera_info camInfo;
    if ( 0 != cModule->get_camera_info(1, &camInfo)){
      printf("Failed to get cameraInformation");
      return 1;
    }   
    return 0;
}
