#ifndef PATCHER_H
#define PATCHER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gccore.h>

typedef enum {
  RESPONSE_NOTINIT = 0,
  RESPONSE_OK = 100,
  RESPONSE_INVALID = 610,
  RESPONSE_AREGISTERED = 211,
  RESPONSE_DB_ERROR = 410,
} serverResponseCode;

typedef union {
  struct fileNWC24MSG {
    char magic[0x4];
    char unknwown[0x4];
    s64 friendCode;
    char idGen[0x4];
    char idRegistration[0x4];
    char mailDomain[0x40];
    char passwd[0x20];
    char mlchkid[0x24];
    char urls[0x5][0x80];
    char reserved[0xDC];
    unsigned int titleBooting;
    unsigned int checksum;
  } structNWC24MSG;

  char charNWC24MSG[0x400];
} unionNWC24MSG;

typedef struct {
  char filename[0x8];
  u8 filehash[0x14];
} contentMapObject;

s64 getFriendCode();
s32 patchMail();

#endif
