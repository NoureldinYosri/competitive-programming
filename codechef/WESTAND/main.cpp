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


int speed[10],salary[10],K;
int dishes[50],deadline[50],N;


int work(int msk) {
	vi chef;
	loop(i,msk) if(msk & (1 << i)) chef.pb(i);
	sort(all(chef),[](const int & a,const int & b) {
		return speed[a] > speed[b];
	});

	vi ord;
	loop(i,N) ord.pb(i);
	sort(all(ord),[](const int & a,const int & b) {
		return deadline[a] < deadline[b];
	});

	set<pair<double,int> > E;



	int ret = 0;
	for(int c : chef) ret += salary[c];
	return ret;
}


int solve(){
	int ret = INT_MAX;
	loop(msk,1 << K)
		if(msk)
			ret = min(ret,work(msk));
	if(ret == INT_MAX)ret = -1;
	return ret;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	int T; scanf("%d",&T);
	range(t,1,T) {
		scanf("%d",&K);
		loop(i,K) scanf("%d %d",speed+i,salary+i);
		scanf("%d",&N);
		loop(i,N) scanf("%d %d",dishes+i,deadline+i);
		printf("%d\n",solve());
	}
	return 0;
}
