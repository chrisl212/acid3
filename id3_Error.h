//
//  id3_Error.h
//  acid3
//
//  Created by Christopher Loonam on 9/16/15.
//  Copyright (c) 2015 Christopher Loonam. All rights reserved.
//

#ifndef __acid3__id3_Error__
#define __acid3__id3_Error__

#include <stdio.h>

#define ID3_TRUE 1
#define ID3_FALSE 0

#define ID3_SUCCESS 0
#define ID3_FOPEN_ERR -1
#define ID3_MALLOC_ERR -2
#define ID3_INVALIDARG_ERR -3
#define ID3_FCLOSE_ERR -4
#define ID3_FREAD_ERR -5

typedef signed int id3_Error;
typedef unsigned int id3_Bool;

char *id3_Strerror(id3_Error);

#endif /* defined(__acid3__id3_Error__) */
