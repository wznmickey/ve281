#include <algorithm>
#include <climits>
#include <cstddef>
#include <iostream>
#include <list>
#include <vector>
// You are not allowed to include additional libraries, either in shortestP2P.hpp or shortestP2P.cc

#define INF INT_MAX

using namespace std;

class ShortestP2P
{
public:
    ShortestP2P( )
    {
    }

    /* Read the graph from stdin
     * The input has the following format:
     *
     * Firstline: 1 unsigned int, the total number of verticies, X.
     * Secondline: 1 unsigned int, the total number of edges between vertices, Y.
     * A set of Y lines, each line contains tuple of 2 unsigned int and 1 int (not unsigned int!), in the format of:
     * A(point 1, unsigned) B(point 2, unsigned) dist(distance, int)
     *
     * Example:
     * 4
     * 4
     * 0 1 5
     * 1 2 -1
     * 2 3 4
     * 3 1 6
     *
     *
     *
     *
     * Vertices that are not connected have a infinitly large distance. You may use INF (previously defined at the top
     * of this cope snippet) for infinitly large distance.
     *
     * Special: when the graph is not proper, where there exist any pair of vertices whose minimum distance does not
     * exist, terminate immediately by printing: cout << "Invalid graph. Exiting." << endl;
     *
     * Note: vertex pairs that are not connected, which have infinitely large distances are not considered cases where
     * "minimum distances do not exist".
     */
    void readGraph( )
    {

        unsigned int x;
        unsigned int y;
        scanf( "%u", &x );
        // std::cin >> x;
        // std::vector< std::pair< unsigned int, int > > temp;
        // temp.reserve( x );
        // d.resize( x, temp );
        // d.resize( x + 1, std::vector< int >( x + 1, INF ) );
        d = new int *[ x + 1 ];
        for ( unsigned int i = 0; i < x + 1; ++i )
        {
            d [ i ] = new int [ x + 1 ];
        }

        for ( unsigned int i = 0; i < x + 1; i++ )
        {
            for ( unsigned int j = 0; j < x + 1; j++ )
            {
                d [ i ][ j ] = INF;
            }
        }
        for ( unsigned int i = 0; i <= x; i++ )
        {
            // d.emplace_back( std::vector<int  > { } );
            // d [ i ].resize( x );
            linked.emplace_back( std::vector< int > { } );
            linked [ i ].reserve( x + 1 );
        }
        caled.resize( x, false );
        n = x;
        // ans = new int [ n ];
        // for ( unsigned int i = 0; i < n; i++ )
        // {
        //     ans [ i ] = INF;
        // }
        scanf( "%u", &y );
        // std::cin >> y;
        for ( auto i = y; i > 0; i-- )
        {
            unsigned int a = 0;
            unsigned int b = 0;
            int          c = 0;
            scanf( "%u%u%d", &a, &b, &c );
            // std::cin >> a >> b >> c;
            // d [ a ].emplace_back( b, c );
            // d [ a ].emplace_back( b, c );
            d [ a ][ b ] = c;
            linked [ a ].emplace_back( b );

            if ( c < 0 )
            {
                negative = true;
            }
            // [[unlikely]] if ( ( a == b ) && ( c < 0 ) )
            if ( ( a == b ) && ( c < 0 ) )
            {
                invalid = true;
                std::cout << "Invalid graph. Exiting." << std::endl;
                return;
            }
        }
        if ( negative )
        {
            // d.resize( x + 1 );
            for ( decltype( x ) i = 0; i < x; i++ )
            {
                d [ x ][ i ] = 0;
                linked [ x ].emplace_back( i );
            }

            distance0.resize( n + 1, INF );
            distance0 [ n ] = 0;
            if ( ! spfa( distance0 ) )
            {
                invalid = true;
                std::cout << "Invalid graph. Exiting." << std::endl;
                return;
            }
            for ( decltype( x ) i = 0; i < x; i++ )
            {
                for ( auto &j : linked [ i ] )
                {
                    d [ i ][ j ] = d [ i ][ j ] + distance0 [ i ] - distance0 [ j ];
                }
            }
            // d.resize( x );
        }
        // for ( unsigned int A = 0; A < x; A++ )
        // {
        //     d [ A ][ A ] = 0;
        //     Heap  temp( n );
        //     auto *queue = &temp;
        //     queue->emplace( A, 0 );
        //     while ( ! queue->empty( ) )
        //     {
        //         auto temp = queue->pop_less( );
        //         // std::cout<<temp.first<<std::endl;
        //         // if ( visited [ temp.first ] )
        //         //     continue;
        //         // visited [ temp.first ] = true;
        //         for ( auto const &i : linked [ temp.first ] )
        //         {
        //             // std::cout<<i<<std::endl;
        //             if ( temp.second + d [ temp.first ][ i ] <= d [ A ][ i ] )
        //             {
        //                 d [ A ][ i ] = temp.second + d [ temp.first ][ i ];
        //                 queue->emplace( i, d [ A ][ i ] );
        //             }
        //         }
        //     }
        // }
        for ( unsigned int i = 0; i < n; i++ )
        {
            for ( unsigned int j = 0; j < n; j++ )
            {
                for ( unsigned int k = 0; k < n; k++ )
                {
                    if ( ( d [ j ][ i ] != INF ) && ( ( d [ i ][ k ] ) != INF ) && ( ( d [ j ][ k ] ) != INF ) )
                    {
                        if ( d [ j ][ i ] + d [ i ][ k ] < d [ j ][ k ] )
                            d [ j ][ k ] = d [ j ][ i ] + d [ i ][ k ];
                    }
                    else if ( ( ( d [ j ][ k ] ) == INF ) && ( d [ j ][ i ] != INF ) && ( ( d [ i ][ k ] ) != INF ) )
                        d [ j ][ k ] = d [ j ][ i ] + d [ i ][ k ];
                }
            }
        }

        return;
    }

