#include<iostream>
#include <time.h>
#include <stdlib.h>
#include <vector>

using namespace std;

class Node
{
public:
    Node( );
    Node( int column, int value );
    void setNextNode( Node *next );
    Node* getNode( );
    int getValue( );
    int getColumn( );
    void printNode( );
    Node( const Node & obj );
    Node( Node * obj );
    virtual ~ Node( );

private:
    int column, value;
    Node *nextNode;
};

Node::Node( )
{
    column = 0;
    value = 0;
    nextNode = NULL;
}

Node::Node( Node * obj )
{
    if ( obj->getNode( ) != NULL )
    {
        column = obj->column;
        value = obj->value;
        if ( obj->nextNode != NULL )
        {
            nextNode = new Node( obj->nextNode );
        }
    }
}

Node::Node( int column, int value )
{
    this->column = column;
    this->value = value;
    nextNode = NULL;
}

void Node::setNextNode( Node *next )
{
    this->nextNode = next;
}

int Node::getColumn( )
{
    return column;
}

int Node::getValue( )
{
    return value;
}

Node * Node::getNode( )
{
    if ( nextNode != NULL )
    {
        return nextNode;
    }
}

Node::Node( const Node & obj )
{

    column = obj.column;
    value = obj.value;
    nextNode = obj.nextNode;
}

void Node::printNode( )
{
    if ( nextNode != NULL )
    {
        cout << value << " ";
    }
    else
    {
        cout << value;
    }
}

Node::~ Node( )
{
    if ( nextNode != NULL )
    {
        delete nextNode;
    }
}

class linkedList
{
public:
    linkedList( );
    linkedList( linkedList *obj );
    linkedList( const linkedList &obj );
    int getSize( );
    void setHighestCol( int high );
    int getHighestCol( );
    void insertNode( Node* obj );
    void insertNode( int column, int value );
    linkedList* addLinkedList( linkedList *ll );
    Node* getNode( int position );
    Node* getNode( );
    Node* deleteNode( int position );
    void printLinkedList( );
    virtual ~ linkedList( );
private:
    Node *head = NULL;
    Node *endNode = NULL;
    int highestCol;
    int size;
};

linkedList::linkedList( )
{
    head = NULL;
    endNode = head;
    size = 0;
}

linkedList::linkedList( linkedList *obj )
{

    head = new Node( obj->head );
    endNode = obj->endNode;
    size = obj->size;

}

linkedList::linkedList( const linkedList &obj )
{

    head = new Node( obj.head );
    endNode = obj.endNode;
    size = obj.size;

}

void linkedList::insertNode( Node* obj )
{
    Node* temp = new Node( obj->getColumn( ), obj->getValue( ) );
    if ( head == NULL )
    {
        head = temp;
        endNode = head;
    }
    else
    {
        endNode->setNextNode( temp );
        endNode = temp;
    }
    size ++;
}

linkedList* linkedList::addLinkedList( linkedList *ll )
{
    int greatersize = 0;
    linkedList *result = new linkedList( );
    if ( ll->getSize( ) > size )
    {
        greatersize = ll->getSize( );
    }
    else
    {
        greatersize = size;
    }
    for ( int i = 0; i < greatersize; i ++ )
    {
        if ( ll->getNode( i ) != NULL )
        {
            if ( getNode( i ) != NULL )
            {
                result->insertNode( i, ll->getNode( i )->getValue( ) + getNode( i )->getValue( ) );
            }
            else
            {
                result->insertNode( i, ll->getNode( i )->getValue( ) );
            }
        }
        else
        {
            if ( getNode( i ) != NULL )
            {
                result->insertNode( i, getNode( i )->getValue( ) );
            }
        }
    }
    return result;
}

int linkedList::getSize( )
{
    return size;
}

void linkedList::setHighestCol( int high )
{
    this->highestCol = high;
}

int linkedList::getHighestCol( )
{
    return highestCol;
}

void linkedList::printLinkedList( )
{
    Node *iterator = head;
    for ( int i = 0; i < size; i ++ )
    {
        iterator->printNode( );
        iterator = iterator->getNode( );
    }
    cout << endl;
}

void linkedList::insertNode( int column, int value )
{
    Node *temp = new Node( column, value );
    if ( head == NULL )
    {
        head = temp;
        endNode = head;
    }
    else
    {
        endNode->setNextNode( temp );
        endNode = temp;
    }
    size ++;

}

