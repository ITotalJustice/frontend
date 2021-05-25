#include "interface.h"

#include <stdlib.h>
#include <assert.h>


#ifdef MGB_VIDEO_BACKEND_SDL1
    #include "sdl1/sdl1.h"
    #define VIDEO_INTERFACE_INIT video_interface_init_sdl1
#elif MGB_VIDEO_BACKEND_SDL1_OPENGL
    #include "sdl1/sdl1_opengl.h"
    #define VIDEO_INTERFACE_INIT video_interface_init_sdl1_opengl
#elif MGB_VIDEO_BACKEND_SDL2
    #include "sdl2/sdl2.h"
    #define VIDEO_INTERFACE_INIT video_interface_init_sdl2
#elif MGB_VIDEO_BACKEND_SDL2_OPENGL
    #include "sdl2/sdl2_opengl.h"
    #define VIDEO_INTERFACE_INIT video_interface_init_sdl2_opengl
#elif MGB_VIDEO_BACKEND_CACA
    #include "caca/caca.h"
    #define VIDEO_INTERFACE_INIT video_interface_init_caca
#elif MGB_VIDEO_BACKEND_NCURSES
    #include "ncurses/ncurses.h"
    #define VIDEO_INTERFACE_INIT video_interface_init_ncurses
#else
    #error "NO VIDEO BACKEND SELECTED FOR MGB!"
#endif


struct VideoInterface* video_interface_init(
    const struct VideoInterfaceInfo* info,
    void* user, void (*on_event)(void*, const union VideoInterfaceEvent*)
) {
    return VIDEO_INTERFACE_INIT(info, user, on_event);
}

void video_interface_quit(
    struct VideoInterface* self
) {
    assert(self->quit);
    self->quit(self->_private);
    free(self);
}

void video_interface_render_begin(
    struct VideoInterface* self
) {
    assert(self->render_begin);
    self->render_begin(self->_private);
}

void video_interface_render_game(
    struct VideoInterface* self
) {
    assert(self->render_game);
    self->render_game(self->_private);
}

void video_interface_render_end(
    struct VideoInterface* self
) {
    assert(self->render_end);
    self->render_end(self->_private);
}

void video_interface_update_game_texture(
    struct VideoInterface* self,
    const struct VideoInterfaceGameTexture* game_texture
) {
    assert(self->update_game_texture);
    self->update_game_texture(self->_private, game_texture);
}

void video_interface_poll_events(
    struct VideoInterface* self
) {
    assert(self->poll_events);
    self->poll_events(self->_private);
}

void video_interface_toggle_fullscreen(
    struct VideoInterface* self
) {
    assert(self->toggle_fullscreen);
    self->toggle_fullscreen(self->_private);
}

void video_interface_set_window_name(
    struct VideoInterface* self,
    const char* name
) {
    assert(self->set_window_name);
    self->set_window_name(self->_private, name);
}
