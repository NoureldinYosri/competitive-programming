#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
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

int mod = 1234567891,i4 = 308641973;
unsigned int __;

#define mul(a,b) (((a)*1LL*(b))%mod)

const int MAX = 50*100*1000;
int inv[MAX + 1];

int add(ll a,int b){
	a += b;
	if(a >= mod) a -= mod;
	return a;
}
int powmod(int x,int p){
	if(p == 0) return 1;
	int y = 1;
	for(;p > 1;p >>= 1){
		if(p & 1) y = (x*1LL*y)%mod;
		x = (x*1LL*x)%mod;
	}
	return y = (x*1LL*y)%mod;
}

void init(){
	inv[0] = inv[1] = 1;
	for(int i = 2;i <= MAX;i++) {
		if(inv[i] == 0) {
			inv[i] = powmod(i,mod - 2);
			for(int j = i+i,K = 2;j <= MAX;j += i,K++){
				if(inv[j] == 0) inv[j] = 1;
				int k = K,I = inv[i];
				while(k%i == 0) {
					k /= i;
					I = (I * 1LL * inv[i])%mod;
				}
				inv[j] = (I * 1LL * inv[j])%mod;
			}
		}
		//inv[i] = powmod(i,mod - 2);
	}
}

class TheBeautifulBoard{
public:
	
	
	
	inline int BiNomial(ll n,ll k){
		if(k > n) return 0;
		k = min(k,n - k);
		int ret = 1;
		for(int i = 0;i < k;i++){
			ret = mul(ret,(n - i)%mod);
			ret = mul(ret,inv[i+1]);
		}
		return ret;
	}
	
	int multiNomial(ll n,vi checkers){
		ll r = n;
		for(int x : checkers) r -= x;
		if(r < 0) return 0;
		
		int ret = BiNomial(n,r);
		
/*		n -= r;
		for(int x : checkers){
			x = min(x + 0LL,n - x);
			for(int i = 0;i < x;i++){
				ret = mul(ret,n - i);
				ret = mul(ret,inv[i + 1]);
			}
			n -= x;
		}
	*/
		for(int x : checkers){
			ret = mul(ret,BiNomial(n - r,x));
			r += x;
		}

		return ret;
	}


	int solve90(int n,vi checkers){
		int odd = 0;
		for(int & x : checkers){
			odd += x & 1;
			x &= ~1;
			if(x%4) return 0;
			x /= 4;
		}
		if(odd > 1) return 0;
		if(n%2 == 0 && odd) return 0;
		
		ll F = (n/2LL)*(n/2);
		if(n & 1) F += n/2;
		
		return multiNomial(F,checkers);		
	}

	int solve180(int n,vi checkers){
		int odd = 0;
		for(int & x : checkers){
			odd += x & 1;
			x &= ~1;
			x >>= 1;
		}
		if(odd > 1) return 0;
		if(n%2 == 0 && odd) return 0;
		
		ll F = (n/2)*(n/2LL) * 2;
		if(n & 1) F += n ^ 1;
		
		return multiNomial(F,checkers);
	}
	int solveF(int n,int k,vi checkers){
		if(k == 1 || k == 2) return solve90(n,checkers);
		else return solve180(n,checkers);
	}

	
	int count(int n, vector <int> checkers){
		init();
		int ret = multiNomial(n*1LL*n,checkers);
		for(int k = 1;k < 4;k++)
			ret = add(ret,solveF(n,k,checkers));
		ret = mul(ret,i4);
		return ret;
	}
};
vi N;
vector<vi> AV;
vector<int> correct_ans;

int main(){
	N.push_back(1);
	AV.push_back(vi{1});
	correct_ans.push_back(1);
	
	
	N.push_back(2);
	AV.push_back(vi{1,2});
	correct_ans.push_back(3);
	
	N.push_back(3);
	AV.push_back(vi{1,1});
	correct_ans.push_back(18);
	
	N.push_back(3);
	AV.push_back(vi{4,2,1,3});
	correct_ans.push_back(0);
	
	
	N.push_back(3);
	AV.push_back(vi{2});
	correct_ans.push_back(10);
	
	N.push_back(3);
	AV.push_back(vi{8});
	correct_ans.push_back(3);


	N.push_back(91001);
	AV.push_back(vi{73636, 38524, 30308, 99328, 27748, 91812, 73432, 44812, 32784, 97108, 16264, 16656, 68072, 65184, 61880, 22968, 51456, 77992, 83836, 80268, 43352, 75592, 80404, 62528, 23156, 7324, 87724, 21844, 86520, 82140, 72248, 51840, 78332, 82712, 45192, 54320, 94948, 63664, 26428, 68256, 15460, 36536, 70048, 56356, 95960, 79748, 64376, 44452, 8876});
	correct_ans.push_back(877858199);
	
/*	for(int i = 0;i < sz(N);i++){
		cout << "n = " << N[i] << " ,checkers: [";
		for(int x : AV[i]) cout << x << " ";
		cout << "\b] correct = " << correct_ans[i] << " found " << TheBeautifulBoard().count(N[i],AV[i]) << endl;
		TheBeautifulBoard().count(N[i],AV[i]);
	}
	
	*/
	
	cout << TheBeautifulBoard().count( 8, vi{7, 1, 7, 9, 7}) << endl;

	return 0;
}

