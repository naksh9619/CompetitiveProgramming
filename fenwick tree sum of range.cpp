#include<bits/stdc++.h>
#define MAX LONG_LONG_MAX
#define MIN LONG_LONG_MIN
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


int arr[100100],fentree[200200];
int maxi;
void update(int index,int val)
{
    //cout<<"maxi is:"<<maxi<<endl;
    while(index<=maxi)
    {
        fentree[index]+=val;
        index+=((index)&(-index));
        //cout<<"index is:"<<index<<endl;
    }
}

int query(int index)
{
    int sum=0;
    while(index>0)
    {
        sum+=fentree[index];
        index-=((index)&(-index));
        //cout<<"index"<<index<<endl;
    }
    return sum;
}

int main()
{
    int n,l,r,que,ans;
    memset(fentree,0,sizeof(fentree));
    n=read_int();
    maxi=n;
    for(int i=0;i<n;i++)
        arr[i]=read_int();
    que=read_int();
    for(int i=1;i<=n;i++)
        update(i,arr[i-1]);
    cout<<"fenwick tree is:"<<endl;
    for(int i=1;i<=n;i++)
        cout<<fentree[i]<<" ";
    cout<<endl;
    while(que--)
    {
        l=read_int();
        r=read_int();
        ans=query(r+1)-query(l);
        cout<<ans<<endl;
    }
return 0;
}
