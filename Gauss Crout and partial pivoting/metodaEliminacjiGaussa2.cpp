#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

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

//postepowanie proste
double** gaussCroutElimination(double** matrix, int size, std::vector<int>& columnIndices)
{
    for (int i = 0; i < size; i++) 
    {
        columnIndices[i] = i;
    }

    for (std::size_t i = 0; i < size; i++) 
    {
        double maxElement = fabs(matrix[i][i]);
        std::size_t maxColumn = i;
        for (int j = i + 1; j < size; j++) 
        {
            if (fabs(matrix[i][j]) > maxElement) 
            {
                maxElement = fabs(matrix[i][j]);
                maxColumn = j;
            }
        }

        if (maxColumn != i) 
        {
            for (int k = 0; k < size; k++)
            {
                double temp = matrix[k][i];
                matrix[k][i] = matrix[k][maxColumn];
                matrix[k][maxColumn] = temp;
            }

            int tempIndex = columnIndices[i];
            columnIndices[i] = columnIndices[maxColumn];
            columnIndices[maxColumn] = tempIndex;
        }

        for (int j = i + 1; j < size; j++) 
        {
            double multiplier = matrix[j][i] / matrix[i][i];
            for (int k = i; k <= size; k++) 
            {
                double bufor = matrix[i][k] * multiplier;
                matrix[j][k] -= bufor;
            }
        }
    }

    return matrix;
}

//postepowanie odwrotne
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
    double** matrix = readData("RURL_dane2.txt", size);
    double* solutions = new double[size];
    std::cout << "Before:" << std::endl;
    showMatrix(matrix, size);
    matrix = gaussEliminationWithPartialPivoting(matrix, size);
    std::cout << "After:" << std::endl;
    showMatrix(matrix, size);
    solution(matrix, size, solutions);
    std::cout << "Solution:" << std::endl;
    for (std::size_t i = 0; i < size; i++)
    {
        std::cout << "x" << i << " = " << solutions[i] << std::endl;
    }

    int size2 = 0;
    double** matrix2 = readData("RURL_dane2.txt", size2);
    double* solutions2 = new double[size2];
    std::cout << "Before:" << std::endl;
    showMatrix(matrix2, size2);
    std::vector<int> columnIndices(size2);
    matrix2 = gaussCroutElimination(matrix2, size2, columnIndices);
    std::cout << "After:" << std::endl;
    showMatrix(matrix2, size2);
    solution(matrix2, size2, solutions2);
    std::cout << "\nIndices: "<<std::endl;
    std::vector<double> orderedSolutions(size2);
    for (std::size_t i = 0; i < size2; i++) 
    {
        std::cout << columnIndices[i] << " ";
        orderedSolutions[columnIndices[i]] = solutions2[i];
    }
    std::cout << "\nSolution:" << std::endl;
    for (std::size_t i = 0; i < size2; i++) 
    {
        std::cout << "x" << i << " = " << orderedSolutions[i] << std::endl;
    }

   
    return 0;
}
