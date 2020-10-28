#include <iostream>
#include <stdlib.h>

//реализация шаблона класса матрицы
template<typename T>
class Matrix
{
private:

	unsigned int str_num;
	unsigned int col_num;
	T** matrix;

public:

	//конструктор копирования
	Matrix(const Matrix &another)
	{
		/*используется в случае создания полной копии объекта
		допустим есть экземпляр Б матрицы, тогда
		при Matrix<*> A = Б, либо при Matrix<*> A(Б)
		будет создана полная копия объекта Б */
		this->str_num = another.str_num;
		this->col_num = another.col_num;
		this->matrix = new T* [another.str_num];
		for (unsigned int i = 0; i < another.str_num; ++i)
		{
			this->matrix[i] = new T [another.col_num];
			for (unsigned int j = 0; j < another.col_num; ++j)
			{
				this->matrix[i][j] = another.matrix[i][j];
			}
		}
		// std::cout << "\nobject " << this << " has been created";
		// std::cout << "\nit has " << this->matrix << " address to array\n";
	}

	//стандартный конструктор
	Matrix(unsigned int a, unsigned int b)
	{
		if ((a > 0) && (b > 0))
		{
			/*вызывается при стандартном формировании матрицы
			Matrix<*> A(а, б)
			а и б являются размерами формируемой матрицы*/
			this->str_num = a;
			this->col_num = b;
			this->matrix = new T* [this->str_num];
			for (unsigned int i = 0; i < this->str_num; ++i)
			{
				this->matrix[i] = new T [this->col_num];
			}
		}
		else
		{
			std::cerr << "\ninvalid matrix size\n";
			system("pause");
			exit(1);
		}
		// std::cout << "\nobject " << this << " has been created";
		// std::cout << "\nit has " << this->matrix << " address to array\n";
	}

	/*секция операторов для действий над матрицами.
	возвращаемый тип & для возврата области памяти
	где хранится итоговый объект*/
	Matrix & operator= (const Matrix &another)
	{
		/*при применении на матрицах А = Б
		оператор присваивания стирает информацию в А
		и пересоздаёт матрицу для копирования
		соответствующих данных из Б*/
		for (unsigned int i = 0; i < this->str_num; ++i)
		{
			delete [] this->matrix[i];
		}
		delete [] this->matrix;

		this->str_num = another.str_num;
		this->col_num = another.col_num;
		this->matrix = new T* [another.str_num];
		for (unsigned int i = 0; i < another.str_num; ++i)
		{
			this->matrix[i] = new T [another.col_num];
			for (unsigned int j = 0; j < another.col_num; ++j)
			{
				this->matrix[i][j] = another.matrix[i][j];
			}
		}
		
		return (*this);
	}

	Matrix & operator+= (const Matrix &another)
	{
		if ((this->str_num != another.str_num) || (this->col_num != another.col_num))
		{
			std::cerr << "\naddition operation cannot be performed on matrices\n";
			system("pause");
			exit(1);
		}
		
		for (unsigned int i = 0; i < this->str_num; ++i)
		{
			for (unsigned int j = 0; j < this->col_num; ++j)
			{
				this->matrix[i][j] += another.matrix[i][j];
			}
		}

		return (*this);
	}

	Matrix & operator-= (const Matrix &another)
	{
		if ((this->str_num != another.str_num) || (this->col_num != another.col_num))
		{
			std::cerr << "\nsubtraction operation cannot be performed on matrices\n";
			system("pause");
			exit(1);
		}
		
		for (unsigned int i = 0; i < this->str_num; ++i)
		{
			for (unsigned int j = 0; j < this->col_num; ++j)
			{
				this->matrix[i][j] -= another.matrix[i][j];
			}
		}

		return (*this);
	}

	Matrix & operator*= (const Matrix &another)
	{
		//опертор умножения на матрицу
		if (this->col_num != another.str_num)
		{
			std::cerr << "\nthe multiplication operation cannot be performed on matrices\n";
			system("pause");
			exit(1);
		}

		//здесь копируются данные из умножаемой матрицы (которая слева)
		T** buffer = new T* [this->str_num];
		for (unsigned int i = 0; i < this->str_num; ++i)
		{
			buffer[i] = new T [this->col_num];
			for (unsigned int j = 0; j < this->col_num; ++j)
			{
				buffer[i][j] = this->matrix[i][j];
			}
		}

		//здесь формируется будущая итоговая матрица (которая получится)
		for (unsigned int i = 0; i < this->str_num; ++i)
		{
			delete [] this->matrix[i];
		}
		this->col_num = another.col_num;
		for (unsigned int i = 0; i < this->str_num; ++i)
		{
			this->matrix[i] = new T [this->col_num];
			for (unsigned int j = 0; j < this->col_num; ++j)
			{
				this->matrix[i][j] = 0.0;
			}
		}

		//здесь заполняется итоговая матрица путём перемножения исходных
		unsigned int n = another.str_num;
		for (unsigned int i = 0; i < this->str_num; ++i)
		{
			for (unsigned int j = 0; j < another.col_num; ++j)
			{
				for (unsigned int k = 0; k < n; ++k)
				{
					this->matrix[i][j] += (buffer[i][k] * another.matrix[k][j]);
				}
			}
		}

		//чистка
		for (unsigned int i = 0; i < this->str_num; ++i)
		{
			delete [] buffer[i];
		}
		delete [] buffer;

		return (*this);
	}

