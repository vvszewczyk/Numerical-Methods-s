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

void splitMatrices(double** A, double **&Drev, double**& LandU, int size)
{
    LandU = new double* [size];
    Drev = new double* [size];

    for (std::size_t i = 0; i < size; i++)
    {
        LandU[i] = new double[size]();
        Drev[i] = new double[size]();

        if (A[i][i] != 0)
        {
            Drev[i][i] = (1.0 / A[i][i]);
        }
        else
        {
            return;
        }

        for (std::size_t j = 0; j < size; j++)
        {
            LandU[i][j] = A[i][j];
        }
        LandU[i][i] = 0;
    }
}

void multiply(double** matrix, double* vector, double* result, int size) 
{
    for (std::size_t i = 0; i < size; i++)
    {
        result[i] = 0;
        for (std::size_t j = 0; j < size; j++)
        {
            result[i] += matrix[i][j] * vector[j];
        }
    }
}

bool isDominant(double** A, int size)
{
    for (std::size_t i = 0; i < size; i++)
    {
        double sum = 0;
        for (std::size_t j = 0; j < size; j++)
        {
            if (i != j)
            {
                sum += fabs(A[i][j]);
            }
        }
        if (fabs(A[i][i]) < sum)
        {
            return false;
        }
    }
    return true;
}

void jacobiSolve(double** Drev, double** LU, double* b, double* x, int size, int maxIterations) 
{
    double* currX = new double[size]();
    double* nextX = new double[size];
    double* LUxX = new double[size];

    for (std::size_t i = 0; i < maxIterations; i++)
    {
        multiply(LU, currX, LUxX, size);
        for (std::size_t j = 0; j < size; j++)
        {
            nextX[j] = -Drev[j][j] * LUxX[j] + Drev[j][j] * b[j];
        }

        for (std::size_t j = 0; j < size; j++)
        {
            currX[j] = nextX[j];
        }
    }

    for (std::size_t i = 0; i < size; i++)
    {
        x[i] = currX[i];
    }

    delete[] currX;
    delete[] nextX;
    delete[] LUxX;
}

void jacobiSolve2(double** Drev, double** LU, double* b, double* x, int size, int& maxIterations, double epsilon)
{
    double* currX = new double[size]();
    double* nextX = new double[size];
    double* LUxX = new double[size];
    double* deltaX = new double[size];

    std::size_t iteration;
    bool converged;

    for (iteration = 0; iteration < maxIterations; iteration++)
    {
        multiply(LU, currX, LUxX, size);
        converged = true;

        for (std::size_t i = 0; i < size; i++)
        {
            nextX[i] = -Drev[i][i] * LUxX[i] + Drev[i][i] * b[i];
            deltaX[i] = fabs(nextX[i] - currX[i]);
            if (fabs(nextX[i] - currX[i]) >= epsilon)
            {
                converged = false;
            }
        }

        for (std::size_t i = 0; i < size; i++)
        {
            currX[i] = nextX[i];
        }


        if (converged)
        {
            iteration++;
            break;
        }
    }

    for (std::size_t i = 0; i < size; i++)
    {
        std::cout << "delta x[" << i << "] = " << deltaX[i] << std::endl;
        x[i] = currX[i];
    }


    std::cout << "Epsilon: " << epsilon << std::endl;
    std::cout << "Iterations: " << iteration << std::endl;
    maxIterations = iteration;

    delete[] currX;
    delete[] nextX;
    delete[] LUxX;
    delete[] deltaX;
}

double** gaussEliminationWithPartialPivoting(double** matrix, int size)
{
    for (std::size_t i = 0; i < size; i++)
    {
        double maxElement = fabs(matrix[i][i]);
        std::size_t maxRow = i;
        for (std::size_t j = i + 1; j < size; j++)
        {
            if (fabs(matrix[j][i]) > maxElement)
            {
                maxElement = fabs(matrix[j][i]);
                maxRow = j;
            }
        }

        if (maxRow != i)
        {
            double* tempRow = matrix[i];
            matrix[i] = matrix[maxRow];
            matrix[maxRow] = tempRow;
        }

        if (fabs(matrix[i][i]) < 1e-6)
        {
            std::cerr << "0 is still on the diagonal." << std::endl;
            return nullptr;
        }

        for (std::size_t j = i + 1; j < size; j++)
        {
            double multiplier = matrix[j][i] / matrix[i][i];
            for (std::size_t k = i; k <= size; k++)
            {
                double bufor = matrix[i][k] * multiplier;
                matrix[j][k] -= bufor;
            }
        }
    }

    return matrix;
}

double* solution(double** matrix, int size, double* solutions)
{
    for (int i = size - 1; i >= 0; i--)
    {
        solutions[i] = matrix[i][size];
        for (int k = i + 1; k < size; k++)
        {
            double bufor = matrix[i][k] * solutions[k];
            solutions[i] -= bufor;
        }
        solutions[i] /= matrix[i][i];
    }
    return solutions;
}


int main() 
{
    int size = 0;
    double** A = readData("RURL_dane4.txt", size);
    double** Acp = readData("RURL_dane4.txt", size);

    std::cout << "Matrix A|b:\n";
    showMatrix(A, size);

    std::cout << (isDominant(A, size) ? "Matrix is diagonally dominant.\n" : "Matrix is not diagonally dominant.\n");

    double ** Drev, ** LU;
    splitMatrices(A, Drev, LU, size);

    double* b = new double[size];
    for (std::size_t i = 0; i < size; i++) 
    {
        b[i] = A[i][size];
    }

    int maxIterations;
    std::cout << "Enter number of iterations: ";
    std::cin >> maxIterations;

    double* x = new double[size];
    for (std::size_t i = 0; i < size; i++) 
    {
        x[i] = 0;
    }

    //jacobiSolve(Drev, LU, b, x, size, maxIterations);

    double epsilon1 = 0.001, epsilon2 = 0.000001;
    jacobiSolve2(Drev, LU, b, x, size, maxIterations, epsilon2);

    std::cout << "Matrix L+U:\n";
    showMatrix2(LU, size);
    std::cout << "Matrix D^-1:\n";
    showMatrix2(Drev, size);


    std::cout << "Jacobi solution for "<<maxIterations<<" iterations: \n";
    for (int i = 0; i < size; i++) 
    {
        std::cout << "x[" << i << "] = " << x[i] << std::endl;
    }


    double* solutions = new double[size];
    solution(gaussEliminationWithPartialPivoting(Acp, size), size, solutions);
    std::cout << "\nGauss solution:" << std::endl;
    for (std::size_t i = 0; i < size; i++)
    {
        std::cout << "x[" << i << "] = " << solutions[i] << std::endl;
    }

    std::cout << "\nAbsolute error:" << std::endl;
    for (std::size_t i = 0; i < size; i++)
    {
        std::cout << "Δx[" << i << "] = " << fabs(solutions[i] - x[i]) << std::endl;
    }



    for (int i = 0; i < size; i++) 
    {
        delete[] A[i];
        delete[] Drev[i];
        delete[] LU[i];
    }
    delete[] A;
    delete[] Drev;
    delete[] LU;
    delete[] b;
    delete[] x;
    delete[] solutions;

    return 0;
}