    /* Input: 2 vertices A and B
     * Output: distance between them.
     * cout << dist << endl;
     *
     * When the A and B are not connected print INF:
     * cout << "INF" << endl;
     */
    void distance( unsigned int A, unsigned int B )
    {
        if ( invalid )
            return;
        // di( A, B );
        // di( A, B );

        if ( d [ A ][ B ] != INF )
        {
            if ( negative )
            {
                printf( "%d\n", d [ A ][ B ] + distance0 [ B ] - distance0 [ A ] );
            }
            else
            {
                printf( "%d\n", d [ A ][ B ] );
            }
            // std::cout << ans [ B ] << std::endl;
        }
        else
        {
            printf( "INF\n" );
            // std::cout << "INF" << std::endl;
        }
        return;
    }

private:
    // internal data and functions.
    // std::vector< std::vector< int > > d;
    std::vector< std::vector< int > > linked;
    int                             **d;
    // int * linked;
    // std::pair<unsigned,int>
    unsigned int n;
    // int                *ans;
    bool                negative = false;
    std::vector< int >  distance0;
    bool                invalid = false;
    std::vector< bool > caled;
    void                di( unsigned int &A, unsigned int &B )
    {
        if ( caled [ A ] )
        {
            if ( d [ A ][ B ] != INF )
            {
                if ( negative )
                {
                    printf( "%d\n", d [ A ][ B ] + distance0 [ B ] - distance0 [ A ] );
                }
                else
                {
                    printf( "%d\n", d [ A ][ B ] );
                }
                // std::cout << ans [ B ] << std::endl;
            }
            else
            {
                printf( "INF\n" );
                // std::cout << "INF" << std::endl;
            }
            return;
        }

        // static std::vector< int >  ans;
        // int ans[n];

        // static std::vector< bool > visited;
        // visited.reserve(n);
        // ans.resize(n,INF);
        // for (decltype(n) i=0;i<n;i++)
        // {
        //     // visited[i] = false;
        //     ans[i] = INF;
        // }
        // visited.resize( n, false );
        // ans.resize( n, INF );
        d [ A ][ A ] = 0;
        static Heap temp( n );
        auto       *queue = &temp;
        queue->emplace( A, 0 );
        while ( ! queue->empty( ) )
        {

            auto temp = queue->pop_less( );
            // std::cout<<temp.first<<std::endl;
            // if ( visited [ temp.first ] )
            //     continue;
            // visited [ temp.first ] = true;
            for ( auto const &i : linked [ temp.first ] )
            {
                // std::cout<<i<<std::endl;
                if ( temp.second + d [ temp.first ][ i ] <= d [ A ][ i ] )
                {
                    d [ A ][ i ] = temp.second + d [ temp.first ][ i ];
                    queue->emplace( i, d [ A ][ i ] );
                }
            }
        }
        if ( d [ A ][ B ] != INF )
        {
            if ( negative )
            {
                printf( "%d\n", d [ A ][ B ] + distance0 [ B ] - distance0 [ A ] );
            }
            else
            {
                printf( "%d\n", d [ A ][ B ] );
            }
            // std::cout << ans [ B ] << std::endl;
        }
        else
        {
            printf( "INF\n" );
            // std::cout << "INF" << std::endl;
        }
        // for (unsigned int i=0;i<n;i++) ans[i]=INF;
        // d [ A ].resize( n );
        // for ( unsigned int i = 0; i < n; i++ )
        // {
        //     d [ A ][ i ] = std::make_pair( i, ans [ i ] );
        //     ans [ i ]    = INF;
        // }
        caled [ A ] = true;
        return;
    }
    bool spfa( std::vector< int > &distance )
    {
        list< unsigned int > q;
        std::vector< bool >  visit;
        visit.resize( n + 1, false );
        visit [ n ] = true;

        std::vector< unsigned int > count;
        count.resize( n + 1, 0 );

        q.push_back( n );

        while ( ! q.empty( ) )
        {
            auto now      = q.front( );
            visit [ now ] = false;
            q.pop_front( );
            for ( auto const &linked : linked [ now ] )
            {
                const auto &end    = linked;
                const auto &weight = d [ now ][ linked ];
                if ( distance [ end ] > distance [ now ] + weight )
                {
                    distance [ end ] = distance [ now ] + weight;
                    count [ end ]    = count [ now ] + 1;
                    if ( count [ end ] >= n + 1 )
                    {
                        return false;
                    }
                    if ( ! visit [ end ] )
                    {
                        q.push_back( end );
                        visit [ end ] = true;
                    }
                }
            }
        }
        return true;
    }

