/* -*- Mode: C; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * The contents of this file are subject to the Mozilla Public
 * License Version 1.1 (the "License"); you may not use this file
 * except in compliance with the License. You may obtain a copy of
 * the License at http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS
 * IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or
 * implied. See the License for the specific language governing
 * rights and limitations under the License.
 *
 * The Original Code is mozilla.org code, released
 * Jan 28, 2003.
 *
 * The Initial Developer of the Original Code is Netscape
 * Communications Corporation.  Portions created by Netscape are
 * Copyright (C) 2003 Netscape Communications Corporation. All
 * Rights Reserved.
 *
 * Contributor(s):
 *    Garrett Arch Blythe, 28-January-2003
 *
 * Alternatively, the contents of this file may be used under the
 * terms of the GNU Public License (the "GPL"), in which case the
 * provisions of the GPL are applicable instead of those above.
 * If you wish to allow use of your version of this file only
 * under the terms of the GPL and not to allow others to use your
 * version of this file under the MPL, indicate your decision by
 * deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL.  If you do not delete
 * the provisions above, a recipient may use your version of this
 * file under either the MPL or the GPL.
 */
#include <string.h>
#include <stdio.h>
#include "mozce_internal.h"


extern "C" {
#if 0
}
#endif

// #define LOG_CALLS

MOZCE_SHUNT_API char *mozce_fullpath(char *absPath, const char *relPath, size_t maxLength)
{
#ifdef LOG_CALLS
#ifdef DEBUG
    printf("*mozce_fullpath called\n");
#endif
#endif
    return 0;
}

MOZCE_SHUNT_API void mozce_splitpath(const char* inPath, char* outDrive, char* outDir, char* outFname, char* outExt)
{
#ifdef LOG_CALLS
#ifdef DEBUG
    printf("mozce_splitpath called\n");
#endif
#endif
    if(NULL != outDrive)
    {
        *outDrive = '\0';
    }
    if(NULL != outDir)
    {
        *outDir = '\0';
    }
    if(NULL != outFname)
    {
        *outFname = '\0';
    }
    if(NULL != outExt)
    {
        *outExt = '\0';
    }

    if(NULL != inPath && '\0' != *inPath)
    {
		char* dup = (char*) malloc(strlen(inPath));
		if(NULL != dup)
        {
            strcpy(dup, inPath);
			/*
            **  Change all forward slashes to back.
            */
            char* convert = dup;
            do
            {
                if('/' == *convert)
                {
                    *convert = '\\';
                }
                convert++;
            }
            while(*convert);

            /*
            **  Find last slash first.
            */
            char* slash = strrchr(dup, '\\');

            /*
            **  Find extension, must be after any slash.
            */
            char* ext = NULL;
            if(NULL == slash)
            {
                ext = strchr(dup, '.');
            }
            else
            {
                ext = strchr(slash, '.');
            }

            /*
            **  Reap extension.
            */
            if(NULL != ext)
            {
                if(NULL != outExt)
                {
                    strncpy(outExt, ext, _MAX_EXT);
                }

                *ext = '\0';
            }

            /*
            **  Reap filename.
            */
            char* fname = NULL;
            if(NULL == slash)
            {
                fname = dup;
            }
            else
            {
                fname = slash + 1;
            }

            if(NULL != outFname)
            {
                strncpy(outFname, fname, _MAX_FNAME);
            }

            *fname = '\0';

            /*
            **  Reap directory.
            */
            if(NULL != slash && NULL != outDir)
            {
                strncpy(outDir, dup, _MAX_DIR);
            }

            free(dup);
        }
    }
}


MOZCE_SHUNT_API void mozce_makepath(char* outPath, const char* inDrive, const char* inDir, const char* inFname, const char* inExt)
{
#ifdef LOG_CALLS
#ifdef DEBUG
    printf("mozce_makepath called\n");
#endif
#endif
    if(NULL != outPath)
    {
        int dirLen = 0;
        if(NULL != inDir)
        {
            dirLen = strlen(inDir);
            if(dirLen)
            {
                dirLen--;
            }
        }
        _snprintf(outPath, _MAX_PATH, "%s%s%s%s%s",
                  (NULL != inDir) ? inDir : "",
                  (NULL != inDir && '\\' != inDir[dirLen] && '/' != inDir[dirLen]) ? "\\" : "",
                  (NULL != inFname) ? inFname : "",
                  (NULL != inExt && '.' != inExt[0]) ? "." : "",
                  (NULL != inExt) ? inExt : ""
                  );
    }
}

MOZCE_SHUNT_API int mozce_strcmpi(const char *dest, const char *src)
{
#ifdef LOG_CALLS
#ifdef DEBUG
    printf("mozce_strcmpi called\n");
#endif
#endif
    int f,l;
    
    do {
        if ( ((f = (unsigned char)(*(dest++))) >= 'A') && (f <= 'Z') )
            f -= ('A' - 'a');
        
        if ( ((l = (unsigned char)(*(src++))) >= 'A') && (l <= 'Z') )
            l -= ('A' - 'a');
    } while ( f && (f == l) );

    return(f - l);
}

#if 0
{
#endif
} /* extern "C" */
