#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int g_array[127] = {0};

int scan_out(int i, int j)
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

        //если символ под номером k встретился в тексте хотя бы 1 раз, то
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
    //результатом является количество найденных символов из перечня
    return (res);
}

int scan_text(char *text)
{
    int sum = 0;
    int fd;
    char *buffer = (char*)malloc(sizeof(char) * (strlen(text) + 1));
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

    //отобразить текст
    write(1, buffer, strlen(text));
    write(1, "\n\n", 2);

    //сбор статистики символов
    while (*buffer)
    {
        g_array[*buffer - 1] += 1;
        buffer++;
    }

    //чистка памяти
    free(buffer);
    remove(filename);

    //вывод первичной статистики (кол-во для каждого символа)
    sum = scan_out(64, 89) + scan_out(32, 63) + scan_out(90, 95) + scan_out(122, 125);

    //отделяем вывод первой ф-ии от второй, отправляем результат во вторую ф-ию
    write(1, "\n", 1);
    return (sum);
}

void stat_out(int i, int j, int sum)
{
    int h;
    int k;
    float num;
    float div = (float)(sum);
    char ch;
    char snum[5];

    //просматриваем перечень от i-того до j-того символа
    while (i <= j)
    {
        //если латин алфавит, то учитываем регистр, иначе только сам символ
        if ((i >= 64) && (i <= 89)) k = (g_array[i] + g_array[i + 32]);
        else k = g_array[i];

        //если символ под номером k встретился в тексте хотя бы 1 раз, то
        if (k > 0)
        {
            //тут проценты
            num = (float)(k);
            ch = (char)(i + 1);
            itoa(((int)(num * 100 / div)), snum, 10);

            write(1, "'", 1);
            write(1, &ch, 1);
            write(1, "' took ", 7);
            write(1, snum, strlen(snum));
            write(1, "% of text\t", 10);

            //тут гистограммы
            h = 0;
            while (h <= (int)(num * 100 / div))
            {
                write(1, "*", 1);
                h++;
            }

            //переход на след строку
            write(1, "\n", 1);
        }
        i++;
    }
}

void show_stat(int sum)
{
    //подсчёт процентов и построение гистограмм для латин алфавита
    stat_out(64, 89, sum);
    //для всего остального
    stat_out(32, 63, sum);
    stat_out(90, 95, sum);
    stat_out(122, 125, sum);
}

int main(int argc, char *argv[])
{
    if (argc == 2) show_stat(scan_text(argv[1]));
    //в скан_текст идёт первый параметр в качестве текста для анализа,
    //результат функции идёт в шоу_стат для дальнейшей обработки
    else write(1, "Wrong number of params.\n", 24);
    return 0;
}