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
#define pl pair<ll,ll>
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

const int MAX = 1 << 20;
int A[MAX],n;
int L[MAX],R[MAX];
ll ans = 0;
int lst[MAX],reach[MAX];

ll compute(){
	memset(reach,-1,sizeof reach);
	memset(lst,-1,sizeof lst);
//	prArr(L,n,int);
//	prArr(R,n,int);
	ll ret = 0;
	loop(i,n) {
		if(i <= reach[A[i]]) {
			ret += A[i] * (i - lst[A[i]] + 0LL) * (R[i] - i + 0LL);
			lst[A[i]] = i;
//			cerr << A[i] << " " << (i - lst[A[i]] + 0LL) << " " << (R[i] - i + 0LL) << endl;
		}
		else{
			ret += A[i] * (i - L[i] + 0LL) * (R[i] - i + 0LL);
			lst[A[i]] = i;
			reach[A[i]] = R[i];
//			cerr << A[i] << " " << (i - L[i] + 0LL) << " " <<  (R[i] - i + 0LL) << endl;
		}
	}
//	cerr << endl;
	return ret;
}

void work1(){
	vi ST;
	loop(i,n) {
		while(!ST.empty() && A[ST.back()] <= A[i]) ST.pop_back();
		L[i] = ST.empty() ? -1 : ST.back();
		ST.pb(i);
	}
	ST.clear();
	for(int i = n-1;i >= 0;i--){
		while(!ST.empty() && A[ST.back()] <= A[i]) ST.pop_back();
		R[i] = ST.empty() ? n : ST.back();
		ST.pb(i);
	}
	ans = compute();
}
void work2(){
	vi ST;
	loop(i,n) {
		while(!ST.empty() && A[ST.back()] >= A[i]) ST.pop_back();
		L[i] = ST.empty() ? -1 : ST.back();
		ST.pb(i);
	}
	ST.clear();
	for(int i = n-1;i >= 0;i--){
		while(!ST.empty() && A[ST.back()] >= A[i]) ST.pop_back();
		R[i] = ST.empty() ? n : ST.back();
		ST.pb(i);
	}
	ans -= compute();
}



int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&n);
	loop(i,n) scanf("%d",A + i);
	work1();
//	cout << ans << endl;
	work2();
	cout << ans << endl;
	return 0;
}
