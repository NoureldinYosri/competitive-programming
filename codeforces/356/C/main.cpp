#pragma GCC optimize ("O3")
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

int cnt[5];

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	int n;
	scanf("%d",&n);
	loop(i,n){
		int x; scanf("%d",&x);
		cnt[x]++;
	}
	int ans = 0;
	int m = min(cnt[1],cnt[2]);
	cnt[1] -= m;
	cnt[2] -= m;
	cnt[3] += m;
	ans += m;
//	prArr(cnt+1,4,int);
//	cerr << m << endl;
	if(cnt[1]) {
		cnt[3] = min(cnt[3],2);
		cnt[4] = min(cnt[4],2);
		int tmp = INT_MAX;
		for(int to3 = 0;to3 <= cnt[3] && to3 <= cnt[1];to3++){
			for(int i = 0;i <= cnt[4];i++){
				int c = cnt[1] - to3 + i;
				// 3*x + 4*y = c
				for(int x = 0;3*x <= c;x++) {
					int y = c - 3*x;
					if(y%4) continue;
					y /= 4;
					tmp = min(tmp, 2*x + 3*y + to3);
				}
			}
		}
		if(tmp == INT_MAX) {
			puts("-1");
			return 0;
		}
		ans += tmp;
	}
	else if(cnt[2]) {
		int tmp = INT_MAX;
		for(int a = 0;3*a <= cnt[2];a++){
			int cost = 2*a;
			int c2 = cnt[2] - 3*a;
			cost += 2*(c2/2);
			c2 %= 2;
			if(c2){
				if(cnt[4]) cost++;
				else if(cnt[3] >= 2) cost += 2;
				else cost = INT_MAX;
			}
			tmp = min(tmp,cost);
		}
		if(tmp == INT_MAX) {
			puts("-1");
			return 0;
		}
		ans += tmp;
	}
	cout << ans << endl;

	return 0;
}
