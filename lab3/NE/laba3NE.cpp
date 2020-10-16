#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

vector<double> my_stack;
list<string> in_seq;
int numer = 1;
int err = 0;

//проверка символа действия
int issign(char ch)
{
    if ((ch == '*') || (ch == '+') || (ch == '-') || (ch == '/')) return (1);
    else return (0);
}

//проверка запрещённых символов
int check_symbols(string input_str)
{
    for (size_t i = 0; i < input_str.length(); i++)
    {
        //если найден запрещенный, то return 0
        if (!(((input_str[i] >= 42) && (input_str[i] <= 58)) || (input_str[i] == 32)) || (input_str[i] == 44)) return (0);
    }
    return (1);
}

//добавляет операнды в стэк
void add_ops_to_stack(string op1, string op2)
{
    my_stack.push_back((double)atof(op1.c_str()));
    my_stack.push_back((double)atof(op2.c_str()));
}

//берёт операнды из стэка и применяет оператор
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

//помечает 2 операнда и 1 оператор как использованные
void mark_done(list<string> :: iterator op1, list<string> :: iterator op2, list<string> :: iterator act, double result)
{
    string zamena = to_string(result);
    *op1 = zamena;

    in_seq.erase(op2);
    in_seq.erase(act);
}

//заполняет list входной последовательностью
void fill_list(string input_str)
{
    string buf;
    int i = 0;

    //идём по всему инпуту
    while (i < input_str.length())
    {
        //пропускаем все спейсы
        while (isspace(input_str[i])) i++;

        //если нашли цифру или оператор, то
        if (isdigit(input_str[i]) || issign(input_str[i]))
        {
            //если нашли цифру, то толкаем всё число в буфер
            while (isdigit(input_str[i]) || (input_str[i] == '.'))
            {
                buf.push_back(input_str[i]);
                i++;
            }

            //если нашли оператор, то толкаем оператор в буфер
            if (issign(input_str[i]))
            {
                buf.push_back(input_str[i]);
                i++;
            }

            //толкаем значение из буфера в list
            in_seq.push_back(buf.c_str());

            //освободить буфер
            buf.clear();
        }
    }
}

//выводит содержимое list на экран
void output_list()
{
    for (list<string> :: iterator it = in_seq.begin(); it != in_seq.end(); ++it)
    {
        cout << *it << endl;
    }
}

//основная рабочая функция
void revers_notat()
{
    //инициируем итераторы для работы алгоритма соответственно сдвигая их
    list<string> :: iterator it = in_seq.end();
    auto act = --it;
    auto op2 = --it;
    auto op1 = --it;

    double result;

    //если в данной рекурсии осталось 3 и более элементов во вх. посл., то
    if (in_seq.size() >= 3)
    {
        //цикл ищет ближайшую троицу -операнд- -операнд- -оператор- справа налево (по условию)
        while (!(isdigit((*op1)[0]) && isdigit((*op2)[0]) && issign((*act)[0])))
        {
            //если во всей последовательности не найдено троицы, то
            if (op1 == in_seq.begin())
            {
                err = 1;
                cerr << "expression logic error" << endl;
                return ;
            }
            
            //тут сдвигаем итераторы на следующие позиции внутри вх. посл.
            act = ++it;
            op2 = --it;
            op1 = --it;
        }
        //успешный выход из цикла значит что мы нашли троицу

        //кидаем операнды в стэк
        add_ops_to_stack(*op1, *op2);

        //находим результат
        result = count_it((*act)[0]);

        //если в ходе вычисления возникла ошибка, то
        if (err == 1)
        {
            cerr << endl << "count error" << endl;
            return ;
        }

        //подробный вывод каждого действия на экран
        cout << numer++ << ") " << my_stack[0] << " " << *act << " " << my_stack[1] << " = " << result << endl;

        //освобождаем стэк, ведь мы используем его неявно
        my_stack.clear();

        //помечаем троицу как использованную
        mark_done(op1, op2, act, result);

        //рекурсивно идём дальше
        revers_notat();
    }
    //обработка ошибки
    else if (in_seq.size() == 2)
    {
        cerr << endl << "expression logic error, excess symbols" << endl;
        err = 1;
    }
    return ;
}

int main(void)
{
    //инициируем итератор для list
    list<string> :: iterator it;

    string input_str;
    double result;

    //вывод сообщения для ввода последовательности в обратной польской нотации
    cout << "input (reverse polish notation)" << endl;
    getline(cin, input_str);

    //проверка на запрещённые символы
    if (check_symbols(input_str))
    {
        //формирование входной последовательности в list
        fill_list(input_str);

        //вывод содержимого list на экран
        // output_list();

        //стартовая проверка на размер последовательности, чтобы в ней было хотя бы 2 операнда и 1 оператор
        if ( in_seq.size() >= 3)
        {
            //пропуск одной строки для подробного вывода каждого действия на экран (если подробный вывод выключен, то пропуск строки следует выключить)
            cout << endl;

            revers_notat();
            it = in_seq.begin();
            result = ((double)atof((*it).c_str()));

            //если ошибок не найдено, то показать результат вычислений
            if (err == 0) cout << endl << "Answer: " << result << endl;

            //действия ниже нужны в случае зацикливания программы (чтобы вводить много уравнений и получать ответы)
            // my_stack.clear();
            // in_seq.clear();
            // numer = 1;
            // err = 0;
        }
        else cerr << endl << "expression size error" << endl;
    }
    else cerr << endl << "symbols error" << endl; 
 
    //чтобы консоль не закрывалась сама
    system("pause"); 
    
    return (0);
}