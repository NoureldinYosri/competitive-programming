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

const int MAX = 100*1000 + 1000;
set<pair<pi,pi> > vis;
int m,n,k;
set<int> major[MAX*2],minor[MAX*2];
int X[MAX],Y[MAX];
ll T[MAX];
vi to_delete;

void reflect(pi & pos,pi & dir,ll & t){
	int to_x = (dir.xx == 1) ? m : 0;
	int to_y = (dir.yy == 1) ? n : 0;
	int d1 = abs(to_x - pos.xx),d2 = abs(to_y - pos.yy);
	int d = min(d1,d2);
	t += d;
	pi npos = pos; npos.xx += d*dir.xx,npos.yy += d*dir.yy;
	if(d1 < d2) dir.xx *= -1;
	else dir.yy *= -1;
	pos = npos;
}

void get_diags(pi pos,pi dir,int & d1,int & d2){
	if(dir.xx == dir.yy){
		d1 = -1;
		d2 = pos.xx - pos.yy + MAX;
	}
	else{
		d1 = pos.xx + pos.yy;
		d2 = -1;
	}
}

bool is_corner(pi pos){
	if(pos == mp(0,0)) return 1;
	if(pos == mp(0,n)) return 1;
	if(pos == mp(m,0)) return 1;
	if(pos == mp(m,n)) return 1;
	return 0;
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
		freopen("out.out", "w", stdout);
	#endif
	scanf("%d %d %d",&m,&n,&k);
	loop(i,k){
		scanf("%d %d",X + i,Y + i);
		major[X[i] + Y[i]].insert(i);
		minor[X[i] - Y[i] + MAX].insert(i);
	}
	pi pos = mp(0,0); pi dir = mp(1,1); bool first = 1;
	memset(T,-1,sizeof T);
	for(ll t = 0;!vis.count(mp(pos,dir)) && (first || !is_corner(pos));first = 0){
	//	fprintf(stderr,"at (%d,%d) with dir (%d,%d)\n",pos.xx,pos.yy,dir.xx,dir.yy);
		vis.insert(mp(pos,dir));
		to_delete.clear();
		int d1,d2;
		get_diags(pos,dir,d1,d2);
		if(d1 != -1) {
			for(int x : major[d1]) {
				if(mp(X[x],Y[x]) == pos) to_delete.pb(x);
				else{
					int dx = X[x] - pos.xx,dy = Y[x] - pos.yy;
					dx = (dx > 0) - (dx < 0);
					dy = (dy > 0) - (dy < 0);
					if(dir == mp(dx,dy)) to_delete.pb(x);
				}
			}
		}
		if(d2 != -1){
			for(int x : minor[d2]){
				if(mp(X[x],Y[x]) == pos) to_delete.pb(x);
				else{
					int dx = X[x] - pos.xx,dy = Y[x] - pos.yy;
					dx = (dx > 0) - (dx < 0);
					dy = (dy > 0) - (dy < 0);
					if(dir == mp(dx,dy)) to_delete.pb(x);
				}
			}
		}
		for(int x : to_delete){
			major[X[x] + Y[x]].erase(x);
			minor[X[x] - Y[x] + MAX].erase(x);
			T[x] = t + abs(X[x] - pos.xx);
		}
		reflect(pos,dir,t);
	//	cerr << "go to "; prp(pos); prp(dir); cerr << endl;
	}
//	prArr(T,k,int);
	loop(i,k) printf("%lld\n",T[i]);
	return 0;
}
