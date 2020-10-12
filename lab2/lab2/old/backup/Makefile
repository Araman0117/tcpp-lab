NAME = laba2

FILES = laba2.c source.c headers.h

OPTIONS = -o

CFLAGS = -Wall -Wextra -Werror

.PHONY: all rm re

all: $(NAME)

$(NAME):
	gcc $(CFLAGS) $(FILES) $(OPTIONS) $(NAME)

clean:
	rm -rf $(NAME)

re: clean all