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
float_t uniform0to1Random() 
{
  float_t r = random();
  return r / ((float_t)RAND_MAX + 1);
}

// Returns uniformly distributed random numbers in [a, b].
float_t myRandom(float_t a, float_t b) 
{
  return (-a + b) * uniform0to1Random() + a;
}

// Calculate the distance from the origin to the point 'a'.
float_t distanceFromOrigin(point_t a) 
{
  float_t dx = a.x * a.x;
  float_t dy = a.y * a.y;
  float_t dz = a.z * a.z;
  return sqrt(dx + dy + dz);
}

// Calculate the distance between the points 'a' and 'b'.
float_t distance(point_t a, point_t b) 
{
  float_t dx = b.x - a.x;
  float_t dy = b.y - a.y;
  float_t dz = b.z - a.z;
  return sqrt(dx*dx + dy*dy + dz*dz);
}

void create_random_array(star_t * stars, int size)
{
  int i = 0;
  do 
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
    i++;
  } while(i < size);
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

void insertion_sort(star_t* array, int n) 
{
  int i = 1, j;
  while (i < n) 
  {
    star_t temp = array[i];
    float_t d = distanceFromOrigin(temp.position);
    j = i - 1;
    while (j >= 0 && distanceFromOrigin(array[j].position) > d) 
    {
      array[j+1] = array[j];
      j--;
    }
    array[j+1] = temp;
    i++;
  }
}

void merge(star_t* arr, int l, int m, int r)
{
  int i, j, k;
  int n1 = m - l + 1;
  int n2 =  r - m;

  star_t* L = (star_t*) malloc(n1 * sizeof(star_t));
  star_t* R = (star_t*) malloc(n2 * sizeof(star_t));

  for (i = 0; i < n1; i++)
    L[i] = arr[l + i];
  for (j = 0; j < n2; j++)
    R[j] = arr[m + 1+ j];

  i = 0; 
  j = 0; 
  k = l; 
  while (i < n1 && j < n2)
  {
    if(distanceFromOrigin(L[i].position) <= distanceFromOrigin(R[j].position))
    {
      arr[k] = L[i];
      i++;
    }
    else
    {
      arr[k] = R[j];
      j++;
    }
    k++;
  }

  while (i < n1)
  {
    arr[k] = L[i];
    i++;
    k++;
  }

  while (j < n2)
  {
    arr[k] = R[j];
    j++;
    k++;
  }

  free(L);
  free(R);
}

void merge_sort_helper(star_t* arr, int l, int r)
{
  if (l < r)
  {
    int m = l+(r-l)/2;
    merge_sort_helper(arr, l, m);
    merge_sort_helper(arr, m+1, r);
    merge(arr, l, m, r);
  }
}

void merge_sort(star_t* stars, int n) 
{
  merge_sort_helper(stars, 0, n-1);
}

// If the size of the array is greater than 43, we use merge sort
// in order to improve the performance while decreasing the runtime.
void sort(star_t* array, int n) 
{
//  if (n >= 2 && n <= 43) 
//  {
//    insertion_sort(array, n);
//  }
//  else 
//  {
    merge_sort(array, n);
    printf("Merge sort was used. \n");
//  }
}

void fill_matrix(star_t * array, float_t **matrix, int size)
{
  int i, j;
  for (i = 0; i < size; ++i)
    for (j = 0; j < size; ++j)
      matrix[i][j] = distance(array[i].position, array[j].position) + starfunc(array[i], array[j]);
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

// Find the minimum in the array.
float_t getMinimum(float_t* arr, int size)
{
  float_t min = arr[0];
  int i;
  for (i = 1; i < size; ++i)
    if (arr[i] < min)
      min = arr[i];
  return min;
}

// Find the maximum in the array.
float_t getMaximum(float_t* arr, int size)
{
  float_t max = arr[0];
  int i;
  for (i = 1; i < size; ++i)
    if (arr[i] > max)
      max = arr[i];
  return max;
}

float_t* generate_histogram_values(float_t **matrix, int mat_size) 
{
  int size = (mat_size - 2) * (mat_size - 2);
  float_t* array = (float_t*) malloc(size * sizeof(float_t));

  float_t left, right, up, down, mean;
  
  int count = 0;
  int i, j;
  for (i = 1; i < mat_size - 1; ++i)
    for (j = 1; j < mat_size - 1; ++j)  
    {
      left = fabs(matrix[i][j] - matrix[i][j-1]);
      right = fabs(matrix[i][j] - matrix[i][j+1]);
      up = fabs(matrix[i][j] - matrix[i-1][j]);
      down = fabs(matrix[i][j] - matrix[i+1][j]);
    }
    mean = (left + right + up + down) / 4.0;
    array[count] = mean;
    count++;
  return array;
}

hist_param_t generate_histogram(float_t **matrix, int *histogram, int mat_size, int hist_size)
{
  int size = (mat_size - 2) * (mat_size - 2);
  hist_param_t temp;
  temp.hist_size = hist_size;

  float_t* values = generate_histogram_values(matrix, mat_size);

  temp.min = getMinimum(values, size);
  temp.max = getMaximum(values, size);
  temp.bin_size = (temp.max - temp.min) / (float_t)hist_size;

  float_t start = temp.min;
  float_t end = start + temp.bin_size;

  int i, j, count;
  for (i = 0; i < hist_size; ++i)
  {
    count = 0;

    if (i == hist_size - 1)
    {
      for (j=0; j < size; j++)
        if (values[j] >= start && values[j] <= temp.max)
          count ++;
    }
    else 
    {
      for (j=0; j < size; j++)
        if (values[j] >= start && values[j] <= end)
          count ++;
    }

    histogram[i] = count;
    start = end;
    end += temp.bin_size; 
  }

  free(values);

  return temp;
}

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
