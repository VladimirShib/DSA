/*
Организовать в основной памяти с помощью указателей стек из очередей.
Обеспечить операции ведения очереди из вершины стека,
расширения и сокращения стека, выдачи содержимого стека.

Владимир Шибаков.
C++
Visual Studio Code
*/

#include <iostream>
#include <string>

struct queue
{
    std::string qData;
    queue *nextQ;
};

struct stack
{
    int data;
    stack *next;
    queue *front = 0;
    queue *back = 0;
};

void pushS(stack *&p, int elem)
{
    stack *newNode = new stack;
    newNode -> data = elem;
    newNode -> next = p;
    p = newNode;

    std::cout << "Element " << elem << " pushed to stack.\n\n";
}

void clearQ(stack *&p)
{
    while (p -> front)
    {
        queue *temp = p -> front;
        p -> front = p -> front -> nextQ;
        delete temp;
    }
    p -> back = 0;
}

void popS(stack *&p)
{
    clearQ(p);
    stack *temp = p;
    p = p -> next;
    std::cout << "\nElement " << temp -> data << " popped from stack.\n\n";
    delete temp;
}

void printQ(queue *p)
{
    while (p)
    {
        std::cout << p -> qData << "  ";
        p = p -> nextQ;
    }
}

void printS(stack *p)
{
    std::cout << "\nHere are all stack elements:\n";
    while (p)
    {
        std::cout << p -> data << " --> ";
        if (p -> front)
        {
            printQ(p -> front);
        }
        else
        {
            std::cout << "no queue in this element";
        }
        std::cout << "\n";
        p = p -> next;
    }
    std::cout << "\n";
}

void clearS(stack *&p)
{
    while (p)
    {
        clearQ(p);
        stack *temp = p;
        p = p -> next;
        delete temp;
    }
}

void pushQ(stack *&p, std::string elem)
{
    queue *newNode = new queue;
    newNode -> qData = elem;
    newNode -> nextQ = 0;

    if (!p -> back)
    {
        p -> front = p -> back = newNode;
    }
    else
    {
        p -> back -> nextQ = newNode;
        p -> back = newNode;
    }

    std::cout << "Element \"" << elem << "\" added to queue.\n\n";
}

void popQ(stack *&p)
{
    queue *temp = p -> front;
    p -> front = p -> front -> nextQ;

    if (p -> front == 0)
    {
        p -> back = 0;
    }

    std::cout << "\nElement \"" << temp -> qData << "\" removed from queue.\n\n";
    delete temp;
}

int main()
{
    stack *top = 0;
    char answer;
    char answerQ;

    do
    {
        std::cout << "1. Push.\n";
        std::cout << "2. Pop.\n";
        std::cout << "3. Print stack.\n";
        std::cout << "4. Clear stack.\n";
        std::cout << "5. Work with queue.\n";
        std::cout << "6. Exit.\n";
        std::cout << "Your choice: ";
        std::cin >> answer;

        if (answer == '1')
        {
            int value;
            std::cout << "\nEnter integer value: ";
            std::cin >> value;
            pushS(top, value);
        }

        if (answer == '2')
        {
            if (top)
            {
                popS(top);
            } else
            {
                std::cout << "\nStack is empty!\n\n";
            }
        }

        if (answer == '3')
        {
            if (top)
            {
                printS(top);
            } else
            {
                std::cout << "\nStack is empty!\n\n";
            }
        }

        if (answer == '4')
        {
            if (top)
            {
                clearS(top);
                std::cout << "\nStack cleared!\n\n";
            } else
            {
                std::cout << "\nStack is empty!\n\n";
            }
        }

        if (answer == '5')
        {
            if (!top)
            {
                std::cout << "\nYou need at least one element in stack to work with queue.\n\n"; 
            } else
            {
                std::cout << "\nWorking with queue " << top -> data << ":\n\n";
                do
                {
                    std::cout << "1. Add to queue.\n";
                    std::cout << "2. Move queue.\n";
                    std::cout << "3. Print queue.\n";
                    std::cout << "4. Clear queue.\n";
                    std::cout << "5. Back to stack.\n";
                    std::cout << "Your choice: ";
                    std::cin >> answerQ;

                    if (answerQ == '1')
                    {
                        std::string valueQ;
                        std::cout << "\nEnter string value: ";
                        std::cin >> valueQ;
                        pushQ(top, valueQ);
                    }

                    if (answerQ == '2')
                    {
                        if (top -> front)
                        {
                            popQ(top);
                        } else
                        {
                            std::cout << "\nQueue is empty!\n\n";
                        }
                    }

                    if (answerQ == '3')
                    {
                        if (top -> front)
                        {
                            std::cout << "\nHere are all queue elements: ";
                            printQ(top -> front);
                        } else
                        {
                            std::cout << "\nQueue is empty!";
                        }
                        std::cout << "\n\n";
                    }

                    if (answerQ == '4')
                    {
                        if (top -> front)
                        {
                            clearQ(top);
                            std::cout << "\nQueue cleared!\n\n";
                        } else
                        {
                            std::cout << "\nQueue is empty!\n\n";
                        }
                    }

                    if (answerQ < '1' || answerQ > '5')
                    {
                        std::cout << "\nInvalid command.\n\n";
                    }
                }
                while (answerQ != '5');

                std::cout << "\nWorking with stack:\n\n";
            }
        }

        if (answer < '1' || answer > '6')
        {
            std::cout << "\nInvalid command.\n\n";
        }
    }
    while (answer != '6');
    if (top)
    {
        clearS(top);
    }

    std::cout << "\nProgram stopped.\n";

    return 0;
}