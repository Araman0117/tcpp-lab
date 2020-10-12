#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

//блок функций проверки текущего символа
//65 - 90 большие буквы ascii
//97 - 122 маленькие буквы ascii
int is_letter(char ch)
{
    //если текущий символ это латинская буква, то 1, иначе 0
    if (((ch >= 65) && (ch <= 90)) || ((ch >= 97) && (ch <= 122))) return (1);
    else return (0);
}

//48 - 57 цифры ascii
int is_digit(char ch)
{
    if ((ch >= 48) && (ch <= 57)) return (1);
    else return (0);
}

//33, 44, 45, 46, 58, 59, 63 - знаки пунктуации ascii
int is_sep(char ch)
{
    if ((ch == 33) || ((ch >= 44) && (ch <= 46)) || (ch == 58) || (ch == 59) || (ch == 63)) return (1);
    else return (0);
}

/*эта функция проверяет часть строки (поле) на соответствие
символам заданного шаблона, пока не найдёт символ из
следующего шаблона (здесь используются указатели на функцию)*/
int scan_this_part(char **strr, int(*fst)(char), int(*snd)(char))
{
    int res = 0;

    while (**strr)
    {
        //сначала проверяется сам символ - если он не подошёл, то ошибка
        if (fst(**strr))
        {
            /*затем проверяется следующий символ, и если
            следующий символ соответствует шаблону следующей части,
            то выходим из функции с результатом 1 и сдвигаем указатель*/
            if (snd(*((*strr)+1)))
            {
                res = 1;
                (*strr)++;
                return (res);
            }
            (*strr)++;
        }
        else return (0);
    }
    //если просканированная часть соответствует шаблону, то 1, иначе 0
    return (res);
}

int scan_str(char *str)
{
    //инициализация переменных-флагов
    int is_First_Field_Correct = 0;
    int is_First_Separator_Correct = 0;
    int is_Second_Field_Correct = 0;
    int is_Second_Separator_Correct = 0;

    int result = 0;

    //инициализация указателя на указатель для сдвига исходного указателя
    char **strr = &str;

    //условия следует читать так - если флаг, которому присвоено значение функции, не ноль, то
    if ((is_First_Field_Correct = scan_this_part(strr, &is_letter, &is_sep)))
        if ((is_First_Separator_Correct = scan_this_part(strr, &is_sep, &is_digit)))
            if ((is_Second_Field_Correct = scan_this_part(strr, &is_digit, &is_sep)))
                if ((is_Second_Separator_Correct = scan_this_part(strr, &is_sep, &is_digit)))
                {
                    //этот цикл проверяет последнее поле на соответствие шаблону
                    //также он проверяет последнее ли это поле
                    while(*str)
                    {
                        if (is_digit(*str)) result = 1;
                        else return (0);
                        
                        str++;
                    }
                }

    return (result);
}

//альтернативный вывод на экран, чтоб касперский не ругался
void str_out(char *buf)
{
    // char *temp;
    // int i;
    size_t j;

    //тут считается длина строки, стрлен
    // temp = buf;
    // i = 0;
    // while (*temp)
    // {
    //     i++;
    //     temp++;
    // }

    //тут выделяется память
    // temp = (char*)malloc(sizeof(char) * (i + 1));
    // temp[i] = '\0';
    j = 0;
    
    //тут посимвольно печать
    // while (j < i)
    // {
    //     temp[j] = buf[j];
    //     write(1, &(temp[j]), 1);
    //     j++;
    // }

    while (j < (strlen(buf)))
    {
        write(1, &(buf[j]), 1);
        j++;
    }

    // free(temp);
    write(1, "\n", 1);
}

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

        //вывод корректной строки на экран
        if (scan_str(buf)) str_out(buf);

        //на эту команду почему-то ругается антивирус
        // if (scan_str(buf)) printf("%s\n", buf);

        //альтернативный вывод, более понятный
        // if (scan_str(buf)) printf("correct\n");
        // else printf("not correct\n");
    }

    return (0);
}