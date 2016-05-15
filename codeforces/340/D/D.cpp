#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define vi vector<int>
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
#define pre() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

pi P[3];
int ord[3];
int ans = INT_MAX;
typedef pair<pi,pi> line;

bool on(pi p,line l){
	if(l.xx.xx == l.yy.xx){
		if(p.xx == l.xx.xx && min(l.xx.yy,l.yy.yy) <= p.yy && p.yy <= max(l.xx.yy,l.yy.yy))
			return 1;
	}
	else{
		if(p.yy == l.xx.yy && min(l.xx.xx,l.yy.xx) <= p.xx && p.xx <= max(l.xx.xx,l.yy.xx))
			return 1;
	}
	return 0;
}

bool vertical(line l){
	return l.xx.xx == l.yy.xx;
}

bool append(line & l,line o){
	if(vertical(l) && vertical(o)){
		bool c = l.xx.yy <= l.yy.yy && l.yy.yy <= o.yy.yy;
		c |= l.xx.yy >= l.yy.yy && l.yy.yy >= o.yy.yy;
		l.yy = o.yy;
		return c;
	}
	else if(!vertical(l) && !vertical(o)){
		bool c = l.xx.xx <= l.yy.xx && l.yy.xx <= o.yy.xx;
		c |= l.xx.xx >= l.yy.xx && l.yy.xx >= o.yy.xx;
		l.yy = o.yy;
		return c;
	}
	return 0;
}

void f(vector<line> V){
	int ctr = 0;
	loop(i,sz(V)){
		++ctr;
		int j = i + 1;
		line l = V[i];
		while(j < sz(V) && append(l,V[j]))j++;
		i = j - 1;
	}
	ans = min(ans,ctr);
}

void solve(int j,vector<line> V){
	if(j == 3){
		f(V);		
		return;
	}
	int i = ord[j];
	if(on(P[i],V.back())) solve(j + 1,V);
	else{
		line l = mp(V.back().yy,mp(V.back().yy.xx,P[i].yy));
		if(l != V.back() && l.xx != l.yy) {
			V.pb(l);
			solve(j,V);
			V.pop_back();
		}
		l = mp(V.back().yy,mp(P[i].xx,V.back().yy.yy));
		if(l != V.back() && l.xx != l.yy) {
			V.pb(l);
			solve(j,V);
			V.pop_back();
		}
	}
}

int main(){
	loop(i,3) cin >> P[i].xx >> P[i].yy;
	loop(i,3) ord[i] = i;
	do{
		vector<line> V;
		int i = ord[0],j = ord[1];
		V.pb(mp(mp(P[i].xx,P[i].yy),mp(P[i].xx,P[j].yy)));
		solve(0,V);
		V.pop_back();
		V.pb(mp(mp(P[i].xx,P[i].yy),mp(P[j].xx,P[i].yy)));
		solve(0,V);
	}while(next_permutation(ord,ord + 3));
	cout << ans << endl;	
	return 0;
}
