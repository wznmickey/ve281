#ifndef VE281P1_SORT_HPP
#define VE281P1_SORT_HPP

#include <functional>
#include <stdlib.h>
#include <vector>

const int SEED = 10042; // choose student ID for lack of function to detect time as seed.

template < typename T, typename Compare > void bubble_sort( std::vector< T > &vector, Compare comp = std::less< T >( ) )
{
    auto end = vector.size( );
    for ( decltype( end ) i = 0; i < end; i++ )
    {
        for ( decltype( end ) j = end - 1; j > i; j-- )
        {
            if ( comp( vector [ j ], vector [ j-1 ] ) )
            {
                std::swap( vector [ j ], vector [ j - 1 ]
                );
            }
            // if ( comp( vector.at( j ), vector.at( j - 1 ) ) )
            // {
            //     std::swap( vector.at( j ), vector.at( j - 1 ) );
            // }
        }
    }
    return;
}

template < typename T, typename Compare >
void insertion_sort( std::vector< T > &vector, Compare comp = std::less< T >( ) )
{
    auto end = vector.size( );
    for ( decltype( end ) i = 0; i < end; i++ )
    {
        for ( decltype( end ) j = i + 1; j < end; j++ )
        {
            auto temp = j;
            while ( ( temp >= 1 )
                    && ( comp(
                        vector [ temp ],
                        vector [ temp-1  ] ) ) )
            {
                std::swap(
                    vector [ temp ],
                    vector [ temp - 1 ] );
                temp--;
            }

            // auto temp = j;
            // while ( ( temp >= 1 ) && ( comp( vector.at( temp ), vector.at( temp - 1 ) ) ) )
            // {
            //     std::swap( vector.at( temp ), vector.at( temp - 1 ) );
            //     temp--;
            // }
            break;
        }
    }
    return;
}

template < typename T, typename Compare >
void selection_sort( std::vector< T > &vector, Compare comp = std::less< T >( ) )
{
    auto            end   = vector.size( );
    decltype( end ) front = 0;
    for ( decltype( end ) i = 0; i < end; i++ )
    {
        front = i;
        for ( decltype( end ) j = i + 1; j < end; j++ )
        {
            if ( comp( vector [ j ], vector [ front ] ) )
            {
                front = j;
            }
        }
        std::swap( vector [ front ], vector [ i ] );
        // front = i;
        // for ( decltype( end ) j = i + 1; j < end; j++ )
        // {
        //     if ( comp( vector.at( j ), vector.at( front ) ) )
        //     {
        //         front = j;
        //     }
        // }
        // std::swap( vector.at( front ), vector.at( i ) );
    }
    return;
}

template < typename T, typename Compare >
void merge_sort_re(
    std::vector< T >          &vector,
    decltype( vector.size( ) ) left,
    decltype( vector.size( ) ) right, // sort in [left,right-1], do not sort vector[right].
    Compare                    comp )
{
    if ( right - left <= 1 )
    {
        return;
    }
    if ( right - left == 2 )
    {
        if ( comp( vector [ right - 1 ], vector [ left ] ) )
        {
            std::swap( vector [ right - 1 ], vector [ left ] );
        }
        return;
    }
    auto mid = left + ( right - left ) / 2;
    merge_sort_re( vector, left, mid, comp );
    merge_sort_re( vector, mid, right, comp );
    auto             tempMid  = mid;
    auto             tempLeft = left;
    std::vector< T > temp;
    while ( true )
    {
        if ( ( left >= mid ) || ( tempMid >= right ) )
        {
            break;
        }
        if ( comp( vector [ tempMid ], vector [ left ] ) )
        {
            temp.push_back( std::move( vector [ tempMid ] ) );
            tempMid++;
        }
        else
        {
            temp.push_back( std::move( vector [ left ] ) );
            left++;
        }
    }
    while ( left < mid )
    {
        temp.push_back( std::move( vector [ left ] ) );
        left++;
    }
    while ( tempMid < right )
    {
        temp.push_back( std::move( vector [ tempMid ] ) );
        tempMid++;
    }
    for ( decltype( temp.size( ) ) i = 0; i < temp.size( ); i++ )
    {
        vector [ i + tempLeft ] = temp [ i ];
    }
    return;
    // std::cout<<"a"<<std::endl;
    // std::cout<<left<<" "<<right<<std::endl;
    // if ( right - left <= 1 )
    // {
    //     std::cout<<"e"<<std::endl;
    //     return;
    // }
    // if ( right - left == 2 )
    // {
    //     if ( comp( vector .at ( right-1 ), vector .at ( left ) ) )
    //     {
    //         std::swap( vector .at ( right-1 ), vector .at ( left ) );
    //     }
    //     std::cout<<"f"<<std::endl;
    //     return;
    // }
    // std::cout<<"b"<<std::endl;
    // auto mid = left + ( right - left ) / 2;
    // merge_sort_re( vector, left, mid, comp );
    // merge_sort_re( vector, mid, right, comp );
    // auto             tempMid  = mid;
    // auto             tempLeft = left;
    // std::vector< T > temp;
    // std::cout<<"c"<<std::endl;
    // while ( true )
    // {
    //     if ( ( left >= mid ) || ( tempMid >= right ) )
    //     {
    //         break;
    //     }
    //     if ( comp( vector .at ( left ), vector .at( tempMid ) ) )
    //     {
    //         temp.push_back( std::move( vector .at ( left ) ) );
    //         left++;
    //     }
    //     else
    //     {
    //         temp.push_back(
    //             std::move( vector .at( tempMid ) ) );
    //         tempMid++;
    //     }
    // }
    // std::cout<<"d"<<std::endl;
    // while ( left < mid )
    // {
    //     temp.push_back( std::move( vector.at ( left ) ) );
    //     left++;
    // }
    // while ( tempMid < right )
    // {
    //     temp.push_back( std::move( vector.at( tempMid ) ) );
    //     tempMid++;
    // }
    // for ( decltype( temp.size( ) ) i = 0; i < temp.size( );
    //       i++ )
    // {
    //     vector.at( i + tempLeft ) = temp.at(i );
    // }
    // return;
}

