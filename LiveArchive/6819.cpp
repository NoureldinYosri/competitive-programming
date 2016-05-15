#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define print(A,t) cout << #A << ": "; copy(all(A),ostream_iterator<t>(cout," " )); cout << endl
#define pi pair<int,int>
#define point pi
#define vi vector<int>
#define ll long long
#define pl pair<ll,ll>
#define pre() cin.tie(0),cout.tie(0),ios_base::sync_with_stdio(0)
#define popcnt(x) __builtin_popcount(x)
using namespace std;

double dist(int a,int b,int N){
	double theta = b*2.0*acos(-1)/N - a*2.0*cos(-1)/N;
	if(theta < 0) theta += acos(-1);
	
return sqrt(2e6 - 2e6*cos(theta));
}

bool f(double m,vi & V,int N,int W){
	double d = 0,ctr = 1; vi Q; Q.pb(V[0]);
	int s = 0,e = sz(V) - 1;
	while(s < sz(V) - 1){
		int j = (s + 1)%sz(V),i = s;
		if(!j) break;
		if(d + dist(V[i],V[j],N) <= m) d += dist(V[i],V[j],N);
		else break; 
	}
	while(e >= s){
		int j = (e + 1)%sz(V),i = e;
		if(d + dist(V[i],V[j],N) <= m) d += dist(V[i],V[j],N);
		else break;
	}
	while(s <= e){
		int i = s;
		int j = (i + 1)%sz(V);
		if(d + dist(V[i],V[j],N) > m) {
			++ctr; d = 0;
			Q.clear();
		}
		else{
			d += dist(V[i],V[j],N);
		}
		if(j) Q.pb(j);
		s++;		
	}
	ctr -= Q.empty();
	return ctr <= W;
}


int main(){
	pre();
	int W,N,D;
	while(cin >> W && W){
		cin >> N >> D;
		vi A(N + 1,0);
		loop(i,D){
			int a;
			cin >> a;
			for(int b = a;b <= N;b += a)
				A[b] = 1;
		}
		vi V;
		loop(i,N + 1)
			if(A[i])
				V.pb(i);
		double u = 0,v = 1e8;
		while(abs(v - u) > 1e-4){
			double m = u + (v - u)/2.0;
			if(f(m,V,N,W)) v = m - 1e-4;
			else u = m + 1e-4;
		}
		cout << u << endl;
	}
	return 0;
}

