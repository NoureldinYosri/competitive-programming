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

const int MAX = 4*100*1000 + 10;
int n, m, k;
int L[MAX], R[MAX];
vi aux;
vi ST[MAX], EN[MAX];
vi what[MAX];

int dp[2][1 << 8];
int I[2][MAX];

int get_real_msk(int submsk, const vi & V, int *rI){
	int msk = 0;
	loop(i, sz(V)) if(submsk & (1 << i)){
		int j = V[i];
		int k = rI[j];
		msk |= 1 << k;
	}
	return msk;
}

void fix(const vi & V, int *rI){
	loop(i, sz(V)) rI[V[i]] = i;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d %d", &n, &m, &k);
	loop(i, n){
		int l, r; scanf("%d %d", &l, &r);
		L[i] = l;
		R[i] = r;
		aux.pb(l);
		aux.pb(r);
		aux.pb(l-1);
		aux.pb(r-1);
	}
	sort(all(aux));
	aux.resize(unique(all(aux)) - aux.begin());
	loop(i, n) {
		L[i] = lower_bound(all(aux), L[i]) - aux.begin();
		R[i] = lower_bound(all(aux), R[i]) - aux.begin();		
		ST[L[i]].pb(i);
		EN[R[i]].pb(i);
	}
	set<int> S;
	loop(i, sz(aux)){
		for(int q : ST[i])
			S.insert(q);
		what[i] = vi{all(S)};
		sort(all(what[i]));
		for(int q : EN[i])
			S.erase(q);
//		print(what[i], int);
	}
	
	int cur = 0, other = 1;
	
	
	for(int i = sz(aux)-1; i >= 0; i--){
		swap(cur, other);
		fix(what[i], I[0]);
		fix(what[i+1], I[1]);

		vi In, right_diff;
		for(int q : what[i+1]) {
			if(binary_search(all(what[i]), q)) In.pb(q);
			else right_diff.pb(q);
		}

		for(int msk = 0;msk < (1 << sz(what[i])); msk++)
			dp[cur][msk] = 0;
		
		int w = i ? (aux[i] - aux[i-1]) : 1;

		for(int in_msk = 0; in_msk < (1 << sz(In)); in_msk++){
			int reinterpret = get_real_msk(in_msk, In, I[1]);
			
			for(int diff_msk = 0; diff_msk < (1 << sz(right_diff)); diff_msk++){
				int msk = reinterpret | get_real_msk(diff_msk, right_diff, I[1]);
				dp[other][reinterpret] = max(dp[other][reinterpret], dp[other][msk]);
			}
		}
		for(int in_msk = 0; in_msk < (1 << sz(In)); in_msk++){
			int real_msk = get_real_msk(in_msk, In, I[0]);
			int reinterpret = get_real_msk(in_msk, In, I[1]);
			int offset = dp[other][reinterpret];

			for(int diff_msk = 0; diff_msk < (1 << sz(EN[i])); diff_msk++){
				int msk = real_msk | get_real_msk(diff_msk, EN[i], I[0]);
				int ctr = msk ? popcnt(msk) : 0;
				dp[cur][msk] = max(dp[cur][msk], offset + (ctr & 1) * w);
			}
		}
//		prArr(dp[cur], (1 << k), int);
	}
	
	
	cout << *max_element(dp[cur], dp[cur] + (1 << 8)) << endl;
	return 0;
}
