#include <iostream>
#include <stdlib.h>

// template<typename T>
// class Matrix
// {
// protected:
//
// 	unsigned int str_num;
// 	unsigned int col_num;
// 	T** matrix;
//
// public:
//
// 	Matrix(const Matrix &another)
// 	{
// 		this->str_num = another.str_num;
// 		this->col_num = another.col_num;
// 		this->matrix = new T* [another.str_num];
// 		for (unsigned int i = 0; i < another.str_num; ++i)
// 		{
// 			this->matrix[i] = new T [another.col_num];
// 			for (unsigned int j = 0; j < another.col_num; ++j)
// 			{
// 				this->matrix[i][j] = another.matrix[i][j];
// 			}
// 		}
// 		// std::cout << "\nobject " << this << " has been created";
// 		// std::cout << "\nit has " << this->matrix << " address to array\n";
// 	}
//
// 	Matrix(unsigned int a, unsigned int b)
// 	{
// 		if ((a > 0) && (b > 0))
// 		{
// 			this->str_num = a;
// 			this->col_num = b;
// 			this->matrix = new T* [this->str_num];
// 			for (unsigned int i = 0; i < this->str_num; ++i)
// 			{
// 				this->matrix[i] = new T [this->col_num];
// 			}
// 		}
// 		else
// 		{
// 			std::cerr << "\ninvalid matrix size\n";
// 			system("pause");
// 			exit(1);
// 		}
// 		// std::cout << "\nobject " << this << " has been created";
// 		// std::cout << "\nit has " << this->matrix << " address to array\n";
// 	}
//
// 	Matrix & operator= (const Matrix &another)
// 	{
// 		for (unsigned int i = 0; i < this->str_num; ++i)
// 		{
// 			delete [] this->matrix[i];
// 		}
// 		delete [] this->matrix;
//
// 		this->str_num = another.str_num;
// 		this->col_num = another.col_num;
// 		this->matrix = new T* [another.str_num];
// 		for (unsigned int i = 0; i < another.str_num; ++i)
// 		{
// 			this->matrix[i] = new T [another.col_num];
// 			for (unsigned int j = 0; j < another.col_num; ++j)
// 			{
// 				this->matrix[i][j] = another.matrix[i][j];
// 			}
// 		}
//		
// 		return (*this);
// 	}
//
// 	Matrix & operator+= (const Matrix &another)
// 	{
// 		if ((this->str_num != another.str_num) || (this->col_num != another.col_num))
// 		{
// 			std::cerr << "\naddition operation cannot be performed on matrices\n";
// 			system("pause");
// 			exit(1);
// 		}
//		
// 		for (unsigned int i = 0; i < this->str_num; ++i)
// 		{
// 			for (unsigned int j = 0; j < this->col_num; ++j)
// 			{
// 				this->matrix[i][j] += another.matrix[i][j];
// 			}
// 		}
//
// 		return (*this);
// 	}
//
// 	Matrix & operator-= (const Matrix &another)
// 	{
// 		if ((this->str_num != another.str_num) || (this->col_num != another.col_num))
// 		{
// 			std::cerr << "\nsubtraction operation cannot be performed on matrices\n";
// 			system("pause");
// 			exit(1);
// 		}
//		
// 		for (unsigned int i = 0; i < this->str_num; ++i)
// 		{
// 			for (unsigned int j = 0; j < this->col_num; ++j)
// 			{
// 				this->matrix[i][j] -= another.matrix[i][j];
// 			}
// 		}
//
// 		return (*this);
// 	}
//
// 	Matrix & operator*= (const Matrix &another)
// 	{
// 		if (this->col_num != another.str_num)
// 		{
// 			std::cerr << "\nthe multiplication operation cannot be performed on matrices\n";
// 			system("pause");
// 			exit(1);
// 		}
//
// 		T** buffer = new T* [this->str_num];
// 		for (unsigned int i = 0; i < this->str_num; ++i)
// 		{
// 			buffer[i] = new T [this->col_num];
// 			for (unsigned int j = 0; j < this->col_num; ++j)
// 			{
// 				buffer[i][j] = this->matrix[i][j];
// 			}
// 		}
//		
// 		for (unsigned int i = 0; i < this->str_num; ++i)
// 		{
// 			delete [] this->matrix[i];
// 		}
//		
// 		this->col_num = another.col_num;
// 		for (unsigned int i = 0; i < this->str_num; ++i)
// 		{
// 			this->matrix[i] = new T [this->col_num];
// 			for (unsigned int j = 0; j < this->col_num; ++j)
// 			{
// 				this->matrix[i][j] = 0.0;
// 			}
// 		}
//
// 		unsigned int n = another.str_num;
// 		for (unsigned int i = 0; i < this->str_num; ++i)
// 		{
// 			for (unsigned int j = 0; j < another.col_num; ++j)
// 			{
// 				for (unsigned int k = 0; k < n; ++k)
// 				{
// 					this->matrix[i][j] += (buffer[i][k] * another.matrix[k][j]);
// 				}
// 			}
// 		}
//
// 		for (unsigned int i = 0; i < this->str_num; ++i)
// 		{
// 			delete [] buffer[i];
// 		}
// 		delete [] buffer;
//
// 		return (*this);
// 	}
//
// 	Matrix & operator*= (const T multiplier)
// 	{
// 		for (unsigned int i = 0; i < this->str_num; ++i)
// 		{
// 			for (unsigned int j = 0; j < this->col_num; ++j)
// 			{
// 				this->matrix[i][j] *= multiplier;
// 			}
// 		}
//
// 		return (*this);
// 	}
//
// 	T & operator() (unsigned int a, unsigned int b) 
// 	{
// 		return this->matrix[a][b];
// 	}
//
// 	T height()
// 	{
// 		return this->str_num;
// 	}
//
// 	T width()
// 	{
// 		return this->col_num;
// 	}
//
// 	~Matrix()
// 	{
// 		// std::cout << "\nobject " << this << " has been deleted";
// 		// std::cout << "\nit has had " << this->matrix << " address to array\n";
// 		for (unsigned int i = 0; i < this->str_num; ++i)
// 		{
// 			delete [] this->matrix[i];
// 		}
// 		delete [] this->matrix;
// 	}
// };

