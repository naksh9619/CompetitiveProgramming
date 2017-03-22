#include<bits/stdc++.h>
#define ll long long
#define mp make_pair
#define pb push_back
#define ff first
#define ss second
#define INF 1e17
using namespace std;
const int mod=1e9+7;

ll exponentiation(ll base,ll power)
{
    ll ans=1;
    while(power>0)
    {
       if(power%2==1)
            ans=(ans*base)%mod;
       base=(base*base)%mod;
       power/=2;
    }
    return ans%mod;
}
inline int read_int()
{
    bool minus=false;
	int result=0;
	char ch;
	ch=getchar();
	while(true){
        if(ch=='-') break;
		if(ch>='0' && ch<='9') break;
		ch=getchar();
	}
	if(ch=='-') minus=true; else result=ch-'0';
	while(true){
		ch=getchar();
		if(ch<'0' || ch>'9') break;
		result=result*10+(ch-'0');
	}
	if(minus)
		return (-result);
	else
		return result;
}

inline ll read_long_long()
{
    bool minus=false;
	ll result=0;
	char ch;
	ch=getchar();
	while(true){
        if(ch=='-') break;
		if(ch>='0' && ch<='9') break;
		ch=getchar();
	}
	if(ch=='-') minus=true; else result=ch-'0';
	while(true){
		ch=getchar();
		if(ch<'0' || ch>'9') break;
		result=result*10+(ch-'0');
	}
	if(minus)
		return (-result);
	else
		return result;
}

ll edges,a,b,weight,t,n,dis[10][10];
//Undirected Graph
int main()
{
    for(int i=0;i<10;i++)
        for(int j=0;j<10;j++)
            dis[i][j]=INT_MAX;
    for(int i=0;i<10;i++)
        for(int j=0;j<10;j++)
            if(i==j) dis[i][j]=0;
    n=read_int();
    edges=read_int();
    while(edges--)
    {
        a=read_int();
        b=read_int();
        weight=read_int();
        dis[a][b]=weight;
        dis[b][a]=weight;//Comment this line to make it directed
    }
    for(int k=0;k<n;k++)
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                if(dis[i][k]+dis[k][j]<dis[i][j])
                    dis[i][j]=dis[i][k]+dis[k][j];
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            cout<<dis[i][j]<<" ";
        cout<<endl;
return 0;
}
