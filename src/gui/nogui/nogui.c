#include "nogui.h"
#include "../../mgb.h"


bool nogui_init(int w, int h) {
    (void)w; (void)h;
    return true;
}

void nogui_exit() {

}

void nogui_event(const union VideoInterfaceEvent* e) {
    (void)e;
}

void nogui_render(struct mgb* mgb) {
    (void)mgb;
}
