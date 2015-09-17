/*
//  id3_File.c
//  acid3
//
//  Created by Christopher Loonam on 9/16/15.
//  Copyright (c) 2015 Christopher Loonam. All rights reserved.
*/

#include "id3_File.h"
#include <stdlib.h>
#include <string.h>
#include "id3_Header.h"
#include "id3_Tag.h"

struct id3_File
{
    FILE *file;
    const char *path;
    id3_Header *head;
    id3_Tag *tag;
};

id3_File *id3_FileCreateWithPath(const char *path)
{
    id3_File *file;
    
    file = calloc(1, sizeof(id3_File));
    if (!file)
        return NULL;
    file->path = strdup(path);
    return file;
}

id3_Error id3_FileOpen(id3_File *f)
{
    if (!f)
        return ID3_INVALIDARG_ERR;
    f->file = fopen(f->path, "rb");
    if (!f->file)
        return ID3_FOPEN_ERR;
    f->head = id3_HeaderCreateFromFile(f);
    f->tag = id3_TagCreateFromFile(f);
    return ID3_SUCCESS;
}

id3_Error id3_FileClose(id3_File *f)
{
    if (!f)
        return ID3_INVALIDARG_ERR;
    if (fclose(f->file) != 0)
        return ID3_FCLOSE_ERR;
    id3_HeaderFree(f->head);
    id3_TagFree(f->tag);
    free((char *)f->path);
    free(f);
    return ID3_SUCCESS;
}

id3_Header *id3_FileGetHeader(id3_File *fi)
{
    return fi->head;
}

struct id3_Tag *id3_FileGetTag(id3_File *fi)
{
    return fi->tag;
}

