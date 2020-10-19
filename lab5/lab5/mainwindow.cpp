#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int g_array[127] = {0};
QString buffer;
//QTextStream out(stdout);

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

            //out << "'" << ch << "' found " << k << " times" << endl;
            buffer.append("'");
            buffer.append(ch);
            buffer.append("' found ");
            buffer.append((QString::number(k)));
            buffer.append(" times\n");
        }
        i++;
    }
    //результатом является количество найденных символов из перечня
    return (res);
}

int scan_text(QString text)
{
    int sum = 0;
    int i = 0; // номер в ascii
    QChar ch;

    //отобразить текст
    // cout << text << endl << endl;

    //сбор статистики символов
    for (int j = 0; j < text.length(); ++j)
    {
        ch = text[j];
        if (ch == '!') i = 33;
        else if (ch == '"') i = 34;
        else if (ch == '#') i = 35;
        else if (ch == '$') i = 36;
        else if (ch == '%') i = 37;
        else if (ch == '&') i = 38;
        else if (ch == "'") i = 39;
        else if (ch == '(') i = 40;
        else if (ch == ')') i = 41;
        else if (ch == '*') i = 42;
        else if (ch == '+') i = 43;
        else if (ch == ',') i = 44;
        else if (ch == '-') i = 45;
        else if (ch == '.') i = 46;
        else if (ch == '/') i = 47;
        else if (ch == '0') i = 48;
        else if (ch == '1') i = 49;
        else if (ch == '2') i = 50;
        else if (ch == '3') i = 51;
        else if (ch == '4') i = 52;
        else if (ch == '5') i = 53;
        else if (ch == '6') i = 54;
        else if (ch == '7') i = 55;
        else if (ch == '8') i = 56;
        else if (ch == '9') i = 57;
        else if (ch == ':') i = 58;
        else if (ch == ';') i = 59;
        else if (ch == '<') i = 60;
        else if (ch == '=') i = 61;
        else if (ch == '>') i = 62;
        else if (ch == '?') i = 63;
        else if (ch == '@') i = 64;
        else if (ch == 'A') i = 65;
        else if (ch == 'B') i = 66;
        else if (ch == 'C') i = 67;
        else if (ch == 'D') i = 68;
        else if (ch == 'E') i = 69;
        else if (ch == 'F') i = 70;
        else if (ch == 'G') i = 71;
        else if (ch == 'H') i = 72;
        else if (ch == 'I') i = 73;
        else if (ch == 'J') i = 74;
        else if (ch == 'K') i = 75;
        else if (ch == 'L') i = 76;
        else if (ch == 'M') i = 77;
        else if (ch == 'N') i = 78;
        else if (ch == 'O') i = 79;
        else if (ch == 'P') i = 80;
        else if (ch == 'Q') i = 81;
        else if (ch == 'R') i = 82;
        else if (ch == 'S') i = 83;
        else if (ch == 'T') i = 84;
        else if (ch == 'U') i = 85;
        else if (ch == 'V') i = 86;
        else if (ch == 'W') i = 87;
        else if (ch == 'X') i = 88;
        else if (ch == 'Y') i = 89;
        else if (ch == 'Z') i = 90;
        else if (ch == '[') i = 91;
        else if (ch == '\\') i = 92;
        else if (ch == ']') i = 93;
        else if (ch == '^') i = 94;
        else if (ch == '_') i = 95;
        else if (ch == '`') i = 96;
        else if (ch == 'a') i = 97;
        else if (ch == 'b') i = 98;
        else if (ch == 'c') i = 99;
        else if (ch == 'd') i = 100;
        else if (ch == 'e') i = 101;
        else if (ch == 'f') i = 102;
        else if (ch == 'g') i = 103;
        else if (ch == 'h') i = 104;
        else if (ch == 'i') i = 105;
        else if (ch == 'j') i = 106;
        else if (ch == 'k') i = 107;
        else if (ch == 'l') i = 108;
        else if (ch == 'm') i = 109;
        else if (ch == 'n') i = 110;
        else if (ch == 'o') i = 111;
        else if (ch == 'p') i = 112;
        else if (ch == 'q') i = 113;
        else if (ch == 'r') i = 114;
        else if (ch == 's') i = 115;
        else if (ch == 't') i = 116;
        else if (ch == 'u') i = 117;
        else if (ch == 'v') i = 118;
        else if (ch == 'w') i = 119;
        else if (ch == 'x') i = 120;
        else if (ch == 'y') i = 121;
        else if (ch == 'z') i = 122;
        else if (ch == '{') i = 123;
        else if (ch == '|') i = 124;
        else if (ch == '}') i = 125;
        else if (ch == '~') i = 126;
        g_array[i - 1] += 1;
    }

    //вывод первичной статистики (кол-во для каждого символа)
    sum = scan_out(64, 89) + scan_out(32, 63) + scan_out(90, 95) + scan_out(122, 125);

    //отделяем вывод первой ф-ии от второй, отправляем результат во вторую ф-ию
//    out << endl;
    buffer.append("\n");
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
            float percent = (num * 100 / div);
            QString b;
            b.setNum(percent);
            //out << "'" << ch << "' took " << (num * 100 / div) << "% of text\t";
            buffer.append("'");
            buffer.append(ch);
            buffer.append("' took ");
            buffer.append(b);
            buffer.append("% of text\t");

            //тут гистограммы
            h = 0;
            while (h <= (int)(num * 100 / div))
            {
                //out << "~";
                buffer.append("*");
                h++;
            }

            //переход на след строку
            //out << endl;
            buffer.append("\n");
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

void MainWindow::on_pushButton_clicked()
{
    //берём текст из поля
    QString text = ui->textEdit->toPlainText();

    //пихаем этот текст в лабу1
    show_stat(scan_text(text));

    //QString result = buffer;

    //ставим готовый текст во второе поле
    ui->textEdit_2->setText(buffer);

    //отключение кнопки
    ui->pushButton->setEnabled(false);
}

void MainWindow::on_pushButton_2_clicked()
{
    //чистка и включение кнопки
    buffer.clear();
    for (int i = 0; i < 127; ++i) {
        g_array[i] = 0;
    }
    ui->textEdit_2->clear();
    //ui->textEdit->clear();
    ui->pushButton->setEnabled(true);
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->textEdit->clear();
}
