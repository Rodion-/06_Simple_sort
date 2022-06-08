#include <iostream>
#include <filesystem>
#include <fstream>
#include <memory>
#include <vector>
#include <chrono>
#include <cstring>
#include <list>

class ISort
{
	public:
	
	virtual void run ( int* _data , int _size ) = 0;
	
	virtual ~ISort() {};
};


class TesterArray 
{
	std::unique_ptr< ISort > itests;
	int size = 0;
	int* data = nullptr;
	public:	
	
	TesterArray( std::unique_ptr< ISort > _itests , int* _data , int _size ) : itests( std::move( _itests ) ) , data(_data ) , size( _size ) {}
	~TesterArray(){}
	
	void RunTests( void )
	{
		itests->run( data , size );			
	}
};

void bubble_sort ( int* data , int size )
{
	for( int i = 0; i < size; i++ )
	{
		for( int j = 0; j < size - i ; j++ )
		{
			int temp = 0;
			
			if( data[ j ] > data[ j + 1 ] )
			{
				temp = data[ j + 1 ];
				data[ j + 1] = data[ j ];
				data[ j ] = temp;
			}
		}
	}
}

class BubbleSort : public ISort
{
	public:
	
	BubbleSort(){}
	~BubbleSort() override {}
	void run ( int* data , int size ) override
	{
		for( int i = 0; i < size; i++ )
		{
			for( int j = 0; j < size - i ; j++ )
			{
				int temp = 0;
			
				if( data[ j ] > data[ j + 1 ] )
				{
					temp = data[ j + 1 ];
				data[ j + 1] = data[ j ];
						data[ j ] = temp;
				}
			}
		}
	}	
};

class InsertSort : public ISort
{
	public:
	
	InsertSort(){}
	~InsertSort() override {}
	void run ( int* data , int size ) override
	{
		for( int i = 1; i < size - 1; i++ )
		{
			int j = i - 1;
		
			while( j > 0 )
			{
				if( data[ j ] < data[ j - 1 ] )
				{
					int temp = data[ j - 1 ];
					data[ j - 1] = data[ j ];
					data[ j ] = temp;
				}
				j--;
			}
		}
	}	
};

class ShellSort : public ISort
{	
	InsertSort insert_sort;
	public:
	
	ShellSort(){}
	~ShellSort() override {}
	
	void run ( int* data , int size ) override
	{
		int n = 16;	
		int gup = size / n;
		int temp_n = gup - 1;
	
		for( int i = 0; i < n; i++ )
		{	
			while( temp_n > 0 )
			{
				for( int j = 0; j < temp_n; j++ )
				{		
					if( data[ ( j * n ) + i ] > data[ ( ( j + 1) * n ) + i ] )
					{
						int temp = data[ ( ( j + 1) * n ) + i ];
						data[ ( ( j + 1) * n ) + i ] = data[ ( j * n ) + i ];
						data[ ( j * n ) + i ] = temp;
					}	
				}
				temp_n--;
			}
			temp_n = gup - 1;
		}
	
		insert_sort.run( data , size );	
	}
};

void insert_sort ( int* data , int size )
{
	for( int i = 1; i < size - 1; i++ )
	{
		int j = i - 1;
		
		while( j > 0 )
		{
			if( data[ j ] < data[ j - 1 ] )
			{
				int temp = data[ j - 1 ];
				data[ j - 1] = data[ j ];
				data[ j ] = temp;
			}
			j--;
		}
	}
}

void shell_sort ( int* data , int size )
{
	int n = 16;	
	int gup = size / n;
	int temp_n = gup - 1;
	
	for( int i = 0; i < n; i++ )
	{	
		while( temp_n > 0 )
		{
			for( int j = 0; j < temp_n; j++ )
			{		
				if( data[ ( j * n ) + i ] > data[ ( ( j + 1) * n ) + i ] )
				{
					int temp = data[ ( ( j + 1) * n ) + i ];
					data[ ( ( j + 1) * n ) + i ] = data[ ( j * n ) + i ];
					data[ ( j * n ) + i ] = temp;
				}	
			}
			temp_n--;
		}
		temp_n = gup - 1;
	}
	
	insert_sort( data , size );
}

struct TestData
{
	int elements;
	double time;
};

