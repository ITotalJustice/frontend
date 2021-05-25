// don't use this yet!

#include "../interface.h"

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <caca.h>


#define BPP     16
#define WIDTH   160
#define HEIGHT  144
#define STRIDE  (WIDTH * sizeof(uint16_t))
#define RMASK   (0x001F << 11)
#define GMASK   (0x001F << 6)
#define BMASK   (0x001F << 1)
#define AMASK   (0x0000)

static caca_canvas_t* canvas = NULL;
static caca_display_t* display = NULL;
static caca_dither_t* dither = NULL;
static int xoff = 0;
static int yoff = 0;
static int width = 0;
static int height = 0;
static void* user_data = NULL;
static void (*user_event)(void*, const union VideoInterfaceEvent*);
static int render = 1;


static void on_quit_event()
{
    const union VideoInterfaceEvent event =
    {
        .quit =
        {
            .type = VideoInterfaceEventType_QUIT,
            .reason = VideoInterfaceQuitReason_DEFAULT
        }
    };

    user_event(user_data, &event);
}

static void on_resize_event(caca_event_t* e)
{
    width = caca_get_event_resize_width(e);
    height = caca_get_event_resize_height(e);
}

static void on_key_event(caca_event_t* e, bool down)
{
    switch (caca_get_event_key_ch(e))
    {
        case 'x':
        case 'X':
            {
                const union VideoInterfaceEvent event =
                {
                    .key =
                    {
                        .type = VideoInterfaceEventType_KEY,
                        .key = VideoInterfaceKey_X,
                        .mod = 0,
                        .down = down,
                    }
                };

                user_event(user_data, &event);
            }
            break;

        case 'z':
        case 'Z':
            {
                const union VideoInterfaceEvent event =
                {
                    .key =
                    {
                        .type = VideoInterfaceEventType_KEY,
                        .key = VideoInterfaceKey_Z,
                        .mod = 0,
                        .down = down,
                    }
                };

                user_event(user_data, &event);
            }
            printf("press: B\n");
            break;

        case 0x1B:
        case CACA_KEY_CTRL_C:
            printf("press: ctrl-c\n");
            on_quit_event();
            break;

        case CACA_KEY_UP:
            printf("press: UP\n");
            if (down)
            render = 1;
            break;

        case CACA_KEY_DOWN:
            printf("press: DOWN\n");
            break;

        case CACA_KEY_LEFT:
            printf("press: LEFT\n");
            break;

        case CACA_KEY_RIGHT:
            printf("press: RIGHT\n");
            break;
    }
}


static void internal_quit(void* _private)
{
    if (dither)
    {
        caca_free_dither(dither);
    }

    if (display)
    {
        caca_free_display(display);
    }

    if (canvas)
    {
        caca_free_canvas(canvas);
    }

    dither = NULL;
    display = NULL;
    canvas = NULL;

}

static void internal_render_begin(void* _private)
{
}

static void internal_render_game(void* _private)
{
}

static void internal_render_end(void* _private)
{
    caca_refresh_display(display);

    const struct timespec sleep_time =
    {
       .tv_sec = 0,
       .tv_nsec = 166666L,
    };

    // nanosleep(&sleep_time, NULL);
}

static void internal_update_game_texture(
    void* _private,
    const struct VideoInterfaceGameTexture* game_texture
) {
    if (render)
    {
        static uint16_t pixels[144][160][2];

        for (size_t y = 0; y < 144; ++y)
        {
            for (size_t x = 0; x < 160; ++x)
            {
                pixels[y][x][0] = game_texture->pixels[y*160+x];
                pixels[y][x][1] = game_texture->pixels[y*160+x];
            }
        }
        caca_dither_bitmap(canvas, xoff, yoff, WIDTH*2, HEIGHT, dither, pixels);

        render = 0;
    }
}

static void internal_poll_events(void* _private)
{
    caca_event_t e;

    while (caca_get_event(display, CACA_EVENT_ANY, &e, 0))
    {
        switch (e.type)
        {
            case CACA_EVENT_NONE:
                return;

            case CACA_EVENT_KEY_PRESS:
            case CACA_EVENT_KEY_RELEASE:
                on_key_event(&e, e.type == CACA_EVENT_KEY_PRESS);
                break;

            case CACA_EVENT_RESIZE:
                on_resize_event(&e);
                break;

            case CACA_EVENT_QUIT:
                on_quit_event();
                return;
        }
    }
}

static void internal_toggle_fullscreen(void* _private)
{
}

static void internal_set_window_name(
    void* _private,
    const char* name
) {
    caca_set_display_title(display, name);
}

struct VideoInterface* video_interface_init_caca(
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

    canvas = caca_create_canvas(0, 0);

    if (!canvas)
    {
        goto fail;
    }

    display = caca_create_display(canvas);

    if (!display)
    {
        goto fail;
    }

    dither = caca_create_dither(
        BPP, WIDTH*2, HEIGHT, STRIDE*2,
        RMASK, GMASK, BMASK, AMASK
    );

    if (!dither)
    {
        goto fail;
    }

    width = caca_get_canvas_width(canvas);
    height = caca_get_canvas_height(canvas);

    user_data = user;
    user_event = on_event;

    return iface;

fail:
    internal_quit(NULL);
    return NULL;
}
