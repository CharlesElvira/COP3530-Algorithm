#include <iostream>
using namespace std;

class Node
{
public:
    Node( );
    Node( int column, int row, int value );
    void store( int column, int row, int value );
    void store( Node *next );
    int getValue( );
    int getColumn( );
    int getRow( );
    void printNode( );
    void setRow( int row );
    Node *getNext( );
    Node( const Node &obj );
    virtual ~ Node( );
private:
    int column, value, row;
    Node *next;
};

Node::Node( )
{
    this->column = - 1;
    this->row = - 1;
    this->value = 0;
    next = NULL;
}

Node::Node( int column, int row, int value )
{
    this->column = column;
    this->row = row;
    this->value = value;
    next = NULL;
}

int Node::getColumn( )
{
    return column;
}

void Node::printNode( )
{
    if ( next != NULL )
    {
        cout << value << " ";
    }
    else
    {
        cout << value;
    }
}

Node* Node::getNext( )
{
    return next;
}

int Node::getRow( )
{
    return row;
}

void Node::setRow( int row )
{
    this->row = row;
}

Node::Node( const Node& obj )
{
    this->column = obj.column;
    this->row = obj.row;
    this->value = obj.value;
    this->next = obj.next;
}

void Node::store( Node* next )
{
    this->next = next;
}

int Node::getValue( )
{
    return value;
}

void Node::store( int column, int row, int value )
{
    if ( this->column == - 1 )
    {
        this->column = column;
        this->row = row;
        this->value = value;
        next = NULL;
    }
    else
    {
        next = new Node( column, row, value );
    }
}

Node::~ Node( )
{
    if ( next != NULL )
    {
        delete next;
    }
}

class linkedList
{
public:
    linkedList( );
    void storeNode( int column, int row, int value );
    int getLinkedListSize( );
    void storeNode();
    void searchValue( int value );
    Node* getNode( int position );
    void insertNode( Node *element, int position );
    void printLinkedList( );
    linkedList( const linkedList &obj );
    virtual ~ linkedList( );
private:
    Node *head, *end;
    int size;
};

linkedList::linkedList( )
{
    head = NULL;
    end = NULL;
    size = 0;
}

void linkedList::searchValue( int value )
{
    for ( int i = 0; i < getLinkedListSize( ); i ++ )
    {
        if ( getNode( i )->getValue( ) == value )
        {
            cout << getNode( i )->getRow( ) << getNode( i )->getColumn( );
        }
    }
}

int linkedList::getLinkedListSize( )
{
    return size;
}

void linkedList::printLinkedList( )
{
    Node *iterator = head;
    for ( int i = 0; i < size; i ++ )
    {
        iterator->printNode( );
        iterator = iterator->getNext( );
    }
    cout << endl;
}

Node* linkedList::getNode( int position )
{
    Node *tempHead = head;
    for ( int i = 0; i < size && i < position; i ++ )
    {
        tempHead = tempHead->getNext( );
    }
    return tempHead;
}
void linkedList::storeNode()
{
    Node *temp = new Node( );
     if ( head == NULL )
    {
        head = temp;
        end = NULL;
        size ++;
    }
    else
    {
        Node *tempHead = head;

        while ( tempHead->getNext( ) != NULL )
        {
            tempHead = tempHead->getNext( );

        }
        tempHead->store( temp );
        end = tempHead;
        size ++;
    }
}
void linkedList::storeNode( int column, int row, int value )
{
    Node *temp = new Node( column, row, value );

    if ( head == NULL )
    {
        head = temp;
        end = NULL;
        size ++;
    }
    else
    {
        Node *tempHead = head;

        while ( tempHead->getNext( ) != NULL )
        {
            tempHead = tempHead->getNext( );

        }
        tempHead->store( temp );
        end = tempHead;
        size ++;
    }
}

void linkedList::insertNode( Node *element, int position )
{
    Node *temp = element;
    Node *previous = getNode( position );
    Node *after = getNode( position - 1 );
    temp->store( previous );
    after->store( temp );
}

linkedList::linkedList( const linkedList& obj )
{
    this->head = obj.head;
    this->end = obj.end;
    this->size = obj.size;
}

linkedList::~ linkedList( )
{

}

class sparseRow
{
public:
    sparseRow( );
    void addColumn();
    void addColumn( int column, int row, int value );
    int getSizeRow( );
    linkedList getlinkedList( );
    void searchValue( int value );
    sparseRow( const sparseRow &obj );
    void sparseRowAddition( sparseRow *row, int rowNum );
    virtual ~ sparseRow( );
private:
    int size;
    linkedList *rowSparseMatrix;
};

sparseRow::sparseRow( )
{
    size = 0;
    rowSparseMatrix = new linkedList( );
}

linkedList sparseRow::getlinkedList( )
{
    return *rowSparseMatrix;
}

void sparseRow::addColumn( int column, int row, int value )
{
    rowSparseMatrix->storeNode( column, row, value );
    size ++;
}
void sparseRow::addColumn()
{
    rowSparseMatrix->storeNode();
}
void sparseRow::searchValue( int value )
{
    
        rowSparseMatrix->searchValue( value );

}

