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

