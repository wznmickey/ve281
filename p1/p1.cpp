#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <functional>
#include <iostream>
#include <vector>
class Point
{
    friend auto operator>>( std::istream & /*is*/, Point & /*x*/ ) -> std::istream &;
    friend auto operator<<( std::ostream & /*is*/, Point & /*x*/ ) -> std::ostream &;

private:
    long long x { 0 };
    long long y { 0 };

public:
    Point( ) = default;
    auto operator<( const Point &b ) const -> bool
    {
        if ( y != b.y )
        {
            return y < b.y;
        }
        return x < b.x;
    }
    auto operator==( const Point &b ) const -> bool
    {
        return ( ( x == b.x ) && ( y == b.y ) );
    }
    auto operator!=( const Point &b ) const -> bool
    {
        return ! ( *this == b );
    }
    auto operator>( const Point &b ) const -> bool
    {
        return ( ( *this != b ) && ( ! ( *this < b ) ) );
    }
    auto operator<=( const Point &b ) const -> bool
    {
        return ( ! ( *this > b ) );
    }
    auto operator>=( const Point &b ) const -> bool
    {
        return ( ! ( *this < b ) );
    }
    static auto ccw( const Point &p1, const Point &p2, const Point &p3 ) -> int // -1,0,1 for ne,0,po
    {

        // Avoid overflow.
        // ccw = first + second + third
        long long first  = p1.x * ( p2.y - p3.y );
        long long second = p2.x * ( p3.y - p1.y );
        long long third  = p3.x * ( p1.y - p2.y );
        if ( ( first == 0 ) && ( second == 0 ) && ( third == 0 ) ) // sum==0
        {
            return 0;
        }
        if ( ( first >= 0 ) && ( second >= 0 ) && ( third >= 0 ) ) // sum>=0 - sum==0
        {
            return 1;
        }
        if ( ( first <= 0 ) && ( second <= 0 ) && ( third <= 0 ) ) // sum<=0 - sum==0
        {
            return -1;
        }
        std::array< long long, 3 > temp = { first, second, third };
        std::sort( temp.begin( ), temp.end( ) );
        long long Min = temp [ 0 ];
        long long Mid = temp [ 1 ];
        long long Max = temp [ 2 ];
        long long Mix = Min + Max;          // One is >=0, one is <=0, so no overflow.
        if ( ( Mix == 0 ) && ( Mid == 0 ) ) // sum==0
        {
            return 0;
        }
        if ( ( Mix >= 0 ) && ( Mid >= 0 ) ) // sum>=0 - sum==0
        {
            return 1;
        }
        if ( ( Mix <= 0 ) && ( Mid <= 0 ) ) // sum<=0 -sum==0
        {
            return -1;
        }
        long long Final = Mix + Mid; // One is >=0, one is <=0, so no overflow.
        if ( Final > 0 )
        {
            return 1;
        }
        if ( Final == 0 )
        {
            return 0;
        }
        if ( Final < 0 )
        {
            return -1;
        }
        // Should not cout here.
        std::cout << "Error in ccw" << std::endl;
        return 0;
    }
    static auto distance( const Point &p1, const Point &p2, const Point &p3 )
        -> bool // Only useful for the point with same angle.
    {
        auto num1 = std::abs( p2.x - p1.x ) + std::abs( p2.y - p1.y );
        auto num2 = std::abs( p3.x - p1.x ) + std::abs( p3.y - p1.y );
        return num1 > num2;
    }
    static auto cmp( const Point &p1, const Point &p2, const Point &p3 ) -> bool
    {
        auto temp = ccw( p1, p2, p3 );
        if ( temp == 0 )
        {
            return distance( p1, p2, p3 );
        }
        return temp != -1;
    }
    // Not used.
    // auto operator*( const Point &b ) const -> long long
    // {
    //     return ( x * b.x + y * b.y ); // May overflow
    // }
    // auto abs( ) const -> long double
    // {
    //     return sqrt( ( double ) ( ( long double ) x * ( long double ) x + ( long double ) y * ( long double ) y ) );
    // }
    // auto angle( const Point &b ) const -> long double
    // {
    //     return cos( (
    //         double ) ( ( ( long double ) ( x * b.x ) ) / this->abs( ) / b.abs( ) + ( ( long double ) ( y * b.y ) ) /
    //         this->abs( ) / b.abs( ) ) ); // Avoid overflow
    // }
};

