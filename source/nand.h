#ifndef NAND_H
#define NAND_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gccore.h>

s32 NAND_Init();
s32 NAND_Exit();

bool isDolphin(void);
bool CheckvWii(void);

bool NAND_IsFilePresent(const char *filePath);
s32 NAND_ReadFile(const char *filePath, void *buffer, u32 bufferLength);
s32 NAND_WriteFile(const char *filePath, const void *buffer, u32 bufferLength, bool createFile);

#endif
