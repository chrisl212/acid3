//
//  id3_Header.c
//  acid3
//
//  Created by Christopher Loonam on 9/16/15.
//  Copyright (c) 2015 Christopher Loonam. All rights reserved.
//

#include "id3_Header.h"
#include "id3_File.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>

struct id3_File
{
    FILE *file;
    const char *path;
    id3_Header *head;
};

struct id3_Header
{
    char majorVersion;
    char revisionVersion;
    char flags;
    uint32_t tagSize;
};

id3_Bool isBitEnabled(char flag, int bit)
{
    bit = pow(2, bit);
    return ((flag & bit) == bit);
}

id3_Header *id3_HeaderCreateFromFile(id3_File *fi)
{
    id3_Header *header;
    char headerBuf[10], fileID[4];
    int i;
    uint32_t headSize[4];

    header = calloc(1, sizeof(id3_Header));
    fread(headerBuf, 1, 10, fi->file);
    
    for (i = 0; i < 3; i++)
        fileID[i] = headerBuf[i];
    fileID[3] = '\0';
    if (strcmp(fileID, "ID3") != 0)
        printf("invalid file"); //implement error checking
    
    header->majorVersion = headerBuf[3];
    header->revisionVersion = headerBuf[4];
    header->flags = headerBuf[5];
    
    for (i = 0; i < 4; i++)
        headSize[i] = headerBuf[6+i];
    header->tagSize = ((headSize[0] << 24) + (headSize[1] << 16) + (headSize[2] << 8) + headSize[3])/2; //big-endian
    return header;
}

char *id3_HeaderGetVersionString(id3_Header *head)
{
    char *versionString = malloc(11);
    sprintf(versionString, "ID3v2.%x.%x", head->majorVersion, head->revisionVersion);
    return versionString;
}

unsigned long id3_HeaderGetTagSize(id3_Header *head)
{
    return head->tagSize;
}

id3_Bool id3_HeaderIsUnsynchronisationUsed(id3_Header *head)
{
    return isBitEnabled(head->flags, 7);
}

id3_Bool id3_HeaderHasExtendedHeader(id3_Header *head)
{
    return isBitEnabled(head->flags, 6);
}

id3_Bool id3_HeaderIsExperimental(id3_Header *head)
{
    return isBitEnabled(head->flags, 5);
}
