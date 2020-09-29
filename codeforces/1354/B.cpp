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

char txt[1 << 20];
int n;
int cnt[4];

int solve(){
	int msk = 0;
	n = strlen(txt);
	loop(i, n) msk |= 1 << (txt[i] - '1');
	if(msk != 7) return 0;
	int ans = n;
	
	int j = -1;
	memset(cnt, 0, sizeof cnt);
	loop(i, n){
		if(j <= i){
			memset(cnt, 0, sizeof cnt);			
			j = i;
		}
		while(j < n && (cnt[1] == 0 || cnt[2] == 0 || cnt[3] == 0)){
			int c = txt[j++] - '0';
			cnt[c]++;
		}
		if(cnt[1] && cnt[2] && cnt[3]) ans = min(ans, j - i);
		cnt[txt[i] - '0']--;
	}
	
	
	return ans;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--){
		scanf("%s", txt);
		printf("%d\n", solve()); 
	}
	return 0;
}
