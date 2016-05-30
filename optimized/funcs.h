/*****
 *  Code for examination project in High Performance Computing and Programming
 * 
 *  funcs.h functions header file
 *
 *  Author: Marcus Holm
 *  Modified by: Elias Rudberg
 *
 **/

#ifndef _FUNCS_H
#define _FUNCS_H

#include "common.h"

#define TRUE 1
#define FALSE 0

void create_random_array(star_t* stars, int size);
void sort(star_t* array, int n);
void print_stars(const star_t* array, int n);

void fill_matrix(star_t* __restrict array, float_t** __restrict matrix, int size);
void print_matrix(float_t** theMatrix, int n);

hist_param_t generate_histogram(float_t** __restrict matrix, int* __restrict histogram, int mat_size, int hist_size);

void display_histogram(const int *histogram, hist_param_t histparams);

#endif
