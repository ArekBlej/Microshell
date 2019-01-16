#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

int main()
{
char cwd[1024];
char buf[1024];
char arguments[1024];


printf("\nWitaj w moim microshellu. \n\n");

while (1)
{
     getcwd(cwd, sizeof(cwd));
     printf("%s$ ", cwd);
     fgets(buf, 1024, stdin);

     /*if (strncmp(buf, "cd", 2) == 0)
     {
         char folder[1024];
         getcwd(folder, sizeof(folder));
         if (chdir("\\Users") == 0)
         {
             getcwd(folder, sizeof(folder));
         }
     }*/

     if (strncmp(buf, "cd ", 3) == 0)
     {
         char korektor[] = " ";
         char * schowek;

         schowek = strtok( buf, korektor );
         schowek = strtok( NULL, korektor );
         printf( "%s!!!!!!!!", &schowek[0] );
         if (buf[strlen(buf) - 1] == '\n')
         {
             buf[strlen(buf) - 1] = '\0';
         }
         printf( "%s", &buf[3]);
         /*buf[strcspn(buf, "\n")] = '\0';
         printf( "%s", &buf[3]);
         strcpy(arguments, schowek);
         printf("%s", arguments);
         buf[strcspn(buf, "\n")] = '\0';*/
         chdir(&buf[3]);
         if (chdir(schowek) == 0)
             chdir(schowek);
         else
             printf("\nError: podaj poprawna sciezke.\n");

     }

     if ((strncmp(buf, "cd .", 4) == 0) || (strncmp(buf, "cd.",3) == 0))
     {
        chdir(".");
     }

     if ((strncmp(buf, "cd ..", 5) == 0) || (strncmp(buf, "cd..", 4) == 0))
     {
        chdir("..");
     }

     /*if (strncmp(argv[0], "cd", 2))
        {
            gdir = getcwd(buf, sizeof(buf));
            dir = strcat(gdir, "\\");
            to = strcat(dir, argv[1]);
            chdir(to);
        }*/
     if (strncmp(buf, "quit", 4) == 0 || strncmp(buf, "QUIT", 4) == 0)
     {
     printf("\nZamykam microshella\n\n");
     exit(0);
     }

      if (strncmp(buf, "help", 4) == 0 || strncmp(buf, "HELP", 4) == 0)
     {
         printf("\nAutor shella: Arkadiusz Blejwas, student I roku informatyka na WMI UAM\n\nKomendy:\ncd - przekierowanie do innego katalogu\nquit - wyjscie z micro    shella\nhelp - pomoc\n\nPamietaj, ze mozesz pisac cale komendy z malych albo duzych liter. Powodzenia :)\n\n");
     }

 }

 return 0;
 }
