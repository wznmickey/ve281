#include "sort.hpp"

#include <bits/stdc++.h>
#include <cstdlib>
// using namespace std;
using std::cout;
using std::endl;
using std::vector;
template < typename T, typename Compare >
void std_sort(
    std::vector< T > &vector,
    Compare           comp = std::less< T >( ) )
{
    std::sort( vector.begin( ), vector.end( ), comp );
}

int main( )
{
    srand( time( NULL ) );
    vector< int > test1;
    vector< int > test2;
    vector< int > test3;
    cout << "123" << endl;
    for ( int i = 0; i < 10000; i++ )
    {
        test1.push_back( rand( ) );
        test2.push_back( test1 [ i ] );
        test3.push_back( test1 [ i ] );
    }
    cout << "123" << endl;
    std_sort( test1, std::less<>( ) );
    bubble_sort( test2, std::less<>( ) );
    insertion_sort( test3, std::less<>( ) );
    for ( int i = 0; i < 10000; i++ )
    {
        if ( test1 [ i ] != test2 [ i ] )
        {
            cout << "wrong1" << endl;
        }
        if ( test1 [ i ] != test3 [ i ] )
        {
            cout << "wrong2" << endl;
        }
    }
    return 0;
}