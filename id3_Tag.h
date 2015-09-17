/*
//  id3_Tag.h
//  acid3
//
//  Created by Christopher Loonam on 9/17/15.
//  Copyright (c) 2015 Christopher Loonam. All rights reserved.
*/

#ifndef __acid3__id3_Tag__
#define __acid3__id3_Tag__

#include <stdio.h>

struct id3_File;
struct id3_Frame;
typedef struct id3_Tag id3_Tag;

id3_Tag *id3_TagCreateFromFile(struct id3_File *);
struct id3_Frame *id3_TagGetFrameWithID(id3_Tag *, const char *);

void id3_TagFree(id3_Tag *);

#endif /* defined(__acid3__id3_Tag__) */
