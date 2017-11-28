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

struct line{
	int group,pos,time_offset,id;
public:
	bool operator < (const line & o) const {
		return tie(pos,time_offset) < tie(o.pos,o.time_offset);
	}
};

const int MAX = 100*1000 + 10;
map<int,set<line> > H,V;
int n,w,h;
int group[MAX],pos[MAX],time_offset[MAX];
pi ans[MAX];

pi get_end(line & l){
	if(l.group == 1) return mp(l.pos,h);
	else return mp(w,l.pos);
}

void solve(set<line> & IU,set<line> & IV){
	vector<line> U {all(IU)};
	vector<line> V {all(IV)};
	for(int i = 0;i < sz(U);i++){
		int who = U[i].id;
		int siz1 = sz(U) - i - 1,siz2 = sz(V);
		int cnt = min(siz1,siz2);
		if(cnt == siz2) ans[who] = get_end(U[i + cnt]);//,cerr << "one" << endl;
		else ans[who] = get_end(V[cnt]);//,cerr << "two" << endl;
	//	cerr << siz1 << " " << siz2 << endl;
	//	cerr << who << " " << ans[who].xx << " " << ans[who].yy << endl;
	}
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d %d",&n,&w,&h);
	loop(i,n){
		scanf("%d %d %d",group + i,pos + i,time_offset + i);
		int val = time_offset[i] - pos[i];
		line cur ({group[i],pos[i],time_offset[i],i});
		if(group[i] == 1) V[val].insert(cur);
		else H[val].insert(cur);
	}
	for(auto & p : V){
		solve(p.yy,H[p.xx]);
//		exit(0);
	}
	for(auto & p : H)
		solve(p.yy,V[p.xx]);
	loop(i,n) printf("%d %d\n",ans[i].xx,ans[i].yy);
	return 0;
}
