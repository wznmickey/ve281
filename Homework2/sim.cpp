#include <bits/stdc++.h>
using namespace std;
const array< pair< string, int >, 7 > input
    = { pair< string, int >( "Blue Tiger", 100 ),
        pair< string, int >( "Gold Monkey", 65 ),
        pair< string, int >( "Red Flamingo", 88 ),
        pair< string, int >( "Glass Frog", 96 ),
        pair< string, int >( "Rainbow Horse", 80 ),
        pair< string, int >( "Honeydew Alligator", 70 ),
        pair< string, int >( "Pink Elephant", 101 ) };
array< pair< string, int >, 10 > selfMap
    = { pair< string, int >( "", 0 ),
        pair< string, int >( "", 0 ),
        pair< string, int >( "", 0 ),
        pair< string, int >( "", 0 ),
        pair< string, int >( "", 0 ),
        pair< string, int >( "", 0 ),
        pair< string, int >( "", 0 ),
        pair< string, int >( "", 0 ),
        pair< string, int >( "", 0 ),
        pair< string, int >( "", 0 ) };
auto getHash( const string &st ) -> int
{
    return ( st [ 0 ] - 'A' ) % 10;
}
auto getT( const string &st ) -> int
{
    return ( st [ 0 ] - 'A' );
}
auto getLinearHash( const string &st, int i ) -> int
{
    return ( getHash( st ) + i ) % 10;
}
auto getQuadraticHash( const string &st, int i ) -> int
{
    return ( getHash( st ) + i * i ) % 10;
}
auto getDoubleHash( const string &st, int i ) -> int
{
    return ( getHash( st ) + ( ( 16 - getT( st ) ) % 6 ) * i ) % 10;
}
auto insert( const string &st, int value ) -> bool
{
    for ( int i = 0; i <= 100; i++ )
    {
        auto hash = getDoubleHash( st, i );
        if ( selfMap.at( hash ) == pair< string, int >( "", 0 ) )
        {
            selfMap.at( hash ) = make_pair( st, value );
            return true;
        }
    }
    return false;
}
auto main( ) -> int
{

    for ( const auto &i : input )
    {
        bool flag = insert( i.first, i.second );
        if ( ! flag )
        {
            cout << "error" << endl;
        }
        for ( int j = 0; j <= 9; j++ )
        {
            cout << j << ":" << selfMap.at( j ).first << " " << selfMap.at( j ).second << endl;
        }
        cout << endl;
    }
    return 0;
}