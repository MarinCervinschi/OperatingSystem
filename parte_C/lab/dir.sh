#!/bin/zsh
#File dir.sh


if [ $# != 2 ]; then
    echo "Usage: $0 <directory> <number>"
    exit 1
fi

if ! [ -d "$1" ]; then
    echo "Error: $1 is not a valid directory"
    exit 2
fi

if ! [[ $2 =~ ^[0-9]+$ ]]; then
    echo "Error: $2 is not a valid number"
    exit 3
fi

content="CC = gcc
CFLAGS = -Wall -std=c11
SRCS = \$(wildcard *.c)
NAME = \$(SRCS:.c=)
OBJS = \$(SRCS:.c=.o)

all: \$(NAME)

\$(NAME): \$(OBJS)
\t\$(CC) \$(CFLAGS) -o \$@ \$(OBJS)

%.o: %.c
\t\$(CC) \$(CFLAGS) -c \$< -o \$@

clean:
\trm -f \$(OBJS)

fclean: clean
\trm -f \$(NAME)

re: fclean all

.PHONY: all clean fclean re"

cd $1

for i in $(seq 1 $2)
do 
    mkdir ex$i
    cd ex$i
    echo "### EX $i" > readme.md 
    echo $content > makefile
    cd ..
done