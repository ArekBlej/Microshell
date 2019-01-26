#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <sys/wait.h>

char **tokens(char *commands)
{
    char *const commEnd = strlen(commands) + commands;
    int count = 0;
    char *token = commands;
    char *last_comma;

    while(*token)
    {
        if (*token == ' ')
        {
            count++;
            last_comma = token;
        }
        token++;
    }
    char **elementy = malloc((count + 1) *sizeof(char*));
    int i = 0;

    for (token = strtok(commands, " "); token && (token + strlen(token)) <= comm                                                                                        End; token = strtok(token + strlen(token) + 1, " "), ++i)
    {
        elementy[i] = token;
        if (elementy[i][strlen(elementy[i]) - 1] == '\n')
        {
            elementy[i][strlen(elementy[i]) - 1] = '\0';
        }
    }
    return elementy;
}

char *command_cd(char **elements, char *prev_path)
{
    if (strcmp(elements[1], "-") == 0)
    {
        strcpy(elements[1], prev_path);
    }
    getcwd(prev_path, sizeof(prev_path));
    if (chdir(elements[1]) != 0)
        printf("\nchdir() to %s failed\n\n", elements[1]);
    return prev_path;
}

void command_quit()
{
    printf("\nThe shell are going to close soon.\n\n");
    exit(0);
}

void command_help()
{
    printf("\nAuthor of microshell: Arkadiusz Blejwas, first year student of com                                                                                        puter science at WMI UAM.\n");
    printf("\nCommands:\n");
    printf("cd - This command changes current directory\n");
    printf("arguments: [..] or [direct_path] or [indirect_path]\n");
    printf("cp - This command copies files and directories\n");
    printf("arguments: [file1.txt] and [file2.txt]\n");
    printf("mkdir - This command creates directory\n");
    printf("arguments: [directory] \n");
    printf("rmdir - This command removes directory\n");
    printf("arguments: [directory] \n");
    printf("color - This cammand changes color of font or color of background\n"                                                                                        );
    printf("arguments: [default] or [[[black] or [white] or [yellow] or [red] or                                                                                         [blue] or [green]] and [[font] or [background]]] or [[inverse on] or [inverse o                                                                                        ff]]\n");
    printf("font - changes settings of font\n");
    printf("arguments: [[bold] or [italic] or [strikethrough] or [underline]] an                                                                                        d [[off] or [on]]\n");
    printf("ls - This command list the files and directories of current director                                                                                        y\n");
    printf("quit - This command closes the program\n");
    printf("help - This command displays a help section\n");
    printf("hostname - This command shows host name\n");
    printf("\nRemember, You can write whole words(except arguments) in capital l                                                                                        etters or lowercase letters. \nIf you write an argument, do not write it in squa                                                                                        re brackets. Good luck.\n\n");
}

void command_hostname()
{
    char name[256];
    gethostname(name, 256);
    printf("%s\n", name);
}

void command_mkdir(char **elements)
{
    if (mkdir(elements[1]) != 0)
    {
        perror("\nYou cannot create dictionary");
        printf("\n");
    }
}

void command_rmdir(char **elements)
{
    if (rmdir(elements[1]) != 0)
    {
        perror("\nYou cannot remove dictionary");
        printf("\n");
    }
}

void command_cp(char **elements)
{
    char tekst[4096];
    FILE *file1, *file2;
    if ((file1 = fopen(elements[1], "r")) == NULL)
    {
        printf("The shell can't open file.\n");
        printf( "Value of errno: %d\n", errno );
        exit(1);
    }
    else
    {
        fscanf(file1, "%s", tekst);
    }
    if ((file2 = fopen(elements[2], "w")) == NULL)
    {
        printf("The Shell can't create %s", elements[2]);
        printf( "Value of errno: %d\n", errno );
        exit(1);
    }
    else
    {
        fprintf(file2, "%s", tekst);
    }
    fclose(file1);
    fclose(file2);
}

void command_ls()
{
    struct dirent *pointer_dir;
    DIR *directory;
    if ((directory = opendir(".")) == NULL)
    {
        printf("The shell can't open current directory\n");
        printf( "Value of errno: %d\n", errno );
    }
    else
    {
        printf("The contents of directory:\n\n");
        while ((pointer_dir = readdir(directory)) != NULL)
        {
            printf("%s\n", pointer_dir -> d_name);
        }
    }
    closedir(directory);
    printf("\n");
}

