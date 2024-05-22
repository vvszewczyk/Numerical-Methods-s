#include <iostream>
#include <fstream>
#include <cmath>


class Point 
{
    double x;
    double y;

  public:
    Point(double x, double y) : x(x), y(y) {}

    double getX()
    {
        return this->x;
    }

    double getY()
    {
        return this->y;
    }
};

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
        for (std::size_t k = i + 1; k < size; k++)
        {
            double bufor = matrix[i][k] * solutions[k];
            solutions[i] -= bufor;
        }
        solutions[i] /= matrix[i][i];
    }
    return solutions;
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

double weight(double x)
{
    return 1.0;
}

double* polynomialApproximation(Point** points, int n, int degree)
{
    int numEquations = degree + 1;
    double** g = new double* [numEquations];
    for (std::size_t i = 0; i < numEquations; i++)
    {
        g[i] = new double[numEquations + 1]();
    }

    for (std::size_t i = 0; i < numEquations; i++)
    {

        // g
        for (std::size_t j = 0; j < numEquations; j++)
        {
            for (std::size_t k = 0; k < n; k++)
            {
                g[i][j] += pow(points[k]->getX(), i) * pow(points[k]->getX(), j) * weight(points[k]->getX()); //wzór 7
            }
        }


        // F
        for (std::size_t k = 0; k < n; k++)
        {
            g[i][numEquations] += pow(points[k]->getX(), i)* points[k]->getY() * weight(points[k]->getX()); //wzór 8
        }
    }

    std::cout << "Matrix (g|F):" << std::endl;
    showMatrix(g, numEquations);

    double** gaussed = gaussEliminationWithPartialPivoting(g, numEquations);
    std::cout << "\nMatrix (g|F) after simple procedure:" << std::endl;
    showMatrix(gaussed, numEquations);

    double* result = new double[numEquations];

    result = solution(gaussed, numEquations, result);

    for (std::size_t i = 0; i < numEquations; i++)
    {
        delete[] g[i];
    }
    delete[] g;

    return result;
}

Point** readData(std::string filename, int& n)
{
    std::ifstream file(filename);
    if (!file.is_open()) 
    {
        std::cerr << "Cannot open file." << std::endl;
        return nullptr;
    }

    file >> n;
    Point** points = new Point * [n];

    for (std::size_t i = 0; i < n; i++)
    {
        double x, y;
        file >> x >> y;
        points[i] = new Point(x, y);
    }


    file.close();

    return points;
}

int main() 
{
    int n = 0;
    Point** points = readData("points.txt", n);

    int degree = 2;

    double* result = polynomialApproximation(points, n, degree);

    std::cout << "\nNumber of nodes: " << n << std::endl;

    std::cout << "\nCoefficients (solutions): ";
    for (std::size_t i = 0; i <= degree; i++)
    {
        std::cout << result[i] << " ";
    }
    std::cout << std::endl;

    // y= a0 ​+ a1​x +a2​x^2 + a3​x^3 + … + an​x^n
    std::cout << "\nPoints and calculated values:" << std::endl;
    for (std::size_t i = 0; i < n; i++)
    {
        double val = 0;
        for (std::size_t j = 0; j <= degree; j++)
        {
            val += result[j] * pow(points[i]->getX(), j);
        }
        std::cout << "(" << points[i]->getX() << ", " << points[i]->getY() << ") -> " << val << std::endl;

    }

    for (std::size_t i = 0; i < n; i++)
    {
        delete points[i];
    }
    delete[] result;

    return 0;
}
