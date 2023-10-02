/*
 * std_types.h

 *
 *  Created on: 1 September 2016
 *      Author: Mohamed Taha
 */

#ifndef STD_TYPES_MT_H_
#define STD_TYPES_MT_H_


typedef char * p2sint8_t;

typedef unsigned char uint8_t;
typedef char sint8_t;

//typedef unsigned short int uint16_t;
typedef short sint16_t;
typedef unsigned long uint32_t;
typedef long sint32_t;
typedef unsigned char boolean_t;
typedef float FB32_t;
typedef double FB64_t; 
typedef char * ptr2char_t;
typedef long int sint32_t;

typedef unsigned char       u8_t ; 
typedef unsigned short int  u16_t;
typedef unsigned long int   u32_t;
typedef unsigned long long  u64_t;

typedef signed char         s8_t ;
typedef signed short int    s16_t;
typedef signed long int     s32_t;

typedef float               f32_t;
typedef double              f64_t;
typedef long double         f96_t;

#define BYTE sint8_t
#define TRUE 1
#define FALSE 0

#define FAILURE  0
#define SUCESS   1
#endif /* STD_TYPE_H_ */
