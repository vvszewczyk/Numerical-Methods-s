#include <iostream>
#include <cmath>


double f1(double x) 
{
    return std::cos(x * x * x - 2 * x);
}

double f2(double x) 
{
    return exp(x) - 3;
}

double f3(double x) 
{
    return x * x * x - 6 * x * x + 11 * x - 6;
}


void bisection(double a, double b, double epsilon, double(*f)(double))
{
    double x0 = (a + b) / 2, fx0 = f(x0), fa, fb;
    std::size_t iteration = 0;

    std::cout << "Iteration\t a\t b\t f(a)\t f(b)\t x0\t f(x0)\t f(a)*f(x0)\n";

        while (std::fabs(fx0) >= epsilon)
        {
            fa = f(a);
            fb = f(b);

            if (fa * fb < 0)
            {
                x0 = (a + b) / 2.0;
                fx0 = f(x0);

                std::cout << iteration << "\t" << a << "\t" << b << "\t" << fa << "\t" << fb << "\t" << x0 << "\t" << fx0 << "\t" << fa * fx0 << "\n";

                if (fa * fx0 < 0)
                {
                    b = x0;
                }
                else
                {
                    a = x0;
                }

                iteration++;
            }
            else
            {
                std::cout << "f(a) * f(b) >= 0 on [" << a << ", " << b << "]\n";
                return;
            }
        }

    std::cout << "x0: " << x0 << ", epsilon: " << epsilon << "\n";
}

void falseLine(double a, double b, double epsilon, double(*f)(double)) 
{
    double x1, fx1, fa, fb;
    std::size_t iteration = 0;

    std::cout << "Iteration\t a\t b\t f(a)\t f(b)\t x1\t f(x1)\t f(a)*f(x1)\n";

    fa = f(a);
    fb = f(b);
    x1 = a - (((fa * (b - a)) / (fb - fa)));
    fx1 = f(x1);

    std::cout << iteration << "\t" << a << "\t" << b << "\t" << fa << "\t" << fb << "\t" << x1 << "\t" << fx1 << "\t" << fa * fx1 << "\n";

        while (std::fabs(fx1) >= epsilon)
        {
            if (fa * fb < 0)
            {
                if (fx1 * fa < 0)
                {
                    b = x1;
                    fb = fx1;
                }
                else
                {
                    a = x1;
                    fa = fx1;
                }

                x1 = a - (((fa * (b - a)) / (fb - fa)));
                fx1 = f(x1);

                iteration++;
                std::cout << iteration << "\t\t" << a << "\t" << b << "\t" << fa << "\t" << fb << "\t" << x1 << "\t" << fx1 << "\n";
            }
            else
            {
                std::cout << "f(a) * f(b) >= 0 on [" << a << ", " << b << "]\n";
                return;
            }
        }
    
    std::cout << "x0: " << x1 << ", epsilon: " << epsilon << "\n";
}

int main() 
{
    double epsilon = 0.01;

    std::cout << "f(x) = cos(x^3 - 2x) = 0\n";
    bisection(0, 2.0, epsilon, f1);
    falseLine(0, 2.0, epsilon, f1);

    std::cout << "\nf(x) = e^x - 3 = 0\n";
    bisection(0, 2.0, epsilon, f2);
    falseLine(0, 2.0, epsilon, f2);

    std::cout << "\nf(x) = x^3 - 6x^2 + 11x - 6 = 0\n";
    bisection(0, 1.5, epsilon, f3);
    falseLine(0, 1.5, epsilon, f3);

    return 0;
}
