/*
    References:->1.https://blog.anudeep2011.com/heavy-light-decomposition/
                 2.https://github.com/anudeep2011/programming/blob/master/qtree.cpp
*/
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back

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


ll n,a,b,que,t,weight,idx,l,r,subtreesize[10100],parent[14][10100],depth[10100],segtree[400400],BaseArray[10100],ans[400400],ind,val;
ll ChainNo,ChainInd[10100],ChainStart[10100],posInBase[10100],ptr,otherend[10100];
vector<ll> v[10100],costs[10100],indexx[10100];


//Function To Make Segment Tree
void BuildSegMentTree(ll pos,ll st,ll en)
{
    if(st==en-1)//Leaf Node Condition
    {
        segtree[pos]=BaseArray[st];
        return;
    }
    //Recursive Function For Both Left And Right Child
    ll mid=(st+en)>>1;
    BuildSegMentTree(2*pos,st,mid);
    BuildSegMentTree(2*pos+1,mid,en);
    segtree[pos]=max(segtree[2*pos],segtree[2*pos+1]);
}


//Function To Update Point Element In Segment Tree
void UpdateSegMentTree(ll pos,ll st,ll en,ll idx,ll val)
{
    if(st>idx || en<=idx)//Out Of Bound Condition
        return;
    if(st==idx && st==en-1)//Required Range Is Perfectly In The Given Range
    {
        segtree[pos]=val;
        return;
    }
    //Recursive Function For Both Left And Right Child
    ll mid=(st+en)>>1;
    UpdateSegMentTree(2*pos,st,mid,idx,val);
    UpdateSegMentTree(2*pos+1,mid,en,idx,val);
    segtree[pos]=max(segtree[2*pos],segtree[2*pos+1]);//Storing Maximum Of Both Left And Right In Their Parent Node
}


//Function To Query For Maximum Element In Segment Tree
void QuerySegMentTree(ll pos,ll st,ll en,ll l,ll r)
{
    if(r<=st || l>=en)//Out Of Bound Conditions
    {
        ans[pos]=-1;
        return;
        //return ans[pos];
    }
    if(l<=st && r>=en)//Required Range Is Perfectly In The Given Range
    {
        ans[pos]=segtree[pos];
        return;
        //return ans[pos];
    }
    //Recursive Function For Both Left And Right Child
    ll mid=(st+en)>>1;
    QuerySegMentTree(2*pos,st,mid,l,r);
    QuerySegMentTree(2*pos+1,mid,en,l,r);
    ans[pos]=max(ans[2*pos],ans[2*pos+1]);//Storing Maximum Again
    //return ans[pos];
}


//Function To Decompose The Tree Into Chains
void HeavyLightDecomposition(ll CurrNode,ll Cost,ll PrevNode)
{
    if(ChainStart[ChainNo]==-1)
    {
        ChainStart[ChainNo]=CurrNode;
    }
    ChainInd[CurrNode]=ChainNo;
    posInBase[CurrNode]=ptr;
    BaseArray[ptr++]=Cost;
    ll sc=-1,ncost;
    //Below For Loop Finds Special Node For A Given Node
    for(int i=0;i<v[CurrNode].size();i++)
    {
        if(v[CurrNode][i]!=PrevNode)
        {
            if(sc==-1 || subtreesize[sc]<subtreesize[v[CurrNode][i]])
            {
                sc=v[CurrNode][i];
                ncost=costs[CurrNode][i];
            }
        }
    }
    //Now Using Heavy Light Decomposition For The Same Chain And Expanding This to The Special Child Of Node
    if(sc!=-1)
        HeavyLightDecomposition(sc,ncost,CurrNode);
    //The Below For Loop Does HLD For Every Child Node And Each Time It Starts A New Chain Therefore ChainNo++
    for(int i=0;i<v[CurrNode].size();i++)
    {
        if(v[CurrNode][i]!=PrevNode)
        {
            if(v[CurrNode][i]!=sc)
            {
                ChainNo++;//Ensures That We Start New Chain
                HeavyLightDecomposition(v[CurrNode][i],costs[CurrNode][i],CurrNode);//Same Recursive Child For Child Nodes
            }
        }
    }
}


//We Query the Chain In Which 'u' Is Present Till Chain Head And Then Move To Next Chain Up
//Do this Until We Find 'u' And 'v' In Same Chain And When We Found Both In Same Chain Then Calculate Answer And Break
ll QueryUpTree(ll u,ll v)//Condition:-> 'v' is Ancestor of 'u'
{
    if(u==v)
        return 0;
    int uchain,vchain=ChainInd[v],answer=-1;
    while(1)
    {
        uchain=ChainInd[u];
        if(uchain==vchain)//Both 'u' and 'v' Belongs To Same Chain So Query From 'u' to 'v' And Get The Required Answer
        {
            if(u==v)
                break;
            QuerySegMentTree(1,0,ptr,posInBase[v]+1,posInBase[u]+1);
            if(ans[1]>answer)//Update Answer
                answer=ans[1];
            break;
        }
        //Querying Segment Tree From 'u' To Stating Point Of Chain Of 'u' And Then Update The Answer
        QuerySegMentTree(1,0,ptr,posInBase[ChainStart[uchain]],posInBase[u]+1);
        if(ans[1]>answer)//Update Answer
            answer=ans[1];
        u=ChainStart[uchain];
        u=parent[0][u];//Moving To Its Parent We will Not Have To Move More Than log(n) Chains
    }
    return answer;
}

