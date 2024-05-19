#include <iostream>
#include <cmath>


double rectangularIntegral(double (*f)(double), double a, double b, int n) 
{
    double s = (b - a) / n;

    double sum = 0.0;
    for (int i = 0; i < n; i++) 
    {
        double xi = a + (i * s);
        double xs = xi + (s / 2);
        sum += f(xs) * s;
    }
    return sum;
}

double trapezoidalIntegral(double (*f)(double), double a, double b, int n) 
{
    double s = (b - a) / n;
    double sum = 0;

    for (int i = 0; i < n; i++) 
    {
        double part1 = ((i + 1) * s) - (i * s);
        double part2 = f(a + (i * s)) + f(a + ((i + 1) * s));
        sum += (part1 / 2) * part2;
    }

    return sum;
}



double simpsonIntegral(double(*f)(double), double a, double b, int n) 
{
    if (n % 2 == 1)
    {
        return 0;
    }
    double s = (b - a) / n;
    double sum = 0.0;

    for (int i = 0; i < n; i += 2)
    {
        double x_i = a + i * s;
        double x_ip1 = x_i + s;
        double x_ip2 = x_i + 2 * s;
        sum += (x_ip2 - x_i) / 6.0 * (f(x_i) + 4.0 * f((x_i + x_ip2) / 2.0) + f(x_ip2));
    }

    return sum;
}


double sinx(double x)
{
    return sin(x);
}

double xx_2x_5(double x) 
{
    return x * x + 2 * x + 5;
}

double expx(double x) 
{
    return exp(x);
}

int main() 
{


    for (int i = 2; i <= 1024; i *= 2)
    {
        double wynikProstokatow = rectangularIntegral(sinx, 0.5, 2.5, i);
        double wynikTrapezow = trapezoidalIntegral(sinx, 0.5, 2.5, i);
        double wynikSimpsona = simpsonIntegral(sinx, 0.5, 2.5, i);

        double wynikProstokatow2 = rectangularIntegral(xx_2x_5, 0.5, 5, i);
        double wynikTrapezow2 = trapezoidalIntegral(xx_2x_5, 0.5, 5, i);
        double wynikSimpsona2 = simpsonIntegral(xx_2x_5, 0.5, 5, i);

        double wynikProstokatow3 = rectangularIntegral(expx, 0.5, 5, i);
        double wynikTrapezow3 = trapezoidalIntegral(expx, 0.5, 5, i);
        double wynikSimpsona3 = simpsonIntegral(expx, 0.5, 5, i);

        std::cout << "\n\nNumber of range: " << i << std::endl;

        std::cout << "Integral sin(x) in <0.5, 2.5>" << std::endl;
        std::cout << "Rectangular: " << wynikProstokatow << std::endl;
        std::cout << "Trapezoid: " << wynikTrapezow << std::endl;
        std::cout << "Simpson: " << wynikSimpsona << std::endl;
        std::cout << std::endl;

        std::cout << "Integral x^2+2x+5 in <0.5, 5>" << std::endl;
        std::cout << "Rectangular: " << wynikProstokatow2 << std::endl;
        std::cout << "Metoda trapezów: " << wynikTrapezow2 << std::endl;
        std::cout << "Metoda Simpsona: " << wynikSimpsona2 << std::endl;
        std::cout << std::endl;

        std::cout << "Integral e^(x) in <0.5, 5>" << std::endl;
        std::cout << "Rectangular: " << wynikProstokatow3 << std::endl;
        std::cout << "Trapezoid: " << wynikTrapezow3 << std::endl;
        std::cout << "Metoda Simpsona: " << wynikSimpsona3 << std::endl;
        std::cout << std::endl;
    }

    return 0;
}
