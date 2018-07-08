/**
 * Copyright (c) 2018, LopeDeVega Research group. All rights reserved.
 *
 * Authors:
 *  Atanas Filipov, it.feel.filipov@gmail.com
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef _STRING_H_
#define	_STRING_H_

#if !defined(NULL)
    #define NULL ((void*)0)
#endif

#if !defined(size_t)
    typedef unsigned long size_t;
#endif

char * strcat(char * s, const char * append);

char * strncat(char * dst, const char * src, size_t n);

char * strchr(const char * p, int ch);

char * strrchr(const char * p, int c);

int strcmp(const char * s1, const char * s2);

int strncmp(const char * s1, const char * s2, size_t n);

char * strcpy(char * to, const char * from);

char * strncpy(char * dst, const char * src, size_t n);

size_t strlen(const char * s);

char * strpbrk(const char *s1, const char *s2);

char * strsep(char ** stringp, const char * delim);

size_t strspn(const char * s, const char * charset);

size_t strcspn(const char * s, const char * charset);

char * strstr(const char * s, const char * find);

char * strnstr(const char *s, const char *find, size_t slen);

char * strtok(char * s, const char * delim);

char * index(const char * s, int c);

char * rindex(const char * s, int c);

#endif /* _STRING_H_ */
