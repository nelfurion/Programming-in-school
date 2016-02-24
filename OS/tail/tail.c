//--------------------------------------------
// NAME: Radostin Angelov
// CLASS: Xib
// NUMBER: 27
// PROBLEM: #1
// FILE NAME: tail.c
// FILE PURPOSE:
// Implement unix tail command.
//---------------------------------------------
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h> //delete this
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

#include "dynamic_array.h"

#define READ_BUFFER_SIZE 200
#define STDIN_OPTION '-'
#define STANDARD_INPUT_NAME "standard input"
#define INPUT_STREAM_NAME_FORMAT "==> %s <==\n"
//We read 11 '\n' symbols, to start printing from the end of the previous line.
#define LINES_TO_READ 10

static char** lines_read;

int read_from_file(int file_descriptor, char* read_buffer, int count, Dynamic_array* arr);
void print_from_file(Dynamic_array arr);
int try_open_file(char* path);
void read_from_stdin(char* read_buffer, Dynamic_array* result);
void print_stdin_tail(Dynamic_array arr);
void print_string(char * name);

//--------------------------------------------
// FUNCTION: main
//  program starting point
// PARAMETERS:
// args_count - count of argumets given when starting the program
// char** argv - the actual arguments given when starting the program
//----------------------------------------------

int main(int args_count, char** argv)
{
	int i;

	char read_buffer[READ_BUFFER_SIZE];

	//one argument is given by default when we start the program
	//even if we don't give any
	// in this case we have to read from the stdin
	if(args_count == 1)
	{
		Dynamic_array result;
		initialize_array(&result);

		read_from_stdin(read_buffer, &result);
		print_stdin_tail(result);
	}
	else
	{
		for(i = 1; i < args_count; i++)
		{
			if(argv[i][0] == STDIN_OPTION || args_count == 1)
			{
				if(args_count > 2)
				{
					print_string(STANDARD_INPUT_NAME);
				}

				Dynamic_array result;
				initialize_array(&result);

				read_from_stdin(read_buffer, &result);
				print_stdin_tail(result);
				if(args_count > 2 && i < args_count - 1)
				{
					write(STDOUT_FILENO, "\n", 1);
				}
			}
			else
			{
				int fd = try_open_file(argv[i]);
				if(fd >= 0)
				{
					if(args_count > 2)
					{
						print_string(argv[i]);
					}

					Dynamic_array result;
					initialize_array(&result);

					read_from_file(fd, read_buffer, READ_BUFFER_SIZE, &result);
					print_from_file(result);
					close(fd);
					//this is how the system function tail formats its output
					if(args_count > 2 && i < args_count - 1)
					{
						write(STDOUT_FILENO, "\n", 1);
					}
				}
			}
		}
	}

	return 0;
}

//--------------------------------------------
// FUNCTION: try_open_file
//  tries to open a file, and handles errors if the operation fails
// PARAMETERS:
// char* path - the path to the file we want to open
//----------------------------------------------
int try_open_file(char* path)
{
	int file_descriptor = open(path, O_RDONLY);
	if (file_descriptor < 0)
	{
		int errnum = errno;
		int total_size = 51 + 40;
		char error_message[total_size + 1];
		error_message[total_size] = '\0';
		if(errnum == ENOENT)
		{
			snprintf(error_message, total_size, "cannot open '%s' for reading: No such file or directory\n", path);
			int i;
			for(i = 0; i < total_size; i++)
			{
				write(STDERR_FILENO, &error_message[i], 1);
				if (error_message[i] == '\n')
				{
					break;
				}
			}
		}
		else if (errnum == EACCES)
		{
			snprintf(error_message, total_size, "cannot open '%s' for reading: Permission denied\n", path);
			int i;
			for(i = 0; i < total_size; i++)
			{
				write(STDERR_FILENO, &error_message[i], 1);
				if (error_message[i] == '\n')
				{
					break;
				}
			}
		}

		return -1;
	}
	else
	{
		return file_descriptor;
	}
}

