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

int X[4],Y[4];

void special(int d){
	Y[0] = 1;
	Y[1] = d;
	Y[2] = 0;
	Y[3] = d-1;
}

int main(){
	int n ,m; cin >> n >> m;
	vp P; double ans = 0;
	P.pb(mp(0,0));
	P.pb(mp(n,m));
	P.pb(mp(0,m));
	P.pb(mp(n,0));
	if(n) P.pb(mp(n-1,m));	
	if(m) P.pb(mp(n,m-1));
	if(n && m) P.pb(mp(n-1,m-1));
	if(n >= 1) P.pb(mp(1,m)),P.pb(mp(1,0));
	if(m >= 1) P.pb(mp(n,1)),P.pb(mp(0,1));
	sort(all(P));
	P.resize(unique(all(P)) - P.begin());
	//for(auto p : P) prp(p);
	//cerr << endl;
	assert(sz(P) >= 4);
	loop(msk,1 << sz(P)) if(popcnt(msk) == 4) {
		vp aux;
		loop(i,sz(P)) if(msk & (1 << i)) aux.pb(P[i]);
		do{
			double dist = 0;
			loop(i,3) dist += hypot(aux[i].xx - aux[i + 1].xx,aux[i].yy - aux[i + 1].yy);
			if(dist > ans){
				ans = dist;
				loop(i,4) X[i] = aux[i].xx,Y[i] = aux[i].yy;
			}
		}while(next_permutation(all(aux)));
	}
	loop(i,4) printf("%d %d\n",X[i],Y[i]);
	prArr(X,4,int);
	prArr(Y,4,int);
	return 0;
}
