#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int g_array[127] = {0};

int scan_text(char *text)
{
    //инициализация переменных
    char filename[] = "testfile.txt";
    int i = 64;
    int s_count = strlen(text);
    int sum = 0;
    int fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU);
    char buffer[s_count];
    // char *buffer = (char*)malloc(sizeof(char) * (s_count + 1));
    char *temp;

    //запись в файл из потока ввода
    write(fd, text, s_count);
    close(fd);

    //чтение из файла в буфер
    fd = open(filename, O_RDONLY, S_IRWXU);
    read(fd, buffer, s_count);
    close(fd);

    //сбор статистики символов
    // temp = buffer;
    temp = text;
    while (*temp)
    {
        g_array[*temp - 1] += 1;
        temp++;
    }

    // printf("%s\ns_count = %d\n", buffer, s_count);
    // free(buffer);

    //вывод первичной статистики для латин алфавита(кол-во для каждого символа)
    while (i < 90)
    {
        if (g_array[i] + g_array[i + 32] > 0)
        {
            printf("'%c' found %d times\n", (i + 1), (g_array[i] + g_array[i + 32]));
            sum += (g_array[i] + g_array[i + 32]);
        }
        i++;
    }

    //вывод первичной статистики для второстепенных символов(кол-во для каждого символа)
    i = 32;
    while (i < 126)
    {
        if ( (g_array[i] > 0) && ( (i < 64) || ((i > 89) && (i < 96)) || (i > 121) ) )
        {
            printf("'%c' found %d times\n", (i + 1), (g_array[i]));
            sum += g_array[i];
        }
        i++;
    }

    write(1, "\n", 1);

    return (sum);
}

void show_stat(int sum)
{
    //инициализация переменных
    int i = 64;
    int j = 0;
    float num;
    float div = (float)(sum);

    //подсчёт процентов и построение гистограмм для латин алфавита
    while (i < 90)
    {
        if (g_array[i] + g_array[i + 32] > 0)
        {
            //тут проценты
            num = (float)((g_array[i] + g_array[i + 32]));
            printf("'%c' took %f%% of text\t\t", (i + 1), (num * 100 / div));

            //тут гистограммы
            while (j < (int)(num * 100 / div))
            {
                write(1, "*", 1);
                j++;
            }
            j = 0;

            write(1, "*\n", 2);
        }
        i++;
    }

    //подсчёт процентов и построение гистограмм для второстепенных символов
    i = 32;
    while (i < 126)
    {
        if ( (g_array[i] > 0) && ( (i < 64) || ((i > 89) && (i < 96)) || (i > 121) ) )
        {
            num = (float)(g_array[i]);
            printf("'%c' took %f%% of text\t\t", (i + 1), (num * 100 / div));

            while (j < (int)(num * 100 / div))
            {
                write(1, "*", 1);
                j++;
            }
            j = 0;

            write(1, "*\n", 2);
        }
        i++;
    }
}

int main(int argc, char *argv[])
{
    if (argc == 2) show_stat(scan_text(argv[1]));
    //в скан_текст идёт первый параметр в качестве текста для анализа, результат функции идёт в шоу стат для дальнейш обработки
    else printf("Wrong number of params, insert 1 param instead of %d", (argc - 1)); //обработка ошибки
    return 0;
}