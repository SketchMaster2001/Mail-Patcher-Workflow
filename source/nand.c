#include "nand.h"
#include <malloc.h>

static bool isNANDInitialised = false;

bool isDolphin(void) {
    s32 checkDolphin;
    checkDolphin = IOS_Open("/dev/dolphin", IPC_OPEN_NONE);
    if (checkDolphin >= 0) 
        return true;
    else 
        return false;
}


bool CheckvWii (void) { // Function taken from priiloader
	s32 ret;
	u32 x;

	//check if the vWii NandLoader is installed ( 0x200 & 0x201)
	ret = ES_GetTitleContentsCount(0x0000000100000200ll, &x);

	if (ret < 0)
		return false; // title was never installed

	if (x <= 0)
		return false; // title was installed but deleted via Channel Management

	return true;
}

s32 NAND_Init() {
    s32 error = ISFS_Initialize();

    if (error >= 0) {
        isNANDInitialised = true;
    } else {
        return error;
    }

    return 0;
}

s32 NAND_Exit() {
    s32 error = ISFS_Deinitialize();

    if (error >= 0) {
        isNANDInitialised = false;
    } else {
        return error;
    }

    return 0;
}

s32 NAND_ReadFile(const char* filePath, void* buffer, u32 bufferLength) {
    if (!isNANDInitialised) return -1;

    if (!NAND_IsFilePresent(filePath)) return -1;

    s32 file = ISFS_Open(filePath, ISFS_OPEN_READ);
    if (file < 0) return file;

    u8* readBuffer = memalign(32, bufferLength);

    s32 error = ISFS_Read(file, readBuffer, bufferLength);
    if (error < 0) {
        ISFS_Close(file);
        return error;
    }

    error = ISFS_Close(file);
    if (error < 0) return error;

    memcpy(buffer, readBuffer, bufferLength);

    return 0;
}

s32 NAND_WriteFile(const char* filePath, const void* buffer, u32 bufferLength, bool createFile) {
    if (!isNANDInitialised) return -1;

    if (!NAND_IsFilePresent(filePath)) {
        if (!createFile) {
            return -1;
        } else {
            ISFS_CreateFile(filePath, 0, 3, 3, 3);
        }
    }

    s32 file = ISFS_Open(filePath, ISFS_OPEN_WRITE);
    if (file < 0) return file;

    s32 error = ISFS_Write(file, buffer, bufferLength);
    if (error < 0) {
        ISFS_Close(file);
        return error;
    }

    error = ISFS_Close(file);
    if (error < 0) return error;

    return 0;
}

bool NAND_IsFilePresent(const char* filePath) {
    if (!isNANDInitialised) return false;

    s32 file = ISFS_Open(filePath, ISFS_OPEN_READ);

    if (file < 0) {
        return false;
    } else {
        ISFS_Close(file);
        return true;
    }
}
