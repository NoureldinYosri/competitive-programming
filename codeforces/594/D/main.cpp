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
#define popcnt(x) __builtin_popcount(x)
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

const int MAXA = 1000*1000 + 10,mod = 1e9 + 7,MAXN = 200*1000 + 10,MAXR = MAXN*7;

int prime[MAXA],f[MAXA];
int A[MAXN],pref[MAXN],n;
int L[MAXN],R[MAXN],lst[MAXA],B[MAXR],prv[MAXR],N;
int BIT[MAXR];
int qL[MAXN],qR[MAXN],ans[MAXN],guess[MAXN];

int mul(int x,int y){
	return (x*1LL*y)%mod;
}

int pow_mod(int x,int b){
	if(!b) return x;
	int y = 1;
	for(;b > 1;b >>= 1){
		if(b & 1) y = mul(x,y);
		x = mul(x,x);
	}
	return mul(x,y);
}


inline void update(int pos,int val){
	for(pos++;pos <= N;pos += LSOne(pos))
		BIT[pos] = mul(BIT[pos],val);
}

inline int get(int pos){
	int ret = 1;
	for(pos++;pos;pos ^= LSOne(pos))
		ret = mul(ret,BIT[pos]);
	return ret;
}

void sieve(){
	f[1] = 1;
	int mx = 0;
	for(int i = 2;i < MAXA;i++){
		if(!prime[i]) {
			prime[i] = i;
			for(ll j = i*1LL*i;j < MAXA;j += i)
				prime[j] = i;
		}
		f[i] = mul(i-1,pow_mod(i,mod - 2));
		int tmp = 0,x = i;
		while(x > 1){
			tmp++;
			int p = prime[x];
			while(x%p == 0) x /= p;
		}
		if(i <= 1000*1000 && tmp == 6) mx++;
	}

}


int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	sieve();
	scanf("%d",&n);
	loop(i,n) {
		scanf("%d",A + i);
		int x = A[i];
		L[i] = N;
		while(x > 1){
			int p = prime[x];
			B[N++] = p;
			while(x%p == 0) x /= p;
		}
		R[i] = N;
		pref[i] = mul(A[i],i ? pref[i - 1] : 1);
	}
	fill(lst,lst + MAXA,-1);
	loop(i,N){
		int p = B[i];
		prv[i] = lst[p];
		lst[p] = i;
	}
	int m; scanf("%d",&m);
	loop(i,m) {
		scanf("%d %d",qL + i,qR + i);
		qL[i]--;
		qR[i]--;
		ans[i] = pref[qR[i]];
		if(qL[i]) ans[i] = mul(ans[i],pow_mod(pref[qL[i] - 1],mod - 2));
		guess[i] = ans[i];
		qL[i] = L[qL[i]];
		qR[i] = R[qR[i]];
	}
	/*prArr(B,N,int);
	prArr(qL,m,int);
	prArr(qR,m,int);
	prArr(pref,n,int);
	prArr(ans,m,int);
	*/
	vector<pair<pi,int> > event; event.reserve(n + 2*m);
	fill(BIT,BIT + N + 1,1);
	loop(i,N) event.pb(mp(mp(i,1),-1));
	loop(i,m) {
		if(qL[i] == qR[i]) continue;
		event.pb(mp(mp(qL[i],-1),i));
		event.pb(mp(mp(qR[i],0),i));
	}
	sort(all(event));
	/*for(auto e : event){
		cerr << "((" << e.xx.xx << " ," << e.xx.yy << ") ," << e.yy << ") ";
		if(e.xx.yy == 1) cerr << prv[e.xx.xx] << " " << B[e.xx.xx] << " " << f[B[e.xx.xx]] ;
		cerr << endl;
	}*/

	for(auto e : event){
		int pos = e.xx.xx,type = e.xx.yy,q = e.yy;
		bool debug = q == 4;
		if(type == -1){
//			if(debug) cerr << "@" << pos << " get < " << qL[q] << " -> " << get(qL[q]) << endl;
//			if(debug) cerr << "was " << ans[q] << endl;
			int tmp = get(qL[q]),rev = pow_mod(tmp,mod - 2);
			ans[q] = mul(ans[q],rev);
//			if(debug) cerr << "became " << ans[q] << " due to division by " << tmp << " which is mul by " << rev<< endl;
		}
		else if (type == 0){
			ans[q] = mul(ans[q],get(qL[q]));
//			if(debug) cerr << "@" << pos << " get < " << qL[q] << " -> " << get(qL[q]) << endl;
//			if(debug) cerr << "thus res of " << q << " is " << ans[q] << endl;
		}
		else if(type == 1){
//			cerr << "@" << pos << " add " << B[pos] << " for postions >= " << prv[pos] + 1 << " mul " << f[B[pos]] << endl;
			update(prv[pos]+1,f[B[pos]]);
		}
	}
	loop(i,m) printf("%d\n",ans[i]);
	return 0;
}
