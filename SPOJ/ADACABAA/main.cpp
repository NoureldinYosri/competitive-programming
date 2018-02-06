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


struct point{
	int X[4];
	bool operator < (const point & o) {
		return X[0] < o.X[0];
	}
	friend ostream& operator << (ostream& st,const point & p) {
		st << "(" ;
		loop(i,4) {
			st << p.X[i];
			if(i!=3) st << " ,";
		}
		cerr << ")";
		return st;
	}
};

point P[1 << 20];
int n;

bool isBigger(point a,point b,vi ord) {
	for(int i : ord)
		if(a.X[i] > b.X[i])
			return 0;
		else
			return 1;
	return 1;
}

bool dominate(point p,point q) {
	loop(i,4)
			if(p.X[i] > q.X[i])
				return 0;
	return 1;
}


int solve(int s,int e,vector<point> & Q) {
	if(s == e) {
		loop(i,sz(Q)) Q[i] = P[s];
		return 1;
	}
	int m = (s + e) >> 1;
	int ret = solve(m+1,e,Q);
	for(int k = m;k >= s;k--)
		ret += checkAndUpdate(P[k],Q);
	cerr << s << " " << e << " -> " ;
	loop(i,6) cerr << Q[i] << " ";
	cerr << endl;
	return ret;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&n);
	loop(i,n) loop(j,4) scanf("%d",&P[i].X[j]);
	sort(P,P + n);
	loop(i,n) cerr << P[i] << " ";
	cerr << endl;
	vector<point> Q(1 << 3);
	printf("%d\n",solve(0,n-1,Q));

	return 0;
}
