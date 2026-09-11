#pragma once

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef signed char    s8;
typedef signed short   s16;
typedef signed int     s32;

#define NULL ((void *)0)
#define OFFSETOF(type, member) ((u32)&((type *)0)->member)
