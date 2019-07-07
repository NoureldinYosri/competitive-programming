#ifdef DEBUG
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

int id[1 << 20];
vi G[1 << 20];
int P[1 << 20];
int target;

void floodfill(int u,int p) {
	P[u] = p;
	for(int v : G[u]) {
		if(v == p) continue;
		floodfill(v,u);
	}
}

bool dfsFind(int u,int p) {
	if(u == target) return 1;
	for(int v : G[u])
		if(v != p && dfsFind(v,u))
			return 1;
	return 0;
}

int get_s(int u) {
	for(int v : G[u]){
		if(v == P[u]) continue;
		if(dfsFind(v,u))
			return v;
	}
	return -1;
}

int get_d(int u,int p) {
	if(u == target) return 0;
	int ret = 1 << 29;
	for(int v : G[u]) {
		if(v == p) continue;
		ret = min(ret,get_d(v,u) + 1);
	}
	return ret;
}

const int MAXN = 10;
mt19937 rnd = mt19937((unsigned ll)(new char()));

int randint(int s,int e) {
	int len = e-s+1;
	return (len + rnd()%len)%len + s;
}


int main(int argc,char **argv){
	freopen("in.in","w",stderr);
	int n = randint(1,MAXN) + 1;
	if(argc > 1) n = 200*1000;
	int u = randint(1,n);
	target = u;
	cout << n << endl;
	cerr << n << " " << u << endl;
	for(int i = 0;i < n;i++)
		id[i] = i+1;
	random_shuffle(id,id + n);
	for(int i = 1;i < n;i++) {
		int p = randint(0,i-1)%i;
		cout << id[p] << " " << id[i] << endl;
		cerr << id[p] << " " << id[i] << endl;
		int a = id[p],b = id[i];
		G[a].push_back(b);
		G[b].push_back(a);
	}
	int ctr = 0;
	while(1){
		ctr++;
		if(ctr > 36) {
			cout << -1 << endl;
			cerr << "exceeded number of queries" << endl;
			exit(1);
		}
		char c; int x;
		cin >> c >> x;
		if(!x) {
			cout << -1 << endl;
			cerr << "x = 0" << endl;
			exit(1);
		}
		if(c == '!') {
			if(x == target) exit(0);
			cerr << "wrong answer recieved " << x << " expected " << target << endl;
			exit(1);
		}
		if(c == 's') {
			int s = get_s(x);
			if(s == -1) {
				cerr << "s " << s << " which is not ancestor of " << target << endl;
				exit(1);
			}
			cout << s << endl;
		}
		else {
			cout << get_d(x,0) << endl;
		}
	}
	return 0;
}
#endif
