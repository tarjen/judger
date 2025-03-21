//meet in middle
#include<bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
#define dbg(x...) do { cout << "\033[32;1m " << #x << " -> "; err(x); } while (0)
void err() { cout << "\033[39;0m" << endl; }
template<template<typename...> class T, typename t, typename... A>
void err(T<t> a, A... x) { for (auto v: a) cout << v << ' '; err(x...); }
template<typename T, typename... A>
void err(T a, A... x) { cout << a << ' '; err(x...); }
#else
#define dbg(...)
#endif
typedef long long ll;
typedef pair<int,int> pi;
typedef vector<int> vi;
template<class T> using vc=vector<T>;
template<class T> using vvc=vc<vc<T>>;
template<class T> void mkuni(vector<T>&v)
{
    sort(v.begin(),v.end());
    v.erase(unique(v.begin(),v.end()),v.end());
}
ll rand_int(ll l, ll r) //[l, r]
{
    static mt19937_64 gen(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<ll>(l, r)(gen);
}
template<class T>
void print(T x,int suc=1)
{
    cout<<x;
    if(suc==1) cout<<'\n';
    else cout<<' ';
}
template<class T>
void print(const vector<T>&v,int suc=1)
{
    for(int i=0;i<v.size();i++)
    print(v[i],i==(int)(v.size())-1?suc:2);
}
int a[40],b[40];
int var;
int n,m;
map<int,ll> mx[40];
ll zans=0;
ll ans=0;
void add(int t,int A,ll B)
{
	if(mx[t].count(A)) mx[t][A]=max(mx[t][A],B);
	else mx[t][A]=B;
}
void dfs(int u,int A,ll B)
{
	if(u>=var)
	{
		if(!A) zans=max(zans,B);
		if(A<=m) ans=max(ans,B);
		for(int i=30;i>=0;i--)
			add(i,(A>>i)<<i,B);
		return;
	}
	dfs(u+1,A^a[u],B+b[u]);
	dfs(u+1,A,B);
}
void dfs2(int u,int A,ll B)
{
	if(u==n)
	{
		if(A<=m) ans=max(ans,zans+B);
		int cur=0;
		for(int i=30;i>=0;i--)
		{
			int cm=(m>>i&1),ca=(A>>i&1);
			if(cm)
			{
				int cc=cm^ca^1;
				int tt=cur;
				if(cc) tt+=1<<i;
				if(mx[i].count(tt))
					ans=max(ans,B+mx[i][tt]);
			}
			if(cm^ca) cur+=1<<i;
		}
		if(mx[0].count(cur))
			ans=max(ans,B+mx[0][cur]);
		return;
	}
	dfs2(u+1,A^a[u],B+b[u]);
	dfs2(u+1,A,B);
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	cin>>n>>m;
	var=n/2;
	for(int i=0;i<n;i++) cin>>a[i];
	for(int i=0;i<n;i++) cin>>b[i];
	dfs(0,0,0);
	dfs2(var,0,0);
	print(ans);
}