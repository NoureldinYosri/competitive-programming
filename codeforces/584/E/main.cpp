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

const int MAX = 5000 + 10;
int n;
int P[MAX],S[MAX],R[MAX];
vp res;

int getPlan1(int i) {
	return R[i] - i + abs(R[i] - P[i]);
}

void doSwap(int a,int b,bool keep) {
	swap(P[a],P[b]);
	R[P[a]] = a;
	R[P[b]] = b;
	if(keep) res.push_back(mp(a,b));
}

int getPlan2(int i) {
	int r = P[i] - i,a = i,b = P[i];
	doSwap(a,b,0);
	r += getPlan1(i);
	doSwap(a,b,0);
	return r;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&n);
	loop(i,n) {
		scanf("%d",&P[i]);
		P[i]--;
	}
	loop(i,n) {
		scanf("%d",&S[i]);
		S[i]--;
		R[S[i]] = i;
	}
	loop(i,n) P[i] = R[P[i]];
	loop(i,n) R[P[i]] = i;

//	prArr(P,n,int);
	ll ans = 0;
	for(int i = 0;i < n;i++) {
		while(P[i] != i) {
			int d1 = INT_MAX,d2 = INT_MAX,d3 = R[i] - i;
			if(P[i] < R[i]) d1 = R[i] - P[i];;
			if(R[R[i]] < R[i]) d2 = R[i] - R[R[i]];
			if(d1 <= d2 && d1 <= d3){
				ans += R[i] - P[i];
				doSwap(P[i],R[i],1);
			}
			else if(d2 <= d3){
				ans += R[i] - R[R[i]];
				doSwap(R[R[i]],R[i],1);
			}
			else {
				ans += R[i] - i;
				doSwap(i,R[i],1);
			}
		}
	}
	printf("%lld\n",ans);
	printf("%d\n",sz(res));
	for(auto p : res)
		printf("%d %d\n",p.xx+1,p.yy+1);
	return 0;
}
