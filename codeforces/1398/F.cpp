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


int pref[2][1 << 20];
char txt[1 << 20];
int n;
int X[1 << 20];
int nxt[1 << 20];


bool isGood(int i, int x){
	if(i + x - 1 > n) return false;
	bool has[2] = {false, false};
	loop(c, 2) has[c] = pref[c][i + x - 1] - pref[c][i-1];
	return !(has[0] && has[1]);
}

int find(int i, int x){
	if(nxt[i] > n || X[nxt[i]] >= x) return nxt[i];
	return nxt[i] = find(nxt[i], x); 
}


int f(int x){
	int ret = 0;
	for(int i = 1; i+x-1 <= n;){
		if(!isGood(i, x)) i = find(i, x);
		else {
			ret ++;
			i += x;
		}
	}
	return ret;
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %s", &n, txt);
	loop(i, n){
		loop(c, 2) pref[c][i + 1] = pref[c][i] + (txt[i]-'0' == c); 
	}
	for(int i = 1; i <= n; i++){
		int s = 1, e = n-i+1;
		while(s < e){
			int m = s + (e-s+1)/2;
			if(isGood(i, m)) s = m;
			else e = m-1;
		}
		X[i] = s;
	}
	vi ST;
	for(int i = n; i; i--){
		while(!ST.empty() && X[ST.back()] <= X[i]) ST.pop_back();
		nxt[i] = ST.empty() ? (n + 1) : ST.back();
		ST.pb(i); 
	}
	for(int x = 1; x <= n; x++)
		printf("%d%c", f(x), " \n"[x == n]);
	return 0;
}
