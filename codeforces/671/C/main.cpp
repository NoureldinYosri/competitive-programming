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

const int MAXA = 200*1000;
int prime[MAXA+1];
vi divs[MAXA+1];
vi who[MAXA+1];
int cnt[MAXA+1],val[MAXA+1];
int A[MAXA+1],n;
set<pi> S;
bool debug = 0;

void sieve(){
	divs[1].pb(1);
	for(int x = 2;x <= MAXA;x++){
		if(prime[x] == 0) {
			prime[x] = x;
			for(ll y = x*(ll)x;y <= MAXA;y += x) {
				prime[y] = x;
			}
		}
		int y = x,p = prime[x],e = 0;
		while(y%p == 0) {
			y /= p;
			e++;
		}
		for(int q = 1;e >= 0;e--,q *= p)
			for(int d : divs[y])
				divs[x].pb(d*q);
	}
}


void get_neighbours(pi p,set<pi>::iterator & prv,set<pi>::iterator & cur,set<pi>::iterator & nxt) {
	cur = S.find(p);
	assert(cur != S.end());
	prv = nxt = cur;
	if(prv == S.begin()) prv = S.end();
	else prv --;

	nxt++;
}

ll f(pi a,pi b) {
	return b.yy*(b.xx - a.xx + 0LL);
}

void output(){
	for(auto p : S) prp(p);
	cerr << endl;
}

ll remove(pi p,int st) {
	if(!S.count(p)) return 0;
	if(debug){
		cerr << "removing "; prp(p); cerr << " from ";
		output();
	}

	set<pi>::iterator prv,cur,nxt;
	get_neighbours(p,prv,cur,nxt);
	ll ret = 0;
	pi A = mp(st,0);
	if(prv != S.end()) A = *prv;
	ret -= f(A,p);
	if(nxt != S.end()) ret -= f(p,*nxt);
	if(nxt != S.end()) ret += f(A,*nxt);

	S.erase(p);
	if(debug){
		cerr << "removed " ; prp(p); cerr << " -> " << ret << endl;
	}
	return ret;
}


ll add(pi p,int st) {
	static vp aux;
	S.insert(p);
	set<pi>::iterator prv,cur,nxt;
	get_neighbours(p,prv,cur,nxt);
	if(nxt != S.end() && p.yy <= nxt->second) {
		S.erase(p);
		return 0;
	}
	aux.clear();
	while(prv != S.end() && prv->yy <= p.yy) {
		aux.pb(*prv);
		if(prv == S.begin()) prv = S.end();
		else prv--;
	}
	if(!aux.empty()){
		S.erase(p);
		ll ret = 0;
		for(auto q : aux) ret += remove(q,st);
		return ret + add(p,st);
	}

	ll ret = 0;
	pi A = mp(st,0);
	if(prv != S.end()) A = *prv;
	if(nxt != S.end()) ret -= f(A,*nxt);
	if(nxt != S.end()) ret += f(p,*nxt);
	ret += f(A,p);
	if(debug){
		cerr << "added " ; prp(p); cerr << " -> " << ret << endl;
	}
	return ret;
}
ll getVal(int st) {
	if(debug){
		for(auto p : S) prp(p);
		cerr << endl;
	}
	pi prv = mp(st,0);
	ll sum = 0;
	for(auto p : S){
		sum += f(prv,p);
		prv = p;
	}
	return sum;
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	sieve();
	scanf("%d",&n);
	loop(i,n) scanf("%d",A + i);

	for(int i = 0;i < n;i++)
		for(int d : divs[A[i]])
			who[d].pb(i);

	vp V;
	for(int x = 1;x <= MAXA;x++)
		if(sz(who[x]) > 1){
			int slst = who[x][sz(who[x]) - 2];
			V.pb(mp(slst,x));
		}
	sort(all(V));
	reverse(all(V));
	int aux = 0;
	for(auto p : V) {
		if(p.yy > aux) {
			aux = p.yy;
			S.insert(p);
		}
	}


	ll sum = getVal(0),res = 0;
	int mx = 0;
	for(int i = 0;i < n;i++) {
		while(!S.empty() && S.rbegin()->yy <= mx) {
			pi q = *S.rbegin();
			sum += remove(q,i);
			S.erase(q);
		}
		if(debug){
			if(sum != getVal(i)){
				cerr << "expected " << getVal(i) << " found " << sum << endl;
				assert(0);
			}
		}

		ll len = n - i;
		if(!S.empty()) len = n - S.rbegin()->xx;
		if(debug)
			cerr << i << ": " << sum << " + " << mx << " * " << len << endl;
		res += sum + mx*len;

		while(!S.empty() && S.begin()->xx == i) S.erase(S.begin());
		for(int d : divs[A[i]]) {
			if(sz(who[d]) <= 1) continue;
			cnt[d]++;
			if(cnt[d] >= 2) mx = max(mx,d);
			else {
				assert(cnt[d] == 1);
				int m = sz(who[d]);
				int slst = who[d][m-2],lst = who[d][m-1];
				sum += remove(mp(slst,d),i);
				sum += add(mp(lst,d),i);
			}
		}
		if(!S.empty())
			sum -= S.begin()->yy;
	}
	cout << res << endl;
	return 0;
}
