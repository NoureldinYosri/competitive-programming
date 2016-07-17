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

const int MAX = 1 << 20;
int A[MAX],B[MAX],n;
int STA[MAX][20],STB[MAX][20];
int lg[MAX];


void init(){
	lg[0] = -1;
	loop(i,MAX - 1){
		int j = i + 1;
		lg[j] = lg[i] + (LSOne(j) == j);
	}
	loop(i,n) STA[i][0] = A[i],STB[i][0] = B[i];
	loop(k,19) loop(i,n){
		int u = STA[i][k],v = (i + (1 << k) < n) ? STA[i + (1 << k)][k] : STA[i][k];
		STA[i][k + 1] =  max(u,v);
		u = STB[i][k],v = (i + (1 << k) < n) ? STB[i + (1 << k)][k] : STB[i][k];
		STB[i][k + 1] = min(u,v);		
	}
}

int get(int l,int r,int ST[MAX][20],int c){
	int q = lg[r - l + 1];
	int (*f)(int,int);
	if(c) f = [](int a, int b){ return std::max(a, b); };
	else f = [](int a, int b){ return std::min(a, b); };
	return f(ST[l][q],ST[r - (1 << q) + 1][q]);
}


int lower_bound(int l){
	int s = l,e = n - 1;
	while(s < e){
		int m = (s + e) >> 1;
		int f = get(l,m,STA,1) - get(l,m,STB,0);
		if(f >= 0) e = m;
		else s = m + 1;
	}
	int f = get(l,s,STA,1) - get(l,s,STB,0);
	return s + (s == n - 1 && f < 0);
}

int upper_bound(int l){
	int s = l,e = n - 1;
	while(s < e){
		int m = (s + e) >> 1;
		int f = get(l,m,STA,1) - get(l,m,STB,0);
		if(f > 0) e = m;
		else s = m + 1;
	}
	int f = get(l,s,STA,1) - get(l,s,STB,0);
	return s + (s == n - 1 && f <= 0);
}




int main(){
	PRESTDIO();
	cin >> n;
	loop(i,n) cin >> A[i];
	loop(i,n) cin >> B[i];
	init();
	ll ans = 0;
	loop(i,n) {
		int tmp = upper_bound(i) - lower_bound(i);		
		ans += tmp;	
	//	cerr << i << " " << lower_bound(i) << " " << upper_bound(i) << " " << tmp << " " << get(i,n-1,STA,1) - get(i,n-1,STB,0) << endl;
	}
	cout << ans << endl;
	cerr << ans << endl;
	return 0;
}