int iterarions = 0;

double return_abs(double numer)
{
	if (numer > 0.0) return (numer);
	else return (-1 * numer);
}

int check(double** a, int n)
{
	double main_diag;
	double other_numers;

	//условие на сходимость

	for (int i = 0; i < n; ++i)
	{
		main_diag = return_abs(a[i][i]);
		other_numers = 0.0;

		for (int j = 0; j < n; ++j)
		{
			if (j == i) continue;
			else other_numers += return_abs(a[i][j]);
		}

		if (other_numers > main_diag) return (0);
	}
	
	return (1);
}

int check_precise(double* current, double* previous, int n, double eps)
{
	for (int i = 0; i < n; ++i)
	{
		if (return_abs(current[i] - previous[i]) > eps) return (1);
	}
	return (0);
}

double* iter(double** a, double* b, int n, double eps)
{
	double* Xn;
	double* betta;
	double* temp;
	double** B;

	//находим бетту и начальное ИКС энное
	Xn = new double [n];
	temp = new double [n];
	betta = new double [n];
	for (int i = 0; i < n; i++)
	{
		betta[i] = b[i] / a[i][i];
		Xn[i] = 0.0;
		temp[i] = 1.0;
	}

	//считаем матрицу БЭ
	B = new double* [n];
	for (int i = 0; i < n; ++i)
	{
		B[i] = new double [n];

		for (int j = 0; j < n; ++j)
		{
			if (j == i) B[i][j] = 0;
			else B[i][j] = (-1 * a[i][j] / a[i][i]);
		}
	}

	//итерационный метод
	while (check_precise(Xn, temp, n, eps))
	{
		for (int i = 0; i < n; ++i)
		{
			temp[i] = Xn[i];
			Xn[i] = betta[i];
			for (int j = 0; j < n; ++j)
			{
				Xn[i] += B[i][j] * Xn[j];
			}
		}
		++iterarions;
	}

	return Xn;
}

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

