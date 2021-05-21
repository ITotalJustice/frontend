// my custom wrapper, simpiler to the sdl2 impl
#pragma once

#include "imgui.h"


extern "C" union VideoInterfaceEvent;


namespace im {

bool ImGui_ImplMGB_Init(int w, int h, int display_w, int display_h);
void ImGui_ImplMGB_Shutdown();
void ImGui_ImplMGB_RenderBegin();
void ImGui_ImplMGB_RenderEnd();
void ImGui_ImplMGB_RenderDemo();
bool ImGui_ImplMGB_Event(const union VideoInterfaceEvent* e);

ImVec2 ScaleVec2(int x, int y);
ImVec4 ScaleVec4(int x, int y, int w, int h);

int Width();
int Height();

float ScaleW(int w);
float ScaleH(int h);

float ScaleW();
float ScaleH();

} // namespace im
