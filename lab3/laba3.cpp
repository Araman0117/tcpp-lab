#include <iostream>
#include <string>
#include <vector>

using namespace std;

//инициализируем стэк и входную последовательность
vector<double> my_stack;
vector<string> in_seq;
int numer = 1;
int err = 0;

//проверяет знак ли это
int issign(char ch)
{
    if ((ch == '*') || (ch == '+') || (ch == '-') || (ch == '/')) return (1);
    else return (0);
}

//пропускает разрешенные символы и return (1), но если есть запрещённые - то return (0)
int check_symbols(string input_str)
{
    for (size_t i = 0; i < input_str.length(); i++)
    {
        if (!(((input_str[i] >= 42) && (input_str[i] <= 58)) || (input_str[i] == 32)) || (input_str[i] == 44)) return (0);
    }
    return (1);
}

//кладём два операнда в стэк
void add_ops_to_stack(int pos)
{
    my_stack.push_back((double)atof((in_seq[pos]).c_str()));
    my_stack.push_back((double)atof((in_seq[pos+1]).c_str()));
}

// берём из стэка 2 операнда и применяем действие, return результат
double count_it(char action)
{
    if (action == '*') return (my_stack[0] * my_stack[1]);
    else if (action == '+') return (my_stack[0] + my_stack[1]);
    else if (action == '-') return (my_stack[0] - my_stack[1]);
    else if (action == '/') return (my_stack[0] / my_stack[1]);
    else 
    {
        err = 1;
        return (0);
    }
}

//пометить оператор и 2 операнда как исполненные (вычеркнуть как выполненные)
void mark_done(int pos, double result)
{
    in_seq.erase(in_seq.begin() + pos+1);
    in_seq.erase(in_seq.begin() + pos);
    in_seq[pos-1] = to_string(result);
}

//заполнить входную последовательность объектами
void fill_vector(string input_str)
{
    //буфер
    string buf;
    unsigned int i = 0;

    //идём по инпуту
    while (i < input_str.length())
    {
        //если есть спейсы - пропускаем их
        while (isspace(input_str[i])) i++;

        //если нашли цифру или знак, то
        if (isdigit(input_str[i]) || issign(input_str[i]))
        {
            //если цифра, то читаем число до конца и затем толкаем его в буфер
            while (isdigit(input_str[i]) || (input_str[i] == '.'))
            {
                buf.push_back(input_str[i]);
                i++;
            }

            // если знак, то сразу кидаем его в буфер
            if (issign(input_str[i]))
            {
                buf.push_back(input_str[i]);
                i++;
            }

            //формируем последовательность, по одному объекту за такт
            in_seq.push_back(buf.c_str());

            //чистим буфер
            buf.clear();
        }
    }
}

//основная функция
void direct_notat(unsigned int pos)
{
    double result;

    //если в данном узле (ноде или рекурсии) есть что посчитать, то посчитаем, иначе проверка на скрытую (умышленную) ошибку при вводе
    if (in_seq.size() >= 3)
    {
        //пока не прошли всю входящую последовательность и не нашли 2 подряд операнда, идём по вх. посл.
        while ((pos+1 < in_seq.size()) && (!(isdigit(in_seq[pos][0]) && isdigit(in_seq[pos+1][0])))) pos++;

        //если перед операндами есть знак и мы всё ещё не вышли из вх. посл. и перед операндами действительно стоит знак, то
        if (pos > 0 && pos+1 < in_seq.size() && issign(in_seq[pos-1][0]))
        {
            //кинем в стэк операнды
            add_ops_to_stack(pos);

            //применим на них действие соотв. знаку
            result = count_it(in_seq[pos-1][0]);

            //если ошибка в ходе вычислений то выйдем
            if (err == 1)
            {
                cerr << "count error" << endl;
                return ;
            }

            //подробный вывод каждого действия
            cout << numer++ << ") " << my_stack[0] << " " << in_seq[pos-1] << " " << my_stack[1] << " = " << result << endl;

            //чистим стэк, потому что мы исп. его неявно
            my_stack.clear();

            //помечаем в последовательности выполненное действие
            mark_done(pos, result);

            //рекурсивно работаем дальше
            direct_notat(0);
        }
        //если перед операндами нет знака или мы вышли за пределы вх. посл.
        else
        {
            cerr << endl << "expression logic error" << endl;
            err = 1;
        }
    }
    //находит лишний знак или число
    else if (in_seq.size() == 2)
    {
        cerr << endl << "expression logic error, excess symbols" << endl;
        err = 1;
    }
    return ;
}

int main(void)
{
    string input_str;
    double result;

    //вводим строку
    cout << "input (direct polish notation)" << endl;
    getline(cin, input_str);

    //проверка символов
    if (check_symbols(input_str))
    {
        fill_vector(input_str);

        //проверка длины входной последовательности
        if ( in_seq.size() >= 3)
        {
            cout << endl;
            direct_notat(0);
            result = ((double)atof((in_seq[0]).c_str()));

            // если в ходе работы не было ошибок, то
            if (err == 0) cout << endl << "Answer: " << result << endl;

            //очистка в случае зацикленных уравнений
            // my_stack.clear();
            // in_seq.clear();
            // numer = 1;
            // err = 0;
        }
        else cerr << endl << "expression size error" << endl;
    }
    else cerr << endl << "symbols error" << endl;
 
    //чтобы консоль не закрывалась
    system("pause"); 
    
    return (0);
}