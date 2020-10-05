#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int g_array[127];

int count(char *v)
{
    int res = 0;
    char *str = v;
    while (*str)
    {
        res++;
        str++;
    }
    return res;
}

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        int s_count = count(argv[1]);
        char filename[] = "testfile.txt";
        int w_flags = O_WRONLY | O_CREAT;
        int r_flags = O_RDONLY;
        mode_t mode = S_IRWXU;
        int fd = open(filename, w_flags, mode);
        char *str = argv[1];
        write(fd, str, s_count);
        close(fd);
        //printf("str = %s\ns_count = %d", str, s_count);
        //printf("amount of symbols - %d\nargc = %d", s_count, argc);
        fd = open (filename, r_flags, mode);
        char text[s_count];
        read(fd, text, s_count);
        char *temp = text;
        //printf("text = %s", text);
        while (*temp)
        {
            g_array[*temp - 1] += 1;
            temp++;
        }

        int j = 0;
        int i = 32;
        while (i < 122)
        {
            if (g_array[i])
            {
                j++;
            }
            i++;
        }

        i = 64;
        while (i < 90)
        {
            if ((g_array[i]+g_array[i+32]))
            {
                printf("num of %c = %d %d\t\t", (i+1), (g_array[i]+g_array[i+32]), ((g_array[i]+g_array[i+32])*100/j));
                int k = 0;
                while (k < (g_array[i]+g_array[i+32])*100/j)
                {
                    write(1, "*", 1);
                    k++;
                }
                write(1, "\n", 1);
            }
            i++;
        }

        i = 32;
        while (i < 64)
        {
            if (g_array[i])
            {
                printf("num of %c = %d %d\t\t", (i+1), (g_array[i]), ((g_array[i])*100/j));
                int k = 0;
                while (k < g_array[i]*100/j)
                {
                    write(1, "*", 1);
                    k++;
                }
                write(1, "\n", 1);
            }
            i++;
        }

    }
    return 0;
}