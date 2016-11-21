/**
 * \usergroup{SceUdcd}
 * \usage{psp2/udcd.h,-lSceUdcd_stub}
 */

/**
 * \file udcd.h
 * \brief Header file which defines touch related variables and functions
 *
 * Copyright (C) 2016 VITASDK Project
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _PSP2_UDCD_H_
#define _PSP2_UDCD_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <psp2/types.h>

typedef struct SceUdcdState {
	SceUInt32	unk_0;
	SceUInt32	unk_4;
	SceUInt32	unk_8;
	SceUInt32	unk_c;
	SceUInt32	unk_10;
	SceUInt32	unk_14;
} SceUdcdState;

/**
 * @param[out]	statue
 * @return 0. <0 on error
 */
int sceUdcdWaitState(SceUdcdState *state);

/**
 * @param[in]	cbid	see ::sceKernelCreateCallback
 * @param[in]	unk		use 300
 * @return 0. <0 on error
 */
int sceUdcdRegisterCallback(int cbid, int unk);

/**
 * @param[in]	cbid	see ::sceKernelCreateCallback
 * @return 0. <0 on error
 */
int sceUdcdUnregisterCallback(int cbid);

/**
 * @param[out]	statue
 * @return 0. <0 on error
 */
int sceUdcdGetDeviceState(SceUdcdState *state);

#ifdef __cplusplus
}
#endif

#endif

