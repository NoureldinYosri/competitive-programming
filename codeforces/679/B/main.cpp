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

const int MAX = 100*1000;
vector<ll> cubes;

ll cube(ll x) {
	return x*x*x;
}

void init(){
	for(int i = 0;i <= MAX;i++)
		cubes.push_back(cube(i));
}

vector<ll> path;

int getLen(ll x,bool debug = 0) {
	path.clear();
	int lst = sz(cubes);
	int ret = 0;
	while(x){
		auto ptr = upper_bound(cubes.begin(),cubes.begin() + lst,x);
		lst = ptr - cubes.begin();
		lst --;
		if(debug) cerr << x/cubes[lst] << " of " <<  cubes[lst] << " index: " << lst << endl;
		int num = x/cubes[lst];
		while(num) path.push_back(cubes[lst]),num--;
		ret += x/cubes[lst];
		x %= cubes[lst];
	}
	return ret;
}

/*
 * unordered_map<ll,int> mem;

int getLen(ll x) {
	if(mem.count(x) || !x) return mem[x];
	auto ptr = upper_bound(cubes.begin(),cubes.end(),x);
	int lst = ptr - cubes.begin();
	lst --;
	int ret = x/cubes[lst];
	x %= cubes[lst];
	ret += getLen(x);
	return ret;
}

 *
 */

pair<int,ll> searchNeighbours(ll x,ll lim,int B = 1000) {
	pair<int,ll> ret(0,-1);
	for(int i = -B;i <= B;i++){
		ll y = x + i;
		if(y <= 0) continue;
		if(y > lim) continue;
		int f = getLen(y);
		ret = max(ret,mp(f,y));
	}
	return ret;
}

int getBig(ll v) {
	auto ptr = upper_bound(all(cubes),v);
	ptr--;
	return ptr - cubes.begin();
}




bool valid(ll v,int r) {
	for(int i = 0;i < r;i++) {
		ll x = cubes[getBig(v)];
		if(path[i] != x) return 0;
		v -= x;
	}
	return 1;
}

void bt2(ll v,int r,int L,ll lim,ll & ans) {
	ll diff = lim - v;
	if(diff < 0) return;
	cerr << v << " " << r << " " << L << endl;
	for(int a = 0;a <= 7 && a <= L-r;a++){
		int b = L - r - a;
		if(b > 27/8) continue;
		ll x = v + a + b*8;
		ans = max(ans,x);
	}
}

void bt(ll v,int r,int L,ll lim,ll & ans) {
	if(v > lim) return ;
	if(!valid(v,r)) return;
	if(r == L) {
		ans = max(ans,v);
		return;
	}
	cerr << v << " " << r << " " << L << endl;
	if(r == sz(path)) return bt2(v,r,L,lim,ans);
	int i = getBig(path[r]);
	assert(path[r] == cubes[i]);
	for(int k = 0;k < 3;k++) {
		int j = i - k;
		if(j <= 0) continue;
		path[r] = cubes[j];
		bt(v + path[r],r+1,L,lim,ans);
		path[r] = cubes[i];
	}
}

pair<int,ll> bt(ll x){
	if(!x) return mp(0,0);
	int c = getBig(x);
	auto res = bt(x - cubes[c]);
	res.first++;
	res.second += cubes[c];

	if(c > 1 ) {
		auto res2 = bt(cubes[c]-1-cubes[c-1]);
		res2.first++;
		res2.second += cubes[c-1];

		res = max(res,res2);
	}
	return res;
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	init();
	ll x; cin >> x;
	auto ans = bt(x);
	cout << ans.first << " " << ans.second << endl;
	return 0;
}
