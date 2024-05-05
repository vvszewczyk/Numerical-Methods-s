#include <iostream>
#include <fstream>

double** readData(const char* filename, int& size)
{
    std::ifstream plik(filename);
    if (!plik.is_open())
    {
        std::cerr << "No file." << std::endl;
        return nullptr;
    }

    plik >> size;

    double** matrix = new double* [size];
    for (std::size_t i = 0; i < size; i++)
    {
        matrix[i] = new double[size + 1];
    }

    for (std::size_t i = 0; i < size; i++)
    {
        for (std::size_t j = 0; j < size + 1; j++)
        {
            plik >> matrix[i][j];
        }
    }

    plik.close();
    return matrix;
}

void showMatrix(double** matrix, int size)
{
    for (std::size_t i = 0; i < size; i++)
    {
        for (std::size_t j = 0; j < size + 1; j++)
        {
            std::cout << matrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

void showMatrix2(double** matrix, int size)
{
    for (std::size_t i = 0; i < size; i++)
    {
        for (std::size_t j = 0; j < size; j++)
        {
            std::cout << matrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

void doolittle(double** A, double**& L, double**& U, int size)
{
    L = new double* [size];
    U = new double* [size];
    for (std::size_t i = 0; i < size; i++)
    {
        L[i] = new double[size]();
        U[i] = new double[size]();
        for (std::size_t j = 0; j < size; j++)
        {
            L[i][j] = (i == j) ? 1 : 0;
        }
    }

    for (std::size_t i = 0; i < size; i++)
    {
        //U
        for (std::size_t j = i; j < size; j++)
        {
            double sum = 0.0;
            for (std::size_t k = 0; k < i; k++)
            {
                double bufor = (L[i][k] * U[k][j]);
                sum += bufor;
            }
            U[i][j] = A[i][j] - sum;
        }

        //L
        for (std::size_t j = i + 1; j < size; j++)
        {
                double sum = 0.0;
                for (std::size_t k = 0; k < i; k++)
                {
                    double bufor = (L[j][k] * U[k][i]);
                    sum += bufor;
                }
                if (fabs(U[i][i]) < 1e-6)
                {
                    std::cerr << "0 is on the diagonal" << std::endl;
                    return;
                }
                L[j][i] = (A[j][i] - sum) / U[i][i];
        }
    }
}

//Ly = b dla y
void forwardSubstitution(double** L, double* b, double* y, int size) 
{
    for (std::size_t i = 0; i < size; i++)
    {
        y[i] = b[i];
        for (std::size_t j = 0; j < i; j++)
        {
            double bufor = L[i][j] * y[j];
            y[i] -= bufor;
        }
    }
}

//Ux = y dla x
void backwardSubstitution(double** U, double* y, double* x, int size) 
{
    for (int i = size - 1; i >= 0; i--)
    {
        x[i] = y[i];
        for (std::size_t j = i + 1; j < size; j++)
        {
            double bufor = U[i][j] * x[j];
            x[i] -= bufor;
        }
        x[i] = x[i]/U[i][i];
    }
}


int main()
{
    const char* filename = "RURL_dane2.txt";
    int n;
    double** A = readData(filename, n);

    std::cout << "Before:" << std::endl;
    showMatrix(A, n);

    double** L, ** U;
    doolittle(A, L, U, n);

    std::cout << "L matrix:" << std::endl;
    showMatrix2(L, n);
    std::cout << "U matrix:" << std::endl;
    showMatrix2(U, n);

    double* b = new double[n];
    for (std::size_t i = 0; i < n; i++)
    {
        b[i] = A[i][n];
    }

    //Ly = b dla y
    double* y = new double[n];
    forwardSubstitution(L, b, y, n);
    std::cout << "Vector Y:" << std::endl;
    for (std::size_t i = 0; i < n; i++)
    {
        std::cout << "Y[" << i << "] = " << y[i] << std::endl;
    }

    //Ux = y dla x
    double* x = new double[n];
    backwardSubstitution(U, y, x, n);
    std::cout << "Solution:" << std::endl;
    for (std::size_t i = 0; i < n; i++)
    {
        std::cout << "X[" << i << "] = " << x[i] << std::endl;
    }

    for (std::size_t i = 0; i < n; i++)
    {
        delete[] A[i];
        delete[] L[i];
        delete[] U[i];
    }

    delete[] A;
    delete[] L;
    delete[] U;
    delete[] b;
    delete[] y;
    delete[] x;

    return 0;
}