	Matrix & operator*= (const T multiplier)
	{
		//опертор умножения на число
		for (unsigned int i = 0; i < this->str_num; ++i)
		{
			for (unsigned int j = 0; j < this->col_num; ++j)
			{
				this->matrix[i][j] *= multiplier;
			}
		}

		return (*this);
	}

	T & operator() (unsigned int a, unsigned int b) 
	{
		//оператор доступа к ячейкам матрицы через круглые скобки
		return this->matrix[a][b];
	}

	//некоторые методы класса
	T height()
	{
		return this->str_num;
	}

	T width()
	{
		return this->col_num;
	}

	Matrix & take_link()
	{
		return (*this);
	}

	//деструктор для чистки
	~Matrix()
	{
		// std::cout << "\nobject " << this << " has been deleted";
		// std::cout << "\nit has had " << this->matrix << " address to array\n";
		for (unsigned int i = 0; i < this->str_num; ++i)
		{
			delete [] this->matrix[i];
		}
		delete [] this->matrix;
	}
};

//возвращает модуль от числа с плавающей запятой двойной точности (double)
double return_abs(double numer)
{
	if (numer > 0.0) return (numer);
	else return (-1 * numer);
}

//проверяет матрицу на условие сходимости решения
//если не сходится то матрица не имеет единственного решения
int check(Matrix<double>* p_mat, unsigned int n)
{
	double main_diag;
	double other_numers;

	/*условие сходимости сводится к сравнению элемента на главной диагонали
	с остальными элементами в строке.
	если этот элемент больше суммы остальных элементов, то решения сходятся*/
	for (unsigned int i = 0; i < n; ++i)
	{
		main_diag = return_abs((*p_mat)(i,i));
		other_numers = 0.0;

		for (unsigned int j = 0; j < n; ++j)
		{
			if (j == i) continue;
			else other_numers += return_abs((*p_mat)(i,j));
		}

		if (other_numers > main_diag) return (0);
	}
	
	return (1);
}

//проверяет достигнута ли заданная точность
int check_precise(Matrix<double>* current, Matrix<double>* previous, unsigned int n, double* eps)
{
	//чтобы это проверить, сравниваются текущий и предыдущий результаты вычислений
	for (unsigned int i = 0; i < n; ++i)
	{
		if (return_abs((*current)(i,0) - (*previous)(i,0)) > (*eps)) return (1);
	}
	return (0);
}

//поиск решений СЛАУ методом простых итераций
void iter(Matrix<double>* p_mat, Matrix<double>* p_vec, Matrix<double>* X_n, unsigned int n, double* eps, unsigned int* iterations)
{
	//X_n+1=B*X_n+betta
	Matrix<double> betta(n, 1);
	Matrix<double> temp(n, 1);
	Matrix<double> B(n, n);

	//находим бетту и начальное ИКС энное
	for (unsigned int i = 0; i < n; ++i)
	{
		betta(i,0) = (*p_vec)(i,0) / (*p_mat)(i,i);
		(*X_n)(i,0) = 0.0;
		temp(i,0) = 1.0;
	}

	//считаем матрицу БЭ
	for (unsigned int i = 0; i < n; ++i)
	{
		for (unsigned int j = 0; j < n; ++j)
		{
			if (j == i) B(i,j) = 0;
			else B(i,j) = (-1 * (*p_mat)(i,j) / (*p_mat)(i,i));
		}
	}

	//поиск решения
	while (check_precise(X_n, &temp, n, eps))
	{
		for (unsigned int i = 0; i < n; ++i)
		{
			temp(i,0) = (*X_n)(i,0);
			(*X_n)(i,0) = betta(i,0);
			for (unsigned int j = 0; j < n; ++j)
			{
				(*X_n)(i,0) += B(i,j) * (*X_n)(j,0);
			}
		}
		++(*iterations);
	}
}

