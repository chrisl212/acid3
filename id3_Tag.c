/*
//  id3_Tag.c
//  acid3
//
//  Created by Christopher Loonam on 9/17/15.
//  Copyright (c) 2015 Christopher Loonam. All rights reserved.
*/

#include <stdlib.h>
#include <string.h>
#include <iconv.h>
#include "id3_Tag.h"
#include "id3_Header.h"
#include "id3_File.h"
#include "id3_Frame.h"

struct id3_File
{
    FILE *file;
    const char *path;
    id3_Header *head;
    id3_Tag *tag;
};

struct id3_Frame
{
    const char *id;
    uint32_t size;
    char flags[2];
    char *data;
    id3_Frame *next;
};

struct id3_Tag
{
    id3_Frame *frame;
};

id3_Tag *id3_TagCreateFromFile(id3_File *fi)
{
    id3_Header *head;
    id3_Tag *tag;
    uint32_t tagSize;
    char /*tagData*/frameHeader[11], frameID[5], flags[2], *frameData;
    unsigned char frameSizeBytes[4];
    uint32_t i, loc, frameSize, totalRead;
    id3_Frame *frame;
    
    frame = NULL;
    loc = totalRead = 0;
    tag = calloc(1, sizeof(id3_Tag));
    
    head = id3_FileGetHeader(fi);
    tagSize = id3_HeaderGetTagSize(head);
    /*tagData = malloc(tagSize);*/
    
    /*fread(tagData, 1, tagSize, fi->file);*/
    
    while ((totalRead += (uint32_t)fread(frameHeader, 1, 11, fi->file)) < tagSize)
    {
        if (!frame)
            tag->frame = frame = id3_FrameCreate();
        else
        {
            frame->next = id3_FrameCreate();
            frame = frame->next;
        }
        
        for (i = 0; i < 4; i++)
            frameID[i] = frameHeader[i];
        loc += 4;
        frameID[4] = '\0';
        id3_FrameSetID(frame, frameID);
        
        for (i = 0; i < 4; i++)
            frameSizeBytes[i] = (unsigned char)frameHeader[loc+i];
        loc += 4;
        frameSize = (((uint32_t)frameSizeBytes[0] << 24) | (uint32_t)(frameSizeBytes[1] << 16) | (uint32_t)(frameSizeBytes[2] << 8) | (uint32_t)frameSizeBytes[3]) - 1;
        id3_FrameSetSize(frame, frameSize);
        
        for (i = 0; i < 2; i++)
            flags[i] = frameHeader[loc+i];
        loc = 0;
        id3_FrameSetFlags(frame, flags);
        
        frameData = malloc(frameSize);
        totalRead += fread(frameData, 1, frameSize, fi->file);
        
       /* i = 0;
        while (i < frameSize)
            putc((frameData[i] == '\0') ? 'N' : frameData[i], stdout), i++;
        fflush(stdout); */
        id3_FrameSetData(frame, frameData);

        free(frameData);
    }
    
    return tag;
}

struct id3_Frame *id3_TagGetFrameWithID(id3_Tag *tag, const char *id)
{
    id3_Frame *frame;
    for (frame = tag->frame; frame != NULL; frame = frame->next)
        if (strcmp(frame->id, id) == 0)
            return frame;
    return NULL;
}

void id3_TagFree(id3_Tag *t)
{
    id3_FrameFree(t->frame);
    free(t);
}
