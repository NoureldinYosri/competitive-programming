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

typedef pair<int,pi> edge;
#define cost first
#define from second.first
#define to second.second

const int MAX = 100*1000 + 10;
edge E[MAX];
int id[MAX],W[MAX];
ll tot;
int n,m;

int find(int a){
	return id[a] = (a == id[a]) ? a : find(id[a]);
}

void join(int a,int b){
	a = find(a),b = find(b);
	if(a == b) return;
	tot -= W[a]*(W[a] - 1LL)/2;
	tot -= W[b]*(W[b] - 1LL)/2;
	if(W[a] < W[b]) swap(a,b);
	W[a] += W[b];
	id[b] = a;
	tot += W[a]*(W[a] - 1LL)/2;
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d",&n,&m);
	range(i,1,n) id[i] = i,W[i] = 1;
	loop(i,m) scanf("%d %d %d",&E[i].from,&E[i].to,&E[i].cost);
	sort(E,E + m);
	ll cnt = 0;
	for(int i = m-1;i >= 0;i--){
		join(E[i].from,E[i].to);
		cnt += tot*E[i].cost;
		cnt %= 1000000000;
	}
	cout << cnt << endl;
	return 0;
}
