#include <stdio.h>

int is_letter(char ch)
{
    if (((ch >= 65) && (ch <= 90)) || ((ch >= 97) && (ch <= 122))) return (1);
    else return (0);
}

int is_digit(char ch)
{
    if ((ch >= 48) && (ch <= 57)) return (1);
    else return (0);
}

int is_div(char ch)
{
    if ((ch == 33) || ((ch >= 44) && (ch <= 46)) || (ch == 58) || (ch == 59) || (ch == 63)) return (1);
    else return (0);
}

int scan_this_part(char **strr, int(*fst)(char), int(*snd)(char))
{
    int res = 0;

    while (**strr)
    {
        if (fst(**strr) == 0) return (0);

        if ((fst(**strr)) && (snd(*((*strr)+1))))
        {
            res = 1;
            (*strr)++;
            return (res);
        }
        (*strr)++;
    }
    return (res);
}

int scan_str(char *str)
{
    //48 - 57 цифры
    //65 - 90 большие буквы
    //97 - 122 маленькие буквы
    //33, 44, 45, 46, 58, 59, 63 - знаки пунктуации
    int isFstCorrect = 0;
    int isDiv1Correct = 0;
    int isSndCorrect = 0;
    int isDiv2Correct = 0;
    int result;
    char **strr = &str;

    // while (*str)
    // {
    //     if (is_letter(*str) == 0) return (0);

    //     if ((is_letter(*str)) && (is_div(*(str+1))))
    //     {
    //         isFstCorrect = 1;
    //         str++;
    //         break;
    //     }
    //     str++;
    // }

    if ((isFstCorrect = scan_this_part(strr, &is_letter, &is_div)))
        if ((isDiv1Correct = scan_this_part(strr, &is_div, &is_digit)))
            if ((isSndCorrect = scan_this_part(strr, &is_digit, &is_div)))
                if ((isDiv2Correct = scan_this_part(strr, &is_div, &is_digit)))
                {
                    while(*str)
                    {
                        if (is_digit(*str)) result = 1;
                        else return (0);
                        
                        str++;
                    }
                }

    // if (isFstCorrect)
    // {
    //     while(*str)
    //     {
    //         if (is_div(*str) == 0) return (0);

    //         if ((is_div(*str)) && (is_digit(*(str+1))))
    //         {
    //             isDiv1Correct = 1;
    //             str++;
    //             break;
    //         }
    //         str++;
    //     }
    // }

    // if ((isFstCorrect) && (isDiv1Correct))
    // {
    //     while(*str)
    //     {
    //         if (is_digit(*str) == 0) return (0);

    //         if ((is_digit(*str)) && (is_div(*(str+1))))
    //         {
    //             isSndCorrect= 1;
    //             str++;
    //             break;
    //         }
    //         str++;
    //     }
    // }

    // if ((isFstCorrect) && (isDiv1Correct) && (isSndCorrect))
    // {
    //     while(*str)
    //     {
    //         if (is_div(*str) == 0) return (0);

    //         if ((is_div(*str)) && (is_digit(*(str+1))))
    //         {
    //             isDiv2Correct = 1;
    //             str++;
    //             break;
    //         }
    //         str++;
    //     }
    // }

    // if ((isFstCorrect) && (isDiv1Correct) && (isSndCorrect) && (isDiv2Correct))
    // {
    //     while(*str)
    //     {
    //         if (is_digit(*str)) result = 1;
    //         else return (0);
            
    //         str++;
    //     }
    // }

    return (result);
}

int main(void)
{
    char buf[512];

    while (1)
    {
        gets(buf);
        if (buf[0] == 'x') break;
        // if (scan_str(buf) == 1) printf("%s\n", buf);
        if (scan_str(buf) == 1) printf("correct\n");
    }

    return (0);
}