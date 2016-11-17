/**
 * \file
 * \brief Header file which defines font (PVF) variables and functions
 *
 * Copyright (C) 2016 PSP2SDK Project
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _PSP2_PVF_H_
#define _PSP2_PVF_H_

#include <psp2/types.h>
#include <psp2/pgf.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* struct */

enum {
	SCE_PVF_ERROR_OUT_OF_MEMORY        = 0x80460001,
	SCE_PVF_ERROR_INVALID_LIBID        = 0x80460002,
	SCE_PVF_ERROR_INVALID_PARAMETER    = 0x80460003,
	SCE_PVF_ERROR_HANDLER_OPEN_FAILED  = 0x80460005,
	SCE_PVF_ERROR_HANDLER_CLOSE_FAILED = 0x80460006,
	SCE_PVF_ERROR_HANDLER_READ_FAILED  = 0x80460007,
	SCE_PVF_ERROR_TOO_MANY_OPEN_FONTS  = 0x80460009,
	SCE_PVF_ERROR_INVALID_FONT_DATA    = 0x8046000a,
	SCE_PVF_ERROR_UNKNOWN_B            = 0x8046000b,
	SCE_PVF_ERROR_UNKNOWN_D            = 0x8046000d,
	SCE_PVF_ERROR_UNKNOWN_E            = 0x8046000e,
};

typedef struct ScePvfCharInfo {
	int unk_0;
	int unk_4;
	int unk_8;
	int unk_C;
	int unk_10;
	int unk_14; // width?
	int unk_18; // height?
	int unk_1C; // left?
	int unk_20; // top?
	int unk_24;
	int unk_28;
	int unk_2C;
	int unk_30;
	int unk_34;
	int unk_38;
	short unk_3C;
	short unk_3E;
} ScePvfCharInfo;

typedef struct _ScePvfHandle {
	char unk_0[2];
	short unk_2; // code?
	float em;
	float unk_8;
	float fontH;
	float fontV;
	char unk_14[20];
	void *font;
	int unk_2C;
	SceFontCharInfo lastCharInfo;
	void *unk_70;
	int unk_74;
	int unk_78;
	int unk_7C;
	float unk_80;
} *ScePvfHandle;

typedef struct ScePvfNewLibParams {
	void *userData;
	int numFonts;
	int unk_8;
	int unk_C; // should be 0
	void *(*allocFunc)(void *userData, size_t size);
	void *(*memcpyFunc)(void *userData, void*, size_t size);
	void (*freeFunc)(void *userData, void*);
} ScePvfNewLibParams;

typedef struct _ScePvfLibHandle {
	char unk_0[4];
	int unk_4;
	ScePvfNewLibParams params;
	ScePvfHandle fontHandles; // 132 * numFonts
	void *unk_28; // 276 * numFonts
	unsigned short openedFonts;
	unsigned short unk_2E;
	float unk_30; // hRes?
	float unk_34; // vRes?
	float unk_38;
	float unk_3C;
	float unk_40;
	float unk_44;
	int unk_48;
	int unk_4C;
	char unk_50[4];
	short altCharCode;
	char unk_56[522];
	int64_t unk_260;
	char unk_268[500];
	int unk_45c;
} *ScePvfLibHandle;

typedef struct ScePvfStyle {
	float unk_0; //fontWeight?
	unsigned short fontFamily;
	unsigned short fontStyle;
	unsigned short fontStyleSub;
	unsigned short fontLanguage;
	unsigned short fontRegion;
	unsigned short fontCountry;
	char fontName[64];
	char fontStyleName[64];
	char fontPath[64];
	float unk_D0; // fontH?
	float unk_D4; // fontW?
} ScePvfStyle;

typedef struct ScePvfInfo {
	unsigned int unk_0;
	unsigned int unk_4;
	int unk_8;
	int unk_C;
	int unk_10;
	int unk_14;
	int unk_18;
	int unk_1C;
	int unk_20;
	int unk_24;
	float unk_28;
	float unk_2C;
	float unk_30;
	float unk_34;
	float unk_38;
	float unk_3C;
	float unk_40;
	float unk_44;
	float unk_48;
	float unk_4C;
	char unk_50[4];
	ScePvfStyle fontStyle;
} ScePvfInfo;

/**
 * @param[in] params
 * @param[out] errorCode
 *
 * @return ScePvfLibHandle, 0 on error
 */
ScePvfLibHandle scePvfNewLib(ScePvfNewLibParams *params, unsigned int *errorCode);

