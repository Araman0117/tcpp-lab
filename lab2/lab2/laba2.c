#include "headers.h"

int main(void)
{
    //размечаем буфер для строки
    char buf[512];

    //зацикливаем ввод и анализ строки
    while (1)
    {
        //ввод строки
        gets(buf);

        //если первый символ строки ноль, то выйти из цикла
        // if (buf[0] == '0') break;

        //на эту команду почему-то ругается антивирус
        // if (scan_str(buf)) printf("%s\n", buf);

        //альтернативный вывод корректной строки на экран
        if (scan_str(buf)) str_out(buf);

        //ещё один альтернативный вывод, более понятный
        // if (scan_str(buf)) printf("correct\n");
        // else printf("not correct\n");
    }

    return (0);
}