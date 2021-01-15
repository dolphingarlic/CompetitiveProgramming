#include <iostream>
#define F(i,y) for(l i=1;i<=y;i++)
#define M 1000000007
typedef long long l;l d[1000001],a[101],n,m;main(){d[0]=1;std::cin>>n>>m;F(i,n)std::cin>>a[i];F(i,m){F(j,n){if(i-a[j]>-1){d[i]=d[i]+d[i-a[j]];if(d[i]>M)d[i]-=M;}}}std::cout<<d[m];}