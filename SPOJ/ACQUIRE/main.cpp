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

const ll oo = 1LL << 60;
const int MAX = 50*1000 + 10,MAXLG = 17;
int n;
int W[MAX],H[MAX];

ll f(int idx,pl line){
	return line.xx*H[idx] + line.yy;
}

double g(pl a,pl b){
	// a.xx*x + a.yy <= b.xx * x + b.yy
	// (b.yy - a.yy)/(a.xx - b.xx)
	if(a.xx == b.xx) {
		if(b.yy > a.yy) return LLONG_MAX;
		else return LLONG_MIN;
	}
	else return (b.yy - a.yy + 0.0)/(a.xx - b.xx);
}

ll solve(){
	deque<pl> lines;
	lines.pb(mp(W[1],0));
	int siz = 1;
	range(i,1,n){
		while(siz > 1 && f(i,lines[0]) >= f(i,lines[1])){
			siz--;
			lines.pop_front();
		}
		pl line = mp(W[i + 1],f(i,lines.front()));
		while(siz > 1 && g(lines[siz - 2],lines[siz - 1]) >= g(lines[siz - 1],line)) {
			siz--;
			lines.pop_back();
		}
		lines.pb(line);
		siz++;
//		for(auto line : lines) prp(line);
//		cerr << endl;
	}
	return lines.back().yy;
}



bool dominates(pi u,pi v){
	return v.xx >= u.xx && v.yy >= u.yy;
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&n);
	vp V(n),aux;
	loop(i,n) scanf("%d %d",&V[i].xx,&V[i].yy);
	sort(all(V));
	for(auto p : V){
		while(!aux.empty() && dominates(aux.back(),p)) aux.pop_back();
		aux.pb(p);
	}
	n = sz(aux);
	range(i,1,n) {
		H[i] = aux[i - 1].xx,W[i] = aux[i - 1].yy;
	//	prp(aux[i - 1]);
	}
	//cerr << endl;
	//cerr << "=================================" << endl;
	cout << solve() << endl;
	return 0;
}
