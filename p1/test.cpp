#include <bits/stdc++.h>
#include <string>
using namespace std;
int main( )
{
    for ( int i = 0; i <= 9; i++ )
    {
        string ifile = "input";
        ifile        = ifile + to_string( i );
        string ofile = "output";
        ofile        = ofile + to_string( i );
        auto   fstream( ifile );
        string tfile = "test";
        tfile        = tfile + to_string( i );
        system( ( "cat ./others/project1/Input/" + ifile + ".txt | ./a.out >" + tfile ).c_str( ) );
    }
}