void sparseRow::sparseRowAddition( sparseRow *row, int rowNum )
{
    int biggestrow = 0, counta = 0, countb = 0;
    sparseRow *temp = new sparseRow( );
    Node *a, *b;
    if ( row->getSizeRow( ) > getSizeRow( ) )
    {
        biggestrow = row->getSizeRow( );

    }
    else
    {
        biggestrow = size;
    }

    a = row->getlinkedList().getNode(counta);
    b = getlinkedList().getNode(countb);
    for ( int i = 0; counta < biggestrow && countb <biggestrow; i ++ )
    {

        if ( a->getColumn( ) != i )
        {
            if ( b->getColumn( ) != i )
            {
            }
            else
            {
                temp->addColumn( b->getColumn( ), rowNum, b->getValue( ) );
                countb++;
                b = getlinkedList().getNode(countb);
            }
        }
        else
        {
            if ( b->getColumn( ) != i )
            {
                temp->addColumn( a->getColumn( ), rowNum, a->getValue( ) );
                counta++;
                a = getlinkedList().getNode(counta);
            }
            else
            {
                temp->addColumn( a->getColumn( ), rowNum, b->getValue() + a->getValue( ) );
                counta++;
                countb++;
                a = getlinkedList().getNode(counta);
                b = getlinkedList().getNode(countb);
            }
        }
        
    }
    rowSparseMatrix = new linkedList( temp->getlinkedList( ) );
}

int sparseRow::getSizeRow( )
{
    return size;
}

sparseRow::sparseRow( const sparseRow& obj )
{
    this->rowSparseMatrix = obj.rowSparseMatrix;
    this->size = obj.size;
}

sparseRow::~ sparseRow( )
{

}

class sparseMatrix
{
public:
    sparseMatrix( );
    sparseMatrix( int size );
    void addElement( int row, int column, int value );
    void addElement( int rowindex);
    int getSparseMatrixSize( );
    sparseMatrix *sparseMatrixAddition( sparseMatrix mat );
    void setSparseRow( sparseRow *row );
    sparseRow *getSparseMatrix( );
    void sparseMatrixSearch( int value );
    void printSparseMatrix( );
    void setSizeSparseMatrix( int size );
    sparseMatrix( const sparseMatrix &obj );
    virtual ~ sparseMatrix( );
private:
    int m;
    sparseRow *row;
};

sparseMatrix::sparseMatrix( )
{
    m = 0;
    row = NULL;
}

sparseMatrix::sparseMatrix( int size )
{
    m = size;
    row = new sparseRow[m];
}

sparseMatrix::sparseMatrix( const sparseMatrix& obj )
{
    this->m = obj.m;
    this->row = obj.row;
}

void sparseMatrix::setSizeSparseMatrix( int size )
{
    m = size;
    row = new sparseRow[m];
}

void sparseMatrix::setSparseRow( sparseRow *row )
{
    this->row = row;
}

void sparseMatrix::printSparseMatrix( )
{
    for ( int i = 0; i < m; i ++ )
    {
        row[i].getlinkedList( ).printLinkedList( );
    }
}

void sparseMatrix::addElement( int rowindex, int column, int value )
{
    this->row[rowindex].addColumn( column, rowindex, value );
}
void sparseMatrix::addElement(int rowindex )
{
    this->row[rowindex].addColumn( );
}
int sparseMatrix::getSparseMatrixSize( )
{
    return m;
}

sparseRow* sparseMatrix::getSparseMatrix( )
{
    if(row !=NULL){
            return row;
    }

}

void sparseMatrix::sparseMatrixSearch( int value )
{
    for(int i=0;i<m;i++)
    {
        row[i].searchValue( value );
    }
    cout<<endl;
}

sparseMatrix *sparseMatrix::sparseMatrixAddition( sparseMatrix mat )
{
    sparseMatrix *tmp = new sparseMatrix(mat);
    sparseRow *temprow = new sparseRow[getSparseMatrixSize( )];
    for ( int i = 0; i < tmp->getSparseMatrixSize(); i ++ )
    {
       
        row[i].sparseRowAddition( &tmp->row[i] , i );
        temprow[i] = row[i];
        
    }
    sparseMatrix *sp = new sparseMatrix( getSparseMatrixSize( ) );
    sp->setSparseRow( row );
    return sp;
}

sparseMatrix::~ sparseMatrix( )
{

}

int main( int, char** )
{
    //5 2 1 12 3 5 0 1 4 2 1 3 6 4 0 1 2 4 4 9 5 16 5 2 1 12 3 5 0 1 4 2 1 3 6 4 0 1 2 4 4 9 5 16

    int numOfrows = 0,searchNum =0,search =0, numOfElement = 0, column = 0, value = 0, highestcol = 0;
    sparseMatrix *mat, *result;
    mat = new sparseMatrix[2];
    for ( int k = 0; k < 2; k ++ )
    {//which matrix
        cin>> numOfrows;
        mat[k].setSizeSparseMatrix( numOfrows );
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
                mat[k].addElement( i, column, value );
            }
            
        }
    }
    mat[0].printSparseMatrix( );
    mat[1].printSparseMatrix( );

    result = mat[0].sparseMatrixAddition( mat[1] );
    result->printSparseMatrix( );
    cin>>searchNum;
    for(int i = 0;i<searchNum;i++)
    {
        cin>>search;
        result->sparseMatrixSearch(search);
    }
    

}