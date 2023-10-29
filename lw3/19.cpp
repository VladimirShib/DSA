/*
Имеется сеть автомобильных дорог. Для каждой дороги известна
максимальная масса груза, которую можно провезти по этой дороге.
С помощью алгоритма Дейкстры определить максимальный груз,
который можно провезти между двумя указанными городам.

Владимир Шибаков.
C++
Visual Studio Code
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

constexpr int MAX_NUM = 1000;

struct City
{
    int number;
    std::string name;
};

struct Mark
{
    int tempMark;
    int finalMark;
    int from;
};

void getCities(std::vector<City>& cities)
{
    std::ifstream file;
    file.open("cities.txt");

    if (file.is_open())
    {
        int number;
        std::string name;

        while (file >> number >> name)
        {
            cities.push_back({number, name});
        }
        file.close();
    }
    else
    {
        std::cout << "Couldn't open the file cities.txt\n";
    }
}

void fillMatrix(std::vector<std::vector<int>>& matrix, const int& size)
{
    std::ifstream file;
    file.open("roads.txt");

    if (file.is_open())
    {
        int from, to, weight;

        while (file >> from >> to >> weight)
        {
            matrix[from - 1][to - 1] = weight;
        }
        file.close();
    }
    else
    {
        std::cout << "Couldn't open the file roads.txt\n";
    }
}

void findAndPrintPath(std::vector<std::vector<int>>& matrix, const int& size, std::vector<City>& cities, const int& from, const int& to)
{
    int lastFinalMark = from - 1;
    bool pathExists = true;
    std::vector<Mark> marks;
    for (int i = 0; i < size; ++i)
    {
        Mark mark;
        mark.tempMark = -1;
        mark.finalMark = (i == lastFinalMark ? MAX_NUM : -1);
        mark.from = -1;
        marks.push_back(mark);
    }

    int newTemp, newFinal;
    while (pathExists && marks[to - 1].finalMark == -1)
    {
        pathExists = false;
        for (int i = lastFinalMark, j = 0; j < size; ++j)
        {
            if (matrix[i][j] != 0)
            {
                newTemp = std::max(std::min(marks[i].finalMark, matrix[i][j]), marks[j].tempMark);
                if (newTemp > marks[j].tempMark)
                {
                    marks[j].tempMark = newTemp;
                    marks[j].from = i;
                }
            }
        }

        for (int i = 0; i < size; ++i)
        {
            if (marks[i].tempMark > -1)
            {
                pathExists = true;
            }
        }

        if (pathExists)
        {
            newFinal = lastFinalMark;
            for (int i = 0; i < size; ++i)
            {
                if (marks[i].tempMark > marks[newFinal].tempMark)
                {
                    newFinal = i;
                }
            }
            marks[newFinal].finalMark = marks[newFinal].tempMark;
            marks[newFinal].tempMark = -1;
            lastFinalMark = newFinal;
        }
    }

    if (!pathExists)
    {
        std::cout << "-----------------------------------------------------------\n";
        std::cout << "No path between " << cities[from - 1].name << " and " << cities[to - 1].name << "\n";
        std::cout << "-----------------------------------------------------------\n";
    }
    else
    {
        int pointer = lastFinalMark;
        std::vector<int> path;

        while (pointer != -1)
        {
            path.push_back(pointer);
            pointer = marks[pointer].from;
        }

        std::cout << "-----------------------------------------------------------\n";
        std::cout << "Maximum weight that can be transported from " << cities[from - 1].name
        << " to " << cities[to - 1].name << " is " << marks[to - 1].finalMark << "\n";
        std::cout << "And the path is following: \n";
        while (path.size() != 0)
        {
            std::cout << cities[path.back()].number << "." << cities[path.back()].name << "  ";
            path.pop_back();
        }
        std::cout << "\n-----------------------------------------------------------\n";
    }
}

int main()
{
    std::vector<City> cities;
    getCities(cities);

    int matrixSize;
    matrixSize = cities.size();

    std::vector<std::vector<int>> matrix(matrixSize, std::vector<int>(matrixSize));
    fillMatrix(matrix, matrixSize);

    char answer;
    int from, to;
    do
    {
        std::cout << "\n1. Find max weight and the path.\n";
        std::cout << "2. Exit.\n\n";
        std::cout << "Your choice: ";
        std::cin >> answer;

        if (answer == '1')
        {
            std::cout << "\nEnter departure point and arrival point: ";
            std::cin >> from >> to;
            findAndPrintPath(matrix, matrixSize, cities, from, to);
        }

        if (answer < '1' || answer > '2')
        {
            std::cout << "\nInvalid command.\n";
        }
    }
    while (answer != '2');
    std::cout << "\nProgram stopped.\n";
}