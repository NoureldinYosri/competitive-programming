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

const int mod = 1000000009;
int add(int a,int b){
	a += b;
	if(a >= mod) a -= mod;
	return a;
}
int mul(int a,int b) {
	return (a*(ll)b)%mod;
}

const int MAX = 100*1000 + 10;
int X[MAX],Y[MAX],n;
bool dead[MAX];
map<pi,int> id;

vi getNeighbours(int i,bool up) {
	vi ret;
	int x = X[i],y = Y[i];
	int dy = 2*up - 1;
	for(int dx = -1;dx <= 1;dx++) {
		pi p(x + dx,y + dy);
		if(id.count(p)) {
			int j = id[p];
			if(!dead[j]) ret.push_back(j);
		}
	}
	return ret;
}

bool isFree(int i) {
	vi dependants = getNeighbours(i,1);
	if(dependants.empty()) return 1;
	for(int j : dependants)
		if(sz(getNeighbours(j,0)) == 1)
			return 0;
	return 1;
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	scanf("%d",&n);
	loop(i,n) {
		scanf("%d %d",X + i,Y + i);
		id[mp(X[i],Y[i])] = i;
	}
	set<int> S;
	loop(i,n) if(isFree(i)) S.insert(i);
	int ans = 0;
	for(int t = 0;t < n;t++) {
		assert(!S.empty());
		int i = *S.rbegin();
		if(t&1) i = *S.begin();
//		cerr << t << ": " << i << " " << X[i] << " " << Y[i] << endl;
		S.erase(i);
		ans = add(mul(ans,n),i);
		dead[i] = 1;
		for(int j : getNeighbours(i,0)) {
			if(isFree(j))
				S.insert(j);
		}
		for(int j : getNeighbours(i,1)) {
			for(int k : getNeighbours(j,0))
				if(!isFree(k))
					S.erase(k);
		}
	}
	cout << ans << endl;
	return 0;
}
