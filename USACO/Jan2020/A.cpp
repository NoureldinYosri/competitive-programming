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

const int MAXN = 20, MAX = MAXN*MAXN;
const int mod = 1e9 + 7;
char G[MAXN][MAXN];
int p2[MAX];
int m, n;
int add(int a,int b){
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}
int mul(int a, int b){
	return (a*(ll)b)%mod;
}

int name[MAXN][MAXN];
pi cnts[MAX];
bool rise[MAXN];



int main(){
	freopen("cave.in", "r", stdin);
	freopen("cave.out", "w", stdout);
	p2[0] = 1;
	for(int i = 1;i < MAX;i++) p2[i] = mul(p2[i-1], 2);

	scanf("%d %d", &m, &n);
	loop(i, m){
		scanf("%s", G[i]);
	}
	
	

	int res = 1;
	for(int r = m-2; r >= 0; r--){
		int q = 0;
		for(int c = 0;c < n;c++){
			if(G[r+1][c] == '#') continue;
			name[r][c] = name[r+1][c];
			rise[name[r][c]] = 0;
			q = max(q, name[r][c]);
		}
		
		
		vector<pair<bitset<MAXN>, pair<list<int>, list<int>> >> ST;
		for(int c = 0;c < n;c++) if(G[r][c] == '.'){
			bitset<MAXN> bits;
			list<int> U;
			list<int> V;
			while(c < n && G[r][c] == '.'){
				U.push_back(c);
				if(name[r][c]) {
					bits.set(name[r][c]);
					V.pb(name[r][c]);
				}
				c++;
			}
			while(!ST.empty()){
				if((ST.back().first & bits).any()) {
					bits |= ST.back().first;
					U.splice(U.end(), ST.back().second.first);
					V.splice(V.end(), ST.back().second.second);
					ST.pop_back();
				}
				else break;
			}
			ST.push_back(mp(bits, mp(U,V)));
//			cerr << bits << endl;
		}
		
//		cerr << endl;
		
		vector<pi> tmp;
		for(int i = 0;i < sz(ST);i++){
			for(int c : ST[i].second.first)
				name[r][c] = i+1;
			pi ctr;
			for(int j : ST[i].second.second)
				if(ST[i].first.test(j)){
					ST[i].first.reset(j);
					rise[j] = 1;
					ctr.first += cnts[j].first;
					ctr.second += cnts[j].second;
				}
			if(ctr.first == 0) ctr.first++;
			else ctr.second++;
			tmp.push_back(ctr);
		}
		for(int j = 1;j <= q;j++)
			if(!rise[j]){
		//		cerr << j << ": " << cnts[j] << endl;
				res = mul(res, add(p2[cnts[j].first], cnts[j].second));
			}
		for(int i = 0;i < sz(ST);i++)
			cnts[i+1] = tmp[i];
		
	}
	cout << res << endl;
	cerr << res << endl;
	return 0;
}


