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

int A[1 << 20];
int n,x;
int bad[1 << 20];
int R[1 << 20];



int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	int MAX; scanf("%d %d",&n,&MAX);
	loop(i,n) scanf("%d",A + i);
	int mx = -1;
	loop(i, n){
		bad[A[i]] = mx;
		mx = max(mx, A[i]);
	}
	
	R[MAX+1] = MAX;
	for(int i = MAX; i; i--){
		if(bad[i] > i) R[i] = R[i+1];
		else if(R[i+1] == i) R[i] = i-1;
		else R[i] = R[i+1];
	}

	ll ans = MAX+1-R[1];
	mx = -1;
	for(int l = 1; l <= MAX; l++){
		mx = max(mx, bad[l]);
		if(bad[l] > l) MAX = min(MAX, bad[l]);
		int r = max(mx, l) + 1;
		cerr << l << " " << mx << " " << r << " " << R[r] << endl;
		ans += MAX-R[r]+1;
		cerr << l << " " << R[r] << " " << MAX+1-R[r] << endl;
	}
	cout << ans << endl;
	
	return 0;
}
