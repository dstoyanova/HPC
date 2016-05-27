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

// float_t uniform0to1Random();
// float_t myRandom(float_t a, float_t b);

// float_t distanceFromOrigin(point_t a);
// float_t distance(point_t a, point_t b);

void create_random_array(star_t * array, int size);
void sort(star_t* array, int n);
void print_stars(star_t* array, int n);

void fill_matrix(star_t * array, float_t **matrix, int size);
void print_matrix(float_t** matrix, int n);

// float_t getMinimum(float_t* arr, int size);
// float_t getMaximum(float* arr, int size);

// float getMinimum(float* arr, int size);
// float getMaximum(float* arr, int size);

hist_param_t generate_histogram(float_t **matrix, int *histogram, int mat_size, int hist_size);

void display_histogram(int *histogram, hist_param_t histparams);

#endif
