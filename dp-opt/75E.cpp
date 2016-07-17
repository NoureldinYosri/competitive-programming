#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define print(A,t) cout << #A << ": "; copy(all(A),ostream_iterator<t>(cout," " )); cout << endl
#define pi pair<int,int>
#define point pi
#define vi vector<int>
#define ll long long
#define pl pair<ll,ll>
#define pre() cin.tie(0),cout.tie(0),ios_base::sync_with_stdio(0)
#define sgn(x) (((x) > 0) - ((x) < 0))
#define popcnt(x) __builtin_popcount(x)
using namespace std;

const int MAX = 1e5 + 10;
ll a[MAX],b[MAX];
deque<int> bucket[1010];
int buck_sz;
pair<pi,pi> Q[MAX];
int T[MAX];
int n,m;

inline long double g(int j,int i){
	return (a[i] - a[j] + 0.0)/(b[i] - b[j]);
}

inline ll f(int i,ll t){
	return b[i] * t + a[i];
}

bool cmp(const int i,const int j){
	return (b[i] == b[j]) ? (a[i] < a[j]) : (b[i] < b[j]);
}

void construct(deque<int> & dq){
	sort(all(dq),&cmp);
	deque<int> tmp;
	for(int i : dq){
		while(sz(tmp) >= 1 && b[tmp.back()] == b[i]) tmp.pop_back();
		while(sz(tmp) > 1 && g(tmp[sz(tmp) - 2],i) <= g(tmp[sz(tmp) - 1],i)) tmp.pop_back();
		tmp.pb(i);
	}
	dq = tmp;
}

pair<int,ll> get(int l,int r,ll t){
	r = min(r,n - 1);
	pair<int,ll> ret = mp(l,LLONG_MIN);
	for(;l <= r;l++) {
		ll tmp = f(l,t);
		if(tmp > ret.second) ret.first = l,ret.second = tmp;
	}
	return ret;
}

int main(){
	scanf("%d %d",&n,&m);
	buck_sz = sqrt(n) + 1; buck_sz = min(buck_sz,n);
	int ctr = -1;	
	loop(i,n){
		scanf("%I64d %I64d",&a[i],&b[i]);
		if(i%buck_sz) bucket[ctr].pb(i);
		else bucket[++ctr].pb(i);
	}
	loop(i,ctr + 1) construct(bucket[i]);
	loop(i,m) scanf("%d %d %d",&Q[i].second.first,&Q[i].second.second,&Q[i].first.first),Q[i].first.second = i;
	sort(Q,Q + m);
	loop(i,m){
		int idx = Q[i].first.second,t = Q[i].first.first,l = Q[i].second.first - 1,r = Q[i].second.second - 1;
		int L = l/buck_sz,R = r/buck_sz;
		if(L == R) T[idx] = get(l,r,t).first;
		else{
			pair<int,ll> tmp,z;
			tmp = get(l,(L + 1)*buck_sz - 1,t);
			z = get(R*buck_sz,r,t);
			if(z.second > tmp.second) tmp = z;
			for(++L; L < R;L++){
				while(sz(bucket[L]) > 1 && f(bucket[L][0],t) <= f(bucket[L][1],t)) bucket[L].pop_front();
				ll ttt = f(bucket[L][0],t);
				if(ttt > tmp.second) tmp.first = bucket[L][0],tmp.second = ttt;
			}
			T[idx] = tmp.first;
		}
	}
	loop(i,m) printf("%d\n",T[i] + 1);
}
