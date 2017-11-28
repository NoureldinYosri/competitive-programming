#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define popcnt(x) __builtin_popcountll(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
using namespace std;

const int MAX = 1000;
int f[MAX][MAX];
char S[MAX];

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	while(scanf("%s",S) == 1){
		int n = strlen(S);
		memset(f,-1,sizeof f);
		for(int i = 0;i < n;i++)
			for(int j = 0;j < n;j++){
				int t = 0;
				while(i+t < n && j + t < n && S[i + t] == S[j + t]) t++;
				f[i][j] = t;
			}
		int ans = n;
		for(int len = 1;len <= n;len++)
			for(int i = 0;i < n;i++){
				int cnt[MAX] = {0};
				for(int j = n-1;j >= 0;j--){
					cnt[j] = cnt[j + 1];
					if(f[i][j] >= len)
						cnt[j] = max(cnt[j],cnt[j + len] + 1);
				}
				ans = min(ans,n + cnt[0] + len - cnt[0]*len);
			}
		cout << ans << endl;
	}
	return 0;
}