/**
 * @param[in] libHandle
 *
 * @return 0, <0 on error
 */
int scePvfDoneLib(ScePvfLibHandle libHandle);

/**
 * @param[in] libHandle
 * @param[in] index
 * @param[in] mode - 0 or 1
 * @param[out] errorCode
 *
 * @return ScePvfHandle, 0 on error
 */
ScePvfHandle scePvfOpen(ScePvfLibHandle libHandle,
	int index, unsigned int mode, unsigned int *errorCode);

/**
 * @param[in] fontHandle
 *
 * @return 0, <0 on error
 */
int scePvfClose(ScePvfHandle fontHandle);

/**
 * @param[in] libHandle
 * @param[out] errorCode
 *
 * @return ScePvfHandle, 0 on error
 */
ScePvfHandle scePvfOpenDefaultJapaneseFontOnSharedMemory(ScePvfLibHandle libHandle,
	unsigned int *errorCode);

/**
 * @param[in] libHandle
 * @param[out] errorCode
 *
 * @return ScePvfHandle, 0 on error
 */
ScePvfHandle scePvfOpenDefaultLatinFontOnSharedMemory(ScePvfLibHandle libHandle,
	unsigned int *errorCode);

/**
 * @param[in] libHandle
 * @param[in] file
 * @param[in] mode - 0 or 1
 * @param[out] errorCode
 *
 * @return ScePvfHandle, 0 on error
 */
ScePvfHandle scePvfOpenUserFile(SceFontLibHandle libHandle,
	char *file, int mode, unsigned int *errorCode);

/**
 * @param[in] libHandle
 * @param[in] file
 * @param[in] mode - 0 or 1
 * @param[in] index
 * @param[out] errorCode
 *
 * @return ScePvfHandle, 0 on error
 */
ScePvfHandle scePvfOpenUserFileWithSubfontIndex(ScePvfHandle libHandle,
	char *file, int mode, int index, unsigned int *errorCode);

/**
 * @param[in] libHandle
 * @param[in] pMemoryFont
 * @param[in] pMemoryFontSize
 * @param[out] errorCode
 *
 * @return ScePvfHandle, 0 on error
 */
ScePvfHandle scePvfOpenUserMemory(ScePvfLibHandle libHandle,
	void *pMemoryFont, SceSize pMemoryFontSize, unsigned int *errorCode);

/**
 * @param[in] libHandle
 * @param[in] pMemoryFont
 * @param[in] pMemoryFontSize
 * @param[in] index
 * @param[out] errorCode
 *
 * @return ScePvfHandle, 0 on error
 */
ScePvfHandle scePvfOpenUserMemoryWithSubfontIndex(ScePvfLibHandle libHandle,
	void *pMemoryFont, SceSize pMemoryFontSize, int index, unsigned int *errorCode);

/**
 * @param[in] libHandle
 * @param[in] fontStyle
 * @param[out] errorCode
 *
 * @return index
 */
int scePvfFindOptimumFont(ScePvfLibHandle libHandle,
	ScePvfStyle *fontStyle, unsigned int *errorCode);

/**
 * @param[in] libHandle
 * @param[in] fontStyle
 * @param[out] errorCode
 *
 * @return index
 */
int scePvfFindFont(ScePvfLibHandle libHandle,
	ScePvfStyle *fontStyle, unsigned int *errorCode);

/**
 * @param[in] fontHandle
 * @param[out] fontInfo
 *
 * @return 0, <0 on error
 */
int scePvfGetFontInfo(ScePvfHandle fontHandle, ScePvfInfo *fontInfo);

/**
 * @param[in] libHandle
 * @param[out] fontStyle
 * @param[in] fontIndex
 *
 * @return 0, <0 on error
 */
int scePvfGetFontInfoByIndexNumber(ScePvfLibHandle libHandle,
	ScePvfStyle *fontStyle, int fontIndex);

/**
 * @param[in] fontHandle
 * @param[in] charCode
 * @param[in/out] glyphImage
 *
 * @return 0, <0 on error
 */
int scePvfGetCharGlyphImage(ScePvfHandle fontHandle,
	unsigned int charCode, SceFontGlyphImage *glyphImage);

/**
 * @param[in] fontHandle
 * @param[in] charCode
 * @param[out] charRect
 *
 * @return 0, <0 on error
 */
int scePvfGetCharImageRect(ScePvfHandle fontHandle,
	unsigned int charCode, SceFontImageRect *charRect);

