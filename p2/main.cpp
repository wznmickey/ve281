#include "hashtable.hpp"
#include <bits/stdc++.h>
#include <iterator>
using namespace std;
int main()
{
    // vector<int> a;
    // auto i=a.begin();
    // std::advance(i, 2);

    HashTable<string, string, std::hash< string >, std::equal_to< string>> ans;
    while (true)
    {
        string st1,st2;
        int i;
        // int i=0;
        std::cin>>i>>st1>>st2;
        if (i==0) ans.insert(st1, st2);
        if (i==1) ans.erase(st1);
        if (i==3) ans[st1]=st2;
        if (i==2) 
        {
            for (auto x= ans.begin();x!=ans.end();x++)
            {
                cout<<x->first<<x->second<<endl;
            }
        }
    }
    
}

// C++ program to illustrate the
// before_begin() function
// #include <bits/stdc++.h>
// using namespace std;
 
// // // Driver Code
// int main()
// {
//     // initialising the forward list
//     forward_list<int> fl = { 20, 30, 40, 50 };
 
//     // performing before_begin function
//     auto it = fl.before_begin();
 
//     // inserting element before the first element
//     fl.emplace_front(10);
//     cout << "Element of the list are:" << endl;
//     fl.erase_after(it);
//     // loop to print the elements of the list
//     for (auto it = fl.begin(); it != fl.end(); ++it)
//         cout << *it << " ";
 
//     return 0;
// }