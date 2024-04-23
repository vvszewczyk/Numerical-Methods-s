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

Point* readData(std::string& path , int &size)
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
    for(std::size_t i=0; i<size; i++)
    {
        file >> value;
        arr[i].setX(value);
        file >> value;
        arr[i].setY(value);
    }
    file.close();
    return arr;
}

void showData(Point* arr, int size)
{
    for (std::size_t i = 0; i < size; i++)
    {
        std::cout << "X: " << arr[i].getX() << " Y: "<<arr[i].getY() << std::endl;
    }
    std::cout<<std::endl;
}

void lagrangePolynomial(Point* points, int size) 
{
    double x;
    std::cout << "Enter X: ";
    std::cin >> x;

    double y = 0.0;

    for (std::size_t i = 0; i < size; i++)
    {
        double f_xi = 1.0;
        for (std::size_t j = 0; j < size; j++) 
        {
            if (i != j) 
            {
                f_xi *= (x - points[j].getX()) / (points[i].getX() - points[j].getX()); //(x-xj)/(xi-xj)
            }
        }
        y += f_xi * points[i].getY();
    }
    std::cout << "\nX: " << x << "\tY: " << y << std::endl;
}

int main()
{
    int size=0;
    
    //Exercise 1
    std::cout << "MN-1.txt" << std::endl;
    std::string file1 = "MN-1.txt";
    Point* array1 = readData(file1, size);
    showData(array1, size);
    lagrangePolynomial(array1, size);

    std::cout << std::endl;

    //Exercise 2
    std::cout << "MN-2.txt" << std::endl;
    std::string file2 = "MN-2.txt";
    Point* array2 = readData(file2, size);
    showData(array2, size);
    lagrangePolynomial(array2, size);
    


}