auto operator>>( std::istream &is, Point &x ) -> std::istream &
{
    is >> x.x >> x.y;
    return is;
}
auto operator<<( std::ostream &is, Point &x ) -> std::ostream &
{
    is << x.x << " " << x.y;
    return is;
}

auto main( ) -> int
{
    unsigned long long   n = 0;
    std::vector< Point > ans;
    std::cin >> n;
    if ( n == 0 )
    {
        return 0;
    }
    std::vector< Point > map( n );
    Point                P0;
    if ( n >= 1 )
    {
        // Use .at to detect issues and use [] to have better performance
        // std::cin >> map.at( 0 );
        // P0 = map.at( 0 );
        std::cin >> map [ 0 ];
        P0 = map [ 0 ];
    }
    for ( unsigned long long i = 1; i < n; i++ )
    {
        // Use .at to detect issues and use [] to have better performance
        // std::cin >> map.at( i );
        // P0 = std::min( P0, map.at( i ) );
        std::cin >> map [ i ];
        P0 = std::min( P0, map [ i ] );
    }
    for ( unsigned long long i = 0; i < map.size( ); i++ )
    {
        // Use .at to detect issues and use [] to have better performance
        // if ( P0 == map.at( i ) )
        // {
        //     std::swap( map.at( i ), map.at( map.size( ) - 1 ) );
        //     map.pop_back( );
        //     i--;
        // }

        if ( P0 == map [ i ] )
        {
            std::swap( map [ i ], map [ map.size( ) - 1 ] );
            map.pop_back( );
            i--;
        }
    }
    auto temp_cmp = [ P0 ]( auto &&PH1, auto &&PH2 )
    {
        return Point::cmp( P0, std::forward< decltype( PH1 ) >( PH1 ), std::forward< decltype( PH2 ) >( PH2 ) );
    };
    std::sort( map.begin( ), map.end( ), temp_cmp );
    decltype( map.size( ) ) j = 0;
    for ( decltype( map.size( ) ) i = 0; i < map.size( ); i++ )
    {
        // Use .at to detect issues and use [] to have better performance
        // map.at( j ) = map.at( i );
        // j++;
        // while (
        //     ( i + 1 < map.size( ) )
        //     && ( ( ( Point::ccw( P0, map.at( i ), map.at( i + 1 ) ) ) == 0 ) || ( map.at( i ) == map.at( i + 1 ) ) )
        //     )
        // {
        //     i++;
        // }

        map [ j ] = map [ i ];
        j++;
        while ( ( i + 1 < map.size( ) )
                && ( ( ( Point::ccw( P0, map [ i ], map [ i + 1 ] ) ) == 0 ) || ( map [ i ] == map [ i + 1 ] ) ) )
        {
            i++;
        }
    }
    for ( auto i = map.size( ); i > j; i-- )
    {
        map.pop_back( );
    }
    for ( auto i : map )
    {
        // Use .at to detect issues and use [] to have better performance
        // while ( ( ans.size( ) > 1 ) && ( Point::ccw( ans.at( ans.size( ) - 2 ), ans.at( ans.size( ) - 1 ), i ) <= 0 )
        // )
        // {
        //     ans.pop_back( );
        // }

        while ( ( ans.size( ) > 1 ) && ( Point::ccw( ans [ ans.size( ) - 2 ], ans [ ans.size( ) - 1 ], i ) <= 0 ) )
        {
            ans.pop_back( );
        }
        ans.push_back( i );
    }
    std::cout << P0 << std::endl;
    for ( auto i : ans )
    {
        std::cout << i << std::endl;
    }
    return 0;
}