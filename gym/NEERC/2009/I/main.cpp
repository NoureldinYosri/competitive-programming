#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define point pair<double,double>
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

const int MAX = 1 << 23;

int n;
int vis[MAX];
int tour[MAX],idx;


string bin(int x,int len){
	char s [len + 1] = {0};
	for(int i = 0;i < len;i++)
		if(x & (1 << i))
			s[i] = '1';
		else 
			s[i] = '0';
	reverse(s,s + len);
	return string(s);
}



void solve(){
	int cur = 0,u,v;
	while(1){
		tour[idx++] = cur;
		vis[cur] = 1;
		u = (cur & ~(1 << (n - 1))) << 1;
		if(!vis[u | 1]) cur = u | 1;
		else if(!vis[u]) cur = u ;
		else break;
	}
}

char out[MAX];

int main(){
	FILE *fin = fopen("infinite.in","r");
	FILE *fout = fopen("infinite.out","w");
	fscanf(fin,"%d",&n);
	solve();
//	prArr(tour,idx,int);
//	reverse(tour,tour + idx);

	//prArr(tour,idx,int);	
	strcpy(out,bin(0,n).c_str());
	int cur = n;
	for(int i = 1;i < idx;i++) out[cur++] = (tour[i]&1) + '0';
	fprintf(fout,"%s\n",out);
	return 0;
}


