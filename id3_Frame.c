/*
//  id3_Frame.c
//  acid3
//
//  Created by Christopher Loonam on 9/17/15.
//  Copyright (c) 2015 Christopher Loonam. All rights reserved.
*/

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "id3_Frame.h"
#include "id3_Error.h"

struct id3_Frame
{
    const char *id;
    uint32_t size;
    char flags[2];
    char *data;
    id3_Frame *next;
};

extern id3_Bool isBitEnabled(char flag, int bit);

id3_Frame *id3_FrameCreate()
{
    id3_Frame *frame = calloc(1, sizeof(id3_Frame));
    return frame;
}

void id3_FrameSetID(id3_Frame *f, const char *id)
{
    f->id = strdup(id);
}

void id3_FrameSetSize(id3_Frame *f, uint32_t sz)
{
    f->size = sz;
}

void id3_FrameSetFlags(id3_Frame *f, const char *flgs)
{
    f->flags[0] = flgs[0], f->flags[1] = flgs[1];
}

void id3_FrameSetData(id3_Frame *f, char *dat)
{
    f->data = strdup(dat);
}

const char *id3_FrameGetID(id3_Frame *f)
{
    return f->id;
}

uint32_t id3_FrameGetSize(id3_Frame *f)
{
    return f->size;
}

const char *id3_FrameGetFlags(id3_Frame *f)
{
    return f->flags;
}

const char *id3_FrameGetData(id3_Frame *f)
{
    return f->data;
}

void id3_FrameFree(id3_Frame *f)
{
    free(f->data);
    free((char *)f->id);
    if (f->next)
        id3_FrameFree(f->next);
    free(f);
}

id3_Bool id3_FrameShouldBePreservedTagAlter(id3_Frame *f)
{
    return isBitEnabled(f->flags[0], 7);
}

id3_Bool id3_FrameShouldBePreservedFileAlter(id3_Frame *f)
{
    return isBitEnabled(f->flags[0], 6);
}

id3_Bool id3_FrameIsReadOnly(id3_Frame *f)
{
    return isBitEnabled(f->flags[0], 5);
}

id3_Bool id3_FrameIsCompressed(id3_Frame *f)
{
    return isBitEnabled(f->flags[1], 7);
}

id3_Bool id3_FrameIsEncrypted(id3_Frame *f)
{
    return isBitEnabled(f->flags[1], 6);
}

id3_Bool id3_FrameHasGroupingIdentity(id3_Frame *f)
{
    return isBitEnabled(f->flags[1], 5);
}


