#include "headers.h"

int scan_out(int i, int j, int* g_array)
{
    char ch;
    char snum[5];
    int k;
    int res = 0;

    while (i <= j)
    {
        if ((i >= 64) && (i <= 89)) k = (g_array[i] + g_array[i + 32]);
        else k = g_array[i];

        if (k > 0)
        {
            ch = (char)(i + 1);
            itoa(k, snum, 10);
            res += k;

            write(1, "'", 1);
            write(1, &ch, 1);
            write(1, "' found ", 8);
            write(1, snum, strlen(snum));
            write(1, " times\n", 7);
        }
        i++;
    }
    return (res);
}

int scan_text(char *text, int* g_array)
{
    int sum = 0;
    int fd;
    char *buffer = (char*)malloc(sizeof(char) * (strlen(text) + 1));
    char filename[] = "cache";

    fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU);
    write(fd, text, strlen(text));
    close(fd);

    fd = open(filename, O_RDONLY, S_IRWXU);
    read(fd, buffer, strlen(text));
    buffer[strlen(text)] = '\0';
    close(fd);

    write(1, buffer, strlen(text));
    write(1, "\n\n", 2);

    while (*buffer)
    {
        g_array[*buffer - 1] += 1;
        buffer++;
    }

    free(buffer);
    remove(filename);

    sum = scan_out(64, 89, g_array) + scan_out(32, 63, g_array) + scan_out(90, 95, g_array) + scan_out(122, 125, g_array);

    write(1, "\n", 1);
    return (sum);
}

void stat_out(int i, int j, int sum, int* g_array)
{
    int h;
    int k;
    float num;
    float div = (float)(sum);
    char ch;
    char snum[5];

    while (i <= j)
    {
        if ((i >= 64) && (i <= 89)) k = (g_array[i] + g_array[i + 32]);
        else k = g_array[i];

        if (k > 0)
        {
            num = (float)(k);
            ch = (char)(i + 1);
            itoa(((int)(num * 100 / div)), snum, 10);

            write(1, "'", 1);
            write(1, &ch, 1);
            write(1, "' took ", 7);
            write(1, snum, strlen(snum));
            write(1, "% of text\t", 10);

            h = 0;
            while (h <= (int)(num * 100 / div))
            {
                write(1, "*", 1);
                h++;
            }

            write(1, "\n", 1);
        }
        i++;
    }
}

void show_stat(int sum, int* g_array)
{
    stat_out(64, 89, sum, g_array);
    stat_out(32, 63, sum, g_array);
    stat_out(90, 95, sum, g_array);
    stat_out(122, 125, sum, g_array);
}