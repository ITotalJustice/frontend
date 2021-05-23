#pragma once

#ifdef __cplusplus
extern "C" {
#endif


#include <stdbool.h>


struct mgb;
union VideoInterfaceEvent;


enum GuiMenu {
	GuiMenu_MAIN,
	GuiMenu_LOADROM,
	GuiMenu_CORE_SETTINGS,
	GuiMenu_GUI_SETTINGS,
	GuiMenu_HELP,
};

enum GuiMainMenuOptions {
	GuiMainMenuOptions_LOADROM,
	GuiMainMenuOptions_CORE_SETTINGS,
	GuiMainMenuOptions_GUI_SETTINGS,
	GuiMainMenuOptions_HELP,
	GuiMainMenuOptions_QUIT,
};

struct GuiMainMenuData {
	bool stub;
};

union GuiMenuData {
	struct GuiMainMenuData main;
};

struct Gui {
	int window_w, window_h;
	int viewport_w, viewport_h;

	enum GuiMenu menu;

	union GuiMenuData data;
};


bool gui_init(struct mgb* mgb);
void gui_exit(struct mgb* mgb);

void gui_run(struct mgb* self);
void gui_event(struct mgb* mgb, const union VideoInterfaceEvent* e);
void gui_render(struct mgb* self);

#ifdef __cplusplus
}
#endif
