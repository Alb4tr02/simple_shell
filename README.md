
# Simple Shell :V

# Description

Shell is a program that takes commands from the standard input(keyboard) and gives them to the operating system to execute. This repository contains a small versión of a Shell.

## Usage

you need to compile all the c files:

```bash
gcc *c -o hsh
./hsh
```
hsh can work in interactive mode: 

```c
$ ./hsh
>:v ls
README.md   clfun.c	 getargs.c	 getvar.c	 look.c~
_realloc.c  cpyenv.c	  getenv.xc	  help_documents  malloc.c
actenv.xc   environ	   getline.c	   holberton.h	   man_1_simple_shell
add_node.c  funcbuilt.c  getline_main.c  hsh			 prompt.c
back.xc     funexe.c	  getrealenv.c	  look.c			 signal.c
```

but also hsh can work in non-interactive mode:

```c
echo "/bin/ls" | ./hsh
README.md   clfun.c	 getargs.c	 getvar.c	 look.c~
_realloc.c  cpyenv.c	  getenv.xc	  help_documents  malloc.c
actenv.xc   environ	   getline.c	   holberton.h	   man_1_simple_shell
add_node.c  funcbuilt.c  getline_main.c  hsh			 prompt.c
back.xc     funexe.c	  getrealenv.c	  look.c			 signal.c
```

## Invoke


To invoke the simple_shell, you need to write the next command: 

```c
./hsh
>:v 

```

After you run this command you will see the prompt: >:v. After that propmt you can put the command (extern or builtin), example: 

```c
./hsh
<:v ls
README.md   add_node.c	cd_functions.c	 environ	       funexe.c   getline_main.c  h_cd.txt    h_history.txt   holberton.h  malloc.c        test
_realloc.c  alias	clfun.c		 		        errores_env.c		         getargs.c  getrealenv.c	     h_env.txt   h_setenv.txt    hsh    man_1_simple_shell  tonya.out alias.c	commandfilter.c  errores_otrosbuilt.c  getenv.xc  getvar.c		   h_exit.txt  h_unsetenv.txt  itoa.c		    prompt.c
actenv.xc   back.xc	cpyenv.c	  funcbuilt.c	              getline.c  h_alias.txt	     h_help.txt  help_documents  look.c		       signal.c
>:v 
```
