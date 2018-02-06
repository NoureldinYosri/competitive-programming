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
	ll x,y;
	int type;
	friend ostream& operator << (ostream & st,const point & p) {
		st << "(" << p.x << " ," << p.y << " ," << p.type << ")";
		return st;
	}
	point operator - (const point & o){
		return point({x-o.x,y-o.y,type});
	}
};

int n,m;
point P[2 << 10],U[2 << 10],D[2 << 10];


ll cross(point o,point a,point b) {
	ll ax = a.x - o.x,ay = a.y - o.y;
	ll bx = b.x - o.x,by = b.y - o.y;
	return ax*by - ay*bx;
}

inline int sgn(ll val) {
	return (val > 0) - (val < 0);
}

inline int getScore(int *cnt) {
	int a = cnt[0] + m - cnt[1];
	int b = cnt[1] + n - cnt[0];
	return min(a,b);
}

int work(point *U,point *D,int n,int m,point pivot) {
	int cnt[2] = {0};
	cnt[pivot.type]++;

	loop(i,m) {
		point & p = D[i];
		cnt[p.type]++;
	}
	int score = getScore(cnt);
	int ret = score;


	int i = 0,j = 0;
	while(i < n && j < m) {
		double t1 = atan2(U[i].y,U[i].x);
		double t2 = PI - atan2(-D[j].y,D[j].x);
//		assert(t2 > -1e-9);
		if(t1 < t2) {
			cnt[U[i].type]++;
			i++;
		}
		else {
			cnt[D[j].type]--;
			j++;
		}
		ret = min(ret,getScore(cnt));
	}
	while(i < n) {
		cnt[U[i].type]++;
		i++;
		ret = min(ret,getScore(cnt));
	}
	while(j < m) {
		cnt[D[j].type]--;
		j++;
		ret = min(ret,getScore(cnt));
	}
	return ret;
}

void prepare(int i,int & n,int & m) {
	int N = ::n + ::m;
	point O ({0,0,-1});
	loop(j,N)
		if(i != j){
			auto p = P[j] - P[i];
			if(p.y > 0) U[n++] = p;
			else if(p.y < 0) D[m++] = p;
			else if(p.x > 0) U[n++] = p;
			else D[m++] = p;
		}

	sort(U,U + n,[O](const point & a,const point & b) {
		return cross(O,a,b) > 0;
	});
	sort(D,D + m,[O](const point & a,const point & b) {
		return cross(O,a,b) >  0;
	});

//	cerr << "pivot " << P[i] << endl;
//	prArr(U,n,point);
//	prArr(D,m,point);

}

int solve(){
	int N = ::n + ::m,ret = n + m;
	loop(i,N){
		int n = 0,m = 0;
		prepare(i,n,m);
		int tmp = work(U,D,n,m,P[i]);
//		cerr << P[i] << " " << tmp << endl;
		ret = min(ret,tmp);
	}
	return ret;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	int T; scanf("%d",&T);
	range(t,1,T){
		scanf("%d %d",&n,&m);
		loop(i,n) scanf("%lld %lld",&P[i].x,&P[i].y),P[i].type = 0;
		loop(i,m) scanf("%lld %lld",&P[i+n].x,&P[i+n].y),P[i+n].type = 1;
		printf("%d\n",solve());
	}
	return 0;
}
