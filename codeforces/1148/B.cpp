#ifdef ACTIVE
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

const int MAX = 200*1000 + 10;
int A[MAX],B[MAX],n,m,K,ta,tb;
int To[MAX];

bool can(int pivot) {
	static vi VA,VB;
	VA.clear(),VB.clear();
	int ctr = 0;
	loop(i,n) {
		if(A[i] + ta > B[pivot]) break;
		VA.push_back(A[i] + ta);
	}
	if(VA.empty()) return 0;
	loop(i,m) {
		if(B[i] > B[pivot]) break;
		if(B[i] < VA[0]) continue;
		VB.push_back(B[i]);
	}
	int res = min(sz(VA),sz(VB));
	loop(i,sz(VA)){
		ctr = i;
		int t = VA[i];
		auto ptr = lower_bound(all(VB),t);
		ctr += VB.end() - ptr;
		res = min(res,ctr);
	}
	return res > K;
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	scanf("%d %d %d %d %d",&n,&m,&ta,&tb,&K);
	loop(i,n) scanf("%d",A + i);
	loop(i,m) scanf("%d",B + i);
	if(K >= n || K >= m || !can(m-1)) {
		puts("-1");
		return 0;
	}
	int s = 0,e = m-1;
	while(s < e) {
		int mid = (s + e) >> 1;
		if(can(mid)) e = mid;
		else s = mid + 1;
	}
	printf("%d\n",B[s] + tb);
	return 0;
}
#endif