    // void spfa2( unsigned int &A, unsigned int &B )
    // {

    //     if ( caled [ A ] )
    //     {
    //         if ( d [ A ][ B ].second != INF )
    //         {

    //             {
    //                 printf( "%d\n", d [ A ][ B ].second );
    //             }
    //             // std::cout << ans [ B ] << std::endl;
    //         }
    //         else
    //         {
    //             printf( "INF\n" );
    //             // std::cout << "INF" << std::endl;
    //         }
    //         return;
    //     }
    //     list< unsigned int > q;
    //     std::vector< bool >  visit;
    //     visit.resize( n, false );
    //     visit [ A ] = true;

    //     // std::vector< unsigned int > count;
    //     // count.resize( n , 0 );

    //     q.push_back( A );

    //     while ( ! q.empty( ) )
    //     {
    //         auto now      = q.front( );
    //         visit [ now ] = false;
    //         q.pop_front( );
    //         for ( auto const &linked : d [ now ] )
    //         {
    //             auto end    = linked.first;
    //             auto weight = linked.second;
    //             if ( ans [ end ] > ans [ now ] + weight )
    //             {
    //                 ans [ end ] = ans [ now ] + weight;
    //                 // count [ end ]    = count [ now ] + 1;
    //                 // if ( count [ end ] >= n + 1 )
    //                 // {
    //                 //     return false;
    //                 // }
    //                 if ( ! visit [ end ] )
    //                 {
    //                     q.push_back( end );
    //                     visit [ end ] = true;
    //                 }
    //             }
    //         }
    //     }

    //     if ( ans [ B ] != INF )
    //     {

    //         printf( "%d\n", ans [ B ] );

