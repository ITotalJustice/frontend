#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

union VideoInterfaceEvent;
struct mgb;

bool nogui_init(int w, int h);
void nogui_exit();
void nogui_event(const union VideoInterfaceEvent* e);
void nogui_render(struct mgb* mgb);

#ifdef __cplusplus
}
#endif
