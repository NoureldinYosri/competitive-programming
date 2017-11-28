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

int n,m,q,k;
int A[500][500];
pair<int,pi> T[500*500];

bool cond(ll t){
	memset(A,0,sizeof A);
	for(int i = 0;i < q;i++){
		if(T[i].xx <= t) A[T[i].yy.xx][T[i].yy.yy] = 1;
		else break;
	}
	loop(i,n) loop(j,m) {
		if(i) A[i][j] += A[i-1][j];
		if(j) A[i][j] += A[i][j-1];
		if(i && j) A[i][j] -= A[i-1][j-1];
	}
	for(int i = 0;i <= n-k;i++)
		for(int j = 0;j <= m - k;j++){
			int sum = A[i + k - 1][j + k - 1];
			if(i) sum -= A[i - 1][j + k - 1];
			if(j) sum -= A[i + k - 1][j - 1];
			if(i && j) sum += A[i-1][j-1];
			if(sum == k*k) return 1;
		}
	return 0;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d %d %d",&n,&m,&k,&q);
	loop(i,q){
		scanf("%d %d %d",&T[i].yy.xx,&T[i].yy.yy,&T[i].xx);
		T[i].yy.xx--;
		T[i].yy.yy--;
	}
	sort(T,T + q);
	if(!cond(INT_MAX)) puts("-1");
	else {
		ll s = 0,e = INT_MAX;
		while(s < e){
			ll m = (s + e) >> 1;
			if(cond(m)) e = m;
			else s = m + 1;
		}
		cout << s << endl;
	}
	return 0;
}
