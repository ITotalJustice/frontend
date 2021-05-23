#include "cfile.h"

#include <stdlib.h>

#define PRIVATE_TO_CTX ctx_t* ctx = (ctx_t*)_private

// if we are using sdl, then might as well use sdlrwops
// the added benifit here rwops just work (tm) with android assets
#ifdef MGB_SDL

#include <SDL_rwops.h>

typedef SDL_RWops ctx_t;

static void internal_close(void* _private) {
    PRIVATE_TO_CTX;

    SDL_RWclose(ctx);
}

static bool internal_read(void* _private, void* data, size_t len) {
    PRIVATE_TO_CTX;

    const size_t result = SDL_RWread(ctx, data, len, 1);

    return result == 1;
}

static bool internal_write(void* _private, const void* data, size_t len) {
    PRIVATE_TO_CTX;

    const size_t result = SDL_RWwrite(ctx, data, len, 1);

    return result == 1;
}

static bool internal_seek(void* _private, long offset, int whence) {
    PRIVATE_TO_CTX;

    const Sint64 result = SDL_RWseek(ctx, offset, whence);

    return result != -1;
}

static size_t internal_tell(void* _private) {
    PRIVATE_TO_CTX;

    const Sint64 result = SDL_RWtell(ctx);

    if (result < 0) {
        return 0;
    }

    return (size_t)result;
}

static size_t internal_size(void* _private) {
    PRIVATE_TO_CTX;

    const Sint64 file_size = SDL_RWsize(ctx);

    if (file_size < 0) {
        return 0;
    }

    return (size_t)file_size;
}

IFile_t* icfile_open(const char* file, enum IFileMode mode) {
    IFile_t* ifile = NULL;
    ctx_t* ctx = NULL;

    ifile = malloc(sizeof(IFile_t));

    if (!ifile) {
        goto fail;
    }

    const char* modes[] = {
        [IFileMode_READ] = "rb",
        [IFileMode_WRITE] = "wb",
        [IFileMode_APPEND] = "ab",
    };

    ctx = SDL_RWFromFile(file, modes[mode]);

    if (!ctx) {
        goto fail;
    }

    const IFile_t _ifile = {
        ._private = ctx,
        .close  = internal_close,
        .read   = internal_read,
        .write  = internal_write,
        .seek   = internal_seek,
        .tell   = internal_tell,
        .size   = internal_size,
    };

    // copy the above struct
    *ifile = _ifile;

    return ifile;

fail:
    if (ifile) {
        free(ifile);
    }

    return NULL;
}

#else

#include <stdio.h>

typedef FILE ctx_t;


static void internal_close(void* _private) {
    PRIVATE_TO_CTX;

    fclose(ctx);
}

static bool internal_read(void* _private, void* data, size_t len) {
    PRIVATE_TO_CTX;

    const size_t result = fread(data, len, 1, ctx);

    return result == 1;
}

static bool internal_write(void* _private, const void* data, size_t len) {
    PRIVATE_TO_CTX;

    const size_t result = fwrite(data, len, 1, ctx);

    return result == 1;
}

static bool internal_seek(void* _private, long offset, int whence) {
    PRIVATE_TO_CTX;

    const int result = fseek(ctx, offset, whence);

    return result == 0;
}

static size_t internal_tell(void* _private) {
    PRIVATE_TO_CTX;

    const long result = ftell(ctx);

    if (result < 0) {
        return 0;
    }

    return (size_t)result;
}

static size_t internal_size(void* _private) {
    PRIVATE_TO_CTX;

    const size_t old_offset = internal_tell(ctx);
    internal_seek(ctx, 0, SEEK_END);
    const long file_size = internal_tell(ctx);
    internal_seek(ctx, old_offset, SEEK_SET);

    if (file_size < 0) {
        return 0;
    }

    return (size_t)file_size;
}

IFile_t* icfile_open(const char* file, enum IFileMode mode) {
    IFile_t* ifile = malloc(sizeof(IFile_t));

    // if this ever fails, we have less than 56 bytes of mem
    if (!ifile) {
        exit(-1);
    }

    const char* modes[] = {
        [IFileMode_READ] = "rb",
        [IFileMode_WRITE] = "wb",
        [IFileMode_APPEND] = "ab",
    };

    ctx_t* ctx = fopen(file, modes[mode]);

    if (!ctx) {
        goto fail;
    }

    // i create the struct this way as the compiler will warn if
    // new entries are added, but are not filled out below.
    // same idea as always using switch() on enums
    const IFile_t _ifile = {
        ._private = ctx,
        .close  = internal_close,
        .read   = internal_read,
        .write  = internal_write,
        .seek   = internal_seek,
        .tell   = internal_tell,
        .size   = internal_size,
    };

    // copy the above struct
    *ifile = _ifile;

    return ifile;

fail:
    if (ifile) {
        free(ifile);
    }

    return NULL;
}

#endif // MGB_SDL
