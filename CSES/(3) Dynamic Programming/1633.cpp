#include <iostream>
#define F(i,y) for(l i=1;i<y;i++)
using l=long;l d[(l)2e6],n;main(){d[0]=1;std::cin>>n;F(i,n+1)F(j,7)if(i>j-1)d[i]=(d[i]+d[i-j])%(l)(1e9+7);std::cout<<d[n];}