int main ( int argc , char** argv )
{
	std::cout<<"algo6"<<std::endl;
		
	try
	{					
	
		std::vector<TestData> BSort(0);
		std::vector<TestData> InSort(0);
		std::vector<TestData> ShSort(0);
		
		
		
		#define EXP1 1
		#if EXP1
		{
			std::cout << "BubbleSort elements 100 " <<   "\n";
			
			int pool[110] = { 0 };
			
			for( int i = 0; i < 100; i++ )
			{
				pool[ i ] = std::rand( ) % 100;
			}
						
			TesterArray tester( std::make_unique<BubbleSort>() , pool , 100 );
			
			auto start = std::chrono::system_clock::now();
			
			tester.RunTests();
			
			for( int i = 0; i < 100; i++ )
			{
				std::cout<<" "<< pool [ i ];
			}
			std::cout<<std::endl;
			
			auto end = std::chrono::system_clock::now();
       		std::chrono::duration<double> diff = end - start;
       		
       		TestData td;
       		
       		td.elements = 100;
       		td.time = diff.count();
       		
       		BSort.push_back( td );
       		
		}
		#endif
		
		#define EXP2 1
		#if EXP2
		{
			std::cout << "BubbleSort elements 1000 " <<   "\n";
			int pool[1100] = { 0 };
			
			for( int i = 0; i < 1000; i++ )
			{
				pool[ i ] = std::rand( ) % 1000;
			}
						
			TesterArray tester( std::make_unique<BubbleSort>() , pool , 1000 );
			
			auto start = std::chrono::system_clock::now();
			
			tester.RunTests();
			
			for( int i = 0; i < 1000; i++ )
			{
				std::cout<<" "<< pool [ i ];
			}
			std::cout<<std::endl;
			
			auto end = std::chrono::system_clock::now();
       		std::chrono::duration<double> diff = end - start;
       		
       		TestData td;
       		
       		td.elements = 1000;
       		td.time = diff.count();
       		
       		BSort.push_back( td );
       		
		}
		#endif
		
		#define EXP3 1
		#if EXP3
		{
			std::cout << "InsertSort elements 100 " <<   "\n";
			int pool[110] = { 0 };
			
			for( int i = 0; i < 100; i++ )
			{
				pool[ i ] = std::rand( ) % 100;
			}
						
			TesterArray tester( std::make_unique<InsertSort>() , pool , 100 );
			
			auto start = std::chrono::system_clock::now();
			
			tester.RunTests();
			
			for( int i = 0; i < 100; i++ )
			{
				std::cout<<" "<< pool [ i ];
			}
			std::cout<<std::endl;
			
			auto end = std::chrono::system_clock::now();
       		std::chrono::duration<double> diff = end - start;
       		
       		TestData td;
       		
       		td.elements = 100;
       		td.time = diff.count();
       		
       		InSort.push_back( td );       		
		}
		#endif
		
		#define EXP4 1
		#if EXP4
		{
			std::cout << "InsertSort elements 1000 " <<   "\n";
			
			int pool[1100] = { 0 };
			
			for( int i = 0; i < 1000; i++ )
			{
				pool[ i ] = std::rand( ) % 1000;
			}
						
			TesterArray tester( std::make_unique<InsertSort>() , pool , 1000 );
			
			auto start = std::chrono::system_clock::now();
			
			tester.RunTests();
			
			for( int i = 0; i < 1000; i++ )
			{
				std::cout<<" "<< pool [ i ];
			}
			std::cout<<std::endl;
			
			auto end = std::chrono::system_clock::now();
       		std::chrono::duration<double> diff = end - start;
       		
       		TestData td;
       		
       		td.elements = 1000;
       		td.time = diff.count();
       		
       		InSort.push_back( td );
		}
		#endif
		
		#define EXP5 1
		#if EXP5
		{
			std::cout << "ShellSort elements 100 " <<  "\n";
			
			int pool[110] = { 0 };
			
			for( int i = 0; i < 100; i++ )
			{
				pool[ i ] = std::rand( ) % 100;
			}
						
			TesterArray tester( std::make_unique<ShellSort>() , pool , 100 );
			
			auto start = std::chrono::system_clock::now();
			
			tester.RunTests();
			
			for( int i = 0; i < 100; i++ )
			{
				std::cout<<" "<< pool [ i ];
			}
			std::cout<<std::endl;
			
			auto end = std::chrono::system_clock::now();
       		std::chrono::duration<double> diff = end - start;
       		
       		TestData td;
       		
       		td.elements = 100;
       		td.time = diff.count();
       		
       		ShSort.push_back( td );
		}
		#endif
		
		#define EXP6 1
		#if EXP6
		{
			std::cout << "ShellSort elements 1000 " <<  "\n";
			
			int pool[1100] = { 0 };
			
			for( int i = 0; i < 1000; i++ )
			{
				pool[ i ] = std::rand( ) % 1000;
			}
						
			TesterArray tester( std::make_unique<ShellSort>() , pool , 1000 );
			
			auto start = std::chrono::system_clock::now();
			
			tester.RunTests();
			
			for( int i = 0; i < 1000; i++ )
			{
				std::cout<<" "<< pool [ i ];
			}
			std::cout<<std::endl;
			
			auto end = std::chrono::system_clock::now();
       		std::chrono::duration<double> diff = end - start;
       		
       		TestData td;
       		
       		td.elements = 1000;
       		td.time = diff.count();
       		
       		ShSort.push_back( td );
		}
		#endif
		
	
		
		for( auto a : BSort )
		{
			std::cout << "BubbleSort  : elements : " << a.elements << " : time left : " << a.time << " s\n";
		}
		
		for( auto a : InSort )
		{
			std::cout << "InsertSort  : elements : " << a.elements << " : time left : " << a.time << " s\n";
		}
		
		for( auto a : ShSort )
		{
			std::cout << "ShellSort   : elements : " << a.elements << " : time left : " << a.time << "s" <<" N = 16 " << "\n" ;
		}
				
	}
	catch( ... )
	{
		std::cout<<"error"<<std::endl;
	}
	
	

	return 0;
}





