#include <iostream>
#include <vector>

using namespace std;

vector<double> myStack;
string input_str;
string buf;

int count_it(int op1, int pos, int op2)
{

}

int f(int pos)
{
    int result;

    result = count_it(f(pos), pos, f(pos-1));

    return (result);
}

//нужно попробовать сделать рекурсию - функция получает позицию в параметр и ищет 2 подряд операнда и применяет действие, потом как-то помечает эти операнды и знак, пихает туда результат либо хранит в себе и затем запускает сама себя же и в параметр новая позиция и так по кругу пока весь стэк не кончится

int checkSymbols()
{
    for (size_t i = 0; i < input_str.length(); i++)
    {
        if (!(((input_str[i] >= 42) && (input_str[i] <= 58)) || (input_str[i] == 32))) return (0);
    }
    return (1);
}

void count_it(int pos, char action)
{
    if (action == '*') myStack[pos-1] = myStack[pos-1] * myStack[pos];
    else if (action == '+') myStack[pos-1] = myStack[pos-1] + myStack[pos];
    else if (action == '-') myStack[pos-1] = myStack[pos-1] - myStack[pos];
    else if ((action == '/') || (action == ':')) myStack[pos-1] = myStack[pos-1] / myStack[pos];

    myStack.pop_back();  
}

void directNotation()
{
    int i = 0;
    int row = 0;
    int pos = -1;

    while (i < input_str.length())
    {
        if (isdigit(input_str[i]))
        {
            while (isdigit(input_str[i]) || (input_str[i] == '.') || (input_str[i] == ','))
            {
                buf.push_back(input_str[i]);
                i++;
            }

            myStack.push_back((double)atof(buf.c_str()));
            pos++;
            buf.clear();

            if (row == 1)
            {
                while (!((input_str[i] == '*') || (input_str[i] == '+') || (input_str[i] == '-') || (input_str[i] == '/') || (input_str[i] == ':'))) i++;
                count_it(pos, input_str[i]);
                pos--;
            }

            while (isspace(input_str[i])) i++;

            if (isdigit(input_str[i])) row = 1;
        }
        else row = 0;

        i++;
    }
    // cout << "stack check ok" << endl;
}

int main(void)
{
    cout << "input (straight polish write)" << endl;
    getline(cin, input_str);
    // cout << input_str << endl;

    if (checkSymbols())
    {
        cout << "symbols ok" << endl;
        directNotation();

        // for (size_t i = 0; i < myStack.size(); i++)
        // {
        //     cout << myStack[i] << endl;
        // }
        
        //если ответ найдет то показать ответ
        //иначе ошибка
    }
    else cerr << "symbols error" << endl;    

    system("pause");
    return (0);
}