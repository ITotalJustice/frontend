#include "gui.h"

// this is a bit hacky atm
// this codebase started off as a small wrapper
// around TotalGB which added file loading, zip support
// states, saves etc...
// adding video backends and gui was added after
// because of this, gui and video backend
// don't work well together, as its slapped together

// i plan to change it so gui is the main_loop(), and the
// gui backend is selected at build time (imgui, nogui, ncurses, qt...)

// for now though, its a mess...

#ifdef MGB_GUI
    #include "dearimgui/dearimgui.h"
    #define GUI_INIT dearimgui_init
    #define GUI_EXIT dearimgui_exit
    #define GUI_EVENT dearimgui_event
    #define GUI_RENDER dearimgui_render
#else
    #include "nogui/nogui.h"
    #define GUI_INIT nogui_init
    #define GUI_EXIT nogui_exit
    #define GUI_EVENT nogui_event
    #define GUI_RENDER nogui_render
#endif


bool gui_init(struct mgb* mgb) {
	(void)mgb;
	
    if (!GUI_INIT(160*2, 144*2)) {
        return false;
    }

    // more stuff will go here...
    return true;
}

void gui_exit(struct mgb* mgb) {
	(void)mgb;

    GUI_EXIT();
}

void gui_run(struct mgb* mgb) {
	(void)mgb;
}

void gui_event(struct mgb* mgb, const union VideoInterfaceEvent* e) {
	(void)mgb;
    GUI_EVENT(e);
}

void gui_render(struct mgb* mgb) {
	// todo: select menu
    GUI_RENDER(mgb);
}
