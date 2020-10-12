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

int is_space(char ch)
{
    if ((ch == 33) || ((ch >= 44) && (ch <= 46)) || (ch == 58) || (ch == 59) || (ch == 63)) return (1);
    else return (0);
}

int scan_str(char *currentSymbol)
{
    //48 - 57 цифры
    //65 - 90 большие буквы
    //97 - 122 маленькие буквы
    //33, 44, 45, 46, 58, 59, 63 - знаки пунктуации
    int isFstCorrect = 0;
    int isSpace1Correct = 0;
    int isSndCorrect = 0;
    int isSpace2Correct = 0;
    int result;

    while (*currentSymbol)
    {
        if (is_letter(*currentSymbol) == 0) return (0);

        if ((is_letter(*currentSymbol)) && (is_space(*(currentSymbol+1))))
        {
            isFstCorrect = 1;
            currentSymbol++;
            break;
        }
        currentSymbol++;
    }

    if (isFstCorrect)
    {
        while(*currentSymbol)
        {
            if (is_space(*currentSymbol) == 0) return (0);

            if ((is_space(*currentSymbol)) && (is_digit(*(currentSymbol+1))))
            {
                isSpace1Correct = 1;
                currentSymbol++;
                break;
            }
            currentSymbol++;
        }
    }

    if ((isFstCorrect) && (isSpace1Correct))
    {
        while(*currentSymbol)
        {
            if (is_digit(*currentSymbol) == 0) return (0);

            if ((is_digit(*currentSymbol)) && (is_space(*(currentSymbol+1))))
            {
                isSndCorrect= 1;
                currentSymbol++;
                break;
            }
            currentSymbol++;
        }
    }

    if ((isFstCorrect) && (isSpace1Correct) && (isSndCorrect))
    {
        while(*currentSymbol)
        {
            if (is_space(*currentSymbol) == 0) return (0);

            if ((is_space(*currentSymbol)) && (is_digit(*(currentSymbol+1))))
            {
                isSpace2Correct = 1;
                currentSymbol++;
                break;
            }
            currentSymbol++;
        }
    }

    if ((isFstCorrect) && (isSpace1Correct) && (isSndCorrect) && (isSpace2Correct))
    {
        while(*currentSymbol)
        {
            if (is_digit(*currentSymbol) == 1) result = 1;
            else return (0);
            currentSymbol++;
        }
    }

    return (result);
}

int main(void)
{
    char buf[512];

    while (1)
    {
        gets(buf);
        if (buf[0] == 'x') break;
        if (scan_str(buf) == 1) printf("%s\n", buf);
        // if (scan_str(buf) == 1) printf("correct\n");
    }

    return (0);
}