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
using namespace std;

const int MAX = 1 << 20,MAXLG = 20;
int A[MAX],n;
int ans[MAX];
int ST[MAX][MAXLG],lg[MAX];

#define mymin(a,b) (((a) < (b)) ? (a) : (b))
#define mymax(a,b) (((a) > (b)) ? (a) : (b))

void init(){
	lg[0] = -1;
	loop(i,MAX - 1) {
		lg[i + 1] = lg[i] + ((i + 1) == LSOne(i + 1));
	}
	loop(i,n) ST[i][0] = A[i];
	loop(k,MAXLG - 1){
		loop(i,n){
			int j = i + (1 << k);
			if(j >= n) j = i;
			ST[i][k + 1] = mymax(ST[i][k],ST[j][k]);
		}
	}
}

int readInt () {
	bool minus = false;
	int result = 0;
	char ch;
	ch = getchar();
	while (true) {
		if (ch == '-') break;
		if (ch >= '0' && ch <= '9') break;
		ch = getchar();
	}
	if (ch == '-') minus = true; else result = ch-'0';
	while (true) {
		ch = getchar();
		if (ch < '0' || ch > '9') break;
		result = result*10 + (ch - '0');
	}
	if (minus)
		return -result;
	else
		return result;
}

int get(int a,int b){
	int l = lg[b - a + 1];
	return mymax(ST[a][l],ST[b - (1 << l) + 1][l]);
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	n = readInt();
	loop(i,n) A[i] = readInt();
	init();
	ans[n-1] = get(0,n-1);
 	for(int len = 3,k = n-3,m,t,i;len <= n;len += 2,k -= 2){
		for(i = 0,m = len/2;i <= n - len;i++,m++){
			t = mymin(A[m],mymax(A[m - 1],A[m + 1]));
			ans[k] = mymax(ans[k],t);
		}
	}
 	for(int len = 2,k = n-2;len <= n;len += 2,k -= 2)
		ans[k] = get(len/2 - 1,n-len/2);
	loop(k,n) printf("%d%C",ans[k]," \n"[k==n-1]);
	return 0;
}
