/*
//  id3_Frame.h
//  acid3
//
//  Created by Christopher Loonam on 9/17/15.
//  Copyright (c) 2015 Christopher Loonam. All rights reserved.
*/

#ifndef __acid3__id3_Frame__
#define __acid3__id3_Frame__

#include <stdio.h>
#include <stdint.h>

#ifndef id3_Bool
#define id3_Bool signed char
#endif

typedef struct id3_Frame id3_Frame;

id3_Frame *id3_FrameCreate();

void id3_FrameSetID(id3_Frame *, const char *);
void id3_FrameSetSize(id3_Frame *, uint32_t);
void id3_FrameSetFlags(id3_Frame *, const char *);
void id3_FrameSetData(id3_Frame *, char *);

const char *id3_FrameGetID(id3_Frame *);
uint32_t id3_FrameGetSize(id3_Frame *);
const char *id3_FrameGetFlags(id3_Frame *);
const char *id3_FrameGetData(id3_Frame *);

id3_Bool id3_FrameShouldBePreservedTagAlter(id3_Frame *);
id3_Bool id3_FrameShouldBePreservedFileAlter(id3_Frame *);
id3_Bool id3_FrameIsReadOnly(id3_Frame *);
id3_Bool id3_FrameIsCompressed(id3_Frame *);
id3_Bool id3_FrameIsEncrypted(id3_Frame *);
id3_Bool id3_FrameHasGroupingIdentity(id3_Frame *);

void id3_FrameFree(id3_Frame *);

#endif /* defined(__acid3__id3_Frame__) */
