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

struct point{
	ll x,y,z;
	point(){memset(this,0,sizeof *this);}
};

struct shape{
	point corner[6];
	shape(){memset(this,0,sizeof *this);}
	shape(ll x,ll y,ll z,ll s){
		for(int i = 0;i < 6;i++) {
			ll v = (1 - 2*(i%2))*s;
			if(i/2 == 0)
				corner[i].x = v;
			else if(i/2 == 1)
				corner[i].y = v;
			else
				corner[i].z = v;
		}
	}
};

const int MAX = 1 << 20;
ll X[MAX],Y[MAX],Z[MAX];
int n;
ll A,B,C;

bool inter(shape A,shape B) {

}

bool can(int s) {
	shape S (X[0],Y[0],Z[0],s);
	for(int i = 1;i < n;i++) {
		shape cur(X[i],Y[i],Z[i],s);
		if(!inter(S,cur))
			return 0;
	}
	A = S.x;
	B = S.y;
	C = S.z;
	return 1;
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	int T; scanf("%d",&T);
	while(T--) {
		scanf("%d",&n);
		loop(i,n) scanf("%lld %lld %lld",X + i,Y + i,Z + i);
		ll s = 0,e = 3e18;
		while(s < e) {
			ll m = s + (e-s)/2;
			if(can(m)) e = m;
			else s = m+1;
		}
		can(s);
		printf("%lld %lld %lld\n",A,B,C);
	}
	return 0;
}