//реализация фунцкии нахождения факториала для числа с плавающей запятой двойной точности (double)
double my_factorial(double nb)
{
	double result = 1.0;
	double i = 1.0;

	if (nb >= 0)
	{
		while (i <= nb)
		{
			result *= i;
			++i;
		}
	}
	else
		result = 0;

	return (result);
}

//нахождение наибольшего общего делителя между двумя числами
double nod(double n, double m)
{
    if (m == 0) return n;
    if (n > m) return nod(m, n - m);
    else return nod(n, m - n);
}

//строит СЛАУ по вводным данным
void build_hilbert(Matrix<double>* p_mat, Matrix<double>* p_vec, unsigned int n)
{
	int temp = n;
	double multiplier;
	double nod_;
	double h;

	//переменная множитель отвечает за формирование адекватных значений в СЛАУ при малых n
	//для небольших систем ищется общий знаменатель, от которого надо избаваиться
	//затем ищется НОД
	if (n < 7) multiplier = my_factorial(temp);
	else multiplier = 1;

	for (unsigned int i = 0; i < n; ++i)
	{
		//формируется вектор правой части СЛАУ
		if (i == 0) (*p_vec)(i,0) = 10*multiplier;
		else (*p_vec)(i,0) = 0;

		//формируется матрица левой части СЛАУ
		for (unsigned int j = 0; j < n; ++j)
		{
			h = (-1*multiplier/(i+j+1));
			(*p_mat)(i,j) = h;
			if (j == i) (*p_mat)(i,j) += 10*multiplier;
		}

		//деление на НОД при малых n 
		if (n < 7)
		{
			nod_ = return_abs((*p_mat)(i,0));
			for (unsigned int j = 1 ; j < n ; ++j)
			{
				nod_ = nod(return_abs(nod_), return_abs((*p_mat)(i,j)));
			}

			// std::cout << "nod of " << i+1 << " str: " << nod_ << "\n";

			for (unsigned int j = 0; j < n; ++j)
			{
				(*p_mat)(i,j) /= nod_;
			}
			(*p_vec)(i,0) /= nod_;
		}
		
		//множитель увеличивается с каждой строкой (особенность матрицы Гильберта)
		++temp;
		if (n < 7) multiplier = my_factorial(temp);
	}
	
}

//поиск решений СЛАУ методом Гаусса
void gauss(Matrix<double>* p_mat, Matrix<double>* p_vec, Matrix<double>* X_n, unsigned int un, double* eps) 
{
	int k = 0;
	int index;
	int n = (int)(un);
	double max;
	double temp;

	while (k < n) 
	{
		// Поиск строки с максимальным a[i][k]
		max = return_abs((*p_mat)(k,k));
		index = k;
		for (int i = k + 1; i < n; ++i) 
		{
			if (return_abs((*p_mat)(i,k)) > max)
			{
				max = return_abs((*p_mat)(i,k));
				index = i;
			}
		}

		// Перестановка строк (строка с максимальным a[i][k] станет первая)
		if (max < (*eps)) 
		{
			// нет ненулевых диагональных элементов
			std::cout << "The solution cannot be obtained because of the null column ";
			std::cout << index << " of matrix\n";
			system("pause");
			exit(1);
		}
		for (int j = 0; j < n; ++j) 
		{
			temp = (*p_mat)(k,j);
			(*p_mat)(k,j) = (*p_mat)(index,j);
			(*p_mat)(index,j) = temp;
		}
		temp = (*p_vec)(k,0);
		(*p_vec)(k,0) = (*p_vec)(index,0);
		(*p_vec)(index,0) = temp;

		// Нормализация уравнений
		for (int i = k; i < n; ++i) 
		{
			temp = (*p_mat)(i,k);

			if (return_abs(temp) < (*eps)) continue; // для нулевого коэффициента пропустить
			for (int j = 0; j < n; ++j)
			{
				(*p_mat)(i,j) = (*p_mat)(i,j) / temp;
			}

			(*p_vec)(i,0) = (*p_vec)(i,0) / temp;

			if (i == k) continue; // уравнение не вычитать само из себя
			for (int j = 0; j < n; ++j)
			{
				(*p_mat)(i,j) = (*p_mat)(i,j) - (*p_mat)(k,j);
			}

			(*p_vec)(i,0) = (*p_vec)(i,0) - (*p_vec)(k,0);
		}
		k++;
	}
	// обратная подстановка
	for (k = n - 1; k >= 0; k--)
	{
		(*X_n)(k,0) = (*p_vec)(k,0);
		for (int i = 0; i < k; i++)
		{
			(*p_vec)(i,0) = (*p_vec)(i,0) - (*p_mat)(i,k) * (*X_n)(k,0);
		}
	}
}

