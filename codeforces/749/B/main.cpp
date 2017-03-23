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

int X[3],Y[3];
vp ans;

void work(int i,int j,int k,int x){
	if(X[i] == X[j]){
		if(X[k] != x) return;
		int y = Y[k] + Y[j] - Y[i];
		ans.pb(mp(x,y));
		return;
	}
	else if(x == X[k]) return;
	int g = (Y[j] - Y[i]) * (x - X[k]);
	if(g%(X[j] - X[i])) return;
	g /= (X[j] - X[i]) ;
	int y = g + Y[k];
	int a = y - Y[j],b = x - X[j],c = Y[k] - Y[i],d = X[k] - X[i];	
	if(a*d == b*c) 
		ans.pb(mp(x,y));
}


int main(){
	loop(i,3) scanf("%d %d",X + i,Y + i);
	for(int x = -3000;x <= 3000;x++){
		loop(i,3) loop(j,i) {
			work(i,j,3 - i - j,x);
			work(j,i,3 - i - j,x);
		}
	}
	sort(all(ans));
	ans.resize(unique(all(ans)) - ans.begin());
	printf("%d\n",sz(ans));
	for(auto p : ans) printf("%d %d\n",p.xx,p.yy);	
	cerr << sz(ans) << endl;
	return 0;
}
