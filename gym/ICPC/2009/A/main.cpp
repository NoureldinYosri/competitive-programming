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

int A[8],B[8],n,ord[8];

bool can(int sep){
	loop(i,n) ord[i] = i;
	do{
		int cur = 0,possible = 1;
		for(int i = 0;i < n && possible;i++){
			if(!i) cur = A[ord[i]] + sep;
			else if(cur > B[ord[i]]) possible = 0;
			else cur = max(cur,A[ord[i]]) + sep;
		}
		if(possible) return 1;
	}while(next_permutation(ord,ord + n));
	return 0;
}

int main(){
	freopen("logger.out","w",stderr);
	#ifndef ONLINE_JUDGE
		freopen("input.in", "r", stdin);
		freopen("output.out", "w", stdout);
	#endif
	for(int t = 1;scanf("%d",&n) == 1 && n;t++){
		loop(i,n) {
			scanf("%d %d",A + i,B + i);
			A[i] *= 60*1000;
			B[i] *= 60*1000;
		}
		int s = 0,e = 24*60*60 * 1000;
		while(s < e){
			int m = s + (e - s + 1)/2;
			if(can(m)) s = m;
			else e = m - 1;
		}
		printf("Case %d: %d:",t,s/(60*1000));
		s %= 60*1000;
		s = s/1000 + (s%1000 >= 500);
		if(s <= 9) putchar('0');
		printf("%d\n",s);
	}

	return 0;
}
