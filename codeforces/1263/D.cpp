#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
typedef std::vector<int> vi;
typedef std::pair<int,int> pi;
typedef std::vector<pi> vp;
typedef long long ll;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
using namespace std;

int id[1 << 20];
int W[1 << 20];
int n;
char buffer[1 << 20];
vi who[128];

int find(int a){
	return id[a] = (a == id[a]) ? a : find(id[a]);
}
void join(int a,int b){
	a = find(a);
	b = find(b);
	if(a == b) return;
	n--;
	if(W[a] < W[b]) swap(a, b);
	id[b] = a;
	W[a] += W[b];
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	loop(i,n){
		scanf("%s",buffer);
		int m = strlen(buffer);
		sort(buffer,buffer + m);
		m = unique(buffer, buffer + m) - buffer;
		buffer[m] = 0;
		loop(j,m)  who[(int)buffer[j]].pb(i);
	}
	loop(i,n) id[i] = i, W[i] = 1;
	
	for(char c = 'a'; c <= 'z'; c++){
		int u = -1;
		for(int v : who[(int)c]){
			if(u != -1) join(u, v);
			u = v;
		}
	}
	cout << n << endl;
	return 0;
}
