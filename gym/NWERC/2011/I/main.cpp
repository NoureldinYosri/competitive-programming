#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define point pair<double,double>
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

const int MAX = 250'000;
set<pi> S;
int s,r,w,p;
pi st[10],en[10];

int ccw(pi O,pi u,pi v){
	u.xx -= O.xx; u.yy -= O.yy;
	v.xx -= O.xx; v.yy -= O.yy;
	return u.xx*v.yy - u.yy*v.xx;
}

bool special_case(pi a,pi b,pi c,pi d){
	if(a.xx > b.xx) swap(a,b);
	if(c.xx > d.xx) swap(c,d);
	if(a.xx > c.xx) swap(a,c),swap(b,d);
	return c.xx <= b.xx;
}

bool intersect(pi a,pi b,pi c,pi d,int t = 1){
	if(!ccw(a,b,c) && !ccw(a,b,d) && ccw(c,d,a) == 0 && ccw(c,d,b) == 0) return special_case(a,b,c,d);
	int x = ccw(a,b,c);
	int y = ccw(a,b,d);
	x = (x > 0) - (x < 0);
	y = (y > 0) - (y < 0);
	if(t) return (!x || !y || (x != y)) ? intersect(c,d,a,b,0) : 0;
	return !x || !y || (x != y);
}

int main(){
	int T,cnt = 0; scanf("%d",&T);
	while(T--){
		S.clear();
		scanf("%d %d %d %d",&s,&r,&w,&p);
		loop(i,s){
			int x,y; scanf("%d %d",&x,&y);
			S.insert(mp(x,y));
		}
		loop(i,w) scanf("%d %d %d %d",&st[i].xx,&st[i].yy,&en[i].xx,&en[i].yy);
		while(p--){
			int x,y; scanf("%d %d",&x,&y);
			pi a = mp(x,y);
			vp ans;
			range(dx,-r,r) range(dy,-r,r) if(dx*dx + dy*dy <= r*r && S.find(mp(x+dx,y+dy)) != S.end()){
				pi b = mp(x+dx,y + dy);
				int ctr = 0;
				loop(i,w) ctr += intersect(a,b,st[i],en[i]);
				if(ctr <= r && dx*dx + dy*dy <= (r-ctr)*(r-ctr))
					ans.pb(b);
			}
			//sort(all(ans));
			printf("%d",sz(ans));
			for(auto p : ans) printf(" (%d,%d)",p.xx,p.yy);
			puts("");
		}
	}	
	
	
	return 0;
}
