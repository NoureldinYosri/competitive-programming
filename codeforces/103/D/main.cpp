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

const int MAX = 300*1000,MAXB = 500;
int A[MAX],n,m;
pair<pi,int> Q[MAX];
ll val[MAX],ans[MAX];


int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&n);
	loop(i,n) scanf("%d",A + i);
	scanf("%d",&m);
	loop(i,m) {
		scanf("%d %d",&Q[i].xx.yy,&Q[i].xx.xx);
		Q[i].xx.yy--;
		Q[i].yy = i;
	}
	sort(Q,Q + m);
	for(int i = 0;i < m;i++) {
		int k = Q[i].xx.xx;
		if(k > MAXB) {
			int p = Q[i].xx.yy,idx = Q[i].yy;
			while(p < n) {
				ans[idx] += A[p];
				p += k;
			}
		}
		else {
			for(int p = n-1;p >= 0;p--) {
				val[p] = A[p];
				if(p + k < n) val[p] += val[p + k];
			}
			int j = i;
			while(j < m && Q[i].xx.xx == Q[j].xx.xx) {
				int p = Q[j].xx.yy,idx = Q[j].yy;
				ans[idx] = val[p];
				++j;
			}
			i = j - 1;
		}
	}
	loop(i,m) printf("%lld\n",ans[i]);
	return 0;
}
