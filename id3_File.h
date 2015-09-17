/*
//  id3_File.h
//  acid3
//
//  Created by Christopher Loonam on 9/16/15.
//  Copyright (c) 2015 Christopher Loonam. All rights reserved.
*/

#ifndef __acid3__id3_File__
#define __acid3__id3_File__

#include <stdio.h>
#include "id3_Error.h"

struct id3_Header;
typedef struct id3_File id3_File;

id3_File *id3_FileCreateWithPath(const char *);
id3_Error id3_FileOpen(id3_File *);
id3_Error id3_FileClose(id3_File *);

struct id3_Header *id3_FileGetHeader(id3_File *);
struct id3_Tag *id3_FileGetTag(id3_File *);

#endif /* defined(__acid3__id3_File__) */
