#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
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
using namespace std;

const int MAX = 10*1000 + 10;
deque<int> primes;
int n;

void init(){
	for(int i = 2;i <= n;i++) {
		int k = i;
		for(int j = 2;j*j <= i;j++)
			while(k%j == 0)
				k /= j;
		if(k == i)
			primes.push_back(i);
	}
}

int main(int argc,char **argv){
	freopen("gcd.in","r",stdin);
#ifndef HOME
	freopen("gcd.out","w",stdout);
#endif
	scanf("%d",&n);
	init();
	int ans = 0;
	while(!primes.empty()) {
		int v = primes.back(); primes.pop_back();
		while(!primes.empty() && primes.front()*v <= n) {
			v *= primes.front();
			primes.pop_front();
		}
		ans++;
	}

	printf("%d\n",ans);
	return 0;
}