void dfs(ll CurrNode,ll PrevNode,ll _depth=0)//This Function Calculates Depth Of Node,Subtree Size,position Of Node In Tree,Starting and end points of chain
{
    subtreesize[CurrNode]=1;
    depth[CurrNode]=_depth;
    parent[0][CurrNode]=PrevNode;
    for(int i=0;i<v[CurrNode].size();i++)
    {
        if(v[CurrNode][i]!=PrevNode)
        {
            otherend[indexx[CurrNode][i]]=v[CurrNode][i];
            dfs(v[CurrNode][i],CurrNode,_depth+1);
            subtreesize[CurrNode]+=subtreesize[v[CurrNode][i]];
        }
    }
}


ll lca(ll u,ll v)//This Function Calculates Lowest Common Ancestor Of Given Two Nodes Considering that 'u' is present above 'v' in the tree
{
    if(depth[u]<depth[v])
        swap(u,v);
    int diff=depth[u]-depth[v];
    for(int i=0;i<14;i++)
    {
        if((diff>>i)&1)
        {
            u=parent[i][u];
        }
    }
    if(u==v)
        return u;
    for(int i=13;i>=0;i--)
    {
        if(parent[i][u]!=parent[i][v])
        {
            u=parent[i][u];
            v=parent[i][v];
        }
    }
    return parent[0][u];
}


int main()
{
    //ChainNo=-1;
    //TESTING DFS AND LCA FUNCTIONS
    /*
        dfs(0,-1);
        cin>>que;
        while(que--)
        {
            cin>>a>>b;
            a--,b--;
            cout<<lca(a,b)<<endl;
        }
    */
    //TESTING SEGMENT TREE FUNCTIONS
    /*
        cin>>n;
        for(int i=1;i<=n;i++)
            cin>>BaseArray[i];
        BuildSegMentTree(1,1,n);
        for(int i=1;i<16;i++)
            cout<<segtree[i]<<" ";
        cout<<endl;
        cin>>que;
        while(que--)
        {
            cin>>idx>>val;
            UpdateSegMentTree(1,1,n,idx,val);
            cout<<QuerySegMentTree(1,1,n,idx,val);
        }
    */
    //scanf("%d",&t);
    t=read_long_long();
    while(t--)
    {
        ptr=0,ChainNo=0;
        //scanf("%d",&n);
        n=read_long_long();
        //Clearing Everything For A new TestCase
        for(int i=0; i<n; i++)
        {
			v[i].clear();
			costs[i].clear();
			indexx[i].clear();
			ChainInd[i]=0;
			posInBase[i]=0;
			ChainStart[i]=-1;
            segtree[i]=0;
            subtreesize[i]=0;
            otherend[i]=0;
            depth[i]=0;
            BaseArray[i]=0;
            ans[i]=0;
			for(int j=0;j<14;j++)
                parent[j][i]=-1;
		}
		//Input And Creating Lists
        for(int i=1;i<n;i++)
        {
            //scanf("%d %d %d",&a,&b,&weight);
            a=read_long_long();
            b=read_long_long();
            weight=read_long_long();
            a--,b--;
            v[a].pb(b);
            costs[a].pb(weight);
            indexx[a].pb(i-1);
            v[b].pb(a);
            costs[b].pb(weight);
            indexx[b].pb(i-1);
        }

        //This Function Is Required For Calculating parent,SubtreeSize,DepthOfNode
        dfs(0,-1);
        //for(int i=0;i<n;i++)
        //  cout<<i<<" "<<depth[i]<<" "<<subtreesize[i]<<" "<<pa[0][i]<<endl;

        //This the Algorithm Implementation of How It decomposes the tree
        HeavyLightDecomposition(0,-1,-1);

        //Building Segment Tree
        BuildSegMentTree(1,0,ptr);

        //for(int i=0;i<=n;i++)
        //    cout<<BaseArray[i]<<" ";
        //cout<<endl;
        //for(int i=1;i<=8;i++)
        //    cout<<segtree[i]<<" ";
        //cout<<endl;
        //This is the Dynamic Code for Calculating Lowest Common Ancestor
        for(int i=1;i<14;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(parent[i-1][j]!=-1)
                {
                    parent[i][j]=parent[i-1][parent[i-1][j]];
                }
            }
        }
        while(1)
        {
            //cout<<"queries"<<endl;
            char s[100];
            scanf("%s",s);
            if(s[0]=='D')
            {
				break;
			}
            if(s[0]=='Q')//Answers Query
            {
                //scanf("%d %d",&l,&r);
                l=read_long_long();
                r=read_long_long();
                l--,r--;
                //Query From Both Paths Calculate Answer From Both Paths And Then Print Maximum Amongst Them
                ll LowestAncestor=lca(l,r);
                ll answer1=QueryUpTree(l,LowestAncestor);//Calculating First Answer
                ll answer2=QueryUpTree(r,LowestAncestor);//Calculating Second Answer
                //cout<<answer1<<" "<<answer2<<endl;
                if(answer2>answer1)//Taking Maximum of Both Answers
                    answer1=answer2;
                printf("%d\n",answer1);
            }
            else//Update Operation
            {
                //scanf("%d %d",&idx,&val);
                idx=read_long_long();
                val=read_long_long();
                idx--;
                ll p=otherend[idx];
                UpdateSegMentTree(1,0,ptr,posInBase[p],val);
            }
        }
    }
return 0;
}
