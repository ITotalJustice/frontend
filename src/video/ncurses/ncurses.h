#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "../interface.h"


struct VideoInterface* video_interface_init_ncurses(
    const struct VideoInterfaceInfo* info,
    void* user, void (*on_event)(void*, const union VideoInterfaceEvent*)
);

#ifdef __cplusplus
}
#endif