//--------------------------------------------
// FUNCTION: print_string
// used to print input stream names - such as stdin, file names
// PARAMETERS:
// char* name - the name of the file / input stream
// --- the name is taken from the parameters given at program start
//----------------------------------------------
void print_string(char * name)
{
	char file_name[100];
	int name_size = 100;
	snprintf(file_name, name_size, INPUT_STREAM_NAME_FORMAT, name);
	int i;
	for(i = 0; i < 200; i++)
	{
		write(STDOUT_FILENO, &file_name[i], 1);
		if(file_name[i] == '\n')
		{
			break;
		}
	}

}

//--------------------------------------------
// FUNCTION: read_from_file
// reads all lines from a file into a dynamic array
// PARAMETERS:
// int file_descriptor - a file descriptor for the file we want to read
// char* read_buffer - a buffer to read to from the file,
// --- the buffer contents are then saved in the dynamic array
// int count - how many bytes do we want to read at a time
// --- in this case the size of the read buffer
// Dynamic_array * - struct dynamic_array_t
// --- the dynamic_array in which we save the read data
//----------------------------------------------
int read_from_file(int file_descriptor, char* read_buffer, int count, Dynamic_array* arr)
{
	int read_chars_count = read(file_descriptor, read_buffer, count);
	if (read_chars_count < 0)
	{
		print_string("error while reading from file");
	}

	int i;
	while(read_chars_count > 0)
	{
		for(i = 0; i < read_chars_count; i++)
		{
			array_add(arr, read_buffer[i]);
		}

		read_chars_count = read(file_descriptor, read_buffer, count);
		if (read_chars_count < 0)
		{
			print_string("error while reading from file\n");
		}
	}
}

//--------------------------------------------
// FUNCTION: print_from_file
// prints the last 10 lines from a file, to the standart output
// PARAMETERS:
// Dynamic_array - struct dynamic_array_t
// --- dynamic array, containing the data from the file
//----------------------------------------------
void print_from_file(Dynamic_array arr)
{
	int new_lines_count = 0;
	int position = 0;
	int i;
	for(i = arr.index - 1; i >= 0; i--)
	{
		if (arr.data[i] == '\n')
		{
			new_lines_count++;
			position = i + 1;
		}

		if(new_lines_count > LINES_TO_READ - 1)
		{
			break;
		}
	}

	if (new_lines_count < LINES_TO_READ - 1)
	{
		position = 0;
	}

	for(i = position; i < arr.index; i++)
	{
		write(STDOUT_FILENO, &arr.data[i], 1);
	}
}

//--------------------------------------------
// FUNCTION: read_from_stdin
// reads user input from the standard input - usually the terminal
// PARAMETERS:
// char* read_buffer - a buffer, to read to - we read predefined number of bytes
// --- in this case the read buffer size - in this function we use the constant
// --- READ_BUFFER_SIZE for this purpose
// Dynamic_array* result - struct dynamic_array_t
// --- a dynamic array to save the data from the read buffer
// --- used for printing the last 10 lines of the file
//----------------------------------------------
void read_from_stdin(char* read_buffer, Dynamic_array* result)
{
	int read_chars = read(STDIN_FILENO, read_buffer, READ_BUFFER_SIZE);

	while(read_chars > 0)
	{
		int i;
		for(i = 0; i < read_chars; i++)
		{
			array_add(result, read_buffer[i]);
		}

		read_chars = read(STDIN_FILENO, read_buffer, read_buffer_size);
		if(read_chars < 0)
		{
			print_string("error reading from stdin");
		}
	}
}

//--------------------------------------------
// FUNCTION: print_stdin_tail
// print the last 10 lines read from the standard input to the standard output
// PARAMETERS:
// Dynamic_array - struct dynamic_array_t
// --- dynamic array which has the read data
//----------------------------------------------
void print_stdin_tail(Dynamic_array arr)
{
	int new_lines_count = 0;
	int position = 0;
	int i;
	for(i = arr.index - 1; i >= 0; i--)
	{
		if (arr.data[i] == '\n')
		{
			new_lines_count++;
			position = i + 1;
		}

		if(new_lines_count > LINES_TO_READ - 1)
		{
			break;
		}
	}

	if (new_lines_count < LINES_TO_READ - 1)
	{
		position = 0;
	}

	for(i = position; i < arr.index; i++)
	{
		write(STDOUT_FILENO, &arr.data[i], 1);
	}
}
