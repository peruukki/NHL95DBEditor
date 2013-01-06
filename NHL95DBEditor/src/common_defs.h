#pragma once

/* Boolean values */
#define TRUE 1
#define FALSE 0

/* Number of elements in an array */
#define ELEM_COUNT(x) sizeof(x) / sizeof(x[0])

/* Boolean value type */
typedef int bool_t;

/* Number value of one byte */
typedef unsigned char number_1_t;

/* Number value of two bytes */
typedef unsigned short number_2_t;

/* Signed number value of two bytes */
typedef signed short number_s_2_t;

/* Index value */
typedef unsigned char index_t;

/* File offset */
typedef unsigned int offset_t;
