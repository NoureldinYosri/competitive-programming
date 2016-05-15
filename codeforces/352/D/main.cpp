#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0,_ = (n);i < _;i++)
#define range(i,a,b) for(int i = (a),_ = (b);i <= _;i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b),_ = (a);i >= _;i--)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define vi vector<int>
#define vl vector<long>
#define vd vector<double>
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

int n,k;
int A[1 << 20];
int B[1 << 20];
map<int,int> S;

void process(){
	sort(A,A + n);
	int k = 0;
	loop(i,n){
		int j = i;
		while(j < n && A[i] == A[j]) j++;
		A[k] = A[i];
		B[k] = j - i;
		i = j - 1;
	}
	n = k;
}

int solve(int s,int e){
	if(e - s + 1 == 1) return 0;
	else if(n == 2){
		int x = min(A[s],A[e]), y = max(A[s],A[e]);
		int d = y - x;
		if(d & 1){
			if(k >= d/2) return 1;
			else return d - 2*k;
		}
		else{
			if(k >= d/2) return 0;
			else return d - 2*k;
		} 
	}
	else{
		process();
		e = n - 1;		
		while(k){
			if(s == e) return 0;
			ll d1 = A[s + 1] - A[s],d2 = A[e] - A[e - 1];
			ll d = min(d1,d2);
			ll n = k/d; n = min(n,B[s]); n = min(n,B[e]);
			B[s] -= n*d/d1;
			B[e] -= n*d/d2;
			k -= n * d;			
		}
		return abs(A[s] - A[e]);
	}
}

int main(){
	scanf("%d %d",&n,&k);
	loop(i,n) {
		scanf("%d",A + i);
	}
	cout << solve(0,n - 1) << endl;
	return 0;
}
