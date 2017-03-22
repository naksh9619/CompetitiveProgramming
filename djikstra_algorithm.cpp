#include<bits/stdc++.h>
#define ff first
#define ss second
using namespace std;
vector<pair<int,int> > vecto[100];
int distanc[100];
void dijkstra(int start_point)
{
    distanc[start_point]=0;
    priority_queue<pair<int,int> > que;
    que.push({start_point,0});
    while(!que.empty())
    {
        pair<int,int> pa=que.top();
        que.pop();
        if(pa.ss>distanc[pa.ff])
            continue;
        for(int i=0;i<vecto[pa.ff].size();i++)
        {
            int alt=distanc[pa.ff]+vecto[pa.ff][i].ss;
            if(alt<distanc[vecto[pa.ff][i].ff])
                que.push({vecto[pa.ff][i].ff,distanc[vecto[pa.ff][i].ff]=alt});
        }
    }
}
int main()
{
    int nodes,edges,x,y,start_point,dis;
    cin>>nodes>>edges;
    for(int i=0;i<100;i++)
    {
        vecto[i].clear();
        distanc[i]=INT_MAX;
    }
    for(int i=0;i<edges;i++)
    {
        cin>>x>>y>>dis;
        vecto[x].push_back(make_pair(y,dis));
        vecto[y].push_back(make_pair(x,dis));
    }
    cin>>start_point;
    dijkstra(start_point);
    for(int i=0;i<nodes;i++)
        cout<<i<<"     "<<distanc[i]<<endl;
return 0;
}
