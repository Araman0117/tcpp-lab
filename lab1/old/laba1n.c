#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int g_array[127] = {0};

// int cap_of(int num)
// {
//     int razrad = 0;
//
//     while (num)
//     {
//         num /= 10;
//         razrad++;
//     }
//   
//     return (razrad);
// }

int scan_text(char *text)
{
    //инициализация переменных
    char filename[] = "cache.txt";
    int cap;
    int i = 64;
    int s_count = strlen(text);
    int sum = 0;
    // int fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU);
    FILE *fp = fopen(filename, "w");
    char buffer[s_count + 12];
    char *temp;
    char ch;
    char snum[5];

    //запись в файл из потока ввода
    // write(fd, text, s_count);
    fwrite(text, sizeof(char), s_count, fp);
    fclose(fp);

    //чтение из файла в буфер
    fp = fopen(filename, "rt");
    fread(buffer, sizeof(char), s_count, fp);
    fclose(fp);
    //////////////////////////////////////////////////////////////////////////////////////./
    //сбор статистики символов
    temp = buffer;
    // temp = text;
    ////////////////////////////////////////////////////////////////////////////////////////
    while (*temp)
    {
        g_array[*temp - 1] += 1;
        temp++;
    }

    // printf("%s\ns_count = %d\n", buffer, s_count);
    // write(1, buffer, s_count);
    // write(1, "\n", 1);
    // free(buffer);

    //вывод первичной статистики для латин алфавита(кол-во для каждого символа)
    while (i < 90)
    {
        if (g_array[i] + g_array[i + 32] > 0)
        {
            // printf("'%c' found %d times\n", (i + 1), (g_array[i] + g_array[i + 32]));
            ch = (char)(i + 1);
            itoa((g_array[i] + g_array[i + 32]), snum, 10);
            write(1, "'", 1);
            write(1, &ch, 1);
            write(1, "' found ", 8);
            cap = strlen(snum);
            write(1, snum, cap);
            write(1, " times\n", 7);
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
            // printf("'%c' found %d times\n", (i + 1), (g_array[i]));
            ch = (char)(i + 1);
            itoa((g_array[i]), snum, 10);
            write(1, "'", 1);
            write(1, &ch, 1);
            write(1, "' found ", 8);
            cap = strlen(snum);
            write(1, snum, cap);
            write(1, " times\n", 7);
            sum += g_array[i];
        }
        i++;
    }

    // printf("\n");
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
