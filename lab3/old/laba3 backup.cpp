#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<double> my_stack;
vector<string> in_seq;
string input_str;
string buf;

//нужно попробовать сделать рекурсию - функция получает позицию в параметр и ищет 2 подряд операнда и применяет действие, потом как-то помечает эти операнды и знак, пихает туда результат либо хранит в себе и затем запускает сама себя же и в параметр новая позиция и так по кругу пока весь стэк не кончится

int issign(char ch)
{
    if ((ch == '*') || (ch == '+') || (ch == '-') || (ch == '/') || (ch == ':')) return (1);
    else return (0);
}

int check_symbols()
{
    for (size_t i = 0; i < input_str.length(); i++)
    {
        if (!(((input_str[i] >= 42) && (input_str[i] <= 58)) || (input_str[i] == 32))) return (0);
    }
    return (1);
}

void add_to_stack(int pos)
{
    my_stack.push_back((double)atof((in_seq[pos]).c_str()));

    // int i = 0;

    // while (isdigit(in_seq[pos][i]) || (in_seq[pos][i] == '.') || (in_seq[pos][i] == ','))
    // {
    //     buf.push_back(in_seq[pos][i]);
    //     i++;
    // }

    // my_stack.push_back((double)atof(buf.c_str()));
    // buf.clear();
}

// void count_it(char action)
// {
//     int last = my_stack.size() - 1;
//     int pre_last = last - 1;
//
//     if (action == '*') my_stack[pre_last] = my_stack[pre_last] * my_stack[last];
//     else if (action == '+') my_stack[pre_last] = my_stack[pre_last] + my_stack[last];
//     else if (action == '-') my_stack[pre_last] = my_stack[pre_last] - my_stack[last];
//     else if ((action == '/') || (action == ':')) my_stack[pre_last] = my_stack[pre_last] / my_stack[last];
//
//     my_stack.pop_back();  
// }

double count_it(char action)
{
    if (action == '*') return (my_stack[0] * my_stack[1]);
    else if (action == '+') return (my_stack[0] + my_stack[1]);
    else if (action == '-') return (my_stack[0] - my_stack[1]);
    else if ((action == '/') || (action == ':')) return (my_stack[0] / my_stack[1]);
    else return (0);
}

void fill_vector()
{
    int i = 0;

    while (i < input_str.length())
    {
        while (isspace(input_str[i])) i++;

        if (isdigit(input_str[i]) || issign(input_str[i]))
        {
            while (isdigit(input_str[i]) || (input_str[i] == '.') || (input_str[i] == ','))
            {
                buf.push_back(input_str[i]);
                i++;
            }

            if (issign(input_str[i]))
            {
                buf.push_back(input_str[i]);
                i++;
            }

            in_seq.push_back(buf.c_str());
            buf.clear();
        }
    }
}

void direct_notat(int pos)
{
    double result;

    if (in_seq.size() > 1)
    {
        while (!(isdigit(in_seq[pos][0]) && isdigit(in_seq[pos+1][0]))) pos++;

        add_to_stack(pos);
        add_to_stack(pos+1);

        result = count_it(in_seq[pos-1][0]);

        my_stack.clear();

        in_seq.erase(in_seq.begin() + pos+1);
        in_seq.erase(in_seq.begin() + pos);
        in_seq[pos-1] = to_string(result);

        direct_notat(0);
    }
    
    return;
}

// void directNotation()
// {
//     int i = 0;
//     int row = 0;
//     int pos = -1;
//
//     while (i < input_str.length())
//     {
//         if (isdigit(input_str[i]))
//         {
//             while (isdigit(input_str[i]) || (input_str[i] == '.') || (input_str[i] == ','))
//             {
//                 buf.push_back(input_str[i]);
//                 i++;
//             }
//
//             my_stack.push_back((double)atof(buf.c_str()));
//             pos++;
//             buf.clear();
//
//             if (row == 1)
//             {
//                 while (!((input_str[i] == '*') || (input_str[i] == '+') || (input_str[i] == '-') || (input_str[i] == '/') || (input_str[i] == ':'))) i++;
//                 count_it(pos, input_str[i]);
//                 pos--;
//             }
//
//             while (isspace(input_str[i])) i++;
//
//             if (isdigit(input_str[i])) row = 1;
//         }
//         else row = 0;
//
//         i++;
//     }
//     // cout << "stack check ok" << endl;
// }

int main(void)
{
    cout << "input (straight polish write)" << endl;
    getline(cin, input_str);
    // cout << input_str << endl;

    if (check_symbols())
    {
        cout << "symbols ok" << endl;

        fill_vector();
        // cout << "vector fill ok" << endl;

        for (size_t i = 0; i < in_seq.size(); i++)
        {
            cout << in_seq[i] << endl;
        }
        
        direct_notat(0);
        cout << in_seq[0] << endl;

        //если ответ найдет то показать ответ
        //иначе ошибка
    }
    else cerr << "symbols error" << endl;    

    system("pause");
    return (0);
}