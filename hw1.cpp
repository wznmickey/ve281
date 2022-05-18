#include <bits/stdc++.h>
using namespace std;
unsigned long long TigerNacci(unsigned int n) {
  if (n <= 3)
    return 1;
  return TigerNacci(n - 1) + TigerNacci(n - 2) + TigerNacci(n - 3);
}
int main() {
  for (auto i = 1; i <= 50; i++) {
    cout<<i<<" "<<TigerNacci(i)<<" "<<(double)TigerNacci(i+1)/TigerNacci(i)<<endl;

  }
  return 0;
}