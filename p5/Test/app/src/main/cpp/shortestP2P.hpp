#include <climits>
#include <iostream>
#include <list>
#include <vector>

#define INF INT_MAX

using namespace std;

class ShortestP2P
{
public:
    ShortestP2P( )
    {
    }

    /**
     * read the graph from a vector, the graph is connected and you don't need to consider negative edges.
     *
     * @param vertex_number: the number of vertices in the graph
     * @param edges: a vector representing the edges in the undirected graph,
     *               each element of it is a vector containing three integers,
     *               the first two integers are the two vertices of an edge,
     *               the third integer is the length of the edge
     */

    void setGraph( int vertex_number, vector< vector< int > * > *edges )
    {
        // TODO: implement this function
        n = vertex_number;
        d.resize(vertex_number);
        for ( auto const &i : ( *edges ) )
        {
//            std::cout<<"123"<<std::endl;
//            if ( d.size( ) < ( *i ) [ 0 ] )
//            {
//                d.resize( ( *i ) [ 0 ] );
//            }
//            if ( d.size( ) < ( *i ) [ 1 ] )
//            {
//                d.resize( ( *i ) [ 1 ] );
//            }
            d [ ( *i ) [ 0 ] ].emplace_back(  ( *i ) [ 1 ],( *i ) [ 2 ] );
            d [ ( *i ) [ 1 ] ].emplace_back(  ( *i ) [ 0 ] ,( *i ) [ 2 ]);

        }
        return;
    }

    /**
     * input: two vertices A and B
     * @param A
     * @param B
     * @return a vector, which contains all the vertices in the shortest path (including A and B)
     */
    vector< int > *distance( unsigned int A, unsigned int B )
    {
        // TODO: implement this function
        return di( A, B );
    };

private:
    // internal data and functions.
    std::vector< std::vector< std::pair< unsigned int, int > > > d;
    unsigned int                                                 n;
    bool                                                         negative = false;
    std::vector< int >                                           distance0;
    bool                                                         invalid = false;
    vector< int >                                               *di( unsigned int &A, unsigned int &B )
    {
        std::vector< int > ans;
        std::vector< int > before;
        ans.resize( n, INF );
        before.resize( n );
        ans [ A ]    = 0;
        before [ A ] = A;
        SimpleList temp;
        auto      *queue = &temp;
        queue->emplace( A, 0 );
        while ( ! queue->empty( ) )
        {
            auto temp = queue->pop_less( );
            for ( auto const &i : d [ temp.first ] )
            {
                if ( i.second + ans [ temp.first ] < ans [ i.first ] )
                {
                    ans [ i.first ] = i.second + ans [ temp.first ];
                    queue->emplace( i.first, ans [ i.first ] );
                    before [ i.first ] = temp.first;
                }
            }
        }
        auto x   = new std::vector< int >;
        auto now = B;
        while ( true )
        {
            x->push_back( now );
            if ( now == before [ now ] )
            {
                break;
            }
            now = before [ now ];
        }
        return x;
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
            for ( auto const &linked : d [ now ] )
            {
                auto end    = linked.first;
                auto weight = linked.second;
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
    };
};
