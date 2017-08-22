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

int cur [] = {1,2,3,4,5,6,7,6,5,4,3,2,1};
int cnt[13];
int A[1 << 20];
int T,n;

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&T);
	while(T--) {
		scanf("%d",&n);
		loop(i,n) scanf("%d",A + i);
		bool cond = 1;
		int itr = 0;
		for(int i = 0;i < n;itr++) {
			if(itr == 13 || A[i] != cur[itr]) {
				cond = 0;
				break;
			}
			int j = i;
			while(j < n && A[i] == A[j]) j++;
			cnt[itr] = j - i;
			i = j;
		}
		if(itr != 13) cond = 0;
		if(cond) {
			loop(i,6) cond &= cnt[i] == cnt[12 - i];
		}
		puts(cond ? "yes" : "no");
	}
	return 0;
}
