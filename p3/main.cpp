#include "kdtree.hpp"
#include <iostream>
#include <tuple>
using namespace std;

int main( )
{
    std::vector< std::pair< std::tuple< int, int,int >, int > > ans;
    auto                                                    key1 = std::make_tuple( 0 , 0,0 );
    auto                                                    key2 = std::make_tuple( -1, 2,0 );
    auto                                                    key3 = std::make_tuple( 1, -1,0 );
    auto                                                    key4 = std::make_tuple( -1,2,-4);
    // auto                                                    key5 = std::make_tuple( 9,6,9 );
    // // auto                                                    key6 = std::make_tuple( 6, 3 );e
    // // auto                                                    key7 = std::make_tuple( 7, 3 );
    ans.emplace_back(key1,280);
    ans.emplace_back(key1,370);
    ans.emplace_back(key2,281);
    ans.emplace_back(key3,482);
    KDTree< std::tuple< int, int ,int>, int >                   kk(ans);
    
    for (auto i:kk)
    {
        std::cout<<" "<<i.second<<std::endl;
    }
    std::cout<<endl;

    kk.insert( key1, 1 );
    // kk.insert( key1, 5 );

    kk.insert( key2, 2 );

    kk.insert( key3, 3 );

    kk.insert( key4, 4 );
    // kk.insert( key3, 3 );
    auto i = kk.find( key4 );
    std::cout<<(i->second)<<std::endl;
    // std::cout<<kk.erase(key1)<<true<<std::endl;
    // ans.emplace_back( key1, 1 );
    // ans.emplace_back( key2, 2 );
    // ans.erase( ans.begin( ) );
    // auto xx = ans.begin();
    // xx++;
    // xx++;
    // k.erase(key1);
    // KDTree< std::tuple< int, int ,int>, int > kkkkk( ans );
    // KDTree< std::tuple< int, int ,int>, int > kkk = kk;
    // KDTree< std::tuple< int, int,int >, int > kkkk( kkk );
    // kk.insert(key1, 1);
    // kk.insert(key2, 2);
    // kk.insert(key3, 3);
    // kk.insert(key4, 4);
    // kk.insert(key5, 5);

    // // std::cout<<kk.findMax(1)->second<<std::endl;

    auto it = kk.begin();
    while (true)
    {
        std::cout<<it->second<<std::endl;
        it++;
        // int a;
        // std::cin>>a;
        if (it==kk.end()){
            return 0;
        }
    }
    
    return 0;
}