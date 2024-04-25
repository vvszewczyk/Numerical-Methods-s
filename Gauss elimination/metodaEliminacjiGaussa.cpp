#include <iostream>
#include <fstream>
#include <cmath>


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

//postepowanie proste
double** gaussElimination(double** matrix, int size) 
{
    for (std::size_t i = 0; i < size; i++)
    {
        if (fabs(matrix[i][i]) < 1e-6) 
        {
            std::cerr << "0 on the diagonal" << std::endl;
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


//postepowanie odwrotne
double* solution(double** matrix, int size, double* results)
{
    for (int i = size - 1; i >= 0; i--)
    {
        results[i] = matrix[i][size];
        for (int k = i + 1; k < size; k++)
        {
            double bufor = matrix[i][k] * results[k];
            results[i] -= bufor;
        }
        results[i] /= matrix[i][i];
    }
    return results;
}


int main() 
{
    int size = 0;
    double** matrix = new double*[size];
    double* solutions = new double[size];

    matrix = readData("RURL_dane2.txt", size);
    
    std::cout << "Before:" << std::endl;
    showMatrix(matrix, size);
    matrix = gaussElimination(matrix, size);

    std::cout << "After:" << std::endl;
    showMatrix(matrix, size);
    solution(matrix, size, solutions);

    std::cout << "Solution:" << std::endl;
    for (std::size_t i = 0; i < size; i++)
    {
        std::cout << "x" << i << " = " << solutions[i] << std::endl;
    }

    return 0;
}
