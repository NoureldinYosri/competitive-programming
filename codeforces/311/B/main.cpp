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

const int MAXN = 100*1000 + 10,MAXT = 1000*1000*1000;
typedef pair<ll,ll> line;
const ll oo = 1LL << 60;
int n,m,P;
int pos[MAXN];
ll S[MAXN],pref[MAXN];
ll dp[2][MAXN];


auto f = [](const line & L,const ll & x) {
	return L.first*x + L.second;
};

double g(line a,line b) {
	assert(a.first > b.first);
	return (b.second - a.second + 0.0)/(a.first - b.first);
}

void insert(line L,deque<line> & dq) {
	while(sz(dq) > 1) {
		int s = sz(dq);
		line a = dq[s-2],b = dq[s-1];
		//a.first > b.first > L.first
		if(g(a,L) <= g(a,b)) dq.pop_back();
		else break;
	}
	dq.push_back(L);
}

ll query(ll x,deque<line> & dq) {
	while(sz(dq) > 1 && f(dq[0],x) >= f(dq[1],x))
		dq.pop_front();
	return f(dq[0],x);
}


int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	scanf("%d %d %d",&n,&m,&P);
	for(int i = 2;i <= n;i++) {
		int d ; scanf("%d",&d);
		pos[i] = pos[i - 1] + d;
	}
	ll mn = INT_MAX,mx = INT_MIN;
	for(int i = 1;i <= m;i++) {
		int h,t; scanf("%d %d",&h,&t);
		S[i] = t - pos[h];
//		S[i] = max(S[i],0LL);
		mn = min(mn,S[i]);
		mx = max(mx,S[i]);
	}
	sort(S+1,S + m + 1);
	for(int i = 1;i <= m;i++)
		pref[i] = pref[i - 1] + S[i];
//	prArr(S,m+1,ll);
	for(int i = 0;i <= m;i++)
		dp[0][i] = (i != 0)*oo;
	int cur = 0,prv = 1;
	deque<line> dq;
	for(int p = 1;p <= P;p++) {
		swap(cur,prv);
		dq.clear();
		insert(line(0,0),dq);
		//f[r] = min dp[l] + sum S[r] - S[i]
		//     = min dp[l] + S[r]*(r - l) - pref[r] + pref[l]
		//     = min -l*S[r] + dp[l] + pref[l] + S[r]*r - pref[r]
		for(int r = 1;r <= m;r++) {
			dp[cur][r] = query(S[r],dq) + S[r]*r - pref[r];
			line L(-r,dp[prv][r] + pref[r]);
			insert(L,dq);
		}
//		prArr(dp[cur],m+1,ll);
	}

	cout << dp[cur][m] << endl;
	return 0;
}
