//--------------------------------------------
// NAME: Radostin Angelov
// CLASS: Xib
// NUMBER: 27
// PROBLEM: #1
// FILE NAME: dynamic_array.h
// FILE PURPOSE:
// implement a dynamic array functionality
// this can be used for everything, but in the purpose
// of this homework, we will use it to read data from files and stdin;
// the point of this is to be able to get the last 10 lines from the input
//---------------------------------------------

// how much bytes we read at a time from a file
// or in other words the initial size of our array's data
#define read_buffer_size 200
#include <stdlib.h>
#include <stdio.h>

// struct implementation of the dynamic_array
typedef struct dynamic_array_t {
	char* data;
	int index;
	int max;
} Dynamic_array;

void reallocate_array(Dynamic_array* arr);
void initialize_array(Dynamic_array* arr);
void array_add(Dynamic_array* arr, char c);

//--------------------------------------------
// FUNCTION: initialize_array
//  initializes default values for the dynamic array's:
// char* data
// int index
// int max
// --- the actual struct is created elswhere in the code, but here we set default
// --- values to its properties
// PARAMETERS:
// Dynamic_array* - struct dynamic_array_t
// --- the dinamic array which we want to initialize
//----------------------------------------------
void initialize_array(Dynamic_array* arr)
{
	arr->data = malloc(sizeof(char) * read_buffer_size * 2);
	arr->index = 0;
	arr->max = read_buffer_size;
}

//--------------------------------------------
// FUNCTION: array_add
//  adds one char to the dinamic array's char* data
// PARAMETERS:
// Dynamic_array*  - struct dynamic_array_t
// --- pointer for the dynamic array, that we want to use
// char c - the char we want to add to the array
//----------------------------------------------
void array_add(Dynamic_array* arr, char c)
{
	if(arr->index >= arr->max)
	{
		reallocate_array(arr);
	}
	else
	{
		arr->data[arr->index] = c;
		arr->index++;
	}
}

//--------------------------------------------
// FUNCTION: reallocate_array
// our array's char* data has allocated memory
// 1.we reach the last index that is allocated
// 2. we want ot add more data to the array
// 3. we get segmentation fault
// 4. so we allocate more data, and we copy the previous into the new array
// 5. in this implementation, as in the default one i beleive, we allocate exactly
// twice the size of the previous one
// PARAMETERS:
// Dynamic_array*  - struct dynamic_array_t
// --- the array which arr->data we want to increase
//----------------------------------------------
void reallocate_array(Dynamic_array* arr)
{
	char temp_data[arr->index];
	int i;
	for(i = 0; i < arr->index; i++)
	{
		temp_data[i] = arr->data[i];
	}

	arr->max *= 2;

	arr->data = malloc(sizeof(char) * arr->max);

	for(i = 0; i < arr->index; i++)
	{
		arr->data[i] = temp_data[i];
	}
}
