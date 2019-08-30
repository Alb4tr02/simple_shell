# Simple Shell :V

# Description

Shell is a program that takes commands from the standard input(keyboard) and gives them to the operating system to execute. This repository contains a small versión of a Shell.

## Usage

You need to compile all the c files:

```bash
gcc *c -o hsh
./hsh
```
hsh can work in interactive mode:

```c
$ ./hsh
>:v ls
README.md   clfun.c	 getargs.c	 getvar.c	 look.c~
_realloc.c  cpyenv.c	   getenv.xc	   help_documents  malloc.c
actenv.xc   environ	      getline.c	      holberton.h     man_1_simple_shell
add_node.c  funcbuilt.c  getline_main.c  hsh			 prompt.c
back.xc     funexe.c	   getrealenv.c	   look.c				 signal.c
```

But also hsh can work in non-interactive mode:

```c
echo "/bin/ls" | ./hsh
README.md   clfun.c	 getargs.c	 getvar.c	 look.c~
_realloc.c  cpyenv.c	   getenv.xc	   help_documents  malloc.c
actenv.xc   environ	      getline.c	      holberton.h     man_1_simple_shell
add_node.c  funcbuilt.c  getline_main.c  hsh			 prompt.c
back.xc     funexe.c	   getrealenv.c	   look.c				 signal.c
```

##  Execution


To invoke the simple_shell, you need to write the next command:

```c
./hsh
>:v

```

After you run this command you will see the prompt: >:v. After that propmt you can put the command (extern or builtin), example:

```c
./hsh
>:v ls
README.md   add_node.c	cd_functions.c	 environ	       funexe.c   getline_main.c  h_cd.txt    h_history.txt   holberton.h  malloc.c        test
_realloc.c  alias	clfun.c		 		        	  		          errores_env.c	      		            getargs.c  getrealenv.c      h_env.txt   h_setenv.txt    hsh    man_1_simple_shell  tonya.out alias.c commandfilter.c  errores_otrosbuilt.c  getenv.xc  getvar.c     h_exit.txt  h_unsetenv.txt  itoa.c      prompt.c
actenv.xc   back.xc	cpyenv.c								    funcbuilt.c				                  getline.c  h_alias.txt          h_help.txt  help_documents  look.c		         signal.c
>:v
```
## Command Execution

## Exit status

hsh returns Zero for success and differnt Zero for failure

## Signals

hsh ignores the Ctrl + C input, you can use Ctrl + d to exit the program.

```c
./hsh
>:v ^C
>:v ^C
>:v ^C
>:V
```
## $?

? is relplaced with return value of the las program executed

Example:

```c
>:v echo $?
>:v 0
```

## $$

In this case the second $ is replaced by the current process ID

Example:

```c
>:v echo $$
>:v 6494
```

## $$

hsh ignores all words and characters preceeded by a # character on a line

```c
>:v echo $$
>:v 13245
```
## operators

hsh can handle ; Command separator. Commands that are separeted with ; areexecuted sequentially.

```c
>:v echo "hello" ; echo "world"
"hello"
"world"
```
You can usea ; separator with spaces or tabs or nothing between the command and the separator.

## cd

- Use cd to change current directory, if no argument is given, the command is interpeted as a cd $HOME.
- if the argument - is  given, the command is interpreted as cd $OLDPATH

Example

```c
>:v ls
README.md   alias     builthelp.c      commandfilter2.c  errores_env.c	funexe.c	getrealenv.c  h_env.txt      h_setenv.txt    hsh    malloc.c        signal.c
_realloc.c  alias.c   cd_functions.c   cpyenv.c		 		 			       filtro.c	     getargs.c     getvar.c      h_exit.txt     h_unsetenv.txt  itoa.c      man_1_simple_shell  test
a.out	            alias2.c  clfun.c             directories.c					       		       fun_env.c   getline.c     h_alias.txt   h_help.txt     help_documents  justhelp.txt  prompt.c           tony
add_node.c  alias3.c  commandfilter.c  environ	  								       		   		   	       		       funcbuilt.c  getline_main.c  		          h_cd.txt      h_history.txt  holberton.h     look.c      salir.c
>:v cd
>:v ls
0-main.c	     100-wildcmp.c	 5-firstlines	      args				   holberton.h		    sf-0119_shell_test_suite
0-puts_recursion     100-wildcmp.c~	   7-diagonals	                  bin			   			                     holberton.h~      simple_shell
0-puts_recursion.c   13-unique		   				    								     		             7-main.c              bog-0619_shell_test_suite     holbertonschool-low_level_programming  tests_simple_shell
0-puts_recursion.c~  2-args.c																	     			   				 					                      7-print_diagonal.c   boom                  multi.c
0x15.c		     																																           		   			                   2-args.c~               7-print_diagonal.c~  examples       printf
100-main.c																																									   			   				                             2-print_alphabet         Betty                      exercises-simple_shell     realloc.c
100-wildcmp																																																			     			      				 			                        2-print_alphabet.c  a                       holberton-system_engineering-devops  realloc.c~
>:v
```
## exit

use exit to go out of the program.

example:

```c
>:v exit
➜  simple_shell git:(karen) ✗

```
## env

Unsage: env
prints the current environment

example:

```c
>:v env
NVM_DIR=/home/vagrant/...
...
```

## setenv

Usage setenv [VARIABLE][VALUE]
Create a new environment variable or modifies an existing one

example:

```c
>:v setenv tony Ibague
>:v echo tony
>.v Ibague
...
```

## unsetenv

Usage unsetenv [VARIABLE][VALUE]
Create a new environment variable or modifies an existing one

example:

```c
>:v unsetenv PATH
>:v echo PATH

>:v
```
# AUTHORS

- Karen Herrera
- Johan David Muñoz
