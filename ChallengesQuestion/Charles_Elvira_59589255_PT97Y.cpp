#include <algorithm>
#include <vector>

#include <iostream>
#include <queue>

bool breathfs( std::vector< int > graph[], int u, int n )

{
	
	
	bool visited[ n + 1 ];
	
	
	int i;
	
	int p;
	
	int k;
	
	int count = 0;
	
	
	for ( i = 0;
	i <= n;
	++i )
	
	{
		
		
		visited[ i ] = false;
		
		
	}
	
	
	std::queue< int > q;
	
	q.push(u);
	
	
	
	
	while ( !q.empty() )
	{
		
		
		p = q.front();
		
		q.pop();
		
		visited[p] = true;
		
		
		for ( i = 0;
		i < graph[ p ].size();
		++i )
		
		{
			
			
			k = graph[ p ][ i ];
			
			if ( visited[ k ] )
			
			{
				
				return false;
				
				
			}
			
			else
			
			{
				
				q.push( k );
				
				
			}
			
			
		}
		
		
		count++;
		
		
	}
	
	
	if ( count != n )
	
	{
		
		
		return false;
		
		
		
	}
	
	else
	
	{
		
		return true;
		
		
	}
	
	
}


int main()

{
	
	
	int i,m,n,u, v;
	
	std::cin>>n;
	
	std::cin>>m;
	
	std::vector< int > graph[n+1];
	
	
	for ( i = 0;
	i < m;
	i++)
	
	{
		
		std::cin>>u;
		
		std::cin>>v;
		
		graph[ u ].push_back( v );
		
		
	}
	
	if ( breathfs( graph, 1, n ) )
	
	{
		
		std::cout<<"YES"<<std::endl;
		
		
	}
	
	else
	
	{
		
		std::cout<<"NO"<<std::endl;
		
		
	}
	
	
	return 0;
	
	
}
