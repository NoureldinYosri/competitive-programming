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

struct holder{
	ll x;
	int val;
public:
	bool operator < (const holder & o){
		return tie(x,val) < tie(o.x,o.val);
	}
};

const int MAX = 1 << 24;
int A[100],n;
int lst[100],m = 0;
holder event[MAX];
const ll oo = 1e13;
int ctr[100],N;

map<int,int> cnt;

void brute_force(int x){
	for(int i = 1;i <= x;){
		int j = i;
		while(j <= x && x/i == x/j) j++;
		cerr << "(" << i << " " << j-1 << " -> " << x/i << ")";
		i = j;
	}
	cerr << endl << "================================" << endl;
}
void work(int x,int who,bool debug = 0){
//	brute_force(x);
	for(int i = 1;i  <= x;){
		int s = i,e = x;
		while(s < e) {
			int m = s + (e - s + 1)/2;
			if(x/m == x/i) s = m;
			else e = m-1;
		}
		if(debug)	cerr << "(" << i << " " << s << " -> "  << x/i << ")" ;
		assert(m+2 <= MAX);
		event[m++] = holder({i,-who});
//		event[m++] = holder({s,who});
		i = s + 1;
	}
	assert(m+2 <= MAX);
	event[m++] = holder({x+1,-who});
	event[m++] = holder({oo,who});
	if(debug) cerr << endl << "==================" <<  endl;
}

ll compute(ll D){
	ll ret = 0;
	loop(i,n) ret += A[i]/D;
	return ret;
}

ll compute_cost(ll D){
	ll ret = 0;
	loop(i,n) ret += (D - A[i]%D)%D;
	return ret;
}

void compress(){
	sort(A,A + n);
	N = 0;
	for(int i = 0;i < n;){
		int j = i,x = A[i];
		while(j < n && A[i] == A[j]) j++;
		for(int d = 1;d*d <= x;d++) {
			if(x%d == 0){
				cnt[d] += j - i;
				if(d*d != x) cnt[x/d] += j - i;
			}
		}
		A[N] = A[i];
		ctr[N] = j - i;
		N++;
		i = j;
	}
	swap(n,N);
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	ll K; scanf("%d %lld",&n,&K);
	loop(i,n) scanf("%d",A + i);
	compress();
	loop(i,n) work(A[i],i+1);
	sort(event,event + m);
	ll Sa = 0,Sp = 0;
	loop(i,n) {
		Sa += A[i] *1LL* ctr[i];
		Sp += A[i] *1LL* ctr[i];
		lst[i] = A[i];
	}
/*
	cerr << "intial Sp is " << Sp << endl;
	loop(i,m) cerr << event[i] << " ";
	cerr << endl;
*/
	int lstD = 1;
	ll ans = 0;
	for(int i = 0;i < m;){
		ll D = event[i].x;
		// D*n - (Sa - D*Sp) <= K
		// D*n - Sa + D*Sp <= K
		// D <= (K + Sa)/(Sp + n)
		ll target = (K + Sa)/(Sp + N);
		if(D > 1){
			ll cost = target*N - (Sa - target*Sp);
			if(lstD < target && target <= D && cost <= K) {
				//cerr << Sp << " " << compute(target) << endl;
				assert(cost >= 0);
				//cerr << "predicted Sp is " << Sp << " acutal is " << compute(target) << endl;
//				assert(cost >= compute_cost(target));
				//cerr << "predicted cost is " << cost << " acutal is " << compute_cost(target) << endl;
				//cerr << "type 1: set answer to " << target << endl;
				ans = max(ans+0LL,target);
			}
		}

		int j = i;
	//	cerr << "current D is " << D << endl;
		while(j < m && event[i].x == event[j].x) {
			int cur = abs(event[j].val) - 1;
			int val = A[cur]/D;
	//		cerr << A[cur] << " contributed " << lst[cur] << " now it's " << val << endl;
			Sp = Sp + (- lst[cur] + val + 0LL) * ctr[cur];
			lst[cur] = val;
			j++;
		}
		ll cost = D*1LL*N - (Sa - D*1LL*Sp) - D * 1LL* ((cnt.find(D) != cnt.end()) ? cnt[D] : 0);
		if(cost <= K) {
//			cerr << "predicted Sp is " << Sp << " acutal is " << compute(D) << endl;
//			if(Sp != compute(D)) {
//
//				loop(i,n) cerr << "(" << A[i] << " ," << mp(lst[i],A[i]/D) << ")";
//				cerr << endl;
//			}
//			cerr << "predicted cost is " << cost << " acutal is " << compute_cost(D) << endl;
//			assert(cost == compute_cost(D));
//			cerr << "type 2: set answer to " << D << endl;
			ans = max(ans,D);
		}
		lstD = D;
		i = j;
//		cerr << event[i] << " cur D is " << D << " predicted is " << Sp << " acutal is " << compute(D) << endl;
		assert(Sp >= 0);
//		cerr << event[i] << " " ;
//		cerr << Sa - K << "\t" << Sp << " -> " << target << " " << ans << " " << endl;
	}
	cout << ans << endl;
	return 0;
}
