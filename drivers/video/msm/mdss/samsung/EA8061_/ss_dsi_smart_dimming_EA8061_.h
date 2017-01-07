/*
 * =================================================================
 *
 *
 *	Description:  samsung display panel file
 *
 *	Author: jb09.kim
 *	Company:  Samsung Electronics
 *
 * ================================================================
 */
/*
<one line to give the program's name and a brief idea of what it does.>
Copyright (C) 2012, Samsung Electronics. All rights reserved.

*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
*/
#ifndef _SS_DSI_SMART_MTP_MAGNA_EA8061_SDC__H_
#define _SS_DSI_SMART_MTP_MAGNA_EA8061_SDC__H_

#include "../ss_dsi_panel_common.h"
#include "../ss_dsi_smart_dimming_common.h"

/*
*	From 4.8 inch model use AID function
*	CASE#1 is used for now.
*/
#define AID_OPERATION

enum {
	GAMMA_CURVE_1P9 = 0,
	GAMMA_CURVE_2P15,
	GAMMA_CURVE_2P2,
};

#define REV_A	0x00
#define REV_C	0x01

#define LUMINANCE_MAX 62
#define GAMMA_SET_MAX 33
#define BIT_SHIFT 22
/*
	it means BIT_SHIFT is 22.  pow(2,BIT_SHIFT) is 4194304.
	BIT_SHIFT is used for right bit shfit
*/
#define BIT_SHFIT_MUL 4194304

#define GRAY_SCALE_MAX 256

/* 5.8 * 4194304 */
#define VREG0_REF_5P8 24326963
/* 5.6 * 4194304 */
#define VREG0_REF_5P6 23488102

/*V0,V3,V11,V23,V35,V51,V87,V151,V203,V255*/
#define ARRAY_MAX 11

/* PANEL DEPENDENT THINGS */
#define MIN_CANDELA	5

/*
*	ID 0x20
*/
#define V255_300CD_R_MSB_20 0x01
#define V255_300CD_R_LSB_20 0x00

#define V255_300CD_G_MSB_20 0x01
#define V255_300CD_G_LSB_20 0x00

#define V255_300CD_B_MSB_20 0x01
#define V255_300CD_B_LSB_20 0x00

#define V203_300CD_R_20 0x80
#define V203_300CD_G_20 0x80
#define V203_300CD_B_20 0x80

#define V151_300CD_R_20 0x80
#define V151_300CD_G_20 0x80
#define V151_300CD_B_20 0x80

#define V87_300CD_R_20 0x80
#define V87_300CD_G_20 0x80
#define V87_300CD_B_20 0x80

#define V51_300CD_R_20 0x80
#define V51_300CD_G_20 0x80
#define V51_300CD_B_20 0x80

#define V35_300CD_R_20 0x80
#define V35_300CD_G_20 0x80
#define V35_300CD_B_20 0x80

#define V23_300CD_R_20 0x80
#define V23_300CD_G_20 0x80
#define V23_300CD_B_20 0x80

#define V11_300CD_R_20 0x80
#define V11_300CD_G_20 0x80
#define V11_300CD_B_20 0x80

#define V3_300CD_R_20 0x80
#define V3_300CD_G_20 0x80
#define V3_300CD_B_20 0x80

#define VT_300CD_R_20 0x00
#define VT_300CD_G_20 0x00
#define VT_300CD_B_20 0x00


/* PANEL DEPENDENT THINGS END*/

enum {
	V1_INDEX = 0,
	V3_INDEX = 1,
	V11_INDEX = 2,
	V23_INDEX = 3,
	V35_INDEX = 4,
	V51_INDEX = 5,
	V87_INDEX = 6,
	V151_INDEX = 7,
	V203_INDEX = 8,
	V255_INDEX = 9,
};

struct GAMMA_LEVEL {
	int level_0;
	int level_1;
	int level_3;
	int level_11;
	int level_23;
	int level_35;
	int level_51;
	int level_87;
	int level_151;
	int level_203;
	int level_255;
} __packed;

struct RGB_OUTPUT_VOLTARE {
	struct GAMMA_LEVEL R_VOLTAGE;
	struct GAMMA_LEVEL G_VOLTAGE;
	struct GAMMA_LEVEL B_VOLTAGE;
} __packed;

