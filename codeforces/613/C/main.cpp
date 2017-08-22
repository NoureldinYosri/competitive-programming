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

int A[26],n,odd;


string build(int & ans){
	string ret;
	ans = 0;
	int di = 1,cur = 0,sum = 0;
	loop(i,n) sum += A[i];
	for(;sum;){
		if(A[cur]) {
			A[cur] -= 2;
			sum -= 2;
			if(sum == 0) ans++;
			if(ret.empty()) ans++;
			else if(ret.back() == (cur + 'a')) ans += 2;
			ret += cur + 'a';
		}
		cur += di;
		if(cur == n) cur = n-1,di *= -1;
		else if(cur == -1) cur = 0,di *= -1;
	}
	string tmp = ret;
	reverse(all(tmp));
	ret += tmp;
	return ret;
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&n);
	loop(i,n){
		scanf("%d",A + i);
		odd += A[i] & 1;
	}
	if(n == 1){
		printf("%d\n",A[0]);
		loop(i,n) while(A[i]-- > 0) putchar(i + 'a');
		puts("");
	}
	else if(odd > 1) {
		puts("0");
		loop(i,n) while(A[i]-- > 0) putchar(i + 'a');
		puts("");
	}
	else if(odd == 1){
		char c = 0;
		loop(i,n) if(A[i] & 1) {
			A[i] ^= 1;
			c = i + 'a';
		}
		int ans;
		string out = build(ans);

	}
	else {
		int ans = 0;
		string out = build(ans);
		cerr << ans << endl;
		cerr << out << endl;
	}
	return 0;
}
