#include<iostream>
void bubbleSort(int *listOfInteger, int size)
{
	bool swap = true;
	int temp=0;
	while(swap)
	{	
		for(int i = 0 ; i+1 < size; i++)
		{
			if(listOfInteger[i] > listOfInteger[i+1])
			{
				temp = listOfInteger[i];
				listOfInteger[i] = listOfInteger[i+1];
				listOfInteger[i+1] = temp;
				swap = true;

				for(int i = 0; i<9;i++)
       				{
			                std::cout<<listOfInteger[i]<<" ";
			        }
				std::cout<<std::endl;
				
			}
			else if(listOfInteger[i] < listOfInteger[i+1])
			{
				swap = false;
			}
		
		}
	}
}
int main(int,char*[])
{
        clock_t t;

        int list[] =  {9,2,3,4,5,6,32,98,1};
        t = clock();
        bubbleSort(list,9);
        std::cout<<"It took : "<<((float)t)/CLOCKS_PER_SEC<<std::endl;
        for(int i = 0; i<9;i++)
        {
                std::cout<<list[i]<<" ";
        }	
}
