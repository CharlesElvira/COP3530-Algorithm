#include<iostream>
void bubbleSort(int listOfInteger[], int size)
{
		int temp;
		for(int i = 0 ; i < size - 1; i++)
		{
			for(int j = 0; j< size - i - 1; j++)
			{

				if(listOfInteger[j] > listOfInteger[j+1])
				{
					temp = listOfInteger[j];
					listOfInteger[j] = listOfInteger[j+1];
					listOfInteger[j+1] = temp;
				
				}
			}
			
		}
		
}

int main(int,char*[])
{
        clock_t t;

        int list[] =  {9,2,3,4,5,6,32,98,11,10,35,1};
        t = clock();
        bubbleSort(list,11);
        std::cout<<"It took : "<<((float)t)/CLOCKS_PER_SEC<<std::endl;
        for(int i = 0; i<11;i++)
        {
                std::cout<<list[i]<<" ";
        }	
}
