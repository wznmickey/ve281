#include <algorithm>
#include <cassert>
#include <climits>
#include <cstddef>
#include <forward_list>
#include <functional>
#include <iostream>
#include <iterator>
#include <set>
#include <stdexcept>
#include <tuple>
#include <vector>

/**
 * An abstract template base of the KDTree class
 */
template < typename... > class KDTree;

/**
 * A partial template specialization of the KDTree class
 * The time complexity of functions are based on n and k
 * n is the size of the KDTree
 * k is the number of dimensions
 * @typedef Key         key type
 * @typedef Value       value type
 * @typedef Data        key-value pair
 * @static  KeySize     k (number of dimensions)
 */
template < typename ValueType, typename... KeyTypes > class KDTree< std::tuple< KeyTypes... >, ValueType >
{
public:
    typedef std::tuple< KeyTypes... > Key;
    typedef ValueType                 Value;
    typedef std::pair< Key, Value >   Data;
    static inline constexpr size_t    KeySize = std::tuple_size< Key >::value;
    static_assert( KeySize > 0, "Can not construct KDTree with zero dimension" );

protected:
    struct Node
    {
        Data  data;
        Node *parent;
        Node *left  = nullptr;
        Node *right = nullptr;

        Node( const Key &key, const Value &value, Node *parent )
            : data( key, value )
            , parent( parent )
        {
        }

        const Key &key( )
        {
            return data.first;
        }

        Value &value( )
        {
            return data.second;
        }
    };

public:
    /**
     * A bi-directional iterator for the KDTree
     * ! ONLY NEED TO MODIFY increment and decrement !
     */
    class Iterator
    {
    private:
        KDTree *tree;
        Node   *node;

        Iterator( KDTree *tree, Node *node )
            : tree( tree )
            , node( node )
        {
        }

        Node *leftMost( Node *node )
        {
            while ( node->left != nullptr )
            {
                node = node->left;
            }
            return node;
        }
        Node *rightMost( Node *node )
        {
            while ( node->right != nullptr )
            {
                node = node->right;
            }
            return node;
        }

        /**
         * Increment the iterator
         * Time complexity: O(log n)
         */
        void increment( )
        {
            // TODO: implement this function
            if ( node->right != nullptr )
            {
                node = leftMost( node->right );
                return;
            }
            else
            {
                if ( node == rightMost( tree->root ) )
                {
                    node = nullptr;
                    return;
                }
                if ( ( node->parent != nullptr ) && ( node->parent->left == node ) )
                {
                    node = node->parent;
                    return;
                }
                node = node->parent;

                while ( ( node->parent != nullptr ) && ( node->parent->right == node ) )
                {
                    node = node->parent;
                }
                if ( ( node->parent != nullptr ) && ( node->parent->left == node ) )
                {
                    node = node->parent;
                }
            }
        }

        /**
         * Decrement the iterator
         * Time complexity: O(log n)
         */
        void decrement( )
        {
            // TODO: implement this function
            if ( node == nullptr )
            {
                node = rightMost( tree->root );
                return;
            }
            if ( node->left != nullptr )
            {
                node = rightMost( node->left );
                return;
            }
            else
            {
                if ( node == leftMost( tree->root ) )
                {
                    node = nullptr;
                    return;
                }
                if ( ( node->parent != nullptr ) && ( node->parent->right == node ) )
                {
                    node = node->parent;
                    return;
                }
                node = node->parent;
                while ( ( node->parent != nullptr ) && ( node->parent->left == node ) )
                {
                    node = node->parent;
                }
                if ( ( node->parent != nullptr ) && ( node->parent->right == node ) )
                {
                    node = node->parent;
                }
            }
        }

    public:
        friend class KDTree;

        Iterator( ) = delete;

        Iterator( const Iterator & ) = default;

        Iterator &operator=( const Iterator & ) = default;

        Iterator &operator++( )
        {
            increment( );
            return *this;
        }

        Iterator operator++( int )
        {
            Iterator temp = *this;
            increment( );
            return temp;
        }

        Iterator &operator--( )
        {
            decrement( );
            return *this;
        }

        Iterator operator--( int )
        {
            Iterator temp = *this;
            decrement( );
            return temp;
        }

        bool operator==( const Iterator &that ) const
        {
            return node == that.node;
        }

        bool operator!=( const Iterator &that ) const
        {
            return node != that.node;
        }

        Data *operator->( )
        {
            return &( node->data );
        }

        Data &operator*( )
        {
            return node->data;
        }
    };

protected:                     // DO NOT USE private HERE!
    Node  *root     = nullptr; // root of the tree
    size_t treeSize = 0;       // size of the tree

    /**
     * Compare two keys on a dimension
     * Time Complexity: O(1)
     * @tparam DIM comparison dimension
     * @tparam Compare
     * @param a
     * @param b
     * @param compare
     * @return relationship of two keys on a dimension with the compare function
     */
    template < size_t DIM, typename Compare >
    static bool compareKey( const Key &a, const Key &b, Compare compare = Compare( ) )
    {
        if ( std::get< DIM >( a ) != std::get< DIM >( b ) )
        {
            return compare( std::get< DIM >( a ), std::get< DIM >( b ) );
        }
        return compare( a, b );
    }

    template < size_t DIM, typename Compare >
    static bool compareKeyTest( const Key &a, const Key &b, Compare compare = Compare( ) )
    {
        return compare( std::get< DIM >( a ), std::get< DIM >( b ) );
    }

    template < size_t DIM > static bool compareKey( const std::pair< Key, Value > &a, const std::pair< Key, Value > &b )
    {
        return compareKey< DIM, std::less<> >( a.first, b.first );
    }

    template < size_t DIM, typename Compare >
    static bool compareKeySpecial( const Key &a, const Key &b, Compare compare = Compare( ) )
    {
        return compare( std::get< DIM >( a ), std::get< DIM >( b ) );
    }

    template < size_t DIM > Node *find( const Key &key, Node *node )
    {
        constexpr size_t DIM_NEXT = ( DIM + 1 ) % KeySize;
        // TODO: implement this function

        if ( node == nullptr )
        {
            return nullptr;
        }
        if ( key == node->data.first )
        {
            return node;
        }
        if ( compareKeySpecial< DIM, std::less<> >( key, node->data.first ) )
        {
            return find< DIM_NEXT >( key, node->left );
        }
        return find< DIM_NEXT >( key, node->right );
    }

    /**
     * Insert the key-value pair, if the key already exists, replace the value only
     * Time Complexity: O(k log n)
     * @tparam DIM current dimension of node
     * @param key
     * @param value
     * @param node
     * @param parent
     * @return whether insertion took place (return false if the key already exists)
     */

    template < size_t DIM > bool insert( const Key &key, const Value &value, Node *&node, Node *parent )
    {
        if ( node == nullptr )
        {
            treeSize++;
            node = new Node( key, value, parent );
            return true;
        }
        constexpr size_t DIM_NEXT = ( DIM + 1 ) % KeySize;
        // TODO: implement this function

        if ( key == node->data.first )
        {
            node->data.second = value;
            return false;
        }
        if ( compareKeySpecial< DIM, std::less<> >( key, node->data.first ) )
        {
            return insert< DIM_NEXT >( key, value, node->left, node );
        }
        return insert< DIM_NEXT >( key, value, node->right, node );
    }

    /**
     * Compare two nodes on a dimension
     * Time Complexity: O(1)
     * @tparam DIM comparison dimension
     * @tparam Compare
     * @param a
     * @param b
     * @param compare
     * @return the minimum / maximum of two nodes
     */
    template < size_t DIM, typename Compare > static Node *compareNode( Node *a, Node *b, Compare compare = Compare( ) )
    {
        if ( ! a )
            return b;
        if ( ! b )
            return a;
        return compareKey< DIM, Compare >( a->key( ), b->key( ), compare ) ? a : b;
    }
    template < size_t DIM > static Node *compareNode( Node *a, Node *b )
    {
        return compareNode< DIM, std::less<> >( a, b );
    }

    static bool sameKey( const std::pair< Key, Value > &a, const std::pair< Key, Value > &b )
    {
        return ( a.first == b.first );
    }

    /**
     * Find the minimum node on a dimension
     * Time Complexity: ?
     * @tparam DIM_CMP comparison dimension
     * @tparam DIM current dimension of node
     * @param node
     * @return the minimum node on a dimension
     */
    template < size_t DIM_CMP, size_t DIM > Node *findMin( Node *node )
    {
        constexpr size_t DIM_NEXT = ( DIM + 1 ) % KeySize;
        // TODO: implement this function
        if ( node == nullptr )
        {
            return node;
        }
        auto temp1 = findMin< DIM_CMP, DIM_NEXT >( node->left );
        if ( DIM != DIM_CMP )
        {
            temp1 = compareNode< DIM_CMP, std::less<> >( temp1, findMin< DIM_CMP, DIM_NEXT >( node->right ) );
        }
        return compareNode< DIM_CMP, std::less<> >( temp1, node );
    }

    /**
     * Find the maximum node on a dimension
     * Time Complexity: ?
     * @tparam DIM_CMP comparison dimension
     * @tparam DIM current dimension of node
     * @param node
     * @return the maximum node on a dimension
     */
    template < size_t DIM_CMP, size_t DIM > Node *findMax( Node *node )
    {
        constexpr size_t DIM_NEXT = ( DIM + 1 ) % KeySize;
        // TODO: implement this function
        if ( node == nullptr )
        {
            return node;
        }
        auto temp1 = findMax< DIM_CMP, DIM_NEXT >( node->right );
        if ( DIM != DIM_CMP )
        {
            temp1 = compareNode< DIM_CMP, std::greater<> >( temp1, findMax< DIM_CMP, DIM_NEXT >( node->left ) );
        }

        return compareNode< DIM_CMP, std::greater<> >( temp1, node );
    }

    template < size_t DIM > Node *findMinDynamic( size_t dim )
    {
        constexpr size_t DIM_NEXT = ( DIM + 1 ) % KeySize;
        if ( dim >= KeySize )
        {
            dim %= KeySize;
        }
        if ( dim == DIM )
            return findMin< DIM, 0 >( root );
        return findMinDynamic< DIM_NEXT >( dim );
    }

    template < size_t DIM > Node *findMaxDynamic( size_t dim )
    {
        constexpr size_t DIM_NEXT = ( DIM + 1 ) % KeySize;
        if ( dim >= KeySize )
        {
            dim %= KeySize;
        }
        if ( dim == DIM )
            return findMax< DIM, 0 >( root );
        return findMaxDynamic< DIM_NEXT >( dim );
    }

    /**
     * Erase a node with key (check the pseudocode in project description)
     * Time Complexity: max{O(k log n), O(findMin)}
     * @tparam DIM current dimension of node
     * @param node
     * @param key
     * @return nullptr if node is erased, else the (probably) replaced node
     */
    template < size_t DIM > Node *erase( Node *node, const Key &key )
    {
        constexpr size_t DIM_NEXT = ( DIM + 1 ) % KeySize;
        // TODO: implement this function
        if ( node == nullptr )
        {
            return nullptr;
        }
        if ( key == node->data.first )
        {
            if ( ( ( node->left ) == nullptr ) && ( ( node->right ) == nullptr ) )
            {
                delete node;
                treeSize--;
                return nullptr;
            }
            if ( node->right != nullptr )
            {
                Node *minNode = findMin< DIM, DIM_NEXT >( node->right );
                node->data    = minNode->data;
                node->right   = erase< DIM_NEXT >( node->right, minNode->data.first );
            }
            else
            {
                Node *maxNode = findMax< DIM, DIM_NEXT >( node->left );
                node->data    = maxNode->data;
                node->left    = erase< DIM_NEXT >( node->left, maxNode->data.first );
            }
        }
        else
        {
            if ( compareKeySpecial< DIM, std::less<> >( key, node->data.first ) )
            {
                node->left = erase< DIM_NEXT >( node->left, key );
            }
            else
            {
                node->right = erase< DIM_NEXT >( node->right, key );
            }
        }
        return node;
    }

    template < size_t DIM > Node *eraseDynamic( Node *node, size_t dim )
    {
        constexpr size_t DIM_NEXT = ( DIM + 1 ) % KeySize;
        if ( dim >= KeySize )
        {
            dim %= KeySize;
        }
        if ( dim == DIM )
            return erase< DIM >( node, node->key( ) );
        return eraseDynamic< DIM_NEXT >( node, dim );
    }

    // TODO: define your helper functions here if necessary
public:
    KDTree( ) = default;

    /**
     * Time complexity: O(kn log n)
     * @param v we pass by value here because v need to be modified
     */
    template < size_t DIM >
    Node *KDTree_help(
        std::vector< std::pair< Key, Value > >                          &v,
        Node                                                            *parent,
        const typename std::vector< std::pair< Key, Value > >::iterator &left,
        const typename std::vector< std::pair< Key, Value > >::iterator &right )
    {
        constexpr size_t DIM_NEXT = ( DIM + 1 ) % KeySize;
        if ( left >= right )
        {
            return nullptr;
        }
        if ( std::distance( left, right ) == 1 )
        {
            return new Node( left->first, ( left )->second, parent );
        }

        auto tempIt = left + std::distance( left, right ) / 2;
        std::nth_element( left, tempIt, right, compareKey< DIM > );
        auto temp   = new Node( ( tempIt )->first, ( tempIt )->second, parent );
        temp->left  = KDTree_help< DIM_NEXT >( v, temp, left, tempIt );
        temp->right = KDTree_help< DIM_NEXT >( v, temp, tempIt + 1, right );
        return temp;
    }
    explicit KDTree( std::vector< std::pair< Key, Value > > v )
    {
        // TODO: implement this function
        std::stable_sort( v.begin( ), v.end( ), compareKey< 0 > );
        auto temp = std::unique( v.rbegin( ), v.rend( ), sameKey ).base( );
        v.erase( v.begin( ), temp );
        this->root     = KDTree_help< 0 >( v, nullptr, v.begin( ), v.end( ) );
        this->treeSize = v.size( );
        return;
    }

    /**
     * Time complexity: O(n)
     */

    Node *copy( const Node *that, const Node *parent )
    {
        if ( that == nullptr )
        {
            return nullptr;
        }
        auto temp
            = new Node( that->data.first, that->data.second, const_cast< KDTree< Key, Value >::Node * >( parent ) );
        // auto temp = new Node(that.data.first,that.data.second,parent);
        temp->left  = copy( that->left, temp );
        temp->right = copy( that->right, temp );
        return temp;
    }

    KDTree( const KDTree &that )
    {
        // TODO: implement this function
        if ( ( this->root ) != nullptr )
        {
            nodeFree( this->root );
        }
        this->root     = copy( ( ( that.root ) ), nullptr );
        this->treeSize = that.treeSize;
        return;
    }

    /**
     * Time complexity: O(n)
     */
    KDTree &operator=( const KDTree &that )
    {
        // TODO: implement this function
        if ( this == &that )
        {
            return *this;
        }
        if ( ( this->root ) != nullptr )
        {
            nodeFree( this->root );
        }
        this->root     = copy( that.root, nullptr );
        this->treeSize = that.treeSize;
        return *this;
    }

    /**
     * Time complexity: O(n)
     */

    void nodeFree( Node *x )
    {
        if ( x == nullptr )
        {
            return;
        }
        nodeFree( x->left );
        nodeFree( x->right );
        delete x;
        return;
    }

    ~KDTree( )
    {
        // TODO: implement this function
        nodeFree( this->root );
        return;
    }

    Iterator begin( )
    {
        if ( ! root )
            return end( );
        auto node = root;
        while ( node->left )
            node = node->left;
        return Iterator( this, node );
    }

    Iterator end( )
    {
        return Iterator( this, nullptr );
    }

    Iterator find( const Key &key )
    {
        return Iterator( this, find< 0 >( key, root ) );
    }

    void insert( const Key &key, const Value &value )
    {
        insert< 0 >( key, value, root, nullptr );
    }

    template < size_t DIM > Iterator findMin( )
    {
        return Iterator( this, findMin< DIM, 0 >( root ) );
    }

    Iterator findMin( size_t dim )
    {
        return Iterator( this, findMinDynamic< 0 >( dim ) );
    }

    template < size_t DIM > Iterator findMax( )
    {
        return Iterator( this, findMax< DIM, 0 >( root ) );
    }

    Iterator findMax( size_t dim )
    {
        return Iterator( this, findMaxDynamic< 0 >( dim ) );
    }

    bool erase( const Key &key )
    {
        auto prevSize = treeSize;
        erase< 0 >( root, key );
        return prevSize > treeSize;
    }

    Iterator erase( Iterator it )
    {
        if ( it == end( ) )
            return it;
        auto node = it.node;
        if ( ! it.node->left && ! it.node->right )
        {
            it.node = it.node->parent;
        }
        size_t depth = 0;
        auto   temp  = node->parent;
        while ( temp )
        {
            temp = temp->parent;
            ++depth;
        }
        eraseDynamic< 0 >( node, depth % KeySize );
        return it;
    }

    size_t size( ) const
    {
        return treeSize;
    }
    void allFrom( Node *node, std::vector< Value > &ans )
    {
        if ( node == nullptr )
        {
            return;
        }
        ans.push_back( node->value( ) );
        allFrom( node->left, ans );
        allFrom( node->right, ans );
    }
    template < size_t DIM, size_t DIM_NOW > bool checkAll( Key key, Key &lower, Key &upper )
    {
        if ( DIM == DIM_NOW )
        {
            return true;
        }
        constexpr size_t DIM_NEXT = ( DIM_NOW + 1 ) % KeySize;
        if ( std::get< DIM_NOW >( key ) >= std::get< DIM_NOW >( lower )
             && std::get< DIM_NOW >( key ) <= std::get< DIM_NOW >( upper ) )
        {
            return checkAll< DIM, DIM_NEXT >( key, lower, upper );
        }
        return false;
    }
    template < size_t DIM >
    void
    Range_Search_helper( Node *parent, Key &lower, Key &upper, Key treeLower, Key treeUpper, std::vector< Value > &ans )
    {
        if ( parent == nullptr )
        {
            return;
        }
        constexpr size_t DIM_NEXT = ( DIM + 1 ) % KeySize;
        if ( ( std::get< DIM >( lower ) <= std::get< DIM >( treeLower ) )
             && ( std::get< DIM >( upper ) >= std::get< DIM >( treeUpper ) ) )
        {
            ans.push_back( parent->value( ) );
            allFrom( parent->left, ans );
            allFrom( parent->right, ans );
            return;
        }
        if ( ( std::get< DIM >( lower ) > std::get< DIM >( treeUpper ) )
             || ( std::get< DIM >( upper ) < std::get< DIM >( treeLower ) ) )
        {
            return;
        }

        if ( std::get< DIM >( parent->key( ) ) >= std::get< DIM >( lower )
             && std::get< DIM >( parent->key( ) ) <= std::get< DIM >( upper ) )
        {
            auto temp = checkAll< DIM, DIM_NEXT >( parent->key( ), lower, upper );
            if ( temp )
            {
                ans.push_back( parent->value( ) );
            }
        }
        auto temp1               = treeLower;
        std::get< DIM >( temp1 ) = std::get< DIM >( parent->key( ) );
        auto temp2               = treeUpper;
        std::get< DIM >( temp2 ) = std::get< DIM >( parent->key( ) );
        Range_Search_helper< DIM_NEXT >( parent->left, lower, upper, treeLower, temp2, ans );
        Range_Search_helper< DIM_NEXT >( parent->right, lower, upper, temp1, treeUpper, ans );
        return;
    }
    template < size_t DIM > void getMax( Key &key, int distance )
    {
        constexpr size_t DIM_NEXT = ( DIM + 1 ) % KeySize;
        std::get< DIM >( key ) += distance;
        if ( DIM_NEXT != 0 )
        {
            getMax< DIM_NEXT >( key, distance );
        }
        return;
    }
    template < size_t DIM > void getMin( Key &key, int distance )
    {
        constexpr size_t DIM_NEXT = ( DIM + 1 ) % KeySize;
        std::get< DIM >( key ) -= distance;
        if ( DIM_NEXT != 0 )
        {
            getMin< DIM_NEXT >( key, distance );
        }
        return;
    }
    template < size_t DIM > void getSM( Key &key )
    {
        constexpr size_t DIM_NEXT = ( DIM + 1 ) % KeySize;
        std::get< DIM >( key )    = 0;
        if ( DIM_NEXT != 0 )
        {
            getSM< DIM_NEXT >( key );
        }
        return;
    }

    template < size_t DIM > void getLA( Key &key )
    {
        constexpr size_t DIM_NEXT = ( DIM + 1 ) % KeySize;
        std::get< DIM >( key )    = 500;
        if ( DIM_NEXT != 0 )
        {
            getLA< DIM_NEXT >( key );
        }
        return;
    }

    std::vector< Value > *Range_Search( Key key, int distance )
    {
        auto ans   = new std::vector< Value >;
        auto lower = key;
        auto upper = key;
        getMax< 0 >( upper,distance );
        getMin< 0 >( lower,distance );
        auto treeLower = key;
        getSM< 0 >( treeLower );
        auto treeUpper = key;
        getLA< 0 >( treeUpper );
//        ans->push_back(root->value());
        // TODO: implement this function
        Range_Search_helper<0>( root, lower, upper, treeLower, treeUpper, (*ans) );
        return ans;
    }
};
