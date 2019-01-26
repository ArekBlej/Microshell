all:
  gcc -Wall -ansi -o microshell microshell.c

clean:
  rm microshell
  
run
  ./microshell
