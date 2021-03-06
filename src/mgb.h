#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "mgb.h"
#include "types.h"
#include "util.h"

#include "video/interface.h"
#include "audio/interface.h"

// #include "../../TotalGB/src/gb.h"
// #include "../../TotalGB/src/extras/zrom.h"
#include <gb.h>


enum MgbState {
	// all inputs will be sent to gui, core is paused
	MgbState_GUI,
	// all inputs will be sent to core
	MgbState_CORE,
};

typedef struct mgb {
	struct VideoInterface* video_interface;
    struct AudioInterface* audio_interface;

    uint16_t core_pixels[GB_SCREEN_WIDTH * GB_SCREEN_HEIGHT];

    // todo: make below stuff into a struct
	struct GB_Core* gameboy;

    uint8_t* rom_data;
    size_t rom_size;

    struct SafeString rom_path;

    struct SafeString custom_save_path;
    struct SafeString custom_rtc_path;
    struct SafeString custom_state_path;
	
	enum MgbState state;

	bool rom_loaded;
	bool running;
} mgb_t;

bool mgb_init(mgb_t* self);
void mgb_exit(mgb_t* self);
void mgb_loop(mgb_t* self);

bool mgb_load_rom_filedialog(mgb_t* self);
bool mgb_load_rom_file(mgb_t* self, const char* path);
bool mgb_load_rom_data(mgb_t* self,
    const char* path, const uint8_t* data, size_t size
);

bool mgb_savestate(mgb_t* self);
bool mgb_savestate_filedialog(mgb_t* self);
bool mgb_savestate_file(mgb_t* self, const char* path);

bool mgb_loadstate(mgb_t* self);
bool mgb_loadstate_filedialog(mgb_t* self);
bool mgb_loadstate_file(mgb_t* self, const char* path);

bool mgb_load_save_file(mgb_t* self, const char* path);
bool mgb_load_rtc_file(mgb_t* self, const char* path);
bool mgb_load_state_file(mgb_t* self, const char* path);

bool mgb_load_save_data(mgb_t* self, const uint8_t* data, size_t size);
bool mgb_load_rtc_data(mgb_t* self, const uint8_t* data, size_t size);
bool mgb_load_state_data(mgb_t* self, const uint8_t* data, size_t size);

bool mgb_write_save_file(mgb_t* self, const char* path);
bool mgb_write_rtc_file(mgb_t* self, const char* path);
bool mgb_write_state_file(mgb_t* self, const char* path);

#ifdef __cplusplus
}
#endif
