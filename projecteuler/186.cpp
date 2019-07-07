#ifdef ACTIVE
#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#include "my_math.h"
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define popcnt(x) __builtin_popcountll(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
using namespace std;

const int mod = 1000000;
deque<int> S;


void computeS(){
	for(int k = 1;k <= 55;k++){
		int k2 = mul(k,k,mod),k3 = mul(k,k2,mod);
		int a = 100003;
		int b = mul(200003,k,mod);
		int c = mul(300007,k3,mod);
		int s = add(a,-b,mod);
		s = add(s,c,mod);
		S.pb(s);
	}
}

int id[mod + 1],W[mod + 1];

int find(int a) {
	return id[a] = (a == id[a]) ? a : find(id[a]);
}

void join(int a,int b) {
	a = find(a),b = find(b);
	if(a == b) return;
	if(W[a] < W[b]) swap(a,b);
	W[a] += W[b];
	id[b] = a;
}

bool connected(int a,int b) {
	return find(a) == find(b);
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	computeS();
	loop(i,mod+1) id[i] = i,W[i] = 1;
	int target = 990000,P = 524287,ctr = 0;
	for(int i = 0;i+1 < sz(S);i += 2)
		join(S[i],S[i + 1]),ctr++;
	print(S,int);
	int u = S.back();
	for(int i = 1;W[find(P)] < target;i ^= 1) {
		int v = add(S[0],S[31],mod);
		if(i) {
			if(u != v) {
				join(u,v);
				ctr++;
			}
		}
		S.pb(v);
		u = v;
		S.pop_front();
	}
	cout << ctr << endl;
	cout << W[find(P)] << endl;
	return 0;
}
#endif
