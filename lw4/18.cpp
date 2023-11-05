/*
    На шахматном поле расположены N черных и одна белая шашка.
Требуется написать программу, которая по заданному расположению шашек определяет,
какое максимальное количество шашек может взять белая шашка за один ход.
Взятая шашка сразу снимается с доски.
    Ввод из файла INPUT.TXT. Задается 8 строк, каждая содержит 8 символов.
Символом ‘0’ обозначается пустая клетка, символом ‘1’ - положение черной шашки
и символом ‘2’ - положение белой шашки.
    Вывод в файл OUTPUT.TXT. Вывести единственное число – 
максимальное количество черных шашек, которых можно взять за один ход (11).

Владимир Шибаков.
C++. Компилятор g++.
Visual Studio Code
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

void fillField(std::vector<std::vector<char>>& field, int& positionX, int& positionY);
void initField(std::vector<std::vector<char>>& field, const int& width, const int& height);
void countCapturedAndPrint(std::vector<std::vector<char>>& field, const int& positionX, const int& positionY);
void getMaxNumberOfCaptured(std::vector<std::vector<char>> field, const int& posX, const int& posY, int& max, int count);

int main()
{
    std::vector<std::vector<char>> field;
    int whitePiecePositionX;
    int whitePiecePositionY;
    fillField(field, whitePiecePositionX, whitePiecePositionY);

    countCapturedAndPrint(field, whitePiecePositionX, whitePiecePositionY);
}

void fillField(std::vector<std::vector<char>>& field, int& positionX, int& positionY)
{
    const int width = 8;
    const int height = 8;

    std::ifstream file;
    file.open("input.txt");

    if (file.is_open())
    {
        initField(field, width, height);

        char symbol;
        for (int i = 1; i <= width; ++i)
        {
            for (int j = 1; j <= height; ++j)
            {
                file >> symbol;
                switch (symbol)
                {
                case '0':
                    field[i][j] = '0';
                    break;
                case '1':
                    field[i][j] = '1';
                    break;
                case '2':
                {
                    field[i][j] = '2';
                    positionX = i;
                    positionY = j;
                }
                    break;
                default:
                    break;
                }
            }
        }
        file.close();
    }
    else
    {
        std::cout << "Couldn't open the file input.txt\n";
    }
}

void initField(std::vector<std::vector<char>>& field, const int& width, const int& height)
{
    field.resize(width + 2);
    for (int i = 0; i < width + 2; ++i)
    {
        field[i].resize(height + 2);
        for (int j = 0; j < height + 2; ++j)
        {
            field[i][j] = '-';
        }
    }
}

void countCapturedAndPrint(std::vector<std::vector<char>>& field, const int& positionX, const int& positionY)
{
    std::ofstream file;
    file.open("output.txt");
    
    if (file.is_open())
    {
        int maxPiecesCaptured = 0;
        int count = 0;
        getMaxNumberOfCaptured(field, positionX, positionY, maxPiecesCaptured, count);
        file << maxPiecesCaptured;
        file.close();
    }
    else
    {
        std::cout << "Couldn't open the file output.txt\n";
    }
}

void getMaxNumberOfCaptured(std::vector<std::vector<char>> field, const int& posX, const int& posY, int& max, int count)
{  
    if (field[posX + 1][posY + 1] == '1' && field[posX + 2][posY + 2] == '0')
    {
        field[posX][posY] = '0';
        field[posX + 1][posY + 1] = '0';
        field[posX + 2][posY + 2] = '2';
        count++;
        getMaxNumberOfCaptured(field, posX + 2, posY + 2, max, count);
        max = std::max(max, count);
    }

    if (field[posX - 1][posY + 1] == '1' && field[posX - 2][posY + 2] == '0')
    {
        field[posX][posY] = '0';
        field[posX - 1][posY + 1] = '0';
        field[posX - 2][posY + 2] = '2';
        count++;
        getMaxNumberOfCaptured(field, posX - 2, posY + 2, max, count);
        max = std::max(max, count);
    }

    if (field[posX - 1][posY - 1] == '1' && field[posX - 2][posY - 2] == '0')
    {
        field[posX][posY] = '0';
        field[posX - 1][posY - 1] = '0';
        field[posX - 2][posY - 2] = '2';
        count++;
        getMaxNumberOfCaptured(field, posX - 2, posY - 2, max, count);
        max = std::max(max, count);
    }

    if (field[posX + 1][posY - 1] == '1' && field[posX + 2][posY - 2] == '0')
    {
        field[posX][posY] = '0';
        field[posX + 1][posY - 1] = '0';
        field[posX + 2][posY - 2] = '2';
        count++;
        getMaxNumberOfCaptured(field, posX + 2, posY - 2, max, count);
        max = std::max(max, count);
    }
}