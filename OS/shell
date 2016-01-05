#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

char** parse_cmdline(const char* cmdline)
{
    int params_count = 0;
    int index = 0;
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
    
    char** parsed = malloc(sizeof(char*) * params_count);
    char* not_const_command = strdup(cmdline);
    char* token;
    i = 0;
    while((token = strsep(&not_const_command, " ")) != NULL)
    {
        int length;
        if (i == params_count)
        {
            length = strlen(token) -1;
            parsed[i] = malloc(strlen(token) -1);
        }
        else
        {
            length = strlen(token);
            parsed[i] = malloc(strlen(token));
        }
        
        strncpy(parsed[i], token, length);      
        i++;
    }
    return parsed;
}

int start_process(char** params)
{
    // Fork process
    pid_t pid = fork();

    // Error
    if (pid == -1) {
        char* error = strerror(errno);
        printf("fork: %s\n", error);
        return 1;
    }

    // Child process
    else if (pid == 0) {
        // Execute command
        execv(params[0], params);  
        char* error = strerror(errno);
        printf("%s: No such file or directory.\n", params[0]);
        return 0;
    }

    // Parent process
    else {
        // Wait for child process to finish
        int childStatus;
        waitpid(pid, &childStatus, 0);
        return 1;
    }
}

int main(void)
{
//    FILE *stream;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

//    stream = fopen("./shell.c", "r");
    /*if (stream == NULL)
       exit(EXIT_FAILURE);*/

    while (1) 
    {
        int chars_read = getline(&line, &len, stdin);        
        if (chars_read > 1)
        {
            //TODO: fix this shit
            if (strcmp(line, "exit") == 0)
            {
                printf("read exit command");
                break;
            }
            
            
            char** command = parse_cmdline(line);
            start_process(command);
        }
        else if(chars_read == 1)
        {
            printf("didnt read anything"); //TODO: return correct response
        }
    }

    free(line);
    return 0;
}
