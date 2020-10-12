#ifndef HEADERS_H
# define HEADERS_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

int is_letter(char ch);
int is_digit(char ch);
int is_sep(char ch);
int scan_this_part(char **strr, int(*fst)(char), int(*snd)(char));
int scan_str(char *str);
void str_out(char *buf);

#endif