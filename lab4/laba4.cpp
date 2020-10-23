#include <iostream>

int iterarions = 0;

double return_abs(double numer)
{
	if (numer > 0.0) return (numer);
	else return (-1 * numer);
}

int check(double** a, int n)
{
	int res = 1;
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
	
	return (res);
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

double	my_factorial(double nb)
{
	double result;
	double i;

	result = 1.0;
	i = 1.0;
	if (nb >= 0)
	{
		while (i <= nb)
		{
			result *= i;
			i++;
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

void form_hilbert(double*** p_mat, double** p_vec, int n)
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

int main()
{
	double eps = 0.000001;
	double** matrix;
	double* vector;
	double* result;
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

	form_hilbert(&matrix, &vector, n);

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

		for (int i = 0; i < n; i++)
		{
			ch = (char)(i + 97);
			std::cout << ch << " = " << result[i] << ";" << std::endl;
		}
	}
	else std::cout << "expression error" << std::endl;

	//чистка
	delete [] result;
	delete [] vector;
	for (int i = 0; i < n; ++i)
	{
		delete [] matrix[i];
	}
	delete [] matrix;

	std::cout << std::endl << "Number of iterations: " << iterarions << std::endl;;

	system("pause");

	return 0;
}