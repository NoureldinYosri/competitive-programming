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

const ll oo = 1LL << 60;
int A[15], n;
ll sum[1 << 15];
ll dp[1 << 15][16];
int cnt[1 << 15];
int visID[1 << 15][16], visNum;
int choice[1 << 15][16][15];
bool alive[15];

pair<ll, int> solve(int msk, int s, int e){
	if(!msk) return mp(0LL, -1);
	auto & ret = dp[msk][s][e];
	if(visID[msk][s] == visNum) return ret;
	visID[msk][s] = visNum;
	ret.first = oo;
	ret.second = -1;
	
	for(int m = msk; m; m = (m - 1) & msk){
		if(cnt[m]-1 > s) continue;
		auto tmp = solve(msk ^ m, s - (cnt[m] - 1));
//		if(msk == 31) cerr << m << " -> " << tmp << " " << sum[m] << endl;
		if(tmp.first < sum[m]){
			loop(i, n) if((m & (1 << i)) && tmp.second < i){
				auto aux = mp(sum[m], i);
				if(aux < ret){
					ret = aux;
					choice[msk][s] = m;
				}
			}
		}
	}
	cerr << msk << " " << s << " | " << ret << endl;
	return ret;
}

void ask(int i , int j){
	int a = 0, b = 0;
	loop(k, i+1) a += alive[k];
	loop(k, j+1) b += alive[k];
	printf("%d %d\n", a, b);
	alive[i] = 0;
}

void solve(){
	scanf("%d", &n);
	loop(i, n) scanf("%d", A + i);
//	prArr(A, n, int);
	loop(i, 1 << n){
		sum[i] = 0;
		loop(j, n) if(i & (1 << j)) sum[i] += A[j];
	}
	
	visNum++;
	fill(alive, alive + n, 1);
	
	for(int s = 0; s <= n; s++)
		if(solve((1 << n) - 1, s).first < oo){
			printf("%d\n", s);
			int msk = (1 << n) - 1;
			while(msk){
				int m = choice[msk][s];
				int i = dp[msk][s].second;
				loop(j, n) if(i != j && (m & (1 << j))){
					ask(j, i);
				}
				msk ^= m;
				s -= cnt[m] - 1;
			}
			return ;
		}
	assert(0);
	
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	loop(i, 1 << 15) cnt[i] = cnt[i >> 1] + (i & 1);
	int T; scanf("%d", &T);
	while(T--) solve();
	return 0;
}
