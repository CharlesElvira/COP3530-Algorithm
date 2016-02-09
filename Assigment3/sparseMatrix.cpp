#include<iostream>
#include <time.h>
#include <stdlib.h>
#include <vector>

using namespace std;

template <class T>
class Node
{
public:
    Node();
    Node(int column, int value);
    void setNextNode(Node<T> *next);
    Node* getNode();
    int getValue();
    int getColumn();
    void printNode();
    Node(const Node<T>& obj);
    Node(Node<T>* obj);
    virtual ~Node();

private:
    int column, value;
    Node<T> *nextNode;
};

template<class T>
Node<T>::Node()
{
    column = 0;
    value = 0;
    nextNode = NULL;
}

template<class T>
Node<T>::Node(Node<T>* obj)
{

    column = obj->column;
    value = obj->value;
    if ( obj->nextNode != NULL )
        nextNode = new Node(obj->nextNode);
}

template<class T>
Node<T>::Node(int column, int value)
{
    this->column = column;
    this->value = value;
    nextNode = NULL;
}

template<class T>
void Node<T>::setNextNode(Node<T> *next)
{
    this->nextNode = next;
}

template<class T>
int Node<T>::getColumn()
{
    return column;
}

template<class T>
int Node<T>::getValue()
{
    return value;
}

template<class T>
Node<T>* Node<T>::getNode()
{
    return nextNode;
}

template<class T>
Node<T>::Node(const Node<T>& obj)
{

    column = obj.column;
    value = obj.value;
    nextNode = obj.nextNode;
}

template<class T>
void Node<T>::printNode()
{
    if ( nextNode != NULL )
    {
        cout << value << " ";
    } else
    {
        cout << value;
    }
}

template<class T>
Node<T>::~Node()
{
    if ( nextNode != NULL )
    {
        delete nextNode;
    }
}

template<class T>
class linkedList
{
public:
    linkedList();
    linkedList(T element);
    linkedList(linkedList<T> *obj);
    int getSize();
    void setHighestCol(int high);
    int getHighestCol();
    void insertNode(int column, int value);
    Node<T>* getNode(int position);
    Node<T>* getNode();
    Node<T>* deleteNode(int position);
    void printLinkedList();
    virtual ~linkedList();
private:
    Node<T> *head = NULL;
    Node<T> *endNode = NULL;
    int highestCol;
    int size;
};

template<class T>
linkedList<T>::linkedList()
{
    head = NULL;
    endNode = head;
    size = 0;
}

template<class T>
linkedList<T>::linkedList(linkedList<T> *obj)
{
    if ( obj->head != NULL )
    {
        head = obj->head;
        endNode = obj->endNode;
        size = obj->size;
    }
}

template<class T>
int linkedList<T>::getSize()
{
    return size;
}

template<class T>
void linkedList<T>::setHighestCol(int high)
{
    this->highestCol = high;
}

template<class T>
int linkedList<T>::getHighestCol()
{
    return highestCol;
}

template<class T>
void linkedList<T>::printLinkedList()
{
    Node<T> *iterator = head;
    for ( int i = 0; i < size; i++ )
    {
        iterator->printNode();
        iterator = iterator->getNode();
    }
    cout << endl;
}

template<class T>
void linkedList<T>::insertNode(int column, int value)
{
    Node<int> *temp = new Node<int>(column, value);
    if ( head == NULL )
    {
        head = temp;
        endNode = head;
    } else
    {
        endNode->setNextNode(temp);
        endNode = temp;
    }
    size++;
}

template<class T>
Node<T>* linkedList<T>::getNode()
{
    return head;
}

template<class T>
Node<T>* linkedList<T>::getNode(int position)
{
    Node<T> *prior;
    Node<T> *iterator = head;

    if ( position <= size )
    {
        if ( position != 0 )
        {
            for ( int i = 1; i <= position; i++ )
            {
                prior = iterator;

            }
            return prior->getNode();
        } else
        {
            return head;
        }
    }
    return NULL;
}

template<class T>
Node<T>* linkedList<T>::deleteNode(int position)//Worst case complexity O(n)
{
    Node<T> *iterator = head;
    if ( position < size )
    {
        if ( position != 0 )
        {
            for ( int i = 0; i < position - 1; i++ )
            {
                iterator = iterator->getNode();
            }
            Node<T> *temp = iterator->getNode();
            iterator->setNextNode(iterator->getNode()->getNode());
            temp->setNextNode(NULL);
            delete temp;
            size--;

        } else
        {
            Node<T> *temp = head;
            head = head->getNode();
            temp->setNextNode(NULL);
            delete temp;
            size--;
        }

    }
}

template<class T>
linkedList<T>::~linkedList()
{
    if ( endNode != NULL )
        delete endNode;
    if ( head != NULL )
        delete head;
}

class sparseMatrix
{
public:
    sparseMatrix(int size);
    linkedList<int> getRow(int position);
    void setRow(linkedList<int> *row);
    void addRow(linkedList<int> *row);
    void printSparseMatrix();
    sparseMatrix* addSparse(sparseMatrix mat);
private:
    linkedList<int> *row;
    int numberRow;
    int counter;
};
sparseMatrix::sparseMatrix(int size)
{
    numberRow = size;
    row[size] = new linkedList<int>();
    counter = 0;
}

void sparseMatrix::addRow(linkedList<int> *row)
{
    if(counter < numberRow)
    {
        this->row[counter] = new linkedList(row);
    }
    
}

void sparseMatrix::printSparseMatrix()
{
    for(int i=0;i<counter;i++)
    {
        
    }
}

int main(int,char**)
{
    
}