#include "gui.h"
#include "imgui_wrapper.hpp"
#include "menu/menu.hpp"


bool gui_init(struct mgb* mgb) {
	(void)mgb;
	
	if (!im::ImGui_ImplMGB_Init(160*2, 144*2, 160*2, 144*2)) {
    	return false;
    }

    // more stuff will go here...
    return true;
}

void gui_exit(struct mgb* mgb) {
	(void)mgb;
    im::ImGui_ImplMGB_Shutdown();
}

void gui_run(struct mgb* mgb) {
	(void)mgb;
}

void gui_event(struct mgb* mgb, const union VideoInterfaceEvent* e) {
	(void)mgb;
	im::ImGui_ImplMGB_Event(e);
}

void gui_render(struct mgb* mgb) {
	// todo: select menu
	im::ImGui_ImplMGB_RenderBegin();
	menu::Main(mgb);
	im::ImGui_ImplMGB_RenderEnd();
}
