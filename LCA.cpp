#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
ll n,a,b,subtreesize[100100],pa[100][100],depth[100100],que;
vector<ll> v[100100];
void dfs(ll CurrNode,ll PrevNode,ll _depth=0)
{
    pa[0][CurrNode]=PrevNode;
    depth[CurrNode]=_depth;
    subtreesize[CurrNode]=1;
    for(int i=0;i<v[CurrNode].size();i++)
    {
        if(v[CurrNode][i]!=PrevNode)
        {
            dfs(v[CurrNode][i],CurrNode,_depth+1);
            subtreesize[CurrNode]+=subtreesize[v[CurrNode][i]];
        }
    }
}
ll lca(ll u,ll v)
{
    if(depth[u]<depth[v])
        swap(u,v);
    int diff=depth[u]-depth[v];
    for(int i=0;i<14;i++)
    {
        if((diff>>i)&1)
            u=pa[i][u];
    }
    if(u==v)
        return u;
    for(int i=13;i>=0;i--)
    {
        if(pa[i][u]!=pa[i][v])
        {
            u=pa[i][u];
            v=pa[i][v];
        }
    }
    return pa[0][u];
}
int main()
{
    cin>>n;
    for(int i=0;i<n-1;i++)
    {
        cin>>a>>b;
        a--,b--;
        v[a].pb(b);
        v[b].pb(a);
    }
    dfs(0,-1);
    for(int i=0;i<n;i++)
        cout<<i<<" "<<subtreesize[i]<<" "<<depth[i]<<" "<<pa[0][i]<<endl;
    cin>>que;
    while(que--)
    {
        cin>>a>>b;
        a--,b--;
        cout<<lca(a,b)<<endl;
    }
return 0;
}