    //         // std::cout << ans [ B ] << std::endl;
    //     }
    //     else
    //     {
    //         printf( "INF\n" );
    //         // std::cout << "INF" << std::endl;
    //     }
    //     d [ A ].resize( n );
    //     for ( unsigned int i = 0; i < n; i++ )
    //     {
    //         d [ A ][ i ] = std::make_pair( i, ans [ i ] );
    //         ans [ i ]    = INF;
    //     }
    //     caled [ A ] = true;
    //     return;
    // }
    class Container
    {
    public:
        virtual bool                           empty( )    = 0;
        virtual size_t                         size( )     = 0;
        virtual std::pair< unsigned int, int > pop_less( ) = 0;
        // virtual void                           push( std::pair< unsigned int, int > &pair ) = 0;
        virtual void emplace( unsigned int point, int weight ) = 0;
    };
    class SimpleList : public Container
    {
    public:
        bool empty( ) override
        {
            return ( data.empty( ) );
        }
        size_t size( ) override
        {
            return ( data.size( ) );
        }
        std::pair< unsigned int, int > pop_less( ) override
        {
            auto minIt   = data.begin( );
            auto minData = *minIt;
            for ( auto i = data.begin( ); i != data.end( ); i++ )
            {
                if ( i->second < minData.second )
                {
                    minIt   = i;
                    minData = *i;
                }
            }
            data.erase( minIt );
            return minData;
        }
        // void push( std::pair< unsigned int, int > &pair ) override
        // {
        //     data.push_back( pair );
        //     return;
        // }
        void emplace( unsigned int point, int weight ) override
        {
            data.emplace_back( point, weight );
            return;
        }

    protected:
        std::list< std::pair< unsigned int, int > > data { };
    };
    class Heap : public Container
    {
    protected:
        std::vector< std::pair< unsigned int, int > > data { { 0, 0 } };

    public:
        Heap( unsigned int x )
        {
            data.reserve( x );
            return;
        }
        bool empty( )
        {
            return ( data.size( ) == 1 );
        }
        size_t size( ) override
        {
            return data.size( ) - 1;
        }
        void emplace( unsigned int point, int weight ) override
        {
            decltype( data.size( ) ) id   = 0;
            bool                     flag = false;
            for ( decltype( data.size( ) ) i = 1; i < data.size( ); i++ )
            {
                if ( data [ i ].first == point )
                {
                    data [ i ].second = weight;
                    id                = i;
                    flag              = true;
                    break;
                }
            }
            if ( ! flag )
            {
                data.emplace_back( point, weight );
                id = data.size( ) - 1;
            }
            while ( id > 1 && data [ id / 2 ].second > data [ id ].second )
            {
                swap( data [ id / 2 ], data [ id ] );
                id /= 2;
            }
        }
        std::pair< unsigned int, int > pop_less( ) override
        {
            auto size = data.size( ) - 1;
            swap( data [ 1 ], data [ size ] );
            auto ans = data [ size ];
            data.pop_back( );
            size--;
            decltype( size ) id = 1;
            for ( decltype( size ) j = 2 * id; j <= size; j = 2 * id )
            {
                if ( j < size && data [ j ].second > data [ j + 1 ].second )
                    j++;
                if ( data [ id ].second <= data [ j ].second )
                    break;
                swap( data [ id ], data [ j ] );
                id = j;
            }
            return ans;
        }
    };
    class FHeap : public Container
    {
    protected:
        class Node
        {
        public:
            Node *child;
            Node *parent;

            Node        *left;
            Node        *right;
            unsigned int degree;
            bool         mark;

            unsigned int point;
            int          weight;
        };
        Node  *minNode { nullptr };
        size_t n { 0 };

    public:
        FHeap( )
        {
        }
        void emplace( unsigned int point, int weight )
        {
            auto *x   = new Node;
            x->point  = point;
            x->weight = weight;
            x->degree = 0;
            x->parent = nullptr;
            x->child  = nullptr;
            x->mark   = false;
            if ( minNode == nullptr )
            {
                minNode  = x;
                x->left  = x;
                x->right = x;
            }
            else
            {
                x->left              = minNode;
                x->right             = minNode->right;
                minNode->right->left = x;
                minNode->right       = x;
                if ( minNode->weight > x->weight )
                {
                    minNode = x;
                }
            }
            ++n;
        }
        bool empty( ) override
        {
            return ( n == 0 );
        }
        size_t size( ) override
        {
            return ( n );
        }
        std::pair< unsigned int, int > pop_less( ) override
        {
            auto ans = std::make_pair( minNode->point, minNode->weight );

            if ( minNode == minNode->right )
            {
            }

            return ans;
        }
    };
};