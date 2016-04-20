#include <stdlib.h>
#include <iostream>

#define arraySize 100001

int main(int argc, const char* argv[])
{
    int n=-1;
    int arrayList[arraySize];
    
    while(n!=0)
    {
		std::cin >> n;
	if(n==0)
	{
		break;
	}
        for(int i=0;i<n;i++)
        {
            std::cin>>arrayList[i];
		}
		long long int answer=0;
			
        for(int i=0;i<n-1;i++)
        {
            answer = answer+abs(arrayList[i]);
            arrayList[i+1] = arrayList[i+1]+ arrayList[i];
        }

        std::cout<<answer<<std::endl;
    }
    return 0;
}

