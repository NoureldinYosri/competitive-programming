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
int ans[1 << 20];

void duval(string const& s) {
    int n = s.size();
    loop(i, n) ans[i] = -1;
    int r = -1, len = 0;
    char lst = 127;
    loop(q, n) if((q > r || s[q] > lst) && ans[q] == -1) {
		int i = q;
		while (i < n) {
			int j = i + 1, k = i;
			while (j < n && s[k] <= s[j]) {
				if (s[k] < s[j])
					k = i;
				else
					k++;
				j++;
			}
			while (i <= k) {
				ans[i] = j - k;
				i += j - k;
			}
		}
		r = q + ans[q] - 1;
		lst = s[q];
		len = ans[q];		
//		prArr(ans, n, int);
	}
	else if(ans[q] == -1) ans[q] = --len;
	else {
		r = q + ans[q] - 1;
		lst = s[q];
		len = ans[q]; 
	}
/*	int mx = 0;
	loop(i, n) {
		ans[i] = mx = max(mx, ans[i]);
		mx--;
	}
*/	loop(i, n) printf("%d ", ans[i]);
	puts("");
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--){
		scanf("%d %s", &n, txt);
		string s(txt);
		duval(txt);
	}
	return 0;
}
