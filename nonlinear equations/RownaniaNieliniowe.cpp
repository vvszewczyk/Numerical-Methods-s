#include <iostream>
#include <cmath>


double f1(double x) 
{
    return (-1 * x * x * x) + (10 * x) + 5;
}

double f1_prime(double x) 
{
    return (-3 * x * x) + 10;
}

double f2(double x)
{
    return x * x * x * x + 5 * x * x;
}

double f2_prime(double x)
{
    return 4 * x * x * x + 10 * x;
}

double f3(double x)
{
    return -x * x * x * x * x * x;
}

double f3_prime(double x)
{
    return -6 * x * x * x * x * x;
}

void tangent(double x0, int iterations, double(*f)(double), double(*f_prime)(double))
{
    std::cout << "Tangent method" << std::endl;
    for (std::size_t i = 0; i < iterations; i++)
    {
        double fx = f(x0);
        double fpx = f_prime(x0);
        if (fpx == 0) 
        {
            std::cerr << "Cannot divide by derivative that is equal 0." << std::endl;
            return;
        }
        double x1 = x0 - (fx / fpx);
        std::cout << "Iteration " << i + 1 << ": x = " << x1 << ", f(x) = " << f(x1) << std::endl;
        x0 = x1;
    }
}

void secent(double x1, int iterations, double(*f)(double))
{
    
    double x0 = x1 - 0.1;
    std::cout << "Secent method" << std::endl;
    for (std::size_t i = 0; i < iterations; i++)
    {
        double fx0 = f1(x0);
        double fx1 = f1(x1);
        double x2 = x1 - (fx1 * ((x1 - x0) / (fx1 - fx0)));
        std::cout << "Iteration " << i + 1 << ": x = " << x2 << ", f(x) = " << f(x2) << std::endl;
        x0 = x1;
        x1 = x2;
    }
}

int main() 
{
    double x0;
    int iterations;

    std::cout << "Enter start point x0: ";
    std::cin >> x0;

    std::cout << "Enter number of iterations: ";
    std::cin >> iterations;

    std::cout << "-x^3 + 10x + 5" << std::endl;
    tangent(x0, iterations, f1, f1_prime);
    std::cout << std::endl;
    secent(x0, iterations, f1);

    std::cout << "\nx^4 + 5x^2" << std::endl;
    tangent(x0, 10, f2, f2_prime);
    std::cout << std::endl;
    secent(x0, 10, f2);

    std::cout << "\n-x^6" << std::endl;
    tangent(x0, 12, f3, f3_prime);
    std::cout << std::endl;
    secent(x0, 12, f3);
    return 0;
}