//int scePvfSetSkewValue(ScePvfHandle fontHandle, int value);
//int scePvfSetEmboldenRate(ScePvfHandle fontHandle, int rate);
//int scePvfIsElement(ScePvfHandle fontHandle, unsigned int charCode);

/**
 * @param[in] fontHandle
 * @param[in] charCode
 * @param[out] charInfo
 *
 * @return 0, <0 on error
 */
int scePvfGetCharInfo(ScePvfHandle fontHandle,
	unsigned int charCode, ScePvfCharInfo *charInfo);

/**
 * Require s0 s1 register set
 *
 * @param[in] libHandle
 *
 * @return 0, <0 on error
 */
int scePvfSetResolution(ScePvfLibHandle libHandle);

/**
 * Require s0 s1 register set
 *
 * @param[in] fontHandle
 *
 * @return 0, <0 on error
 */
int scePvfSetEM(ScePvfHandle fontHandle);

/**
 * Require s0 s1 register set
 *
 * @param[in] fontHandle
 *
 * @return 0, <0 on error
 */
int scePvfSetCharSize(ScePvfHandle fontHandle);

//int scePvfGetNumFontList(SceFontLibHandle libHandle, unsigned int *errorCode);
//int scePvfGetVertCharGlyphImage(ScePvfHandle fontHandle,
//	unsigned int charCode, SceFontGlyphImage *glyphImage);
//int sceFontGetCharGlyphImage_Clip(SceFontHandle fontHandle,
//	unsigned int charCode, SceFontGlyphImage *glyphImage,
//	int clipXPos, int clipYPos, int clipWidth, int clipHeight);

/**
 * @param[in] fontHandle
 * @param[in] charCode
 * @param[out] charRect
 *
 * @return 0, <0 on error
 */
int scePvfGetVertCharImageRect(ScePvfHandle fontHandle,
	unsigned int charCode, SceFontImageRect *charRect);

//int scePvfIsVertElement(ScePvfHandle fontHandle, unsigned int charCode);

/**
 * @param[in] libHandle
 * @param[in] code
 *
 * @return 0, <0 on error
 */
int scePvfSetAltCharacterCode(ScePvfLibHandle libHandle, uint16_t code);

/**
 * @param[in] fontHandle
 * @param[in] charCode
 * @param[out] charInfo
 *
 * @return 0, <0 on error
 */
int scePvfGetVertCharInfo(ScePvfHandle fontHandle,
	unsigned int charCode, ScePvfCharInfo *charInfo);

/**
 * @param[in] fontHandle
 *
 * @return 0, <0 on error
 */
int scePvfFlush(ScePvfHandle fontHandle);

/**
 * @param[in] libHandle
 * @param[out] fontStyle
 * @param[in] numFonts
 *
 * @return 0, <0 on error
 */
int scePvfGetFontList(ScePvfLibHandle libHandle,
	ScePvfStyle *fontStyle, int numFonts);

/**
 * @param[in] libHandle
 * @param[in] fontPixelsH
 * @param[out] errorCode
 *
 * @return fontPointsH
 */
float scePvfPixelToPointH(ScePvfLibHandle libHandle,
	float fontPixelsH, unsigned int *errorCode);

/**
 * @param[in] libHandle
 * @param[in] fontPixelsV
 * @param[out] errorCode
 *
 * @return fontPointsV
 */
float scePvfPixelToPointV(ScePvfLibHandle libHandle,
	float fontPixelsV, unsigned int *errorCode);

/**
 * @param[in] libHandle
 * @param[in] fontPointsH
 * @param[out] errorCode
 *
 * @return fontPixelsH
 */
float scePvfPointToPixelH(ScePvfLibHandle libHandle,
	float fontPointsH, unsigned int *errorCode);

/**
 * @param[in] libHandle
 * @param[in] fontPointsV
 * @param[out] errorCode
 *
 * @return fontPixelsV
 */
float scePvfPointToPixelV(ScePvfLibHandle libHandle,
	float fontPointsV, unsigned int *errorCode);

//int scePvfGetKerningInfo(int, int, int, int);
//int scePvfGetCharGlyphImage_Clip(int, int, int, int, int, int, int);
//int scePvfGetVertCharGlyphImage_Clip(int, int, int, int, int, int, int);
//int scePvfGetCharGlyphOutline(ScePvfHandle fontHandle, int, int);
//int scePvfGetVertCharGlyphOutline(ScePvfLibHandle libHandle, int, int);
//int scePvfReleaseCharGlyphOutline(ScePvfHandle fontHandle, int);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_PGF_H_ */