Node* linkedList::getNode( )
{
    return head;
}

Node * linkedList::getNode( int position )
{
    Node *prior;
    Node *iterator = head;

    if ( position <= size )
    {
        if ( position != 0 )
        {
            for ( int i = 1; i <= position; i ++ )
            {
                prior = iterator;

            }
            return prior->getNode( );
        }
        else
        {
            return head;
        }
    }
    return NULL;
}

Node* linkedList::deleteNode( int position )//Worst case complexity O(n)
{
    Node *iterator = head;
    if ( position < size )
    {
        if ( position != 0 )
        {
            for ( int i = 0; i < position - 1; i ++ )
            {
                iterator = iterator->getNode( );
            }
            Node *temp = iterator->getNode( );
            iterator->setNextNode( iterator->getNode( )->getNode( ) );
            temp->setNextNode( NULL );
            delete temp;
            size --;

        }
        else
        {
            Node *temp = head;
            head = head->getNode( );
            temp->setNextNode( NULL );
            delete temp;
            size --;
        }

    }
}

linkedList::~ linkedList( )
{
    if ( endNode != NULL )
        delete endNode;
    if ( head != NULL )
        delete head;
}

class sparseMatrix
{
public:
    sparseMatrix( );
    sparseMatrix( int size );
    linkedList* getRow( int position );
    void setRow( linkedList *row );
    sparseMatrix* sparseMatrixAddition( sparseMatrix mat );

    void setNumRow( int numrow );
    void createRow( );
    void printSparseMatrix( );
    int getNumRow( );
private:
    linkedList *row;
    int numberRow;
    int counter;
};

sparseMatrix::sparseMatrix( )
{
    counter = 0;
    numberRow = 0;
}

sparseMatrix::sparseMatrix( int size )
{
    numberRow = size;
    row = new linkedList[size];
    counter = 0;
}

void sparseMatrix::setRow( linkedList *row )
{
    if ( row->getNode( 0 ) != NULL )
    {
        this->row[counter] = new linkedList( row );
    }
}

int sparseMatrix::getNumRow( )
{
    return numberRow;
}

void sparseMatrix::setNumRow( int numrow )
{
    numberRow = numrow;
    createRow( );
}

void sparseMatrix::createRow( )
{

    row = new linkedList[numberRow];
}

linkedList* sparseMatrix::getRow( int position )
{
    return &row[position];
}

void sparseMatrix::printSparseMatrix( )
{
    for ( int i = 0; i < numberRow; i ++ )
    {
        row[i].printLinkedList( );
    }
}

sparseMatrix* sparseMatrix::sparseMatrixAddition( sparseMatrix mat )
{
    sparseMatrix *result = new sparseMatrix( );
    result->setNumRow( mat.getNumRow( ) );

    for ( int i = 0; i < mat.getNumRow( ); i ++ )
    {
        
        result->setRow( mat.getRow( i )->addLinkedList( &row[i] ) );
        result->printSparseMatrix();
    }
    return result;
}

int main( int, char** )
{
    //5 2 1 12 3 5 0 1 4 2 1 3 6 4 0 1 2 4 4 9 5 16 5 2 1 12 3 5 0 1 4 2 1 3 6 4 0 1 2 4 4 9 5 16


    int numOfrows = 0, numOfElement = 0, column = 0, value = 0, highestcol = 0;
    sparseMatrix *mat, *result;
    mat = new sparseMatrix[2];
    for ( int k = 0; k < 2; k ++ )
    {//which matrix
        cin>> numOfrows;
        mat[k].setNumRow( numOfrows );
        for ( int i = 0; i < numOfrows; i ++ )
        {//which row
            cin>>numOfElement;
            for ( int j = 0; j < numOfElement; j ++ )
            {//which column
                cin>>column;
                cin>>value;
                if ( highestcol <= column )
                {
                    highestcol = column;
                }
                mat[k].getRow( i )->insertNode( column, value );
            }
            mat[k].getRow( i )->setHighestCol( highestcol );
            highestcol = 0;
        }
        mat[k].printSparseMatrix( );
    }
    result = mat[0].sparseMatrixAddition( mat[1] );
    result->printSparseMatrix( );
}