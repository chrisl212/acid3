//
//  id3_Header.h
//  acid3
//
//  Created by Christopher Loonam on 9/16/15.
//  Copyright (c) 2015 Christopher Loonam. All rights reserved.
//

#ifndef __acid3__id3_Header__
#define __acid3__id3_Header__

#include <stdio.h>
#include "id3_Error.h"

typedef struct id3_File id3_File;
typedef struct id3_Header id3_Header;

id3_Header *id3_HeaderCreateFromFile(id3_File *);

char *id3_HeaderGetVersionString(id3_Header *);
unsigned long id3_HeaderGetTagSize(id3_Header *);

id3_Bool id3_HeaderIsUnsynchronisationUsed(id3_Header *);
id3_Bool id3_HeaderHasExtendedHeader(id3_Header *);
id3_Bool id3_HeaderIsExperimental(id3_Header *);

#endif /* defined(__acid3__id3_Header__) */
