#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
    
union VideoInterfaceEvent;
struct mgb;

bool dearimgui_init(int w, int h);
void dearimgui_exit();
void dearimgui_event(const union VideoInterfaceEvent* e);
void dearimgui_render(struct mgb* mgb);

#ifdef __cplusplus
}
#endif
