/*
//  id3_Header.h
//  acid3
//
//  Created by Christopher Loonam on 9/16/15.
//  Copyright (c) 2015 Christopher Loonam. All rights reserved.
*/

#ifndef __acid3__id3_Header__
#define __acid3__id3_Header__

#include <stdio.h>
#include <stdint.h>

#ifndef id3_Bool
#define id3_Bool signed char
#endif

struct id3_File;
typedef struct id3_Header id3_Header;

id3_Header *id3_HeaderCreateFromFile(struct id3_File *);

char *id3_HeaderGetVersionString(id3_Header *);
uint32_t id3_HeaderGetTagSize(id3_Header *);

id3_Bool id3_HeaderIsUnsynchronisationUsed(id3_Header *);
id3_Bool id3_HeaderHasExtendedHeader(id3_Header *);
id3_Bool id3_HeaderIsExperimental(id3_Header *);

void id3_HeaderFree(id3_Header *);

#endif /* defined(__acid3__id3_Header__) */
