#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "../interface.h"


struct VideoInterface* video_interface_init_sdl2(
    const struct VideoInterfaceInfo* info,
    const struct VideoInterfaceUserCallbacks* callbacks
);

#ifdef __cplusplus
}
#endif
