/*
//  id3_Header.c
//  acid3
//
//  Created by Christopher Loonam on 9/16/15.
//  Copyright (c) 2015 Christopher Loonam. All rights reserved.
*/

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
    bit = (int)pow(2, bit);
    return ((flag & bit) == bit);
}

id3_Header *id3_HeaderCreateFromFile(id3_File *fi)
{
    id3_Header *header;
    unsigned char headerBuf[10];
    char fileID[4];
    int i;
    unsigned char headSize[4];
    uint32_t divisor;

    header = calloc(1, sizeof(id3_Header));
    fread(headerBuf, 1, 10, fi->file);
    
    for (i = 0; i < 3; i++)
        fileID[i] = (char)headerBuf[i];
    fileID[3] = '\0';
    if (strcmp(fileID, "ID3") != 0)
        printf("invalid file"); /* implement error checking */
    
    header->majorVersion = (char)headerBuf[3];
    header->revisionVersion = (char)headerBuf[4];
    header->flags = (char)headerBuf[5];
    
    for (i = 0, divisor = 1; i < 4; i++)
    {
        headSize[i] = (unsigned char)headerBuf[6+i];
        if (headSize[i] != '\0')
            divisor++;
    }
    header->tagSize = ((uint32_t)(headSize[0] << 23) + (uint32_t)(headSize[1] << 15) + (uint32_t)(headSize[2] << 7) + (uint32_t)headSize[3]);
    return header;
}

char *id3_HeaderGetVersionString(id3_Header *head)
{
    char *versionString = malloc(11);
    sprintf(versionString, "ID3v2.%x.%x", head->majorVersion, head->revisionVersion);
    return versionString;
}

uint32_t id3_HeaderGetTagSize(id3_Header *head)
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

void id3_HeaderFree(id3_Header *head)
{
    free(head);
}

