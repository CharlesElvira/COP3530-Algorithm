

#include<iostream>
#include<algorithm>


#define testCaseSize 200001


int arrayA[testCaseSize];

int testcase[testCaseSize];


unsigned long long merge(int array[],int temp[],int middle,int left,int right)

{
	
	int i=left,j=middle,k=left;
	
	
	unsigned long long int count = 0;
	//judge test case won't work otherwise
	
	while((i<=middle-1) && (j<=right))
	
	{
		
		if(array[i] <= array[j])
		
		{
			
			temp[k++]=array[i++];
			
			
		}
		
		else
		
		{
			
			temp[k++]=array[j++];
			
			count += (middle-i);
			
			
		}
		
		
	}
	
	while(i <= middle-1)
	
	{
		
		temp[k++]=array[i++];
		
		
	}
	
	while(j<=right)
	{
		
		temp[k++]=array[j++];
		
		
	}
	
	for(int i=left;	
	i<=right;
	i++)
	
	{
		
		array[i] = temp[i];
		
		
	}
	
	return count;
	
	
}

unsigned long long int mergesort(int array[],int temp[],int left,int right)

{
	
	unsigned long long int i=0;
	
	if(right>left)
	{
		
		int middle=(left + right)/2;
		
		i = mergesort(array,temp,left,middle);
		
		i = i+mergesort(array,temp,middle+1,right);
		
		i= i+merge(array,temp,middle+1,left,right);
		
		
	}
	
	return i;
	
	
}

int main(int argc,  char** argv)

{
	
	int t;
	
	int n;
	
	
	std::cin>>t;
	
	while(t--)
	{
		
		std::cin>>n;
		
		for(int i=0;
		i<n;
		i++)
		
		{
			
			std::cin>>arrayA[i];
			
			
		}
		
		std::cout << mergesort(arrayA,testcase,0,n-1)<<std::endl;
		
		
	}
	
	return 0;
	
	
}



