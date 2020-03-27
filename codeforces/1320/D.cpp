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

char S[1 << 20];
int n;

int cnt[1 << 20];
set<int> zeros;
int f[1 << 20][2];
int D[1 << 20];
int mod[2] = {1000000007, 1000000009};
int base[2] = {3, 5};
int base_power[2][1 << 20];

int mul(int a, int b, int m){
	return (a*(ll)b)%m;
}
int add(int a, int b, int m){
	a += b;
	if(a >= m) a -= m;
	if(a < 0) a += m;
	return a;
}

void preprocess(){
	loop(i, n) {
		cnt[i] = S[i] - '0' + (i ? cnt[i-1] : 0);
		if(S[i] == '0'){
			zeros.insert(i);
		}
	}
	loop(k, 2){
		base_power[k][0] = 1;
		for(int i = 1;i <= n;i++)
			base_power[k][i] = mul(base_power[k][i-1], base[k], mod[k]);
	}
	int h[2] = {0, 0};
	int ctr = 0;
	for(int i = 0;i < n;){
		D[i] = ctr;
		if(S[i] == '0'){
			D[i] = ++ctr;
			loop(k, 2){
				h[k] = mul(h[k], base[k], mod[k]);
				h[k] = add(h[k], 1, mod[k]);
				f[i][k] = h[k];
			}
			i++;
			continue;
		}
		int j = i;
		while(j < n && S[j] == '1') j++;
		int v = (j - i) & 1;
		if(!v) {
			i = j;
			continue;
		}
		ctr++;
		loop(k, 2){
			h[k] = mul(h[k], base[k], mod[k]);
			h[k] = add(h[k], 2, mod[k]);
		}
		i = j;
	}
	
}

int get_ones(int s, int len){
	return cnt[s+len-1] - (s ? cnt[s-1] : 0);
}

pair<pi, pi> get_f(int l, int r){
	if(zeros.empty()) return pair<pi, pi>(pi((r-l+1)&1, 0), pi(0, 0));
	auto ptr1 = zeros.lower_bound(l);
	auto ptr2 = zeros.upper_bound(r);
	if(ptr2 == zeros.begin()) return pair<pi, pi>(pi((r-l+1)&1, 0), pi(0, 0));
	ptr2--;
	if(*ptr2 < l) return pair<pi, pi>(pi((r-l+1)&1, 0), pi(0, 0));
	
	int i = *ptr1, j = *ptr2;
	int pref = (i - l)&1;
	int suff = (r - j)&1;
	int h[2] ;
	loop(k, 2){
		h[k] = add(f[j][k], -mul(add(f[i][k], -1, mod[k]), base_power[k][D[j]-D[i]], mod[k]), mod[k]);
	}
	
	
	return pair<pi, pi>(pi(pref, suff), pi(h[0], h[1]));
}

bool solve(int a, int b, int len){
	if(get_ones(a, len) != get_ones(b, len)) return 0;
	//cerr << "\t" << a << " " << b << " " << len << endl;
	return get_f(a, a + len - 1) == get_f(b, b + len - 1);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %s", &n, S);
	int m; scanf("%d", &m);
	preprocess();
	loop(i, m){
		int a, b, len;
		scanf("%d %d %d", &a, &b, &len);
		a--, b--;
		puts(solve(a, b, len) ? "Yes" : "No");
	}
	return 0;
}
