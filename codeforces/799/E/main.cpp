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

struct quanta{
	int idx,val;
public:
	quanta(){idx = val = -1;}
	quanta(int _idx,int _val){
		idx = _idx;
		val = _val;
	}
	bool operator < (const quanta & o) const {
		return tie(val,idx) < tie(o.val,o.idx);
	}
};

const ll oo = 1LL << 58;
const int MAX = 200*1000 + 110;
int n,m,K;
int price[MAX],vis[MAX];
vi A,B,AB,nAB;
vl prefA,prefB,prefAB,prefnAB;
set<quanta> S1,S2;
ll sum_r = 0;



void make(int siz){
	static int first = 1;
	int ctr = 0;
	while(sz(S1) < siz && !S2.empty()){
		S1.insert(*S2.begin());
		sum_r += S2.begin()->val;
		S2.erase(S2.begin());
		++ctr;
	}
	while(sz(S1) > siz) {
		S2.insert(*S1.rbegin());
		sum_r -= S1.rbegin()->val;
		S1.erase(*S1.rbegin());
		++ctr;
	}
	if(siz && sz(S1) == siz && !S2.empty()){
		while(S1.rbegin()->val > S2.begin()->val){
			int x = S1.rbegin()->idx,y = S2.begin()->idx;
			sum_r -= price[x];
			sum_r += price[y];
			auto X = quanta(x,price[x]),Y = quanta(y,price[y]);
			S1.insert(Y); S2.insert(X);
			S1.erase(X); S2.erase(Y);
			++ctr;
		}
	}
	if(!first) assert(ctr <= 10);
	first = 0;
}


void com_sum(vl & pref,vi & A){
	int n = sz(A);
	pref = vl(n,0);
	ll sum = 0;
	for(int i = 0;i < n;i++){
		sum += price[A[i]];
		pref[i] = sum;
	}
}


void preprocess(){
	loop(i,n){
		if(vis[i] == 1) A.pb(i);
		else if(vis[i] == 2) B.pb(i);
		else if(vis[i] == 3) AB.pb(i);
		else nAB.pb(i);
	}
	auto cmp = [](const int & a,const int & b){
		return price[a] < price[b];
	};
	sort(all(A),cmp);
	sort(all(B),cmp);
	sort(all(AB),cmp);
	com_sum(prefA,A);
	com_sum(prefB,B);
	com_sum(prefAB,AB);
	for(int i = 0;i < n;i++) if(vis[i] != 3) S2.insert(quanta(i,price[i]));
}

ll get(vl & A,int n){
	if(n < 0 || n > sz(A)) return oo;
	if(!n) return 0;
	return A[n - 1];
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d %d",&n,&m,&K);
	int M = m;
	loop(i,n) scanf("%d",price + i);
	scanf("%d",&m);
	loop(i,m) {
		int x; scanf("%d",&x); -- x;
		vis[x] = 1;
	}
	scanf("%d",&m);
	loop(i,m) {
		int x; scanf("%d",&x); -- x;
		vis[x] |= 2;
	}

	preprocess();

/*
	print(A,int);
	print(B,int);
	print(AB,int);
	print(nAB,int);
	print(prefA,ll);
	print(prefB,ll);
	print(prefAB,ll);
*/
	ll ans = oo;
	m = M;
	int i = 0;
	for(int k = min(K,sz(AB));k >= 0;k--){
		int r = K - k;
		if(r > sz(A) || r > sz(B)) break;
		while(i < r){
			int x = A[i];
			auto tmp = quanta(x,price[x]);
			if(S1.find(tmp) != S1.end()) {
				sum_r -= price[x];
				S1.erase(tmp);
			}
			else S2.erase(tmp);
			x = B[i];
			tmp = quanta(x,price[x]);
			if(S1.find(tmp) != S1.end()) {
				sum_r -= price[x];
				S1.erase(tmp);
			}
			else S2.erase(tmp);

			i++;
		}
		while(sz(AB) > k) {
			int x = AB.back();
			S2.insert(quanta(x,price[x]));
			AB.pop_back();
		}
		int target = m - 2*K + k;
		if(target < 0) break;
		make(target);
		if(sz(S1) != target) continue;
		ll tmp = sum_r + get(prefAB,k) + get(prefA,K - k) + get(prefB,K - k);
		ans = min(ans,tmp);
	}

	if(ans >= oo) ans = -1;
	cout << ans << endl;

	return 0;
}
