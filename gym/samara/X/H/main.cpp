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
#define popcnt(x) __builtin_popcount(x)
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

int m,n;
int A[1000][1000];
int mx[1000],mx2[1000],cnt[1000];

int main(){
	freopen("logger.out","w",stderr);
	#ifndef ONLINE_JUDGE
		freopen("input.in", "r", stdin);
		freopen("output.out", "w", stdout);
	#endif
	scanf("%d %d",&m,&n);
	loop(i,m) loop(j,n){
		scanf("%d",&A[i][j]);
		if(A[i][j] > mx2[j]) mx2[j] = A[i][j];
		if(mx2[j] > mx[j]) swap(mx2[j],mx[j]);
	}
	int best = INT_MAX,r = 0,c = 0;
	vi aux(n);
	loop(i,m) {
		int x = INT_MIN;
		for(int j = n - 1;j >= 0;j--){
			aux[j] = x;
			int v = mx[j];
			if(v == A[i][j]) v = mx2[j];
			x = max(x,v);
		}
		x = INT_MIN;
		for(int j = 0;j < n;j++){
			int cur = max(x,aux[j]);
			if(cur < best ){
				best = cur;
				r = i;
				c = j;
			}
			int v = mx[j];
			if(v == A[i][j]) v = mx2[j];
			x = max(x,v);
		}
	}
	cout << r + 1 << " " << c + 1 << endl;
	return 0;
}
