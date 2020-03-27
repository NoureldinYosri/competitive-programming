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
int fst[1 << 20], lst[1 << 20];
int len[1 << 20], n;
int latest[1 << 20][21];

bool intersect(int a, int b, int c, int d){
	if(a > c) swap(a, c), swap(b, d);
	return c <= b;
}



int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%s", S);
	n = strlen(S);
	memset(fst, -1,sizeof fst);
	memset(lst, -1,sizeof fst);
	loop(i, n){
		for(int j = 0, m = 0;j < 20 && i+j < n; j++){
			int b = S[i+j] - 'a';
			b = 1 << b;
			if(m & b) break;
			m |= b;
			
			if(fst[m] == -1) fst[m] = i;
			lst[m] = i;
		}
	}
	for(int m = 1; m < (1 << 20); m++)
		len[m] = len[m >> 1] + (m & 1);
	
	memset(latest, -1, sizeof latest);
	for(int m = 1;m < (1 << 20); m++){
		if(lst[m] != -1)
			latest[m][len[m]] = lst[m];
		loop(b, 20){
			if((m >> b) & 1) {
				for(int l = 1;l <= 20; l++)
					latest[m][l] = max(latest[m][l], latest[m ^ (1 << b)][l]);
			}
		}
	}
	
	int ans = 0, tot = (1 << 20) - 1;
	for(int m = 1; m < (1 << 20); m++) if(fst[m] != -1)  {
		ans = max(ans, len[m]);
		int s = tot ^ m;
		for(int l = len[s]; l; l--){
			if(latest[s][l] == -1) continue;
			if(!intersect(fst[m], fst[m] + len[m] - 1, latest[s][l], latest[s][l] + l - 1))
				ans = max(ans, len[m] + l);
		}
	}
	cout << ans << endl;


	return 0;
}
