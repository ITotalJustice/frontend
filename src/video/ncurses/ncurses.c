// don't use this, its a POC, only supports GB

#include "ncurses.h"

#include <stdbool.h>
#include <stdlib.h>
#include <ncurses.h>


#define WIDTH 160
#define HEIGHT 144

#define CC_BLACK        COLOR_BLACK
#define CC_LIGHT_BLACK  COLOR_RED
#define CC_DARK_WHITE   COLOR_GREEN
#define CC_WHITE        COLOR_WHITE

static int counter = 0;

enum
{
    CPAIR_BLACK = 1,
    CPAIR_LIGHT_BLACK,
    CPAIR_DARK_WHITE,
    CPAIR_WHITE,
};


static void internal_quit(void* _private)
{
    endwin();
}

static void internal_render_begin(void* _private)
{
}

static void internal_render_game(void* _private)
{
}

static void internal_render_end(void* _private)
{
    refresh();

    const struct timespec sleep_time =
    {
       .tv_sec = 0,
       .tv_nsec = 166666660L,
    };

    // nanosleep(&sleep_time, NULL);
}

#define C(c) (((c >> 19) & 0x1F)) | (((c >> 11) & 0x1F) << 5) | (((c >> 3) & 0x1F) << 10)

enum
{
   COL0 = C(0xF7E7C6),
   COL1 = C(0xD68E49),
   COL2 = C(0xA63725),
   COL3 = C(0x331E50) 
};

static void render(const uint16_t* pixels, int col, uint16_t COL)
{
    move(0, 0);
    attron(COLOR_PAIR(col + 1));

    for (int y = 0; y < HEIGHT; ++y)
    {

        for (int x = 0; x < WIDTH; ++x)
        {
            if (pixels[y * WIDTH + x] == COL)
            {
                mvaddch(y, x * 2 + 0, ' ');
                mvaddch(y, x * 2 + 1, ' ');
            }
        }
    }

    attroff(COLOR_PAIR(col + 1));
}

static void internal_update_game_texture(
    void* _private,
    const struct VideoInterfaceGameTexture* game_texture
) {
    static const uint16_t colours[] =
    {
        [3] = C(0xF7E7C6),
        [2] = C(0xD68E49),
        [1] = C(0xA63725),
        [0] = C(0x331E50) 
    };

    ++counter;
    if (counter < 10)
    {
        return;
    }
    counter = 0;
    render(game_texture->pixels, 0, colours[0]);
    render(game_texture->pixels, 1, colours[1]);
    render(game_texture->pixels, 2, colours[2]);
    render(game_texture->pixels, 3, colours[3]);
}

static void internal_poll_events(void* _private)
{
}

static void internal_toggle_fullscreen(void* _private)
{
}

static void internal_set_window_name(void* _private, const char* name) {
}

struct VideoInterface* video_interface_init_ncurses(
    const struct VideoInterfaceInfo* info,
    void* user, void (*on_event)(void*, const union VideoInterfaceEvent*)
) {
    struct VideoInterface* iface = NULL;

    iface = malloc(sizeof(struct VideoInterface));

    if (!iface)
    {
        return NULL;
    }

    const struct VideoInterface internal_interface =
    {
        ._private               = NULL,
        .quit                   = internal_quit,
        .render_begin           = internal_render_begin,
        .render_game            = internal_render_game,
        .render_end             = internal_render_end,
        .update_game_texture    = internal_update_game_texture,
        .poll_events            = internal_poll_events,
        .toggle_fullscreen      = internal_toggle_fullscreen,
        .set_window_name        = internal_set_window_name,
    };

    *iface = internal_interface;

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    if (has_colors() == FALSE)
    {
        goto fail;
    }

    start_color();

    #define CC_BLACK        COLOR_BLACK
    #define CC_LIGHT_BLACK  COLOR_RED
    #define CC_DARK_WHITE   COLOR_GREEN
    #define CC_WHITE        COLOR_WHITE

    init_color(CC_BLACK, 0, 0, 0);
    init_color(CC_LIGHT_BLACK, 250, 250, 250);
    init_color(CC_DARK_WHITE, 500, 500, 500);
    init_color(CC_WHITE, 800, 800, 800);

    init_pair(CPAIR_BLACK, CC_BLACK, CC_BLACK);
    init_pair(CPAIR_LIGHT_BLACK, CC_LIGHT_BLACK, CC_LIGHT_BLACK);
    init_pair(CPAIR_DARK_WHITE, CC_DARK_WHITE, CC_DARK_WHITE);
    init_pair(CPAIR_WHITE, CC_WHITE, CC_WHITE);

    return iface;

fail:
    internal_quit(NULL);
    return NULL;
}
