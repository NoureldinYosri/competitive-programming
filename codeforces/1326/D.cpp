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

const int MAX = 3 << 20;
char txt[MAX], T[MAX];
string ans ;
int n;
int P[MAX];

string suff;

void manacher (char *S) {
	int N = n;
//	cerr << S << endl;
	for (int i = 0,r = -1,c = -1;i < N;i++) {
		int l = 0;
		if (i <= r)
			l = min(P[2*c - i],r - i);
		while (i-l-1 >= 0 && i+l+1 < N && S[i-l-1] == S[i+l+1])
			l++;
		P[i] = l;
		if(i + l > r) {
			r = i + l;
			c = i;
		}
	}
}

void fix(char *T){
	int m = 0;
	txt[m++] = '$';
	loop(i, n){
		txt[m++] = T[i];
		txt[m++] = '$';
	}
	txt[m] = 0;
	n = m;
}

void solve2(){
	if(n == 0) return ;
	fix(T);
	manacher(txt);
	int c = -1, len = 0;
	for(int i = 0; i < n; i++){
		int clen = 2*P[i] + 1;
		int left = i - P[i], right = i + P[i];
		if(!(left == 0 || right == n-1)) continue;
		if(clen > len){
			len = clen;
			c = i;
		}
	}
	if(len <= 1) return;
	int left = c - (len - 1)/2, right = c + (len - 1)/2;
	for(int i = left; i <= right;i++)
		if(txt[i] != '$')
			ans.pb(txt[i]);
}

void solve(){
	int s = 0, e = n-1;
	suff.clear();
	ans.clear();
	while(s < e && txt[s] == txt[e]){
		ans.pb(txt[s++]);
		suff.pb(txt[e--]);
	}
	copy(txt + s, txt + e + 1, T);
	n = e-s+1;
	T[n] = 0;
	solve2();
	reverse(all(suff));
	for(char c : suff) ans.pb(c);
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--){
		scanf("%s", txt);
		n = strlen(txt);
		solve();
		printf("%s\n", ans.c_str());
	}
	return 0;
}
