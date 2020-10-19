#ifndef HEADERS_H
# define HEADERS_H
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

int scan_out(int i, int j, int* g_array);
int scan_text(char *text, int* g_array);
void stat_out(int i, int j, int sum, int* g_array);
void show_stat(int sum, int* g_array);

#endif