#include <iostream>
#include <fstream>

class Point
{
private:
    double x;
    double y;
public:
    double getX()
    {
        return this->x;
    }
    double getY()
    {
        return this->y;
    }
    void setX(int x)
    {
        this->x = x;
    }
    void setY(int y)
    {
        this->y = y;
    }
};

Point* readData(std::string& path, int& size)
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        std::cerr << "no file" << std::endl;
        return nullptr;
    }

    file >> size;
    int value;
    Point* arr = new Point[size];
    for (std::size_t i = 0; i < size; i++)
    {
        file >> value;
        arr[i].setX(value);
        file >> value;
        arr[i].setY(value);
    }
    file.close();
    return arr;
}

void showData(Point* arr, int& size)
{
    for (std::size_t i = 0; i < size; i++)
    {
        std::cout << "X: " << arr[i].getX() << " Y: " << arr[i].getY() << std::endl;
    }
    std::cout << std::endl;
}

void newtonPolynomial(Point* arr, int& size)
{
    double x;
    double y = arr[0].getY();
    std::cout << "Enter X: ";
    std::cin >> x;

    double* b = new double[size];

    for (std::size_t i = 0; i < size; i++)
    {
        b[i] = arr[i].getY();
    }

    for (std::size_t i = 1; i < size; i++)
    {
        for (std::size_t j = 0; j < i; j++)
        {
            b[i] = (b[i] - b[j]) / (arr[i].getX() - arr[j].getX()); // (bi-bj)/(xi-xj)
        }
    }

    for (std::size_t i = 0; i < size; i++)
    {
        std::cout << b[i] << ' ';
    }

    for (std::size_t i = 1; i < size; i++)
    {
        double product = 1.0;
        for (std::size_t j = 0; j < i; j++)
        {
            double difference = x - arr[j].getX(); //(x-xj)
            product *= difference;
        }
        y += b[i] * product;
    }


    std::cout << "\nX: " << x << " Y: " << y << std::endl;

    delete[] b;
}

int main()
{
    int size = 0;
    std::string name1 = "MN-2-p1.txt";
    Point* arr=readData(name1, size);
    showData(arr, size);
    newtonPolynomial(arr, size);
    std::cout << std::endl;
    newtonPolynomial(arr, size);

    std::cout << std::endl;

    std::string name2 = "MN-2-p2.txt";
    Point* arr2 = readData(name2, size);
    showData(arr2, size);
    newtonPolynomial(arr2, size);
    std::cout << std::endl;
    newtonPolynomial(arr2, size);
}