template < typename T, typename Compare >
void quick_sort_extra_re(
    std::vector< T >          &vector,
    decltype( vector.size( ) ) left,
    decltype( vector.size( ) ) right, // sort in [left,right-1], do not sort vector[right].
    Compare                    comp )
{
    if ( right - left <= 1 )
    {
        return;
    }
    if ( right - left == 2 )
    {
        if ( comp( vector [ right - 1 ], vector [ left ] ) )
        {
            std::swap( vector [ right - 1 ], vector [ left ] );
        }
        return;
    }
    // Not allowed to use other lib so use basic rand function that not ensure fully uniform result.
    // Due to RAND_MAX, when there are too much elements, it will not choose pivot with some index.
    decltype( vector.size( ) ) temp  = rand( ) % ( right - left );
    auto                       pivot = vector [ left + temp ];
    std::vector< T >           v1;
    std::vector< T >           v2;
    for ( auto i = left; i < right; i++ )
    {
        if ( i == left + temp )
        {
            continue;
        }
        if ( comp( vector [ i ], pivot ) )
        {
            v1.push_back( vector [ i ] );
        }
        else
        {
            v2.push_back( vector [ i ] );
        }
    }
    quick_sort_extra_re( v1, 0, v1.size( ), comp );
    quick_sort_extra_re( v2, 0, v2.size( ), comp );
    vector.swap( v1 );
    vector.push_back( pivot );
    for ( auto i : v2 )
    {
        vector.push_back( i );
    }
    return;
}

template < typename T, typename Compare >
void quick_sort_inplace_re(
    std::vector< T >          &vector,
    decltype( vector.size( ) ) left,
    decltype( vector.size( ) ) right, // sort in [left,right-1], do not sort vector[right].
    Compare                    comp )
{
    if ( right - left <= 1 )
    {
        return;
    }
    if ( right - left == 2 )
    {
        if ( comp( vector [ right - 1 ], vector [ left ] ) )
        {
            std::swap( vector [ right - 1 ], vector [ left ] );
        }
        return;
    }
    // Not allowed to use other lib so use basic rand function that not ensure fully uniform result.
    // Due to RAND_MAX, when there are too much elements, it will not choose pivot with some index.
    decltype( vector.size( ) ) temp  = rand( ) % ( right - left );
    auto                       pivot = vector [ left + temp ];
    std::swap( vector [ temp + left ], vector [ right - 1 ] );
    temp = left;
    for ( auto i = left; i < right - 1; i++ )
    {
        if ( comp( vector [ i ], pivot ) )
        {
            std::swap( vector [ i ], vector [ temp ] );
            temp++;
        }
    }
    std::swap( vector [ temp ], vector [ right - 1 ] );
    quick_sort_inplace_re( vector, left, temp, comp );
    quick_sort_inplace_re( vector, temp + 1, right, comp );
    return;
}

template < typename T, typename Compare > void merge_sort( std::vector< T > &vector, Compare comp = std::less< T >( ) )
{
    merge_sort_re( vector, 0, vector.size( ), comp );
}

template < typename T, typename Compare >
void quick_sort_extra( std::vector< T > &vector, Compare comp = std::less< T >( ) )
{
    srand( SEED );
    quick_sort_extra_re( vector, 0, vector.size( ), comp );
}
template < typename T, typename Compare >
void quick_sort_inplace( std::vector< T > &vector, Compare comp = std::less< T >( ) )
{
    srand( SEED );
    quick_sort_inplace_re( vector, 0, vector.size( ), comp );
    // TODO: implement
}

#endif // VE281P1_SORT_HPP