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

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define DEC 0
#define INC 1


struct event{
	int x,type,y1,y2;
public:
	bool operator < (const event & o){
		return tie(x,type) < tie(o.x,o.type);
	}
};

struct mirror{
	pi pos,rowMajor,colMajor;
	int type;
public:
	mirror(){
		pos = rowMajor = colMajor = mp(-1,-1);
		type = -1;
	}
	mirror(pi S,int t){
		type = t;
		pos = rowMajor = S;
		colMajor = mp(S.yy,S.xx);
	}
};

struct byrowcmp{
public:
	bool operator () (const mirror & m1,const mirror & m2){
		return m1.rowMajor < m2.rowMajor;
	}
};
struct bycolcmp{
public:
	bool operator () (const mirror & m1,const mirror & m2){
		return m1.colMajor < m2.colMajor;
	}
};

const int MAX = 1 << 20;
set<mirror,byrowcmp> byrow;
set<mirror,bycolcmp> bycol;
vp A,B;
int R,C;
string name[4] = {"UP","DOWN","LEFT","RIGHT"};
int BIT[MAX];
vector<event> E;

void update(int p,int v){
	for(;p < MAX;p += LSOne(p))
		BIT[p] += v;
}

int get(int p){
	int ret = 0;
	for(;p;p ^= LSOne(p)) ret += BIT[p];
	return ret;
}

bool same(pi u,pi v,int which){
	if(which == 0) return u.yy == v.yy;
	else return u.xx == v.xx;
}

int get_dir(int dir,int type){
	if(dir == UP) return type ? RIGHT : LEFT;
	else if(dir == DOWN) return type ? LEFT : RIGHT;
	else if(dir == LEFT) return type ? DOWN : UP;
	else return type ? UP : DOWN;
}

bool move(pi & S,int & dir,int motion,int which){
	auto BEG = which ? byrow.begin() : bycol.begin();
	auto END = which ? byrow.end() : bycol.end();
	auto p = which ? byrow.lower_bound(mirror(S,-1)) : bycol.lower_bound(mirror(S,-1));
	if(motion == INC){
		if(p == END) return 0;
		if(p->pos == S) ++p;
		if(p == END) return 0;
//		prp(S); cerr << " " << name[dir] << " " ; prp(p->pos) ; cerr << endl;
		if(!same(p->pos,S,which)) return 0;
		dir = get_dir(dir,p->type);
		S = p->pos;
		return 1;
	}
	else{
		if(p == BEG) return 0;
		if(p == END || p->pos == S) --p;
//		prp(S); cerr << " " << name[dir] << " " ; prp(p->pos) ; cerr << endl;
		if(!same(p->pos,S,which)) return 0;
		dir = get_dir(dir,p->type);
		S = p->pos;
		return 1;
	}
}

pi get_end(pi S,int dir){
	if(dir == RIGHT) return mp(S.xx,C + 1);
	if(dir == LEFT) return mp(S.xx,0);
	if(dir == UP) return mp(0,S.yy);
	return mp(R + 1,S.yy);
}

void get_path(vp & V,pi S,int dir){
	V.clear();
	while(1){
		V.pb(S);
		if(dir == UP) {
			if(!move(S,dir,DEC,0)) break;
		}
		else if(dir == DOWN){
			if(!move(S,dir,INC,0)) break;
		}
		else if(dir == LEFT){
			if(!move(S,dir,DEC,1)) break;
		}
		else if(!move(S,dir,INC,1)) break;
//		prp(S); cerr << " going " << name[dir] << endl;
	}
	V.pb(get_end(S,dir));
}

void PRINT(vp & V){
	for(auto p : V) prp(p);
	cerr << endl;
}

void solve(pi & pos,ll & cnt,vp & A,vp & B){
	E.clear();
	for(int i = 0;i + 1 < sz(A);i += 2){
		int x = A[i].xx,y1 = A[i].yy,y2 = A[i + 1].yy;
		if(y1 > y2) swap(y1,y2);
		if(y1 + 1 <= y2 - 1){
		//	cerr << "horizontal (" << x << " ," << y1 << ")\t(" << x << " ," << y2 << ")" << endl;
			E.pb(event({y1 + 1,-1,x,x}));
			E.pb(event({y2 - 1, 1,x,x}));
		}
	}
	for(int i = 1;i + 1 < sz(B);i += 2){
		int x1 = B[i].xx,x2 = B[i + 1].xx,y = B[i].yy;
		if(x1 > x2) swap(x1,x2);
		if(x1 + 1 <= x2 - 1){
		//	cerr << "vertical (" << x1 << " ," << y << ")\t(" << x2 << " ," << y << ")" << endl;
			E.pb(event({y,0,x1+1,x2-1}));
		}
	}
	sort(all(E));
	memset(BIT,0,sizeof BIT);
	multiset<int> MS;
	for(auto e : E){
		if(e.type == -1) {
//			cerr << "insert " << e.y1 << endl;
			update(e.y1,1);
			MS.insert(e.y1);
		}
		else if(e.type == 1) {
//			cerr << "erase " << e.y1 << endl;
			update(e.y1,-1);
			MS.erase(MS.find(e.y1));
		}
		else{
//			cerr << "query " << e.y1 << " " << e.y2 << " -> ";
			int t = get(e.y2) - get(e.y1 - 1);
//			cerr << t << endl;
			if(t){
				cnt += t;
				int x = e.x;
				int y = *MS.lower_bound(e.y1);
				pos = min(pos,mp(y,x));
			}
		}
	}
}

int solve(pi & pos,ll & cnt){
	get_path(A,mp(1,0),RIGHT);
	//PRINT(A);
	if(A.back() == mp(R,C+1)) return 0;
	get_path(B,mp(R,C+1),LEFT);
	//PRINT(B);
	cnt = 0;
	pos = mp(INT_MAX,INT_MAX);
	solve(pos,cnt,A,B);
	solve(pos,cnt,B,A);
	if(!cnt) return -1;
	return 1;
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	for(int t = 1,m,n;scanf("%d %d %d %d",&R,&C,&m,&n) == 4;t++){
		byrow.clear(); bycol.clear();
		loop(i,m){
			int x,y; scanf("%d %d",&x,&y);
			mirror m = mirror(mp(x,y),1);
			byrow.insert(m);
			bycol.insert(m);
		}
		loop(i,n){
			int x,y; scanf("%d %d",&x,&y);
			mirror m = mirror(mp(x,y),0);
			byrow.insert(m);
			bycol.insert(m);
		}
		pi pos;
		ll cnt;
		int verdict = solve(pos,cnt);
		printf("Case %d: ",t);
		if(verdict == -1) puts("impossible");
		else if(verdict == 0) puts("0");
		else printf("%lld %d %d\n",cnt,pos.xx,pos.yy);
	}
	return 0;
}
