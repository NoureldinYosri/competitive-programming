#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0,_ = (n);i < _;i++)
#define range(i,a,b) for(int i = (a),_ = (b);i <= _;i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b),_ = (a);i >= _;i--)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define vi vector<int>
#define vl vector<long>
#define vd vector<double>
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

int A[10],B[10],vis[10];

void make_standard(){
	fill(vis,vis + 10,0);
	vector<int > aux;
	loop(i,10){
		if(vis[i]) continue;
		int j = i,mx = j;
		while(!vis[j]){
			mx = max(mx,j);
			vis[j] = 1;
			j = A[j];
		}
		aux.pb(mx);
	}
	sort(all(aux));
	fill(vis,vis + 10,0);
	int i = 0;
	for(auto u : aux) {
		int v = u;
		while(!vis[v]){
			vis[v] = 1;
			B[i++] = v;
			v = A[v];
		}
	}
}

bool equal(){
	loop(i,10) if(A[i] != B[i]) return 0;
	return 1;
}

int main(){
	int ctr = 0,q = 5;
	loop(i,10) A[i] = i;
	do{
		make_standard();
		ctr += equal();
	//	if(!q--) break;
	//	prArr(A,10,int);
	//	prArr(B,10,int);
	//	cerr << endl;
	}while(next_permutation(A,A + 10));
	cerr << ctr << endl;
	return 0;
}
