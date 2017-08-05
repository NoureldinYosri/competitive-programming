#pragma GCC optimize("O3")
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

int X[300],Y[300],n;
int P[300],m;
int c1[300],c2[300];
int Q[300];

inline int ccw(int a,int b,int c){
	int x1 = X[b] - X[a],x2 = X[c] - X[a];
	int y1 = Y[b] - Y[a],y2 = Y[c] - Y[a];
	return x1*y2 - x2*y1;
}
/*
double get_angle(int p,int u,int v){
	int x = X[p] - X[u],y = Y[p] - Y[u];
	int x2 = X[v] - X[u],y2 = Y[v] - Y[u];
	int dot = x*x2 + y*y2;
	double l1 = hypot(x,y),l2 = hypot(x2,y2);
	return dot/l1/l2;
}
*/
double get_angle(int o,int p){
	int x = X[p] - X[o],y = Y[p] - Y[o];
	double t = atan2(y,x);
	if(abs(t) < 1e-12) t = 0;
	else if(t < 0) t += 2*PI;
	return t;
}

int work(int x,int y){
//	prArr(P,m,int);
	double c = -1; int ret = 0;
	loop(i,m){
		c1[i] = c;
		if(c == -1) c = P[i];
		else if(ccw(x,c,P[i]) > 0) c = P[i];
	}
	c = -1;
	for(int i = m-1;i >= 0;i--){
		c2[i] = c;
		if(c == -1) c = P[i];
		else if(ccw(y,c,P[i]) < 0) c = P[i];
	}
	//prArr(c1,m,int);
	//prArr(c2,m,int);
	loop(i,m) {
		int t = (c1[i]==-1 || ccw(x,c1[i],P[i]) > 0) && (c2[i]==-1 || ccw(y,c2[i],P[i]) < 0);
		ret += t;
	}
	return ret;
}

int solve(int i,int j){
	m = 0;
	loop(k,n) if(i != k && j != k && ccw(i,j,k) < 0) P[m++] = k;
	int ret = work(i,j);
	return ret;
}

int main(){
	freopen("farmer.in","r",stdin);
	freopen("farmer.out","w",stdout);
	scanf("%d",&n);
	loop(i,n) scanf("%d %d",X + i,Y + i);
	int ans = 0;
	loop(i,n) Q[i] = i;
	deque<int> aux;
	for(int i = 0;i < n;i++) {
		int t = 0;
		loop(j,n) if(i != j) Q[t++] = j;
		sort(Q,Q + n - 1,[i](const int & a,const int & b){
			return get_angle(i,a) < get_angle(i,b);
		});
/*		loop(j,n-1) cerr << Q[j] << " " << get_angle(i,Q[j])*180/PI << endl;
		cerr << endl;
/*		sort(Q,Q + n - 1,[i](const int & a,const int & b){
			return ccw(i,a,b) > 0;
		});
		prArr(Q,n-1,int);
*/		loop(j,n) if(i != j){
			loop(k,n-1) {
				int r = ccw(i,j,Q[k]);
				if(Q[k] == i || Q[k] == j) assert (r == 0);
				if(r < 0) aux.pb(Q[k]);
			}
			int pos = -1;
			for(int k = 0;k + 1 < sz(aux);k++)
				if(ccw(i,aux[k],aux[k + 1]) < 0){
					pos = k;
					break;
				}
//			cerr << "convert "; print(aux,int);
//			cerr << "because pos = " << pos << " convert to " << endl;
			loop(k,pos+1) {
				aux.pb(aux.front());
				aux.pop_front();
			}
//			cerr << i << " " << j << " : ";
//			print(aux,int);
			copy(all(aux),P);
			m = sz(aux);
			ans += work(i,j);
			aux.clear();
		}
//		cerr << endl;
	}
//	cerr << ans << endl;
	assert(ans%3 == 0);
	ans /= 3;
	cerr << ans << endl;
	cout << ans << endl;

	//loop(i,n) loop(j,i) cerr << "(" << i << " ," << j << ") = " << solve(i,j) << " " << solve(j,i) << endl;
	//cerr << solve(0,2)  << endl;
	return 0;
}
