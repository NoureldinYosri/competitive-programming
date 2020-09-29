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


const int MAX = 1 << 21;
int n, m;
int BIT[MAX + 1];
char txt[MAX];
char command[MAX];
vi args[MAX];

void update(int p, int v){
	for(; p <= MAX; p += LSOne(p))
		BIT[p] += v;
}
int get(int p){
	int ret = 0;
	for(; p; p ^= LSOne(p)) ret += BIT[p];
	return ret;
}

int getPos(int x){
	int u = 1, siz = 1 << 20;
	while(siz > 1){
		assert(u + siz - 1 <= MAX);
		siz >>= 1;
		if(BIT[u + siz - 1] < x){
			x -= BIT[u + siz - 1];
			u += siz;
		}
	}
	return u;
}

int ctr[1 << 20];


int main(){
//	freopen("collider.in", "r", stdin);
	freopen("in.in", "r", stdin);
#ifndef HOME
//	freopen("collider.out", "w", stdout);
#endif
	scanf("%d %d %s", &n, &m, txt);
	vi U;
	loop(i, m){
		scanf(" %c", command + i);
		int r = 1 + (command[i] == 'a');
		loop(j, r){
			int x; scanf("%d", &x);
			args[i].pb(x);
		}
		if(command[i] == 'a') {
			U.pb(i);
			ctr[args[i].back()]++;
		}
	}
	for(int i = 1, s = 1; i <= n; i++) {
		int t = ctr[i];
		ctr[i] = s;
		s += t + 1;
	}
	reverse(all(U));
	for(int a : U){
		int p = args[a].back();
		args[a].back() = ctr[p]++;
	}
	string str(sz(U) + n + 1, '$');
	for(int i = 1; i <= n; i++){
		int j = ctr[i];
		str[j] = txt[i - 1];
		update(j, 1);
	}
	
	
	loop(i, m){
		int p = getPos(args[i][0]);
		if(command[i] == 'a'){
			cerr << "move " << str[p] << " from " << p << " to " << args[i].back() << endl;
			str[args[i].back()] = str[p];
			str[p] = '$';
			assert(get(p) == args[i][0]);
			update(p, -1);
			update(args[i].back(), 1);
		} else {
			cerr << "ask about " << p << endl;
			printf("%c\n", str[p]);
		}
	}
	
	return 0;
}
