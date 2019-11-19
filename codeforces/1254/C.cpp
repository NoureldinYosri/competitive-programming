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



ll ask(int t,int i,int j,int k){
	cout << t << " " << i << " " << j << " " << k << endl;
	fflush(stdout);
	ll r; cin >> r;
	return r;
}

ll askSign(int i,int j,int k){
	ll r = ask(2,i,j,k);
	return (r > 0) - (r < 0);
}

ll askArea(int i,int j,int k){
	return ask(1,i,j,k);
}

ll A[1024];



int main(){
	int n; cin >> n;
	int p = 2;
	
	for(int i = 3;i <= n;i++){
		if(askSign(1,p,i) == -1) p = i;
	}
	

	vector<int> S[2];
	int j = p;
	for(int i = 2;i <= n;i++) if(i != p) {
		A[i] = abs(askArea(1,p,i));
		if(A[i] > A[j]) j = i;
	}


	for(int i = 2;i <= n;i++) if(i != j){
		int s = askSign(1,j,i);
		s = (s + 1)/2;
		S[s].push_back(i);
	}

	loop(c,2){
		sort(all(S[c]),[](const int & a,const int & b){
			return A[a] < A[b];
		});
		if(c) reverse(all(S[c]));
	}
	vi P; P.push_back(1);
	for(int x : S[0]) P.push_back(x);
	P.push_back(j);
	for(int x : S[1]) P.push_back(x);
	cout << 0 ;
	for(int x : P) cout << " " << x;
	cout << endl; 
	return 0;
}

