#include<iostream>
#include<sstream>
#include<algorithm>

using namespace std;
template<class T>

class linearList
{
	public: 
		virtual ~linearList();
		virtual bool empty() const = 0;
		virtual int size() const = 0;
		virtual T& get(int index) const= 0;
		virtual int indexOf(const T& element) const = 0;
		virtual void erase(int index) const = 0;
		virtual void insert(int index, const T& element) const = 0;
		virtual void output(std::ostream& out) const =0;

};
template<class T>
class arrayList : public linearList<T>
{
	public:
//constructor, copy constructor and destructor
	arrayList(int initialCapacity = 10);
	arrayList(const arrayList<T>&);
	~arrayList() {delete []element;}
	bool empty() const{return listSize == 0;}
	int size() const{return listSize;}
	T& get(int index) const;
	int indexOf(const T& element) const;
	void erase(int index);
	void insert(int index, const T& element);
	void output(ostream& out) const;	

	int capacity() const{return arrayLength;}
	protected:
		void chechIndex(int index) const;
		T* element;
		int arrayLength;
		int listSize;	

};
template<class T>
void changeLength1D(T*& a, int oldLength, int newLength)
{
//	if(newLength < 0)
//		throw illegalParameterValue();

T* temp = new T[newLength];
//new array
int number = std::min(oldLength, newLength);
//number to copy
copy(a,a+number, temp);
delete [] a;
//deallocate old memory
a = temp;	
}
template<class T>
arrayList<T>::arrayList(int initialCapacity)
{
	if(initialCapacity < 1)
	{
		ostringstream s;
		s<<"Initial capacitty = "<<initialCapacity<<"must be > 0";
		//throw illegalParameterValue(s.str());
	}
arrayLength = initialCapacity;
element = new T[arrayLength];
listSize = 0;
	
}
template<class T>
arrayList<T>::arrayList(const arrayList<T>& list)
{
	arrayLength = list.arrayLength;
	listSize = list.listSize;
	element = new T[arrayLength];
	copy(list.element, list.element + listSize, element);
}

template<class T>
void arrayList<T>::checkIndex(int index) const
{
	if(index<0 || index >=listSize)
	{
		ostringstream s;
		s<<"index = "<<index<<"size = "<<listSize;
	}
}
template<class T>
T& arrayList<T>::get( int index) const
{
	checkIndex(index);
	return element[index];

}
template<class T>
int arrayList<t>::indexOf(const T& element)const
{
	int index = (int) (find(element, element + listSIze,element)- element);
	if(index == listSize)
	return -1;
	else return index;

}
template<class T>
void arrayList<T>erase(int index)
{
checkIndex(index);
copy(element + index+1, element+listSize, element+index);
element[--listSize].~T();
}
template<class T>
void arrayList<T>::insert(int index, const T& element)
{

}
int main(int, char**){
}
