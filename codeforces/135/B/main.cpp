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

pi P[8];


int ccw(pi o,pi u,pi v){
	u.xx -= o.xx,u.yy -= o.yy;
	v.xx -= o.xx,v.yy -= o.yy;
	return u.xx*v.yy - u.yy*v.xx;
}

bool is_sq(vi S){
	loop(i,4) loop(j,i) loop(k,j) if(!ccw(P[S[i]],P[S[j]],P[S[k]])) return 0;
	vi D;
	loop(i,4) loop(j,i) {
		pi p = P[S[i]],q = P[S[j]];
		int d = (p.xx - q.xx)*(p.xx - q.xx) + (p.yy - q.yy)*(p.yy - q.yy);
		D.pb(d);
	}
	sort(all(D));
	return D[0] == D[1] && D[0] == D[2] && D[0] == D[3] && D[4] == D[5] && D[5] == 2*D[0] && D[0];
}


bool is_rect(vi S){
	loop(i,4) loop(j,i) loop(k,j) if(!ccw(P[S[i]],P[S[j]],P[S[k]])) return 0;
	vi D;
	loop(i,4) loop(j,i) {
		pi p = P[S[i]],q = P[S[j]];
		int d = (p.xx - q.xx)*(p.xx - q.xx) + (p.yy - q.yy)*(p.yy - q.yy);
		D.pb(d);
	}
	sort(all(D));
	return D[0] == D[1] && D[2] == D[3] && D[4] == D[5] && D[5] == D[0] + D[2] && D[0] && D[2];
}
int main(){
	loop(i,8) scanf("%d %d",&P[i].xx,&P[i].yy);
	loop(msk,1 << 8) if(popcnt(msk) == 4){
		vi S1,S2;
		loop(i,8) if(msk & (1 << i)) S1.pb(i) ; else S2.pb(i);
		if(is_sq(S1) && is_rect(S2)){
			puts("YES");
			loop(i,4) printf("%d%c",S1[i]+1," \n"[i==3]);
			loop(i,4) printf("%d%c",S2[i]+1," \n"[i==3]);
			return 0;
		}
	}
	puts("NO");
	return 0;
}
