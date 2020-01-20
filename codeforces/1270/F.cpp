#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
typedef std::vector<int> vi;
typedef std::pair<int,int> pi;
typedef std::vector<pi> vp;
typedef long long ll;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
using namespace std;


int n;
char txt[1 << 20];
int S[1 << 20];

int f(int n,int r,int m){
	if(r == 0) return n/m;
	return n/m + (r <= n%m);
}

int nxt[1 << 20];

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%s", txt + 1);
	n = strlen(txt+1);
	for(int i = 1;i <= n;i++)
		S[i] = S[i-1] + txt[i] - '0';
	
	nxt[n+1] = -1;
	for(int i = n;i >= 1;i--)
		nxt[i] = (txt[i+1] == '1') ? i+1 : nxt[i+1];
	int B = sqrt(n);
	

	int big = (B+1)*n;
	vi freq(big+1,0);
	
	ll ans = 0;
	for(int k = 1;k <= B;k++){
		for(int i = 0;i <= n;i++){
			ll f = k*(ll)S[i] - i + n;
			ans += freq[f];
			freq[f]++;
		}
		for(int i = 0;i <= n;i++){
			ll f = k*(ll)S[i] - i + n;
			freq[f]--;
		}
	}
	
	

	for(int k = 1;k <= B;k++){
		int ctr = 0,s = 0;

		for(int l = 1;l <= n;l++){
			while(s < n && ctr < k){
				++s;
				ctr += txt[s] == '1';
			}
			if(ctr != k) break;
			
			int e = nxt[s];
			if(e == -1) e = n;
			else e--;
			
			int r = (l-1)%k;
			if(s-l+1 > k*B) {
				ans += f(e,r,k) - f(s-1,r,k);						
			}
			else if(e-l+1 > k*B){
				ans += f(e,r,k) - f(l+k*B-1,r,k);						
			}
			ctr -= txt[l] == '1';
		}		
	}

	cout << ans << endl;
	return 0;
}