void command_color(char **elements)
{
    if (strcmp(elements[1], "default") == 0)
        printf("\x1b[0m\n");
    else if (strcmp(elements[1], "white") == 0 && strcmp(elements[2], "font") ==                                                                                         0)
        printf("\x1b[37m\n");
    else if (strcmp(elements[1], "black") == 0 && strcmp(elements[2], "font") ==                                                                                         0)
        printf("\x1b[30m\n");
    else if (strcmp(elements[1], "yellow") == 0 && strcmp(elements[2], "font") =                                                                                        = 0)
        printf("\x1b[33m\n");
    else if (strcmp(elements[1], "blue") == 0 && strcmp(elements[2], "font") ==                                                                                         0)
        printf("\x1b[34m\n");
    else if (strcmp(elements[1], "red") == 0 && strcmp(elements[2], "font") == 0                                                                                        )
        printf("\x1b[31m\n");
    else if (strcmp(elements[1], "green")==0 && strcmp(elements[2], "font") == 0                                                                                        )
        printf("\x1b[32m");
    else if (strcmp(elements[1], "black") == 0 && strcmp(elements[2], "backgroun                                                                                        d") == 0)
        printf("\x1b[40m\n");
    else if (strcmp(elements[1], "yellow") == 0 && strcmp(elements[2], "backgrou                                                                                        nd") == 0)
        printf("\x1b[43m\n");
    else if (strcmp(elements[1], "blue") == 0 && strcmp(elements[2], "background                                                                                        ") == 0)
        printf("\x1b[44m\n");
    else if (strcmp(elements[1], "red") == 0 && strcmp(elements[2], "background"                                                                                        ) == 0)
        printf("\x1b[41m\n");
    else if (strcmp(elements[1], "green")==0 && strcmp(elements[2], "background"                                                                                        ) == 0)
        printf("\x1b[42m\n");
    else if (strcmp(elements[1], "white") == 0 && strcmp(elements[2], "backgroun                                                                                        d") == 0)
        printf("\x1b[47m\n");
    else if (strcmp(elements[1], "inverse") == 0 && strcmp(elements[2], "on") ==                                                                                         0)
        printf("\x1b[7m\n");
    else if (strcmp(elements[1], "inverse") == 0 && strcmp(elements[2], "off") =                                                                                        = 0)
        printf("\x1b[27m\n");
    else
        printf("\nThere is no such argument\n\n");
}

void command_font(char **elements)
{
    if (strcmp(elements[1], "bold") == 0 && strcmp(elements[2], "on") == 0)
        printf("\x1b[1m\n");
    else if (strcmp(elements[1], "italic") == 0 && strcmp(elements[2], "on") ==                                                                                         0)
        printf("\x1b[3m\n");
    else if (strcmp(elements[1], "underline") == 0 && strcmp(elements[2], "on")                                                                                         == 0)
        printf("\x1b[4m\n");
    else if (strcmp(elements[1], "strikethrough") == 0 && strcmp(elements[2], "o                                                                                        n") == 0)
        printf("\x1b[9m\n");
    else if (strcmp(elements[1], "bold") == 0 && strcmp(elements[2], "off") == 0                                                                                        )
        printf("\x1b[22m\n");
    else if (strcmp(elements[1], "italic") == 0 && strcmp(elements[2], "off") ==                                                                                         0)
        printf("\x1b[23m\n");
    else if (strcmp(elements[1], "underline") == 0 && strcmp(elements[2], "off")                                                                                         == 0)
        printf("\x1b[24m\n");
    else if (strcmp(elements[1], "strikethrough") == 0 && strcmp(elements[2], "o                                                                                        ff") == 0)
        printf("\x1b[29m\n");
    else
        printf("\nThere is no such arguemtn\n\n");
}

int main()
{
    char current_path[256];
    char previous_path[256];
    char bufor[256];
    char **elements;
    pid_t pid, wpid;
    int status;

    getcwd(previous_path, sizeof(previous_path));

    printf("\nWelcome in my microshell.\n\n");

    for(;;)
    {
        getcwd(current_path, sizeof(current_path));
        printf("%s$ ", current_path);
        fgets(bufor, 1024, stdin);
        elements = tokens(bufor);

        if (strcmp(elements[0], "cd") == 0 || strcmp(elements[0], "CD") == 0)
        {
            strcpy(previous_path, command_cd(elements, previous_path));
        }

        else if (strcmp(elements[0], "cp") == 0 || strcmp(elements[0], "CP") ==                                                                                         0)
        {
            command_cp(elements);
        }

        else if (strcmp(elements[0], "mkdir") == 0 || strcmp(elements[0], "MKDIR                                                                                        ") == 0)
        {
            command_mkdir(elements);
        }

        else if (strcmp(elements[0], "rmdir") == 0 || strcmp(elements[0], "RMDIR                                                                                        ") == 0)
        {
            command_rmdir(elements);
        }

        else if (strcmp(elements[0], "ls") == 0 || strcmp(elements[0], "LS") ==                                                                                         0)
        {
            command_ls();
        }

        else if (strcmp(elements[0], "color") == 0 || strcmp(elements[0], "COLOR                                                                                        ") == 0)
        {
            command_color(elements);
        }

        else if (strcmp(elements[0], "font") == 0 || strcmp(elements[0], "FONT")                                                                                         == 0)
        {
            command_font(elements);
        }

        else if (strcmp(elements[0], "hostname") == 0 || strcmp(elements[0], "HO                                                                                        STNAME") == 0)
        {
            command_hostname();
        }

        else if (strcmp(elements[0], "quit") == 0 || strcmp(elements[0], "QUIT")                                                                                         == 0)
        {
            command_quit();
            break;
        }

        else if (strcmp(elements[0], "help") == 0 || strcmp(elements[0], "HELP")                                                                                         == 0)
        {
            command_help();
        }
        else if ((pid = fork()) == 0)
        {
            execvp(elements[0], elements);
            if (strcmp(elements[0], "") != 0)
                fprintf(stderr,"\nThere is no such command or argument\n\n", ele                                                                                        ments[0]);
            exit(124);
        }
        else if (pid == -1)
        {
            printf("\nFork error\n\n");
        }
        else
        {
            wait(NULL);
        }
    }
    free(elements);
    return 0;

}
