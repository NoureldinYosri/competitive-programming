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

int v,A[9],c = INT_MAX,d;
char out[1 << 20];

int main(){
	scanf("%d",&v);
	loop(i,9) {
		scanf("%d",A + i);
		if(c == A[i]) d = i + 1;
		else if(c > A[i]) d = i + 1,c = A[i];
	}
	int n = v/c,r = v - n*c;
	if(!n){
		puts("-1");
		return 0;
	}
	loop(i,n) out[i] = d + '0';
	cerr << out << endl;
	loop(i,n){
		d = 0;
		loop(i,9) if(A[i] <= r + c) d = i;
		out[i] = d + '0' + 1;
		r -= A[d] - c;
	}
	puts(out);
	return 0;
}
