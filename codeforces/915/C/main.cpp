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

int cnt[10];
int B[20],m;
int A[20],n;

bool bt(int cur,bool eq) {
	if(cur == m) return 1;
	for(int d = 9;d >= 0;d--) if(cnt[d]){
		if(eq){
			if(d > B[cur]) continue;
			cnt[d]--;
			A[cur] = d;
			if(bt(cur+1,d == B[cur])) return 1;
			cnt[d]++;
		}
		else {
			cnt[d]--;
			A[cur] = d;
			if(bt(cur+1,0)) return 1;
			cnt[d]++;
		}
	}
	return 0;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	string a,b;
	cin >> a >> b;
	for(char c : a) cnt[(int)(c - '0')]++;
	m = sz(b);
	for(int i = 0;i < m;i++)
		B[i] = b[i] - '0';
	n = sz(a);
	assert(bt(m-n,m==n));
	loop(i,n) putchar(A[i + m - n] + '0');
	puts("");
	return 0;
}
