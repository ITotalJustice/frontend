#include "sdl2.h"
#include "base/base.h"


typedef struct Ctx
{
    struct Base base;

    SDL_Renderer* renderer;
    SDL_Texture* texture;
} ctx_t;

#define VOID_TO_SELF(_private) ctx_t* self = (ctx_t*)_private;


static void internal_quit(void* _private)
{
    VOID_TO_SELF(_private);

    if (SDL_WasInit(SDL_INIT_VIDEO))
    {
        if (self->texture)
        {
            SDL_DestroyTexture(self->texture);
        }

        if (self->renderer)
        {
            SDL_DestroyRenderer(self->renderer);
        }

        base_sdl2_exit(&self->base);
    }

    SDL_free(self);
}

static void internal_render_begin(void* _private)
{
    VOID_TO_SELF(_private);

    SDL_RenderClear(self->renderer);
    
}

static void internal_render_game(void* _private)
{
    VOID_TO_SELF(_private);

    SDL_RenderCopy(self->renderer, self->texture, NULL, NULL);
}

static void internal_render_end(void* _private)
{
    VOID_TO_SELF(_private);

    SDL_RenderPresent(self->renderer);
}

static void internal_update_game_texture(
    void* _private,
    const struct VideoInterfaceGameTexture* game_texture
) {
    VOID_TO_SELF(_private);

    void* pixels; int pitch;

    SDL_LockTexture(self->texture, NULL, &pixels, &pitch);
    memcpy(pixels, game_texture->pixels, 160*144*2);
    SDL_UnlockTexture(self->texture);
}

static void internal_poll_events(void* _private)
{
    VOID_TO_SELF(_private);

    base_sdl2_poll_events(&self->base);
}

static void internal_toggle_fullscreen(void* _private)
{
    VOID_TO_SELF(_private);

    base_sdl2_toggle_fullscreen(&self->base);
}

static void internal_set_window_name(void* _private,const char* name)
{
    VOID_TO_SELF(_private);

    base_sdl2_set_window_name(&self->base, name);
}

static void on_resize(void* _private, int w, int h)
{
    (void)_private; (void)w; (void)h;
}

struct VideoInterface* video_interface_init_sdl2(
    const struct VideoInterfaceInfo* info,
    void* user, void (*on_event)(void*, const union VideoInterfaceEvent*)
) {
    struct VideoInterface* iface = NULL;
    ctx_t* self = NULL;

    iface = malloc(sizeof(struct VideoInterface));
    self = SDL_malloc(sizeof(struct Ctx));

    if (!iface)
    {
        goto fail;
    }

    if (!self)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s\n\n", SDL_GetError());
        goto fail;
    }

    const struct VideoInterface internal_interface =
    {
        ._private               = self,
        .quit                   = internal_quit,
        .render_begin           = internal_render_begin,
        .render_game            = internal_render_game,
        .render_end             = internal_render_end,
        .update_game_texture    = internal_update_game_texture,
        .poll_events            = internal_poll_events,
        .toggle_fullscreen      = internal_toggle_fullscreen,
        .set_window_name        = internal_set_window_name,
    };

    // set the internal data!
    *iface = internal_interface;

    const struct BaseConfig base_config =
    {
        .callbacks =
        {
            .user = self,
            .on_resize = on_resize
        },
        .user = user,
        .on_event = on_event,
        .window_name = info->window_name,
        .window_flags = SDL_WINDOW_RESIZABLE,
        .x = SDL_WINDOWPOS_CENTERED,
        .y = SDL_WINDOWPOS_CENTERED,
        .w = info->w,
        .h = info->h,
        
        .min_win_w = 160,
        .min_win_h = 144,

        .max_win_w = 0,
        .max_win_h = 0,

        .set_min_win = true,
        .set_max_win = false
    };

    if (!base_sdl2_init_system(&self->base))
    {
        goto fail;
    }

    if (!base_sdl2_init_window(&self->base, &base_config))
    {
        goto fail;
    }

    const int render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

    self->renderer = SDL_CreateRenderer(self->base.window, -1, render_flags);

    if (!self->renderer)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s\n", SDL_GetError());
        goto fail;
    }

    // try and enable blending
    if (SDL_SetRenderDrawBlendMode(self->renderer, SDL_BLENDMODE_BLEND))
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s\n", SDL_GetError());
    }

    self->texture = SDL_CreateTexture(
        self->renderer,
        SDL_PIXELFORMAT_BGR555, SDL_TEXTUREACCESS_STREAMING,
        160, 144
        // game_info.w, game_info.h
    );

    if (!self->texture)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s\n", SDL_GetError());
        goto fail;
    }

    return iface;

fail:
    if (iface)
    {
        free(iface);
        iface = NULL;
    }

    if (self)
    {
        internal_quit(self);
    }

    return NULL;
}
