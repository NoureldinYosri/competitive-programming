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
char aux[1 << 20];
int n;

void tc(){
	scanf("%s", S);
	n = strlen(S);
	if(n == 1){
		puts("0");
		return;
	}
	int ans = n;
	loop(i, 26) loop(j, 26) if(i != j) {
		char c1 = i + 'a';
		char c2 = j + 'a';
		int tmp = 0;
		tmp += c1 != S[0];
		tmp += c2 != S[1];
		aux[0] = c1;
		aux[1] = c2;
		for(int k = 2; k < n; k++){
			bool must_change = false;
			if(S[k] == aux[k - 1]) must_change = true;
			if(S[k] == aux[k - 2]) must_change = true;
			if(must_change) aux[k] = '?';
			else aux[k] = S[k];
			tmp += must_change;
		} 
		ans = min(ans, tmp);
	}
	printf("%d\n", ans);
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--) tc();	
	return 0;
}