struct GRAY_VOLTAGE {
	/*
		This voltage value use 14bit right shit
		it means voltage is divied by 16384.
	*/
	int R_Gray;
	int G_Gray;
	int B_Gray;
} __packed;

struct GRAY_SCALE {
	struct GRAY_VOLTAGE TABLE[GRAY_SCALE_MAX];
	struct GRAY_VOLTAGE VT_TABLE;
} __packed;

/*V0,V1,V3,V11,V23,V35,V51,V87,V151,V203,V255*/

struct MTP_SET {
	char OFFSET_255_MSB;
	char OFFSET_255_LSB;
	char OFFSET_203;
	char OFFSET_151;
	char OFFSET_87;
	char OFFSET_51;
	char OFFSET_35;
	char OFFSET_23;
	char OFFSET_11;
	char OFFSET_3;
	char OFFSET_1;
} __packed;

struct MTP_OFFSET {
	struct MTP_SET R_OFFSET;
	struct MTP_SET G_OFFSET;
	struct MTP_SET B_OFFSET;
} __packed;

struct illuminance_table {
	int lux;
	char gamma_setting[GAMMA_SET_MAX];
} __packed;

struct SMART_DIM {
	struct MTP_OFFSET MTP_ORIGN;

	struct MTP_OFFSET MTP;
	struct RGB_OUTPUT_VOLTARE RGB_OUTPUT;
	struct GRAY_SCALE GRAY;

	/* Because of AID funtion, below members are added*/
	int lux_table_max;
	int *plux_table;
	struct illuminance_table gen_table[LUMINANCE_MAX];

	int brightness_level;
	int ldi_revision;
	int vregout_voltage;
} __packed;

#define AOR_DIM_BASE_CD	115

#define CANDELA_MAX_TABLE 61
#define RGB_COMPENSATION 24

static int candela_table[][2] = {
	{5, 0,},
	{6, 1,},
	{7, 2,},
	{8, 3,},
	{9, 4,},
	{10, 5,},
	{11, 6,},
	{12, 7,},
	{13, 8,},
	{14, 9,},
	{15, 10,},
	{16, 11,},
	{17, 12,},
	{19, 13,},
	{20, 14,},
	{21, 15,},
	{22, 16,},
	{24, 17,},
	{25, 18,},
	{27, 19,},
	{29, 20,},
	{30, 21,},
	{32, 22,},
	{34, 23,},
	{37, 24,},
	{39, 25,},
	{41, 26,},
	{44, 27,},
	{47, 28,},
	{50, 29,},
	{53, 30,},
	{56, 31,},
	{60, 32,},
	{64, 33,},
	{68, 34,},
	{72, 35,},
	{77, 36,},
	{82, 37,},
	{87, 38,},
	{93, 39,},
	{98, 40,},
	{105, 41,},
	{111, 42,},
	{119, 43,},
	{126, 44,},
	{134, 45,},
	{143, 46,},
	{152, 47,},
	{162, 48,},
	{172, 49,},
	{183, 50,},
	{195, 51,},
	{207, 52,},
	{220, 53,},
	{234, 54,},
	{249, 55,},
	{265, 56,},
	{282, 57,},
	{300, 58,},
	{316, 59,},
	{333, 60,},
	{360, 61,},
};
static int base_luminance_revB[][2] = {
	{5, 115,},
	{6, 115,},
	{7, 115,},
	{8, 115,},
	{9, 115,},
	{10, 115,},
	{11, 115,},
	{12, 115,},
	{13, 115,},
	{14, 115,},
	{15, 115,},
	{16, 115,},
	{17, 115,},
	{19, 115,},
	{20, 115,},
	{21, 115,},
	{22, 115,},
	{24, 115,},
	{25, 115,},
	{27, 115,},
	{29, 115,},
	{30, 115,},
	{32, 115,},
	{34, 115,},
	{37, 115,},
	{39, 115,},
	{41, 115,},
	{44, 115,},
	{47, 115,},
	{50, 115,},
	{53, 115,},
	{56, 115,},
	{60, 115,},
	{64, 115,},
	{68, 115,},
	{72, 122,},
	{77, 131,},
	{82, 140,},
	{87, 149,},
	{93, 158,},
	{98, 164,},
	{105, 177,},
	{111, 188,},
	{119, 199,},
	{126, 210,},
	{134, 222,},
	{143, 234,},
	{152, 246,},
	{162, 254,},
	{172, 254,},
	{183, 254,},
	{195, 254,},
	{207, 254,},
	{220, 254,},
	{234, 254,},
	{249, 254,},
	{265, 272,},
	{282, 287,},
	{300, 303,},
	{316, 316,},
	{333, 335,},
	{360, 360,},
};

