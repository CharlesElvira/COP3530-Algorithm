#include<iostream>
#include<time.h>
void InsertionSort(int *listOfInteger, int size)
{
	for(int i=0; i<size;i++)
	{
		int temp = listOfInteger[i];
		int j;
		for(j= i - 1; j>=0 && temp < listOfInteger[j]; j-- )
		{
			listOfInteger[j + 1] = listOfInteger[j];
		}
		listOfInteger[j+1] = temp;
	}
}
int main(int,char*[])
{
	clock_t t;
	
	int list[] =  {9,2,3,4,5,6,32,98,1};
	t = clock();
	InsertionSort(list,9);
	std::cout<<"It took : "<<((float)t)/CLOCKS_PER_SEC<<std::endl;
	for(int i = 0; i<9;i++)
	{
		std::cout<<list[i]<<" ";
	}	
}
