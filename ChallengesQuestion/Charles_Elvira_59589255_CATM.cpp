#include <iostream>
#include <vector>
#include <queue>
#define Max_SIZE 100

int mouthdist[ Max_SIZE ][ Max_SIZE ];

int catdist[ Max_SIZE ][ Max_SIZE ];

int n, m;


struct cordinates
{
	
	int x, y;
	
	
}
;


void mouthbfs( cordinates mouse )
{
	
	bool visited[ n ][ m ];
	
	int i, j;
	
	for ( i = 0;
	i < n;
	++i )
	{
		
		for ( j = 0;
		j < n;
		++j )
		{
			
			visited[ i ][ j ] = false;
			
			
		}
		
		
	}
	
	
	std::queue< cordinates > q;
	
	mouse.x = mouse.x - 1;
	
	mouse.y =mouse.y - 1;
	
	q.push( mouse );
	
	mouthdist[ mouse.x ][ mouse.y ] = 0;
	
	while ( !q.empty() )
	{
		
		cordinates p = q.front();
		
		q.pop();
		
		if ( !visited[ p.x ][ p.y ] )
		{
			
			visited[ p.x ][ p. y ] = true;
			
			if ( p.x + 1 < n && mouthdist[ p.x + 1 ][ p.y ] > mouthdist[ p.x ][ p.y ] + 1 )
			{
				
				q.push( ( cordinates )
				{
					p.x + 1, p.y
				}
				);
				
				mouthdist[ p.x + 1 ][ p.y ] = mouthdist[ p.x ][ p.y ] + 1;
				
				
			}
			
			if ( p.x - 1 >= 0 && mouthdist[ p.x - 1 ][ p.y ] > mouthdist[ p.x ][ p.y ] + 1 )
			{
				
				q.push( ( cordinates )
				{
					p.x - 1, p.y
				}
				);
				
				mouthdist[ p.x - 1 ][ p.y ] = mouthdist[ p.x ][ p.y ] + 1;
				
				
			}
			
			if ( p.y + 1 < m && mouthdist[ p.x ][ p.y + 1 ] > mouthdist[ p.x ][ p.y ] + 1 )
			{
				
				q.push( ( cordinates )
				{
					p.x, p.y + 1
				}
				);
				
				mouthdist[ p.x ][ p.y + 1 ] = mouthdist[ p.x ][ p.y ] + 1;
				
				
			}
			
			if ( p.y - 1 >= 0 && mouthdist[ p.x ][ p.y - 1 ] > mouthdist[ p.x ][ p.y ] + 1 )
			{
				
				q.push( ( cordinates )
				{
					p.x, p.y - 1
				}
				);
				
				mouthdist[ p.x ][ p.y - 1 ] = mouthdist[ p.x ][ p.y ] + 1;
				
				
			}
			
			
		}
		
		
	}
	
	
}

void catbfs( cordinates cat )
{
	
	bool visited[n][m];
	
	int i, j;
	
	
	for ( i = 0;
	i < n;
	++i )
	{
		
		for ( j = 0;
		j < n;
		++j )
		{
			
			visited[ i ][ j ] = false;
			
			
		}
		
		
	}
	
	
	cat.x = cat.x - 1;
	
	cat.y =cat.y- 1;
	
	std::queue< cordinates > q;
	
	q.push( cat );
	
	catdist[ cat.x ][ cat.y ] = 0;
	
	while ( !q.empty() )
	{
		
		cordinates p = q.front();
		
		q.pop();
		
		if ( !visited[p.x][p.y] )
		{
			
			visited[ p.x ][ p. y ] = true;
			
			if ( p.x + 1 < n && catdist[ p.x + 1 ][ p.y ] > catdist[ p.x ][ p.y ] + 1 )
			{
				
				q.push( ( cordinates )
				{
					p.x + 1, p.y
				}
				);
				
				catdist[ p.x + 1 ][ p.y ] = catdist[ p.x ][ p.y ] + 1;
				
				
			}
			
			if ( p.x - 1 >= 0 && catdist[ p.x - 1 ][ p.y ] > catdist[ p.x ][ p.y ] + 1 )
			{
				
				q.push( ( cordinates )
				{
					p.x - 1, p.y
				}
				);
				
				catdist[ p.x - 1 ][ p.y ] = catdist[ p.x ][ p.y ] + 1;
				
				
			}
			
			if ( p.y + 1 < m && catdist[ p.x ][ p.y + 1 ] > catdist[ p.x ][ p.y ] + 1 )
			{
				
				q.push( ( cordinates )
				{
					p.x, p.y + 1
				}
				);
				
				catdist[ p.x ][ p.y + 1 ] = catdist[ p.x ][ p.y ] + 1;
				
				
			}
			
			if ( p.y - 1 >= 0 && catdist[ p.x ][ p.y - 1 ] > catdist[ p.x ][ p.y ] + 1 )
			{
				
				q.push( ( cordinates )
				{
					p.x, p.y - 1
				}
				);
				
				catdist[ p.x ][ p.y - 1 ] = catdist[ p.x ][ p.y ] + 1;
				
				
			}
			
			
		}
		
		
	}
	
	
}




int main()
{
	
	
	int k,i,j;
	
	
	std::cin>>n;
	
	std::cin>>m;
	
	std::cin>>k;
	
	
	cordinates cat1, cat2, mouse;
	
	
	bool isFound;
	
	
	while ( k > 0 )
	{
		//K being the number of k trial
		isFound = false;
		
		for ( i = 0;
		i < n;
		++i )
		{
			
			for ( j = 0;
			j < m;
			++j )
			{
				
				mouthdist[ i ][ j ] = 1000000;
				
				catdist[ i ][ j ] = 1000000;
				//max possible
				
			}
			
			
		}
		
		
		std::cin>>mouse.x;
		
		std::cin>>mouse.y;
		
		std::cin>>cat1.x;
		
		std::cin>>cat1.y;
		
		std::cin>>cat2.x;
		
		std::cin>>cat2.y;
		
		
		catbfs( cat1 );
		
		catbfs( cat2 );
		
		mouthbfs( mouse );
		
		
		if ( !isFound )
		{
			
			for ( i = 0;
			i < n;
			++i )
			{
				
				if ( mouthdist[ i ][ 0 ] < catdist[ i ][ 0 ] || mouthdist[ i ][ m - 1 ] < catdist[ i ][ m - 1 ] )
				{
					
					std::cout<<"YES"<<std::endl;
					
					isFound = true;
					
					break;
					
					
				}
				
				
			}
			
			
		}
		
		
		if ( !isFound )
		{
			
			for ( j = 0;
			j < m;
			++j )
			{
				
				if ( mouthdist[ 0 ][ j ] < catdist[ 0 ][ j ] || mouthdist[ n - 1 ][ j ] < catdist[ n - 1 ][ j ] )
				{
					
					std::cout<<"YES"<<std::endl;
					
					isFound = true;
					
					break;
					
					
				}
				
				
			}
			
			
		}
		
		
		if ( !isFound )
		{
			
			std::cout<<"NO"<<std::endl;
			
			
		}
		
		--k;
		
		
	}
	
	
	return 0;
	
	
}
