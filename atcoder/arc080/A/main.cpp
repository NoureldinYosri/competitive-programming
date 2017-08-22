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

int cnt[4];
int A[1 << 20];

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	int n,x; scanf("%d",&n);
	loop(i,n) {
		scanf("%d",&x);
		cnt[x%4]++;
	}
	memset(A,-1,sizeof A);
	for(int i = 1;i < n && cnt[0];i += 2,cnt[0]--)
		A[i] = 0;
	for(int i = 0;i < n && cnt[1] + cnt[3];i += 2)
		if(cnt[1]) A[i] = 1,cnt[1]--;
		else A[i] = 3,cnt[3]--;
	for(int i = n-1;i >= 0 && cnt[2];i--)
		if(A[i] == -1){
			A[i] = 2;
			cnt[2]--;
		}
	loop(i,n-1) if((A[i] * A[i+1])%4) {
		puts("No");
		return 0;
	}
	puts("Yes");
	return 0;
}