//служит для пользовательского ввода начальных данных
//n - размер будущей СЛАУ, eps - точность искомого решения
unsigned int input(double* eps)
{
	unsigned int n;
	double temp = *eps;
	std::cout << "Enter Hilbert matrix size (more than 1): ";
	std::cin >> n;

	if (n < 2)
	{
		std::cerr << "\nHilbert matrix size error\n";
		system("pause");
		exit(1);
	}

	std::cout << "Default epsilon = " << *eps << "\nIf you'd like to use default put 1\nEnter: ";
	std::cin >> *eps;

	if (*eps == 1)
	{
		*eps = temp;
		std::cout << "You've chosen default epsilon\n\n";
	}
	else if ((*eps < 1) && (*eps != 0))
	{
		std::cout << "Your custom epsilon: " << *eps << "\n\n";
	}

	if ((*eps > 1) || (*eps == 0))
	{
		std::cerr << "\nEpsilon error\n";
		system("pause");
		exit(1);
	}

	return (n);
}

//выводит СЛАУ на экран
void show_SLAU(Matrix<double>* p_mat, Matrix<double>* p_vec, unsigned int n)
{
	char ch;

	//если система не запредельно большая (n<7) то мы её выводим на экран
	/*n >= 7 является слишком большой по той причине что тип double
	не может содержать в себе числа которые превышают его предел.
	этот предел достигается на главной диагонали при попытке найти
	общий знаменатель и НОД ещё на этапе формирования*/
	if (n < 7)
	{
		for (unsigned int i = 0; i < n; i++)
		{
			for (unsigned int j = 0; j <= n; j++)
			{
				ch = (char)(j + 97);
				if (j != n)
				{
					std::cout << (*p_mat)(i,j) << "*" << ch << "\t";
				}
				else
				{
					std::cout << "= " << (*p_vec)(i,0) << ";\n";
				}
			}
		}
	}
	else std::cout << "Coefficients are too big to display them (double type is not ehough)\n";

	std::cout << "\n";
}

//вывод вектор решений на экран
void show_solution(Matrix<double>* iter_result, Matrix<double>* gauss_result, unsigned int n)
{
	char ch;

	//если размер матрицы <= 26 (длина алфовита) то выводятся латинские буквы 
	if (n <= 26)
	{
		for (unsigned int i = 0; i < n; ++i)
		{
			ch = (char)(i + 97);
			std::cout << ch << " = " << (*iter_result)(i,0) << ";\n";
			std::cout << ch << " = " << (*gauss_result)(i,0) << "; //gauss method\n\n";
		}
	}
	//иначе выводятся индексы для каждого корня вектора решений
	else
	{
		for (unsigned int i = 0; i < n; ++i)
		{
			std::cout << "u[" << i+1 << "] = " << (*iter_result)(i,0) << ";\n";
			std::cout << "u[" << i+1 << "] = " << (*gauss_result)(i,0) << "; //gauss method\n\n";
		}
	}
}

//функция применяет методы решения СЛАУ на исходную систему
void solve_an_equations_system(	Matrix<double>* p_mat, Matrix<double>* p_vec, Matrix<double>* p_iter, Matrix<double>* p_gauss, unsigned int n, double* eps, unsigned int* iterations)
{
	if (check(p_mat, n))
	{
		iter(p_mat, p_vec, p_iter, n, eps, iterations);
		gauss(p_mat, p_vec, p_gauss, n, eps);
		show_solution(p_iter, p_gauss, n);
	}
	else
	{
		std::cerr << "\nexpression error\n";
		system("pause");
		exit(1);
	}
}

//вывести на экран кол-во итераций
void show_num_of_iterations(unsigned int* iterations)
{
	std::cout << "Number of iterations: " << (*iterations) << "\n";

}

int main()
{
	//задаём точность вычислений и размер СЛАУ
	double eps = 0.001;
	unsigned int n = input(&eps);
	unsigned int iterations = 0;

	//формируем матрицу и векторы для дальнейшей работы
	Matrix<double> matrix(n, n);
	Matrix<double> vector(n, 1);
	Matrix<double> iter_result(n, 1);
	Matrix<double> gauss_result(n, 1);

	//формируем СЛАУ и выводим её на экран
	build_hilbert(&matrix, &vector, n);
	show_SLAU(&matrix, &vector, n);

	//решаем СЛАУ двумя методами и выводим ответы на экран
	solve_an_equations_system(&matrix, &vector, &iter_result, &gauss_result, n, &eps, &iterations);
	show_num_of_iterations(&iterations);

	system("pause");

	return 0;
}