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

typedef vector<long double> poly;
char line[111];
poly one {1.0};

poly add(poly f,poly g){
	poly q;
	int n1 = sz(f),n2 = sz(g);
	int n = max(n1,n2);
	for(int i = 0;i < n;i++){
		long double v = 0;
		if(i < n1) v += f[i];
		if(i < n2) v += g[i];
		q.pb(v);
	}
	return q;
}

poly sub(poly f,poly g){
	poly q;
	int n1 = sz(f),n2 = sz(g);
	int n = max(n1,n2);
	for(int i = 0;i < n;i++){
		long double v = 0;
		if(i < n1) v += f[i];
		if(i < n2) v -= g[i];
		q.pb(v);
	}
	return q;
}

poly mult(poly f,poly g){
	int n1 = sz(f),n2 = sz(g);
	poly q(n1 + n2 - 1);
	for(int i = 0;i < n1 + n2 - 1;i++)
		for(int j = 0;j < n1 && i - j >= 0;j++) {
			if(i - j >= n2) continue;
			q[i] += f[j] * g[i - j];
		}
	return q;
}

poly integerate(poly f){
	int n = sz(f);
	poly I(n + 1);
	loop(i,n) I[i + 1] = f[i]/(i + 1);
	return I;
}

poly solve(int s,int e,int & nxt){
	if(line[s] == 'x') {
		nxt = s + 1;
		return one;
	}
	poly f1 = solve(s+1,e,nxt);
	poly f2 = solve(nxt,e,nxt);
	if(line[s] == 'M') return add(mult(f1,integerate(f2)),mult(f2,integerate(f1)));
	else return add(mult(f1,sub(one,integerate(f2))),mult(f2,sub(one,integerate(f1))));
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	int T; scanf("%d",&T);
	while(T--){
		scanf("%s",line);
		int aux;
		poly pdf = solve(0,strlen(line) - 1,aux);
		assert(aux == (int)strlen(line));
		poly I = integerate(mult(poly({0.0,1.0}),pdf));
		long double ans = 0.0;
		loop(i,sz(I)) ans += I[i];
		cout << ans << endl;
	}
	return 0;
}