double nod(double n, double m)
{
    if (m == 0) return n;
    if (n > m) return nod(m, n - m);
    else return nod(n, m - n);
}

void build_hilbert(double*** p_mat, double** p_vec, int n)
{
	int temp = n;
	double multiplier;
	double nod_;
	double h;

	if (n < 7) multiplier = my_factorial(temp);
	else multiplier = 1;

	for (int i = 0; i < n; ++i)
	{
		if (i == 0) (*p_vec)[i] = 10*multiplier;
		else (*p_vec)[i] = 0;

		for (int j = 0; j < n; ++j)
		{
			h = (-1*multiplier/(i+j+1));
			(*p_mat)[i][j] = h;
			if (j == i) (*p_mat)[i][j] += 10*multiplier;
		}

		if (n < 7)
		{
			nod_ = return_abs((*p_mat)[i][0]);
			for (int j = 1 ; j < n ; ++j)
			{
				nod_ = nod(return_abs(nod_), return_abs((*p_mat)[i][j]));
			}

			// std::cout << "nod of " << i+1 << " str: " << nod_ << std::endl;

			for (int j = 0; j < n; ++j)
			{
				(*p_mat)[i][j] /= nod_;
			}
			(*p_vec)[i] /= nod_;
		}
		
		++temp;
		if (n < 7) multiplier = my_factorial(temp);
	}
	
}

double* gauss(double **a, double *y, int n, double eps) 
{
  double *x, max;
  int k, index;
  x = new double[n];
  k = 0;
  while (k < n) 
  {
    // Поиск строки с максимальным a[i][k]
    max = return_abs(a[k][k]);
    index = k;
    for (int i = k + 1; i < n; i++) 
    {
      if (return_abs(a[i][k]) > max)
      {
        max = return_abs(a[i][k]);
        index = i;
      }
    }
    // Перестановка строк
    if (max < eps) 
    {
      // нет ненулевых диагональных элементов
      std::cout << "The solution cannot be obtained because of the null column ";
      std::cout << index << " of matrix" << std::endl;
      return 0;
    }
    for (int j = 0; j < n; j++) 
    {
      double temp = a[k][j];
      a[k][j] = a[index][j];
      a[index][j] = temp;
    }
    double temp = y[k];
    y[k] = y[index];
    y[index] = temp;
    // Нормализация уравнений
    for (int i = k; i < n; i++) 
    {
      double temp = a[i][k];
      if (return_abs(temp) < eps) continue; // для нулевого коэффициента пропустить
      for (int j = 0; j < n; j++) 
        a[i][j] = a[i][j] / temp;
      y[i] = y[i] / temp;
      if (i == k)  continue; // уравнение не вычитать само из себя
      for (int j = 0; j < n; j++)
        a[i][j] = a[i][j] - a[k][j];
      y[i] = y[i] - y[k];
    }
    k++;
  }
  // обратная подстановка
  for (k = n - 1; k >= 0; k--)
  {
    x[k] = y[k];
    for (int i = 0; i < k; i++)
      y[i] = y[i] - a[i][k] * x[k];
  }
  return x;
}

