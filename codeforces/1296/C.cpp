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

const int MAX = 3*300*1000 + 10;
const ll oo = 6*MAX;
int n, m;
list<int> which[MAX];
char S[MAX];
int id[MAX], W[MAX], color[MAX];
int visID[MAX], visNum;
ll cnt[MAX][2];


int find(int a, int & c){
	if(id[a] == a) {
		c = color[a];
		return a;
	}
	int p = find(id[a], c);
	color[a] ^= c;
	c = color[a];
	return id[a] = p;
}

void join(int a, int b, bool c){
	int c1, c2;
//	int x = a,y = b;
	a = find(a, c1), b = find(b, c2);
//	cerr << x << "->" << a << " " << c1 << " " << y << "->" << b << " " << c2 << " " << c << endl;
	if(a == b) return;
	if(W[a] < W[b]) swap(a, b);
	W[a] += W[b];
	loop(k, 2){
		cnt[a][(c1+c+k)&1] += cnt[b][(c2+k)&1];		
	}
	id[b] = a;
	color[b] = (c1 + c2 + c)&1;
}

void create(int i){
	id[i] = i;
	W[i] = 1;
	loop(c, 2) cnt[i][c] = 1^c;
	color[i] = 0;
}

void erase(int a, ll & res){
	int c;
	int p = find(a, c);
//	cerr << "- " << a << " -> " << p << endl;
//	prArr(cnt[p], 2, int);
	res -= min(cnt[p][0], cnt[p][1]);
	assert(res >= 0);
}
void add(int a, ll & res){
	int c;
	int p = find(a, c);
//	cerr << "+ " << a << " -> " << p << endl;
//	prArr(cnt[p], 2, int);
	res += min(cnt[p][0], cnt[p][1]);
	assert(res >= 0);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &n, &m);
	scanf("%s", S);
	loop(i, m) {
		int k; scanf("%d", &k);
		while(k--){
			int x; scanf("%d", &x);
			x--;
			which[x].pb(i);
		}
		create(i);
	}
	create(m);
	cnt[m][0] = oo;
	cnt[m][1] = 0;
	
	
	ll res = 0;
	
	loop(i, n){
		if(!which[i].empty()){
			int a = *which[i].begin();
			int b = *which[i].rbegin();
			if(a == b) b = m;
			int c;
			if(find(a, c) != find(b, c)){
				erase(a, res);
				erase(b, res);
				join(a, b, S[i] == '0');
				add(a, res);				
			}
		}

		printf("%lld\n", res);
	}
	return 0;
}
