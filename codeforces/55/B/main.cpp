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

char c1,c2,c3;

ll dfs2(ll a,ll b){
	return (c3 == '*') ? (a*b) : (a + b);
}

ll dfs3(ll a,ll b,ll c){
	ll ret = LLONG_MAX;
	ll A[] = {a,b,c};
	loop(i,3) loop(j,i){
		int B[2],ctr = 0;
		loop(k,3) if(k != i && k != j) B[ctr++] = A[k];
		B[1] = (c2 == '*') ? (A[i] * A[j]) : (A[i] + A[j]);
		ret = min(ret,dfs2(B[0],B[1]));
	}
	return ret;
	
}

ll dfs4(ll a,ll b,ll c,ll d){
	ll ret = LLONG_MAX;
	ll A[] = {a,b,c,d};
	loop(i,4) loop(j,i){
		int B[3],ctr = 0;
		loop(k,4) if(k != i && k != j) B[ctr++] = A[k];
		B[2] = (c1 == '*') ? (A[i] * A[j]) : (A[i] + A[j]);
		ret = min(ret,dfs3(B[0],B[1],B[2]));
	}
	return ret;
}

int main(){
	ll a,b,c,d;
	cin >> a >> b >> c >> d >> c1 >> c2 >> c3;
	cout << dfs4(a,b,c,d) << endl;
	
	return 0;
}
