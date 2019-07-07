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
int A[1000],B[1000];
set<vi> S;
ll C[1000];
int ord[1000];

void getOrder2(ll x,ll y) {
	if(x <= 0 || y <= 0) return;
	loop(i,n) {
		ord[i] = i;
		C[i] = A[i]*(ll)x + B[i]*(ll)y;
	}
	auto cmp = [](const int &a,const int & b) {
		return C[a] < C[b];
	};
	sort(ord,ord + n,cmp);
	loop(i,n-1){
		int a = ord[i],b = ord[i+1];
		if(C[a] == C[b]) return;
	}
	S.insert(vi{ord,ord + n});
}

void getOrder(int a,int b) {
	// a*x + b*y ? 0
	// y = a
	// x = b+1
	for(int i = -2;i <= 2;i++)
		for(int j = -2;j <= 2;j++){
			getOrder2(-b+i,a+j);
			getOrder2(b+i,-a+j);
		}
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	int T; scanf("%d",&T);
	for(int t = 1;t <= T;t++) {
		scanf("%d",&n);
		loop(i,n) scanf("%d %d",A + i,B + i);
		S.clear();
		getOrder2(1,1);
		getOrder2(1,2);
		getOrder2(2,1);
		loop(i,n) loop(j,i) {
			int a = A[i] - A[j];
			int b = B[i] - B[j];
			if(a < 0) a *= -1,b *= -1;
			int g = __gcd(abs(a),abs(b));
			a /= g;
			b /= g;
			getOrder(a,b);
		}
		vi V;
		loop(i,n) {
			V.push_back(A[i]);
			V.push_back(B[i]);
			V.push_back(abs(A[i] - B[i]));
		}
		sort(all(V));
		V.resize(unique(all(V)) - V.begin());
		for(int x : V) {
			for(int i = -2;i <= 2;i++){
				getOrder2(1,x + i);
				getOrder2(x + i,1);
			}
		}
		for(int i = 1;i <= 10000;i++)
			getOrder2(i,1),getOrder2(1,i);
		printf("Case #%d: %d\n",t,sz(S));
	}
	return 0;
}
