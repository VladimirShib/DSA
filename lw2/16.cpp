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
#include <deque>
#include <algorithm>
#include <cmath>

struct Tree
{
    int player;
    Tree *left = 0;
    Tree *right = 0;
};

void insertIntoTree(Tree *&node, std::deque<int> players, int level)
{
    level++;

    std::deque<int> temp;
    std::copy(players.begin(), players.end(), std::back_inserter(temp));

    std::deque<int> strongestPlayers;
    for (int i = 0; i < std::pow(2, level); i++)
    {
        strongestPlayers.push_back(temp.back());
        temp.pop_back();
    }

    bool treeNotFinished = players.size() - strongestPlayers.size();

    if (!node)
    {
        node = new Tree;
        node->player = strongestPlayers.front();
    }

    while (strongestPlayers.front() != node->player)
    {
        strongestPlayers.pop_front();
        strongestPlayers.pop_back();
    }

    node->left = new Tree;
    node->right = new Tree;
    node->left->player = strongestPlayers.front();
    node->right->player = strongestPlayers.back();

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

void printAndDeleteTree(Tree *&node, int level)
{
    if (node)
    {
        printAndDeleteTree(node->left, level - 1);
        for (int i = 0; i < level; i++)
        {
            std::cout << "     ";
        }
        std::cout << node->player << "\n";
        printAndDeleteTree(node->right, level - 1);
        delete node;
    }
}

int main()
{
    std::deque<int> allPlayers{1, 1, 1, 1, 4, 4, 4, 5};
    Tree *root = 0;
    int treeLevel = 0;

    std::sort(allPlayers.begin(), allPlayers.end());

    if (allPlayers.size() > 1)
    {
        insertIntoTree(root, allPlayers, treeLevel);
    }

    int treeHeight = getHeight(root);
    printAndDeleteTree(root, treeHeight - 1);
}