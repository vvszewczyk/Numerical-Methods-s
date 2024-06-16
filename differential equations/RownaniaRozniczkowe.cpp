#include <iostream>
#include <cmath>

double xx_plus_y(double x, double y) 
{
    return x * x + y;
}

double x_plus_y(double x, double y) 
{
    return x + y;
}


double euler(double x0, double x1, double y0, int N, double (*f)(double, double)) 
{
    double h = (x1 - x0) / N;
    for (std::size_t i = 0; i < N; i++)
    {
        y0 += h * f(x0, y0);
        x0 += h;
    }
    return y0;
}

double RK2(double x0, double x1, double y0, int N, double (*f)(double, double))
{
    double h = (x1 - x0) / N;
    for (std::size_t i = 0; i < N; i++)
    {
        double k1 = f(x0, y0);
        double k2 = f(x0 + h, y0 + h * k1);
        y0 += h / 2 * (k1 + k2);
        x0 += h;
    }
    return y0;
}


double RK4(double x0, double x1, double y0, int N, double (*f)(double, double)) 
{
    double h = (x1 - x0) / N;
    for (std::size_t i = 0; i < N; i++)
    {
        double k1 = f(x0, y0);
        double k2 = f(x0 + h / 2, y0 + h * k1 / 2);
        double k3 = f(x0 + h / 2, y0 + h * k2 / 2);
        double k4 = f(x0 + h, y0 + h * k3);
        y0 += h / 6 * (k1 + 2 * k2 + 2 * k3 + k4);
        x0 += h;
    }
    return y0;
}

int main()
{
    double x0 = 0;
    double x1 = 1;
    double y0 = 0.1;
    int N = 10;
    double (*f1)(double, double) = xx_plus_y;
    double (*f2)(double, double) = x_plus_y;

    std::cout << "Warunek początkowy y(0) = " << y0 << std::endl;
    std::cout << "Punkt końcowy x = " << x1 << std::endl;
    std::cout << "Krok obliczeń h = " << (x1 - x0) / N << std::endl;
    std::cout << "Rozwiązanie metodą Eulera: " << euler(x0, x1, y0, N, f1) << std::endl;
    std::cout << "Rozwiązanie metodą RK2: " << RK2(x0, x1, y0, N, f1) << std::endl;
    std::cout << "Rozwiązanie metodą RK4: " << RK4(x0, x1, y0, N, f1) << std::endl;

    std::cout << std::endl;

    std::cout << "Warunek początkowy y(0) = " << y0 << std::endl;
    std::cout << "Punkt końcowy x = " << x1 << std::endl;
    std::cout << "Krok obliczeń h = " << (x1 - x0) / N << std::endl;
    std::cout << "Rozwiązanie metodą Eulera: " << euler(x0, x1, y0, N, f2) << std::endl;
    std::cout << "Rozwiązanie metodą RK2: " << RK2(x0, x1, y0, N, f2) << std::endl;
    std::cout << "Rozwiązanie metodą RK4: " << RK4(x0, x1, y0, N, f2) << std::endl;

    return 0;
}