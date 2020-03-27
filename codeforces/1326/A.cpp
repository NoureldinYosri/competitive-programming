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


const int MAXN = 100*1000 + 10;


bool check(ll n){
	ll m = n;
	while(m){
		if(m%10 == 0) return 0;
		int d = m%10;
		if(n%d == 0) return 0;
		m /= 10;
	}
	return 1;
}

bool check(const string & s){
	set<char> D{all(s)};
	if(D.count('0')) return 0;
	if(D.count('1')) return 0;
	for(char cd : D){
		int d = cd - '0';
		int r = 0;
		for(char c : s)
			r = (r*10 + c - '0')%d;
		if(r == 0) return 0;
	}
	return 1;
}

void increase(string & s){
	for(int i = sz(s) - 1;i >= 0;i--){
		if(s[i] == '9'){
			s[i] = '0';
			continue;
		}
		s[i]++;
		return;
	}
	s = "1" + string(sz(s), '0');
}





int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	string s;
	while(T--){
		int n; scanf("%d", &n);
		if(n == 1) puts("-1");
		else {
			s.clear();
			loop(i, n-1) s.push_back('2');
			s.push_back('3');
			while(!check(s)) increase(s);
			printf("%s\n", s.c_str());
		}
	}
	
	return 0;
}
