/*
Теннисный турнир проходит по олимпийской системе с выбываниями.
В турнире участвуют 2^n игроков. Известен рейтинг каждого игрока.
Чем больше рейтинг, тем выше мастерство игрока.
В первом туре сильнейший игрок встречается со слабейшим, второй по рейтингу с предпоследним и т.д.
Организаторы собираются и в дальнейшем придерживаться этого принципа, предполагая,
что в очередной тур будет выходить сильнейшая половина игроков предыдущего тура.
Известно, что турнир прошел в полном соответствии с рейтингом игроков.
Требуется показать в наглядном виде дерево проведенного турнира.

Владимир Шибаков.
C++
Visual Studio Code
*/

#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <algorithm>
#include <cmath>

struct Tree
{
    std::string playerName;
    int playerRate;
    Tree *left = 0;
    Tree *right = 0;
};

struct Player
{
    std::string name;
    int rate;
};

void readFromFile(std::string &fileName, std::deque<Player> &players)
{
    if (fileName.find_last_of('.') == std::string::npos)
    {
        fileName.append(".txt");
    }
    std::ifstream file;
    file.open(fileName);

    if (file.is_open())
    {
        std::string player;
        int rating;

        while (file >> player >> rating)
        {
            players.push_back({player, rating});
        }

        file.close();
    }
    else
    {
        std::cout << "Couldn't open the file " << fileName << ".\n";
    }
}

void insertIntoTree(Tree *&node, std::deque<Player> players, int level)
{
    level++;

    std::deque<Player> temp;
    std::copy(players.begin(), players.end(), std::back_inserter(temp));

    std::deque<Player> strongestPlayers;
    for (int i = 0; i < std::pow(2, level); i++)
    {
        strongestPlayers.push_back(temp.back());
        temp.pop_back();
    }

    bool treeNotFinished = players.size() - strongestPlayers.size();

    if (!node)
    {
        node = new Tree;
        node->playerName = strongestPlayers.front().name;
        node->playerRate = strongestPlayers.front().rate;
    }

    while (strongestPlayers.front().rate != node->playerRate)
    {
        strongestPlayers.pop_front();
        strongestPlayers.pop_back();
    }

    node->left = new Tree;
    node->right = new Tree;
    node->left->playerName = strongestPlayers.front().name;
    node->left->playerRate = strongestPlayers.front().rate;
    node->right->playerName = strongestPlayers.back().name;
    node->right->playerRate = strongestPlayers.back().rate;

    if (treeNotFinished)
    {
        insertIntoTree(node->left, players, level);
        insertIntoTree(node->right, players, level);
    }
}

int getHeight(Tree *node)
{
    if (!node)
    {
        return 0;
    }
    return 1 + getHeight(node->left);
}

void printAndDeleteTree(std::ofstream &output, Tree *&node, int level)
{
    if (node)
    {
        printAndDeleteTree(output, node->left, level - 1);
        for (int i = 0; i < level; i++)
        {
            output << "          ";
        }
        output << node->playerName << " " << node->playerRate << "\n";
        printAndDeleteTree(output, node->right, level - 1);
        delete node;
    }
}

void printToFile(std::string &fileName, Tree *&node, int level)
{
    if (fileName.find_last_of('.') == std::string::npos)
    {
        fileName.append(".txt");
    }
    std::ofstream file(fileName, std::ios_base::out | std::ios_base::trunc);

    if (file.is_open())
    {
        printAndDeleteTree(file, node, level - 1);
        file.close();
    }
    else
    {
        std::cout << "Failed to open the file " << fileName << "\n";
    }
}

bool lessRating(const Player &x, const Player &y)
{
    return x.rate < y.rate;
}

int main()
{
    std::string input;
    std::string output;
    std::deque<Player> allPlayers;
    Tree *root = 0;
    int treeLevel = 0;

    std::cout << "\nEnter input and output file names: ";
    std::cin >> input >> output;

    readFromFile(input, allPlayers);
    std::sort(allPlayers.begin(), allPlayers.end(), lessRating);

    if (allPlayers.size() > 1)
    {
        insertIntoTree(root, allPlayers, treeLevel);
    }

    int treeHeight = getHeight(root);
    printToFile(output, root, treeHeight);

    std::cout << "\nDone!\n";
}