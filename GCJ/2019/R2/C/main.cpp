#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
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
using namespace std;

int n;
int A[100],B[100];
ll x,y;

void solve(){
	x = y = 1;
	ll prv = 0;
	bool done = 1;
	loop(i,n) {
		ll cur = A[i]*x + B[i]*y;
		if(prv >= cur) done = 0;
		prv = cur;
	}
	if(done) return;
	x = y = -1;
	int evidence = -2;
	int a = 1,b = 1;
	auto cmp = [](const pi & A,const pi & B) {
		return A.xx*(ll)B.yy - A.yy*(ll)B.xx;
	};
	loop(i,n) {
		for(int j = i+1;j < n;j++) {
			int dx = A[j] - A[i],dy = B[j] - B[i];
			if(dx < 0 && dy < 0) return;
			if(dx == 0 && dy == 0) return;
			// dx*x + dy*y > 0
			if(dx == 0 || dy == 0) continue;
			if(dx > 0 && dy > 0) continue;
			if(dx > 0) {
				// dx*x > -dy*y
				int ra = -dy,rb = dx;
				if(evidence == -2 || cmp(mp(a,b),mp(ra,rb)) > 0) {
					a = ra;
					b = rb;
				}
				if(evidence == -2) evidence = 1;
				if(evidence != 1) return;
			}
			else {
				// dy*y > -dx*x
				int ra = -dx,rb = dy;
				if(evidence == -2 || cmp(mp(a,b),mp(ra,rb)) > 0) {
					a = ra;
					b = rb;
				}
				if(evidence == -2) evidence = -1;
				if(evidence != -1) return;
			}

		}
	}
	if(evidence == -2) return;
	x = 1;
	y = b/a + 1;
	if(evidence == 1) swap(x,y);
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	int T; scanf("%d",&T);
	range(t,1,T) {
		scanf("%d",&n);
		loop(i,n) scanf("%d %d",A+i,B+i);
		solve();
		printf("Case #%d: ",t);
		if(x == -1) puts("IMPOSSIBLE");
		else printf("%lld %lld\n",x,y);
	}

	return 0;
}
