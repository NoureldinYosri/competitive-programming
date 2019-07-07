#ifdef ACTIVE
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

const int MAXN = 44722;
int A,B,C,D;
vi vals;
void init(){
	range(i,1,MAXN+1) vals.push_back(i*(i - 1)/2);
}

int get_n(int x){
	if(!binary_search(all(vals),x)) return -1;
	return lower_bound(all(vals),x) - vals.begin() + 1;
}

int f(int x) {
	return x*(x - 1)/2;
}

string solve(){
	if(A+B+C+D == 0) return "0";
	ll zeros = get_n(A),ones = get_n(D);
	if(zeros == -1 || ones == -1) return "impossible";
	if(B == 0 && C == 0) {
		if(A == 0 && D == 0) {

		}
		else if(A == 0) {
			zeros = 0;
		}
		else if(D == 0) {
			ones = 0;
		}
	}
	if(f(zeros) != A || f(ones) != D) return "impossible";
	if(B + C != zeros * ones) return "impossible";
	// 0 <= i <= zeros
	// 01 -= i
	// 10 -= zeros - i
	// b = sum i
	// c = zeros*ones - sum i
	vi pos;
	loop(j,ones) {
		int i = min(B,(int)zeros);
		B -= i;
		pos.push_back(i);
	}
	string ret = "";
	loop(i,zeros) {
		while(!pos.empty() && pos.back() == i){
			ret += '1';
			pos.pop_back();
		}
		ret += '0';
	}
	while(!pos.empty()) {
		ret += '1';
		pos.pop_back();
	}
	return ret;
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	init();
	cin >> A >> B >> C >> D;
	cout << solve() << endl;
	return 0;
}
#endif
