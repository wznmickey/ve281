#include "sort.hpp"

#include <bits/stdc++.h>
#include <cstdlib>
#include <functional>
#include <type_traits>
// using namespace std;
using std::cout;
using std::endl;
using std::pair;
using std::vector;
struct ABC
{
    vector< int > a;
    vector< int > b;
    bool          cmp( int a, int b )
    {
        return a<b;
    }
};
template < typename T, typename Compare > void std_sort( std::vector< T > &vector, Compare comp = std::less< T >( ) )
{
    std::sort( vector.begin( ), vector.end( ), comp );
}
bool cmp( pair< int, int > a, pair< int, int > b )
{
    // return a.first < b.first;
    return std::less< pair< int, int > > { }( a, b );
}

int main( )
{

    // ABC x;
    // ABC *p = &x;
    // bool ( ABC::*func )( int, int ) = &ABC::cmp;
    // std::invoke(&ABC::cmp, x,1,2);

    // auto callback = [p](auto && PH1, auto && PH2) { p->cmp(std::forward<decltype(PH1)>(PH1), std::forward<decltype(PH2)>(PH2)); };
    // auto f = std::bind( &ABC::cmp,x,std::placeholders::_1,std::placeholders::_2 );
    // auto ans = callback(1,2);
    // sort( x.a.begin( ), x.a.end( ), f );
    srand( time( nullptr ) );
    for ( int aaaaaa = 0; aaaaaa <= 100; aaaaaa++ )
    {
        vector< pair< int, int > > test1;
        vector< pair< int, int > > test2;
        vector< pair< int, int > > test3;
        vector< pair< int, int > > test4;
        vector< pair< int, int > > test5;
        vector< pair< int, int > > test6;
        vector< pair< int, int > > test7;

        cout << "123" << endl;
        for ( int i = 0; i < 1000; i++ )
        {
            auto temp = std::make_pair( rand( )%5 ,i );
            test1.push_back( temp );
            test2.push_back( test1 [ i ] );
            test3.push_back( test1 [ i ] );
            test4.push_back( test1 [ i ] );
            test5.push_back( test1 [ i ] );
            test6.push_back( test1 [ i ] );
            test7.push_back( test1 [ i ] );
        }

        cout << "1234" << endl;
        std_sort( test1, cmp );
        cout << "12345" << endl;
        bubble_sort( test2, cmp );
        cout << "123456" << endl;
        insertion_sort( test3, cmp );
        cout << "1234567" << endl;
        selection_sort( test4, cmp );
        cout << "12345678" << endl;
        merge_sort( test5, cmp );
        cout << "123456789" << endl;
        quick_sort_extra( test6, cmp );
        cout << "1234567890" << endl;
        quick_sort_inplace( test7, cmp );
        cout << "12345678901" << endl;

        for ( int i = 0; i < 1000; i++ )
        {
            // cout<<test2[i].first<<" "<<test2[i].second<<endl;
            // cout<<test5[i].first<<" "<<test5[i].second<<endl;
            // cout<<test3[i].first<<"
            // "<<test3[i].second<<endl;
            // cout<<test4[i].first<<"
            // "<<test4[i].second<<endl;
            // if ( test1 [ i ].first != test2 [ i ].first )
            // {
            //     cout << "wrong1" << endl;
            // }
            if ( test1 [ i ].first != test3 [ i ].first )
            {
                cout << "wrong2" << endl;
            }
            if ( test1 [ i ].first != test4 [ i ].first )
            {
                cout << "wrong3" << endl;
            }
            if ( test1 [ i ].first != test5 [ i ].first )
            {
                cout << "wrong3" << endl;
            }
            if ( test1 [ i ].first != test6 [ i ].first )
            {
                cout << "wrong4" << endl;
            }
            if ( test1 [ i ].first != test7 [ i ].first )
            {
                cout << "wrong5" << endl;
            }
            if ( test1 [ i ] != test2 [ i ] )
            {
                cout << "wrong1" << endl;
            }
            if ( test1 [ i ] != test3 [ i ] )
            {
                cout << "wrong2" << endl;
            }
            if ( test1 [ i ] != test4 [ i ] )
            {
                cout << "wrong3" << endl;
            }
            if ( test2 [ i ] != test5 [ i ] )
            {
                cout << "wrong3" << endl;
            }
            if ( test1 [ i ] != test6 [ i ] )
            {
                cout << "wrong4" << endl;
            }
            if ( test1 [ i ] != test7 [ i ] )
            {
                cout << "wrong5" << endl;
            }
        }
    }
    return 0;
}