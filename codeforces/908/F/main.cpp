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

const int MAX = 300*1000 + 10;
int X[MAX],n;
char color[MAX];
deque<int> green,blue,red;
int nxt[MAX];
ll suff[MAX];

bool pure(int l,int r) {
	int content = 0;
	for(int i = l+1;i < r;i++) {
		if(color[i] == 'B') content |= 1;
		if(color[i] == 'R') content |= 2;
	}
	return content != 3;
}

ll work(int l,int r,char target) {
	if(l+1 > r-1) return 0;
//	if(l != -1 && r != n && pure(l,r)) return 0;
	ll ret = 0;
	if(l == -1) {
		int prv = X[r];
		for(int i = r-1; i > l;i--) if(color[i] == target){
			ret += prv - X[i];
			prv = X[i];
		}
	}
	else if(r == n){
		int prv = X[l];
		for(int i = l+1;i < r;i++) if(color[i] == target) {
			ret += X[i] - prv;
			prv = X[i];
		}
	}
	else {
		ret = 1LL << 60;
		int to = X[r];
		suff[r] = 0;
		for(int i = r-1;i > l;i--) {
			suff[i] = suff[i + 1];
			if(color[i] == target) {
				suff[i] += to - X[i];
				to = X[i];
			}
		}

		ll pref = 0;
		int prv = X[l],ctr = 0;
		for(int i = l+1;i < r;i++) if(color[i] == target){
			ret = min(ret,pref + suff[i]);
			pref += X[i] - prv;
			prv = X[i];
			ret = min(ret,pref + suff[i + 1]);
			++ctr;
		}
		if(!ctr) ret = 0;
	}
//	cerr << target << " ret= " << ret << " ,l=" << l << " ,r=" << r  << endl;
	return ret;
}

ll work(char target) {
	ll ret = work(-1,nxt[0],target);
	for(int i = 0;i < n;i++) {
		if(color[i] == 'G')
			ret += work(i,nxt[i + 1],target);
	}
//	cerr << target << ". " << ret << endl;
	return ret;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&n);
	loop(i,n) {
		scanf("%d %c",X + i,color + i);
		if(color[i] == 'G') green.pb(i);
		else if(color[i] == 'B') blue.pb(i);
		else red.pb(i);
	}

	ll ans = 0;
	if(green.empty()) {
		if(!red.empty()) ans += X[red.back()] - X[red[0]];
		if(!blue.empty()) ans += X[blue.back()] - X[blue[0]];
	}
	else {
		nxt[n] = n;
		for(int i = n-1;i >= 0;i--){
			nxt[i] = nxt[i + 1];
			if(color[i] == 'G') {
				if(nxt[i] != n) ans += X[nxt[i]] - X[i];
				nxt[i] = i;
			}
		}
		ans += work('R');
		ans += work('B');
	}
	cout << ans << endl;
	return 0;
}
