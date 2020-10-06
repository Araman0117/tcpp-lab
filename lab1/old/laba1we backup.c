#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int g_array[127] = {0};

int stat_out(int i, int j)
{
    char ch;
    char snum[5];
    int k;
    int res = 0;

    //просматриваем перечень от i-того до j-того символа
    while (i <= j)
    {
        //если латин алфавит, то учитываем регистр, иначе только сам символ
        if ((i >= 64) && (i <= 89)) k = (g_array[i] + g_array[i + 32]);
        else k = g_array[i];

        if (k > 0)
        {
            ch = (char)(i + 1);
            itoa(k, snum, 10);
            write(1, "'", 1);
            write(1, &ch, 1);
            write(1, "' found ", 8);
            write(1, snum, strlen(snum));
            write(1, " times\n", 7);
            res += k;
        }
        i++;
    }
    //результатом является количество найденных символов из перечня
    return (res);
}

int scan_text(char *text)
{
    //инициализация переменных
    int i;
    int sum = 0;
    int fd;
    char *buffer = (char*)malloc(sizeof(char) * (strlen(text) + 1));
    char ch;
    char snum[5];
    char filename[] = "cache";

    //запись в файл из потока ввода
    fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU);
    write(fd, text, strlen(text));
    close(fd);

    //чтение из файла в буфер
    fd = open(filename, O_RDONLY, S_IRWXU);
    read(fd, buffer, strlen(text));
    buffer[strlen(text)] = '\0';
    close(fd);

    // write(1, buffer, strlen(text));
    // write(1, "\n", 1);

    //сбор статистики символов
    while (*buffer)
    {
        g_array[*buffer - 1] += 1;
        buffer++;
    }

    free(buffer);
    remove(filename);

    //вывод первичной статистики для латин алфавита(кол-во для каждого символа)
    sum = stat_out(64, 89) + stat_out(32, 63) + stat_out(90, 95) + stat_out(122, 125);

    // i = 64;
    // while (i < 90)
    // {
    //     if (g_array[i] + g_array[i + 32] > 0)
    //     {
    //         ch = (char)(i + 1);
    //         itoa((g_array[i] + g_array[i + 32]), snum, 10);
    //         write(1, "'", 1);
    //         write(1, &ch, 1);
    //         write(1, "' found ", 8);
    //         write(1, snum, strlen(snum));
    //         write(1, " times\n", 7);
    //         sum += (g_array[i] + g_array[i + 32]);
    //     }
    //     i++;
    // }
    //
    //вывод первичной статистики для второстепенных символов(кол-во для каждого символа)
    // i = 32;
    // while (i < 126)
    // {
    //     if ( (g_array[i] > 0) && ( (i < 64) || ((i > 89) && (i < 96)) || (i > 121) ) )
    //     {
    //         ch = (char)(i + 1);
    //         itoa((g_array[i]), snum, 10);
    //         write(1, "'", 1);
    //         write(1, &ch, 1);
    //         write(1, "' found ", 8);
    //         write(1, snum, strlen(snum));
    //         write(1, " times\n", 7);
    //         sum += g_array[i];
    //     }
    //     i++;
    // }

    write(1, "\n", 1);
    return (sum);
}

void show_stat(int sum)
{
    //инициализация переменных
    int i = 64;
    int j = 0;
    int cap;
    float num;
    float div = (float)(sum);
    char ch;
    char snum[5];

    //подсчёт процентов и построение гистограмм для латин алфавита
    while (i < 90)
    {
        if (g_array[i] + g_array[i + 32] > 0)
        {
            //тут проценты
            num = (float)((g_array[i] + g_array[i + 32]));
            // printf("'%c' took %d%% of text\t", (i + 1), (int)(num * 100 / div));
            ch = (char)(i + 1);
            itoa(((int)(num * 100 / div)), snum, 10);
            write(1, "'", 1);
            write(1, &ch, 1);
            write(1, "' took ", 7);
            cap = strlen(snum);
            write(1, snum, cap);
            write(1, "% of text\t", 10);

            //тут гистограммы
            while (j < (int)(num * 100 / div))
            {
                // printf("*");
                write(1, "*", 1);
                j++;
            }
            j = 0;

            // printf("*\n");
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
            // printf("'%c' took %d%% of text\t", (i + 1), (int)(num * 100 / div));
            ch = (char)(i + 1);
            itoa(((int)(num * 100 / div)), snum, 10);
            write(1, "'", 1);
            write(1, &ch, 1);
            write(1, "' took ", 7);
            cap = strlen(snum);
            write(1, snum, cap);
            write(1, "% of text\t", 10);

            while (j < (int)(num * 100 / div))
            {
                // printf("*");
                write(1, "*", 1);
                j++;
            }
            j = 0;

            // printf("*\n");
            write(1, "*\n", 2);
        }
        i++;
    }
}

int main(int argc, char *argv[])
{
    if (argc == 2) show_stat(scan_text(argv[1]));
    //в скан_текст идёт первый параметр в качестве текста для анализа, результат функции идёт в шоу стат для дальнейш обработки
    else write(1, "Wrong number of params", 22);
    //обработка ошибки
    return 0;
}