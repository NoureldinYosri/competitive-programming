#pragma GCC optimize ("O3")
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
#define pl pair<ll,ll>
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

const int MAX = 20000000;
const int MAXE = (MAX + 62)/63;
const int MAXI = 100000;

#define check_bit(x,i) (((x) >> i) & 1)
ll not_prime[MAXE];
pi ans[MAXI];

void sieve(){
	int ctr = 0;
	for(int i = 2;i < MAX;i++){
		if(!check_bit(not_prime[i/63],i%63)){
			if(i > 3 && !check_bit(not_prime[(i-2)/63],(i-2)%63)){
				ans[ctr++] = mp(i-2,i);
				if(ctr == MAXI) break;
			}
			for(ll j = i*1LL*i;j < MAX;j += i)
				not_prime[j/63] |= 1LL << (j%63);
		}
	}
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	sieve();
	for(int n;scanf("%d",&n) == 1;)
		printf("(%d, %d)\n",ans[n-1].xx,ans[n-1].yy);
	return 0;
}
