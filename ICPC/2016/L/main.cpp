#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define point pair<double,double>
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

const int MAX = 1000*1000;
int A[MAX],B[MAX],C[MAX],n,ord[MAX];
vi T1,T2;

int main(){
	scanf("%d",&n);
	loop(i,n) {
		scanf("%d %d",A + i,B + i);
		C[i] = B[i] - A[i];
		if(C[i] >= 0) T1.pb(i);
		else T2.pb(i);
	}
	ll ans = 0,cap = 0;
	sort(all(T1),[](const int & a,const int & b){
		return tie(A[a],B[b]) < tie(A[b],B[a]);
	});
	sort(all(T2),[](const int & a,const int & b){
		return tie(B[a],A[b]) > tie(B[b],A[a]);
	});
	for(int p : T1) {
		ans += max(A[p] - cap,0LL);
		cap += max(A[p] - cap,0LL);
		cap += B[p] - A[p];
	}
	for(int p : T2){
	//	prp(mp(A[p],B[p]));
		ans += max(A[p] - cap,0LL);
		cap += max(A[p] - cap,0LL);
		cap += B[p] - A[p];
//		cerr << " " << ans << " " << cap << endl;
	}
//	cerr << endl;
	cerr << ans << endl;
	cout << ans << endl;
	return 0;
}