int main()
{
	double eps = 0.00001;
	double** matrix;
	double* vector;
	double* result;
	// double* gauss_res;
	int n;
	char ch;

	std::cout << "Enter Hilbert matrix size (more than 1): ";
	std::cin >> n;

	// std::cout << "Default epsilon = 0.000001\nIf you'd like to use default enter 1\nEnter custom epsilon: ";
	// std::cin >> eps;
	// if (eps == 1) eps = 0.000001;

	if (eps > 1)
	{
		std::cerr << "Epsilon error (eps > 1)" << std::endl;
		system("pause");
		return (0);
	}

	if (n < 2)
	{
		std::cerr << "Hilbert matrix size error" << std::endl;
		system("pause");
		return (0);
	}

	vector = new double [n];
	matrix = new double* [n];
	for (int i = 0; i < n; ++i)
	{
		matrix[i] = new double[n];
	}

	build_hilbert(&matrix, &vector, n);

	if (n < 7)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j <= n; j++)
			{
				ch = (char)(j + 97);
				if (j != n)
				{
					std::cout << matrix[i][j] << "*" << ch << "\t";
				}
				else
				{
					std::cout << "= " << vector[i] << ";" << std::endl;
				}
			}
		}
	}
	else std::cout << std::endl << "Coefficients are too big to display them (double type is not ehough)" << std::endl;

	std::cout << std::endl;

	if (check(matrix, n))
	{
		result = iter(matrix, vector, n, eps);
		// gauss_res = gauss(matrix, vector, n, eps);

		if (n <= 26)
		{
			for (int i = 0; i < n; ++i)
			{
				ch = (char)(i + 97);
				std::cout << ch << " = " << result[i] << ";" << std::endl;
				// std::cout << ch << " = " << gauss_res[i] << "; //gauss method" << std::endl << std::endl;
			}
		}
		else
		{
			for (int i = 0; i < n; ++i)
			{
				std::cout << "u[" << i+1 << "] = " << result[i] << ";" << std::endl;
				// std::cout << "u[" << i+1 << "] = " << gauss_res[i] << "; //gauss method" << std::endl << std::endl;
			}
		}
	}
	else std::cout << "expression error" << std::endl;

	//чистка
	delete [] result;
	// delete [] gauss_res;
	delete [] vector;
	for (int i = 0; i < n; ++i)
	{
		delete [] matrix[i];
	}
	delete [] matrix;

	std::cout << std::endl << "Number of iterations: " << iterarions << std::endl;;

	// Matrix<double> AA(3, 2);
	// std::cout << "\nmatrix AA has been created";
	// std::cout << "\nheight of AA matrix: " << AA.height();
	// std::cout << "\nwidth of AA matrix: " << AA.width();
	//
	// std::cout << "\n\nfilling AA with some data\n";
	//
	// double l = 0.0;
	// for (int i = 0; i < AA.height(); i++)
	// {
	// 	for (int j = 0; j < AA.width(); j++)
	// 	{
	// 		l += 1.0;
	// 		AA(i, j) = l;
	// 		std::cout << AA(i, j) << "\t";
	// 	}
	// 	std::cout << "\n";
	// }
	//
	// Matrix<double> BB(2, 4);
	// // Matrix<double> BB = AA;
	// // std::cout << "\ntrying to call copying constructor to create BB obj and to copy data from AA to BB";
	// std::cout << "\n\nmatrix BB has been created";
	// std::cout << "\nheight of BB matrix: " << BB.height();
	// std::cout << "\nwidth of BB matrix: " << BB.width();
	//
	// // BB = AA;
	// // std::cout << "\n\ncopying data from AA to BB\n";
	// std::cout << "\n\nfilling BB with some data\n";
	// // std::cout << "\n";
	//
	// for (int i = 0; i < BB.height(); i++)
	// {
	// 	for (int j = 0; j < BB.width(); j++)
	// 	{
	// 		l += 1.0;
	// 		BB(i, j) = l;
	// 		std::cout << BB(i, j) << "\t";
	// 	}
	// 	std::cout << "\n";
	// }
	//
	// AA *= 10.0;
	// std::cout << "\ntrying to AA *= 10.0";
	// // std::cout << "\nheight of BB matrix: " << BB.height();
	// // std::cout << "\nwidth of BB matrix: " << BB.width();
	// std::cout << "\n";
	//
	// for (int i = 0; i < AA.height(); i++)
	// {
	// 	for (int j = 0; j < AA.width(); j++)
	// 	{
	// 		std::cout << AA(i, j) << "\t";
	// 	}
	// 	std::cout << "\n";
	// }
	//
	// // std::cout << "\nheight of BB matrix after copying: " << BB.height();
	// // std::cout << "\nwidth of BB matrix after copying: " << BB.width();
	// // std::cout << "\n";

	system("pause");

	return 0;
}