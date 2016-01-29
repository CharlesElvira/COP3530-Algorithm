#include<iostream>
#include <time.h>
#include <stdlib.h>

template <class T > 
class Node
{
public:
    Node(T element);
    void setNextNode(Node<T> *next);
    Node* getNode();
    T getElement();
    void printNode();
    Node(const Node<T>& obj);
    Node( Node<T>* obj);
    virtual ~Node();

private:
    T element;
    Node<T> *nextNode;
};
template<class T>
Node<T>::Node(T element)
{
    this->element = element;
    nextNode = NULL;
}
template<class T>
Node<T>::Node(Node<T>* obj){
    element = obj->element;
    if(obj->nextNode != NULL)
    nextNode = new Node(obj->nextNode);
}
template<class T>
void Node<T>::setNextNode(Node<T> *next)
{
    this->nextNode = next;
}
template<class T>
T Node<T>::getElement()
{
    return element;
}
template<class T>
Node<T>* Node<T>::getNode()
{
    return nextNode;
}
template<class T>
Node<T>::Node(const Node<T>& obj)
{
    element = obj.element;
    nextNode = obj.nextNode;
}
template<class T>
void Node<T>::printNode()
{   if(nextNode != NULL){
    std::cout << element << " ";
	}
	else{
std::cout << element;	
}
}
template<class T>
Node<T>::~Node()
{
    if(nextNode != NULL){
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
    void insertNode(Node<T>* obj);
    void insertNode(T element);
    Node<T>* insertNode(Node<T>* obj, int position);
    void insertNode(T element, int position);
    Node<T>* getNode(int position);
    Node<T>* getNode();
    Node<T>* deleteNode(int position);
    void printLinkedList();
    linkedList<T>*  interleaved( linkedList<T> *L1, linkedList<T> *L2, int step);
    virtual ~linkedList();
private:
    Node<T> *head = NULL;
    Node<T> *endNode = NULL;
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
linkedList<T>::linkedList(T element)
{
    head = new Node<T>(element);
    endNode = head;
    size = 0;
}
template<class T>
linkedList<T>::linkedList(linkedList* obj){
    
    head = new Node<T>(obj->getNode(0));
    endNode= new Node<T>(obj->endNode);
    size = obj->size;
}
template<class T>
int linkedList<T>::getSize()
{
    return size;
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
    std::cout << std::endl;
}
template<class T>
void linkedList<T>::insertNode(T element)
{
    Node<T> *temp = new Node<T>(element);
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
Node<T> *linkedList<T>::insertNode(Node<T>* obj, int position)
{
    Node<T> *iterator = head;
    Node<T> *prior;
    
    if ( position <= size )
    {

        Node<T> *temp = obj;
        if ( position != 0 )
        {
            for ( int i = 1; i <= position; i++ )
            {
                prior = iterator;
                iterator = iterator->getNode();
            }
            prior->setNextNode(temp);
            temp->setNextNode(iterator);
            
                    
        } else
        {
            temp->setNextNode(iterator);
            head = temp;
            
        }
        size++;
    }
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
void linkedList<T>::insertNode(T element, int position) //Worst case complexity O(n) 
{
    Node<T> *iterator = head;
    Node<T> *prior;

    if ( position <= size )
    {

        Node<T> *temp = new Node<T>(element);
        if ( position != 0 )
        {
            for ( int i = 1; i <= position; i++ )
            {
                prior = iterator;
                iterator = iterator->getNode();
            }
            prior->setNextNode(temp);
            temp->setNextNode(iterator);
        } else
        {
            temp->setNextNode(iterator);
            head = temp;
        }
        size++;
    }
}
template<class T>
void linkedList<T>::insertNode(Node<T>* obj)
{
    Node<T>* temp = new Node<T>(obj->getElement());
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
linkedList<T>* linkedList<T>::interleaved(linkedList<T> *L1, linkedList<T> *L2, int step)//Worst case complexity 
{
    int sizeL1 = L1->getSize();
    int sizeL2 = L2->getSize();

    Node<T>* temp1 = L1->getNode(0);
    Node<T>* temp2 = L2->getNode(0);

    linkedList<T> *resultList = new linkedList<T>();
    int position = 0;
    while (temp1 != NULL) { //O(n^3 + n^2)
        for (int i = 0; i < step && temp1 != NULL; i++)//O(n)
        {
            resultList->insertNode(temp1);//O(n)
            temp1 = temp1->getNode();
        }
        if(temp2!=NULL){
        resultList->insertNode(temp2);//O(n)
        temp2 = temp2->getNode();
        }
    }
    return resultList;
}
template<class T>
linkedList<T>::~linkedList()
{
    if(endNode != NULL)
    delete endNode;
    if(head !=NULL)
    delete head;
}

int main(int, char**)
{
    int additionalList = 0;
    int *step;
    int size = 0;
    std::cin>>size;
    int *list = new int[size];
    for ( int i = 0; i < size; i++ )
    {
        std::cin >> list[i];
    }
    std::cin>>additionalList;
    step = new int[additionalList];
    linkedList<int> * ll[additionalList + 1];
    for ( int i = 0; i < additionalList + 1; i++ )
    {
        ll[i] = new linkedList<int>();
    }
    for ( int i = 0; i < size; i++ )
    {
        ll[0]->insertNode(list[i]);
    }

    delete list;
    for ( int i = 0; i < additionalList; i++ )
    {
        std::cin >> step[i];
        std::cin>>size;
        list = new int[size];
        for ( int j = 0; j < size; j++ )
        {
            std::cin >> list[j];
        }
       
            for ( int j = 0; j < size; j++ )
            {
                ll[i+1]->insertNode(list[j]);
            }

        
        delete list;
       
    }
    linkedList<int> *main = ll[0];
    
    for(int i = 0; i < additionalList; i++)
    {
        ll[0] = main->interleaved(ll[0],ll[i+1],step[i]);
    }
    ll[0]->printLinkedList();
    return 0;

}
