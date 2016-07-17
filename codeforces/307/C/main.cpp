#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long>
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

int n, m, A[200000],B[200000];

bool cond(long long t){
	copy(A,A + n,B);
	int e = 0;
	loop(i,n) if(A[i]) e = i;
	int i = 0,j = 0; ll T = t-1;
	while(i < n && j < m){
		ll d = max(min(B[i]+0LL,T),0LL);
		B[i] -= d;
		T -= d;
		if(B[i] == 0 && i == e) return 1;
		while(i < n && B[i] == 0 && T > 0) i++,T--;
		if(T == 0) T = t - i - 1,j++;	
	}
	return i == n;
}

int main(){
	scanf("%d %d", &n, &m);
	loop(i,n) scanf("%d",A + i);
	long long u = 1, v = 1LL << 60, t;
	while (u < v){
		t = (u + v) >> 1;
		if (cond(t)) v = t;
		else u = t + 1;
	}
	cout << u << "\n";
	return 0;
}
