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

const int MAX = 1 << 20;
char A[MAX],B[MAX];
int n,m,D;
string pivot;
bool valid [10];

void getBestChar(){
	for(D = 9;D > 0;D--)
		if(valid[D])
			break;
}

string s1(){
	string ret ;
	ret.pb(D + '0');
	loop(i,n-1) ret.pb(A[i]);
	return ret;
}

string s2(){
	string ret = pivot;
	loop(i,n) {
		int x = A[i] - '0';
		if(D > x){
			ret[i] = D + '0';
			break;
		}
	}
	return ret;
}

string s3(){
	string ret = "";
	queue<int> q;
	int i = 0;
	for(;i + 1 < n;i++) {
		int x = A[i] - '0',y = A[i + 1] - '0';
//		cerr << i << " " << ret << endl;
		if(x < y) {
//			cerr << "found" << endl;
			i++;
			break;
		}
		else {
			ret.pb(A[i]);
		}
	}
//	cerr << "out" << endl;
//	cerr << i << " " << ret << endl;
	for(;i < n && sz(ret) < n;i++){
		int x = A[i] - '0';
		if(x < D) {
			ret.pb(D + '0');
			break;
		}
		ret.pb(A[i]);
	}
	for(;i < n && sz(ret) < n;i++) ret.pb(A[i]);
	if(sz(ret) < n) ret.pb(D + '0');
//	cerr << ret << endl;
	assert(sz(ret) == n);
	return ret;
}

string DO() {
	string ret = string(A);
	ret.pop_back();
	loop(i,n-1) {
		int x = A[i] - '0',y = A[i + 1] - '0';
		if(x < y) {
			string s = string(A);
			s.erase(s.begin() + i);
			ret = max(ret,s);
			break;
		}
	}
	string s = ret;
	ret = "";
	for(int i = 0;i < sz(s);i++) {
		int x = s[i] - '0';
		if(D > x) {
			ret.pb(D + '0');
			for(;i < sz(s);i++)
				ret.pb(s[i]);
			break;
		}
		ret.pb(s[i]);
	}
	if(sz(ret) < n) ret.pb(D + '0');
	return ret;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	int T; scanf("%d",&T);
	range(t,1,T) {
		scanf("%s %s",A,B);
		n = strlen(A);
		m = strlen(B);
		pivot = string(A);
		memset(valid,0,sizeof valid);
		loop(i,m) valid[B[i] - '0'] = 1;
		getBestChar();
		string ans = DO();
		if(ans <= pivot) ans = "impossible";
		printf("%s\n",ans.c_str());
	}
	return 0;
}