static int gradation_offset_revB[][9] = {
/*	V255 V203 V151 V87 V51 V35 V23 V11 V3 */
	{0, 8, 12, 19, 22, 23, 25, 28, 28},
	{0, 7, 11, 16, 20, 21, 23, 23, 23},
	{0, 7, 10, 14, 19, 20, 22, 22, 22},
	{0, 7, 10, 14, 18, 19, 22, 22, 22},
	{0, 6, 8, 12, 15, 17, 20, 20, 20},
	{0, 6, 8, 11, 14, 16, 18, 20, 20},
	{0, 6, 7, 11, 13, 15, 18, 20, 20},
	{0, 6, 7, 10, 12, 14, 17, 19, 19},
	{0, 6, 7, 10, 12, 13, 17, 19, 19},
	{0, 5, 7, 9, 11, 13, 15, 18, 18},
	{0, 5, 7, 9, 11, 12, 15, 18, 18},
	{0, 4, 6, 8, 10, 11, 14, 17, 17},
	{0, 4, 5, 7, 10, 11, 14, 16, 17},
	{0, 4, 4, 7, 9, 10, 13, 15, 16},
	{0, 4, 4, 6, 9, 9, 13, 14, 16},
	{0, 4, 4, 6, 9, 9, 13, 13, 15},
	{0, 4, 4, 5, 8, 9, 12, 12, 13},
	{0, 4, 4, 5, 8, 8, 10, 12, 12},
	{0, 4, 4, 5, 7, 8, 10, 12, 11},
	{0, 4, 4, 5, 7, 7, 10, 11, 11},
	{0, 4, 4, 4, 6, 7, 8, 11, 11},
	{0, 4, 4, 4, 6, 7, 9, 10, 10},
	{0, 4, 4, 4, 6, 6, 8, 9, 10},
	{0, 4, 4, 4, 5, 6, 7, 8, 10},
	{0, 4, 3, 4, 4, 5, 7, 8, 10},
	{0, 3, 3, 4, 4, 4, 7, 7, 9},
	{0, 3, 3, 3, 4, 4, 7, 7, 9},
	{0, 3, 3, 3, 4, 4, 7, 7, 9},
	{0, 3, 3, 3, 4, 3, 6, 7, 8},
	{0, 3, 3, 3, 3, 3, 6, 6, 7},
	{0, 3, 3, 3, 3, 3, 5, 6, 7},
	{0, 3, 3, 3, 3, 3, 5, 6, 7},
	{0, 2, 3, 3, 3, 3, 5, 6, 7},
	{0, 2, 3, 3, 3, 3, 5, 6, 7},
	{0, 2, 3, 3, 3, 2, 4, 5, 6},
	{0, 2, 3, 3, 2, 2, 4, 5, 6},
	{0, 2, 3, 3, 2, 2, 4, 5, 6},
	{0, 2, 3, 3, 2, 2, 4, 4, 6},
	{0, 1, 3, 3, 2, 2, 4, 4, 6},
	{0, 0, 3, 3, 2, 2, 3, 4, 6},
	{0, 1, 3, 3, 2, 2, 3, 4, 5},
	{0, 2, 3, 2, 2, 2, 3, 5, 4},
	{0, 1, 2, 3, 2, 3, 3, 5, 4},
	{0, 1, 2, 2, 2, 2, 3, 4, 4},
	{0, 1, 2, 2, 2, 2, 3, 4, 4},
	{0, 1, 2, 2, 2, 2, 2, 4, 4},
	{0, 2, 2, 3, 2, 2, 2, 3, 4},
	{0, 2, 3, 3, 2, 2, 2, 3, 4},
	{0, 3, 3, 3, 2, 2, 2, 3, 4},
	{0, 3, 3, 2, 2, 2, 1, 3, 4},
	{0, 1, 3, 2, 1, 1, 1, 2, 4},
	{0, 3, 3, 2, 1, 1, 1, 3, 4},
	{0, 3, 3, 1, 1, 1, 1, 2, 4},
	{0, 2, 3, 1, 1, 1, 1, 2, 4},
	{0, 2, 3, 1, 1, 1, 1, 2, 2},
	{0, 2, 3, 1, 1, 1, 0, 1, 1},
	{0, 2, 3, 1, 0, 1, 1, 1, 1},
	{0, 2, 1, 0, 0, 0, 0, 0, 1},
	{0, 2, 2, 1, 0, 0, 1, 1, 1},
	{0, 1, 1, 1, 0, 0, 0, 0, 1},
	{0, 1, 0, -1, -1, -1, -1, 0, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
};
static int rgb_offset_revB[][RGB_COMPENSATION] = {
/*	R255 G255 B255 R203 G203 B203 R151 G151 B151 R87 G87 B87 R51 G51 B51 R35 G35 B35  R23 G23 B23 R11 G11 B11*/
	{-3, 0, -3, -4, 0, -4, -4, 1, -4, -11, 3, -11, -15, 5, -13, -10, 4, -9, -11, 4, -16, 4, 5, -22},
	{-3, 0, -3, -2, 0, -2, -4, 1, -4, -9, 3, -10, -14, 5, -11, -10, 4, -9, -9, 4, -15, 4, 5, -22},
	{-2, 0, -2, -2, 0, -2, -3, 0, -3, -8, 3, -10, -14, 5, -11, -10, 4, -9, -8, 4, -14, 4, 5, -22},
	{-2, 0, -2, -2, 0, -2, -3, 0, -3, -7, 3, -9, -13, 5, -9, -10, 4, -9, -8, 4, -14, 4, 5, -22},
	{-2, 0, -2, -1, 0, -1, -2, 0, -2, -6, 3, -8, -10, 5, -12, -8, 4, -8, -8, 4, -14, 4, 5, -22},
	{-1, 0, -1, -2, 0, -1, -2, 0, -3, -5, 3, -7, -10, 5, -14, -8, 4, -9, -8, 4, -15, 4, 5, -22},
	{-1, 0, -1, -2, 0, -1, -2, 0, -2, -5, 3, -7, -11, 4, -13, -9, 4, -9, -9, 4, -15, 4, 5, -22},
	{-1, 0, -1, -1, 0, -1, -2, 0, -2, -4, 3, -6, -9, 4, -13, -9, 4, -9, -7, 4, -13, 4, 5, -22},
	{-1, 0, -1, -1, 0, -1, -2, 0, -2, -4, 3, -6, -11, 4, -12, -11, 4, -9, -8, 4, -14, 4, 5, -22},
	{-1, 0, -1, -1, 0, -1, -1, 0, -1, -4, 3, -6, -8, 4, -13, -9, 4, -9, -9, 4, -15, 4, 5, -22},
	{-1, 0, -1, -1, 0, -1, -1, 0, -1, -3, 3, -5, -9, 4, -12, -9, 4, -9, -9, 3, -13, 3, 5, -22},
	{-1, 0, -1, -1, 0, -1, -1, 0, -1, -4, 2, -6, -9, 4, -10, -11, 3, -9, -8, 4, -16, 3, 5, -22},
	{-1, 0, -1, 0, 0, 0, -1, 0, -1, -4, 2, -6, -10, 4, -10, -11, 3, -9, -7, 4, -14, 3, 5, -22},
	{-1, 0, -1, 0, 0, 0, -1, 0, -1, -2, 2, -4, -10, 4, -12, -11, 3, -9, -9, 5, -15, 2, 5, -21},
	{-1, 0, -1, 0, 0, 0, 0, 0, -1, -3, 2, -4, -9, 4, -10, -11, 3, -9, -8, 4, -15, 1, 5, -21},
	{-1, 0, -1, 0, 0, 0, 0, 0, -1, -2, 2, -4, -10, 4, -10, -11, 3, -9, -9, 4, -15, 1, 5, -21},
	{-1, 0, -1, 0, 0, 0, 0, 0, -1, -1, 2, -3, -10, 4, -9, -11, 3, -8, -8, 4, -15, 1, 5, -21},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, -2, 2, -4, -8, 3, -10, -11, 3, -8, -6, 4, -15, 1, 5, -21},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, -2, 2, -4, -9, 3, -10, -11, 3, -8, -5, 4, -14, 1, 5, -21},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 1, -4, -9, 3, -10, -11, 3, -8, -4, 4, -13, 1, 5, -21},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 1, -4, -9, 3, -10, -11, 3, -6, -4, 4, -12, 1, 5, -21},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, -2, 1, -3, -8, 3, -11, -12, 2, -7, -3, 4, -12, 1, 5, 20},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 1, -3, -5, 3, -9, -11, 2, -7, -2, 3, -11, 1, 5, -21},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 1, -3, -7, 3, -10, -11, 2, -5, -2, 3, -10, 1, 5, -21},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 1, -2, -7, 3, -10, -11, 2, -4, -1, 3, -10, 1, 5, -21},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, -2, -8, 3, -9, -11, 2, -4, -3, 3, -8, 0, 5, -21},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, -2, -8, 2, -9, -10, 2, -3, -2, 3, -7, 1, 5, -21},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, -1, -6, 2, -9, -9, 1, -4, -2, 3, -5, 1, 5, -21},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, -1, -3, 2, -8, -9, 1, -4, -1, 3, -6, 0, 4, -18},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, -1, -5, 2, -7, -8, 1, -4, -1, 2, -6, 1, 4, -18},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, -1, -4, 2, -7, -8, 1, -3, -2, 2, -5, 0, 4, -18},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, -4, 2, -8, -7, 1, -2, -1, 2, -4, 0, 4, -18},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, -4, 2, -7, -8, 1, -2, -2, 2, -4, 0, 4, -17},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, -4, 2, -6, -8, 1, -2, -1, 2, -4, 0, 4, -17},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -4, 2, -6, -6, 1, -1, -1, 1, -4, -1, 4, -18},
	{0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, -1, -5, 2, -6, -7, 1, -1, -3, 1, -4, -1, 4, -17},
	{0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, -1, -3, 2, -5, -7, 1, -2, -2, 1, -3, -1, 4, -15},
	{0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, -1, -2, 1, -6, -4, 1, -2, -3, 1, -3, -2, 4, -15},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, -2, 0, 2, -5, -3, 1, -1, -3, 1, -2, -1, 4, -15},
	{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, -2, 1, -6, -1, 1, -2, -5, 1, -3, -1, 4, -15},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, -1, 1, -5, -1, 1, -2, -5, 1, -3, -1, 4, -15},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 1, -5, -2, 1, -2, -4, 1, -3, -2, 4, -15},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, -4, -4, 1, -2, -4, 0, -2, -2, 4, -15},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, -1, -1, 1, -3, -3, 1, -2, -4, 0, -1, -2, 4, -15},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, -3, -3, 1, 0, -4, 0, -4, -2, 4, -14},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -2, 0, 1, 0, -3, 1, -3, -2, 1, -2, -2, 4, -14},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, -2, -3, 1, -2, -3, 0, -3, -2, 4, -15},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1, 1, 1, -2, -4, 1, -2, -3, 0, -3, -2, 4, -16},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, -1, 0, -2, -3, 1, -2, -3, 0, -2, -2, 3, -15},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, -1, 0, -2, -3, 1, 0, -3, 0, -2, -2, 3, -13},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 1, 1, -1, -1, 0, -2, -5, 0, -1, -2, 4, -11},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, -1, -3, 0, -2, -1, 0, 0, -2, 2, -10},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, -1, -1, 1, -1, 1, 0, 1, -2, 2, -9},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, -2, -2, 0, -1, 0, 0, 0, -2, 2, -8},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, -2, -1, 0, -1, 1, 0, 2, -2, 1, -8},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, -1, 0, 0, 0, 0, 0, 0, -2, 1, -7},
	{0, 0, 0, -2, 0, -1, 0, 0, 0, 3, 0, 1, 0, 0, -1, -2, 0, 0, -1, 0, 1, -2, 1, -6},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 1, 0, 0, -1, 0, 0, -1, -1, 0, 0, -2, 1, -4},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 2, 0, 0, -1, 0, -1, 0, 0, 2, -1, 1, -4},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 1, -3, 0, -2, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, -1, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};
#endif