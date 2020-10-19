#include <iostream>
#include <string>

using namespace std;

int g_array[127] = {0};

int scan_out(int i, int j)
{
    char ch;
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
            res += k;

            cout << "'" << ch << "' found " << k << " times" << endl;
        }
        i++;
    }
    //результатом является количество найденных символов из перечня
    return (res);
}

int scan_text(string text)
{
    int sum = 0;
    char ch;

    //отобразить текст
    // cout << text << endl << endl;

    //сбор статистики символов
    for (unsigned int i = 0; i < text.length(); ++i)
    {
        ch = text[i];
        g_array[ch - 1] += 1;
    }

    //вывод первичной статистики (кол-во для каждого символа)
    sum = scan_out(64, 89) + scan_out(32, 63) + scan_out(90, 95) + scan_out(122, 125);

    //отделяем вывод первой ф-ии от второй, отправляем результат во вторую ф-ию
    cout << endl;
    return (sum);
}

void stat_out(int i, int j, int sum)
{
    int h;
    int k;
    float num;
    float div = (float)(sum);
    char ch;

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
            cout << "'" << ch << "' took " << (num * 100 / div) << "% of text\t";

            //тут гистограммы
            h = 0;
            while (h <= (int)(num * 100 / div))
            {
                cout << "~";
                h++;
            }

            //переход на след строку
            cout << endl;
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

int main()
{
    string str_input;

    cout << "enter text to analize" << endl;
    getline(cin, str_input);

    show_stat(scan_text(str_input));

    system("pause");

    return (0);
}