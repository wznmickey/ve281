#ifndef VE281P1_SORT_HPP
#define VE281P1_SORT_HPP

#include <functional>
#include <stdlib.h>
#include <vector>

template < typename T, typename Compare >
void bubble_sort(
    std::vector< T > &vector,
    Compare           comp = std::less< T >( ) )
{
    int end = vector.size( );
    for ( int i = 0; i < end; i++ )
    {
        for ( int j = end - 1; j > i; j-- )
        {
            if ( comp( vector [ j ], vector [ j - 1 ] ) )
            {
                std::swap( vector [ j ], vector [ j - 1 ] );
            }
        }
    }
    return;
}

template < typename T, typename Compare >
void insertion_sort(
    std::vector< T > &vector,
    Compare           comp = std::less< T >( ) )
{
    int front;
    for ( int i = 0; i < vector.size( ); i++ )
    {
        front = i;
        for ( int j = i + 1; j < vector.size( ); j++ )
        {
            if ( ! comp( vector [ front ], vector [ j ] ) )
            {
                front = j;
            }
        }
        std::swap( vector [ front ], vector [ i ] );
    }
    return;
}

template < typename T, typename Compare >
void selection_sort(
    std::vector< T > &vector,
    Compare           comp = std::less< T >( ) )
{
    // TODO: implement
}

template < typename T, typename Compare >
void merge_sort(
    std::vector< T > &vector,
    Compare           comp = std::less< T >( ) )
{
    // TODO: implement
}

template < typename T, typename Compare >
void quick_sort_extra(
    std::vector< T > &vector,
    Compare           comp = std::less< T >( ) )
{
    // TODO: implement
}
template < typename T, typename Compare >
void quick_sort_inplace(
    std::vector< T > &vector,
    Compare           comp = std::less< T >( ) )
{
    // TODO: implement
}

#endif // VE281P1_SORT_HPP