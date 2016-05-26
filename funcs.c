/*****
 *  Code for examination project in High Performance Computing and Programming
 * 
 *  funcs.c functions implementation file
 *
 *  Author: Marcus Holm
 *  Modified by: Elias Rudberg
 *
 **/

#include "funcs.h"

char spectralTypes[9] = {'O', 'B', 'A', 'F', 'G', 'K', 'M', 'L', 'T'};

// Returns uniformly distributed random numbers from [0.0, 1.0].
float uniform0to1Random() 
{
  float r = random();
  return r / ((float)RAND_MAX + 1);
}

// Returns uniformly distributed random numbers from [-a, b].
float myRandom(float a, float b) 
{
  return (-a + b) * uniform0to1Random() + a;
}

float distance(float x, float y, float z) 
{
  return sqrt(pow(x,2) + pow(y,2) + pow(z,2));
}

void create_random_array(star_t * stars, int size)
{
  int i;
    for (i=0; i<size; i++)
    {
      star_t star;
      star.index = i;
      star.spectralType = spectralTypes[rand() % 9];
      star.subType = rand() % 10;
      star.magnitude = myRandom(-10, 20);
      star.designation[0] = star.spectralType;
      star.designation[1] = star.subType + '0';
      star.designation[2] = '.';
      star.designation[3] = star.index + '0';
      star.designation[4] = star.index + '\0';
      star.position.x = myRandom(-1e5, 1e5);
      star.position.y = myRandom(-1e5, 1e5);
      star.position.z = myRandom(-3e3, 3e3);
      stars[i] = star;
    } 
}

void print_stars(star_t* array, int n)
{
  int i;
  printf("\nprint_stars, n = %d:\n", n);
  for(i = 0; i<n; i++)
    printf("%s ",array[i].designation);
  printf("\n");
}


float_t starfunc(star_t a, star_t b)
{
  unsigned short x = a.subType;
  unsigned short y = b.subType;
  return sqrt(x + y + x*y/0.6);
}


void sort(star_t* array, int n) 
{
  int i, j;
  for (i = 1; i < n; ++i)
  {
    star_t temp = array[i];
    j = i-1;
    while (j >= 0 && distance(array[j].position.x, array[j].position.y, array[j].position.z) > 
      distance(temp.position.x, temp.position.y, temp.position.z)) 
    {
      array[j+1] = array[j];
      j--;
    }
    array[j+1] = temp;
  }
}

void fill_matrix(star_t * array, float_t **matrix, int size)
{
  
}

void print_matrix(float_t** theMatrix, int n)
{
  int i, j;
  printf("\nprint_matrix, n = %d:\n", n);
  for(i = 0 ; i < n; i++)
    {
      for(j = 0 ; j < n ; j++)
	printf("%.2f " , theMatrix[i][j]);
      putchar('\n');
    }
}

/*
hist_param_t generate_histogram(float_t **matrix, int *histogram, int mat_size, int hist_size)
{
  
}
*/

void display_histogram(int *histogram, hist_param_t histparams)
{
  printf("\ndisplay_histogram:\n");
  int i,j;
  for(i = 0; i < histparams.hist_size && histparams.bin_size*i < histparams.max; i++)
    {
      printf("%11.3e ", histparams.bin_size*i+histparams.min);
    }
  printf("%11.3e\n", histparams.max);
  for(j = 0; j < i; j++)
    {
      printf("%11d ", histogram[j]);
    }
  printf("\n");
}
