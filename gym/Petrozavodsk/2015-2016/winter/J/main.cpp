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

const int MAX = 200*1000 + 10;
int  A[MAX];
int n,m;
ll sum[MAX];

int main(){
	//freopen("logger.out","w",stderr);
	#ifndef ONLINE_JUDGE
		freopen("input.in", "r", stdin);
	//	freopen("output.out", "w", stdout);
	#endif
	scanf("%d %d",&n,&m);
	loop(i,n) scanf("%d",A + i);
	for(int i = n-1;i >= 0;i--)
		sum[i] = sum[i + 1] + A[i];
	map<int,int> B;
	loop(i,m){
		int x; scanf("%d",&x);
		B[x]++;
	}

	ll cnt = 0;
	int ans = 0;

	for(int dist = 0,cur_plug = 0;!B.empty() && cur_plug < n;dist++){
		if(dist == B.begin()->xx){
			ll tmp = 0;
			int ctr = 0;
			for(ctr = 0;cur_plug < n && ctr < cnt && cnt - ctr - 1 + tmp + A[cur_plug] <= n - B.begin()->yy;ctr++,cur_plug++)
				tmp += A[cur_plug];
			ll d = min(ctr - cnt)
			cnt += tmp - ctr;
		}
		else{
			ll tmp = 0;
			int ctr = 0;
			for(ctr = 0;cur_plug < n && ctr < cnt;ctr++,cur_plug++)
				tmp += A[cur_plug];
			cnt += tmp - ctr;
		}
	}
	while(!B.empty() && cnt){
		ll d = min(B.begin()->yy + 0LL,cnt);
		ans += d;
		cnt -= d;
		B.erase(B.begin());
	}
	return 0;
}
