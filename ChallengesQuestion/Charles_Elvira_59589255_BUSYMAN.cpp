#include <algorithm>
#include <iostream>
#include <vector>

int main()

{
	
	int testCase;
	
	
	std::cin>>testCase;
	
	
	while (testCase--)
	
	{
		
		int n;
		
		std::cin>>n;
		
		
		std::vector<std::pair<int, int> > length;
		
		
		for (int i = 0;
		i < n;
		i++)
		
		{
			
			int start, end;
			
			std::cin>>start;
			
			std::cin>> end;
			
			
			length.push_back(std::make_pair(start, -end));
			
			
		}
		
		
		std::sort(length.begin(), length.end());
		
		
		std::vector<std::pair<int, int> > length1;
		
		
		for (int i = 0;
		i < n;
		i++)
		
		{
			
			length[i].second = length[i].second * (-1);
			
			
			while (length1.size() > 0 && length1.back().second >= length[i].second)
			
			{
				
				
				length1.pop_back();
				
				
				
			}
			
			
			length1.push_back(length[i]);
			
			
		}
		
		
		int begin = 0;
		
		int ending = -1;
		
		
		for (int i = 0;
		i < length1.size();
		i++)
		
		{
			
			if (length1[i].first >= ending)
			
			{
				
				
				ending = length1[i].second;
				
				++begin;
				
				
			}
			
			
		}
		
		
		std::cout<<begin<<std::endl;
		
		
	}
	
	
}
