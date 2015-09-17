//
//  main.c
//  acid3Tests
//
//  Created by Christopher Loonam on 9/16/15.
//  Copyright (c) 2015 Christopher Loonam. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include "id3_File.h"
#include "id3_Header.h"

int main(int argc, const char * argv[])
{
    char fpath[512];
    printf("enter file path\n");
    fgets(fpath, 512, stdin);
    size_t len = strlen(fpath);
    fpath[len - 1] = '\0';
    
    // /Users/christopherloonam/Music/iTunes/iTunes Media/Music/Pink Floyd/See Emily Play/See Emily Play.mp3
    
    id3_File *file;
    
    file = id3_FileCreateWithPath(fpath);
    id3_FileOpen(file);
    
    id3_FileClose(file);

    return 0;
}
