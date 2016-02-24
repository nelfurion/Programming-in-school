//--------------------------------------------
//NAME: Radostin Angelov
//CLASS: XIb
//NUMBER: 27
//PROBLEM: #2
//FILE NAME: shell.c
//FILE PURPOSE:
// Implements a simple shell.
//---------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

//--------------------------------------------
//FUNCTION: count_params
//Receives a line of text and counts the parameters, supposedly split by ' ';
//PARAMETERS:
//const char* cmdline - the given line of text,
//in which we want to count the parameters
//----------------------------------------------
int count_params(const char* cmdline);
//--------------------------------------------
//FUNCTION: parse_cmdline
//Parses a line of text, calling count_params, and splitting the text by ' '.
//Then returns char** of the params.
//PARAMETERS:
//const char* cmdline - the line of text we want to parse
//----------------------------------------------
char** parse_cmdline(const char* cmdline);
//--------------------------------------------
//FUNCTION: start_process
//Forks the process and executes the given command with the given parameters,
//using execv. It looks for changes in the state of the fork with waitpid
// and also handles errors from executing the command.
//PARAMETERS:
//char** params - represents the command as params[0] and the parameters
//----------------------------------------------
int start_process(char** params);
//--------------------------------------------
//FUNCTION: read_line
//Reads a line from stream file.
//PARAMETERS:
//FILE* stream - the stream from which we want to read.
//----------------------------------------------
char* read_line(FILE* stream);

int count_params(const char* cmdline)
{
	int params_count = 0;
    int length = strlen(cmdline);
    int inword = 0;
    int i;
    for (i = 0; i < length - 1; i++)
    {
        switch(cmdline[i])
        {
            case ' ':
            case '\0':
            case '\r':
            case '\t':
                if (inword)
                {
                    params_count++;
                    inword = 0;
                }
            break;
            case '\n':
                printf("read new line");
            break;
            default:
                inword = 1;
            break;
        }
    }

    //increment by one to count all the parameters
    params_count++;
    return params_count;
}

char** parse_cmdline(const char* cmdline)
{
	int params_count = count_params(cmdline);
    char** parsed_params = malloc(sizeof(char*) * (params_count + 1));
    char* command = strdup(cmdline);
    char* token;
    int i = 0;
    //split the parameters with strsep and add them to the array
    while((token = strsep(&command, " ")) != NULL
    	&& i < params_count)
    {
        if (i == params_count - 1 && strlen(token) > 0)
        {
        	//remove \n from the last parameter
            parsed_params[i] = strsep(&token, "\n");
        }
        else if (strlen(token) > 0)
        {
            int length = strlen(token);
            parsed_params[i] = malloc(length);
            strncpy(parsed_params[i], token, length);
			i++;
        }
    }

	parsed_params[params_count] = NULL;
    return parsed_params;
}

int start_process(char** params)
{
    pid_t pid = fork();
    if (pid == -1)
    {
    	//check for fork error
        char* error = strerror(errno);
        printf("fork: %s\n", error);
        return 1;
    }
    else if (pid == 0)
    {
    	//check for errors while executing the command
        execv(params[0], params);
        char* error = strerror(errno);
        printf("%s: %s\n", params[0], error);
        return 0;
    }
    else
    {
		//looks for fork state changes, so it won't become a zombie process
        int childStatus;
        waitpid(pid, &childStatus, 0);
        return 1;
    }
}

char* read_line(FILE* stream)
{
	char *line = NULL;
	size_t length = 0;
	ssize_t chars_read = getline(&line, &length, stream);
	if (chars_read > 1)
    {
	    //TODO: should it end on exit?
	    if (line[strlen(line)-1] == '\n')
	    {
			line[strlen(line)-1] = '\0';
		}
				printf("line: %s\n", line);
	    return line;
    }
    else if(line[0] == '\n')
    {
		free(line);
       	return NULL;
    }
}

int main(void)
{
    char* line;
    while (1)
    {
        line = read_line(stdin);
        if (line != NULL)
        {
        	char** command = parse_cmdline(line);
        	start_process(command);
        }
    }

    free(line);
    return 0;
}
