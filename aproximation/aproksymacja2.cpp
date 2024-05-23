#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>


class Point 
{
public:
    double x, y;

    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

int factorial(int n) 
{
    if (n == 0) 
    {
        return 1;
    }
    int result = 1;
    for (std::size_t i = 2; i <= n; i++) 
    {
        result *= i;
    }
    return result;
}

double newton(int n, int k) 
{
    if (k > n) 
    {
        return 0;
    }
    if (k == 0 || k == n) 
    {
        return 1;
    }
    return factorial(n) / (factorial(k) * factorial(n - k));
}

double X(double x, int n)
{
    if (n == 0) 
    {
        return 1;
    }
    double result = 1;
    for (std::size_t j = 0; j < n; j++)
    {
        result *= (x - j);
    }
    return result;
}

double F(int k, int n, double q) 
{
    double sum = 0;
    for (std::size_t s = 0; s <= k; s++)
    {
        sum += pow(-1, s) * newton(k, s) * newton(k + s, s) * (X(q, s) / X(n, s));
    }
    return sum;
}

void approximation(Point* points, int n, int degree)
{
    double h = abs(points[1].x - points[0].x);
    double* cks = new double[degree + 1];
    double* sks = new double[degree + 1];

    std::cout << "Number of nodes: " << n + 1 << std::endl;
    std::cout << "\nNodes and values:" << std::endl;
    for (std::size_t i = 0; i <= n; i++)
    {
        std::cout << "x: " << points[i].x << "   y: " << points[i].y << std::endl;
    }

    std::cout << "\nCoefficients ck, sk:" << std::endl;
    for (std::size_t k = 0; k <= degree; k++)
    {
        double ck = 0;
        double sk = 0;
        for (std::size_t i = 0; i <= n; i++)
        {
            double q = (points[i].x - points[0].x) / h;
            double FValue = F(k, n, q);
            sk += pow(FValue, 2);
            ck += points[i].y * FValue;
        }
        cks[k] = ck;
        sks[k] = sk;
        std::cout << "ck: " << ck << "\tsk: " << sk << std::endl;
    }

    std::cout << "\nYm(x):" << std::endl;
    for (std::size_t i = 0; i <= n; i++)
    {
        double ym = 0;
        for (std::size_t k = 0; k <= degree; k++)
        {
            double q = (points[i].x - points[0].x) / h;
            if (sks[k] != 0)
            {
                ym += (cks[k] / sks[k]) * F(k, n, q);
            }
        }
        std::cout << "x: " << points[i].x << "   ym(x): " << ym << std::endl;
    }

    Point additionalPoints[2] = { {2.5, 0}, {6.5, 0}};
    for (std::size_t i = 0; i < 2; i++)
    {
        double ym = 0;
        for (std::size_t k = 0; k <= degree; k++)
        {
            double q = (additionalPoints[i].x - points[0].x) / h;
            if (sks[k] != 0)
            {
                ym += (cks[k] / sks[k]) * F(k, n, q);
            }
        }
        std::cout << "x: " << additionalPoints[i].x << "   ym(x): " << ym << std::endl;
    }

    delete[] cks;
    delete[] sks;
}

Point* readData(const std::string& filename, int& n) 
{
    std::ifstream file(filename);
    if (!file.is_open()) 
    {
        std::cerr << "Cannot open file." << std::endl;
        return nullptr;
    }

    file >> n;
    Point* points = new Point[n];

    for (std::size_t i = 0; i < n; i++)
    {
        file >> points[i].x >> points[i].y;
    }

    file.close();
    return points;
}

int main() 
{
    int n = 0;
    Point* points = readData("points.txt", n);
    int degree = 7;
    approximation(points, n - 1, degree);
    delete[] points;
    return 0;
}
