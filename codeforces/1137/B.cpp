//#pragma GCC optimize ("O3")
//#include <bits/stdc++.h>
//#define loop(i,n) for(int i = 0;i < (n);i++)
//#define range(i,a,b) for(int i = (a);i <= (b);i++)
//#define all(A) A.begin(),A.end()
//#define pb push_back
//#define mp make_pair
//#define sz(A) ((int)A.size())
//#define vi vector<int>
//#define vd vector<double>
//#define vp vector<pair<int,int> >
//#define ll long long
//#define pi pair<int,int>
//#define popcnt(x) __builtin_popcountll(x)
//#define LSOne(x) ((x) & (-(x)))
//#define xx first
//#define yy second
//#define PQ priority_queue
//#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
//#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
//#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
//#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
//#define what_is(x) cerr << #x << " is " << x << endl
//#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
//using namespace std;
//
//const int MAXN = 500*1000 + 10;
//
//int pf[MAXN];
//char S[MAXN],T[MAXN];
//int m,n;
//
//
//
//int mem[MAXN][2];
//
//int GetLen(char c,int l,char *s){
//	int & ret = mem[l][c - '0'];
//	if(ret != -1) return ret;
//	while(l && s[l] != c) l = pf[l - 1];
//	if(s[l] == c) l++;
//	return ret = l;
//}
//
//void BuildFailure(char *s){
//	pf[0] = 0;
//	int n = strlen(s);
//	range(i,1,n - 1) pf[i] = GetLen(s[i],pf[i - 1],s);
//}
//
//
//int main(int argc,char **argv){
//#ifdef HOME
//	freopen("in.in","r",stdin);
//#endif
//	scanf("%s %s",S,T);
//	m = strlen(S);
//	n = strlen(T);
//	memset(mem,-1,sizeof mem);
//	BuildFailure(T);
//	int ctr [2] = {0};
//	loop(i,m) ctr[S[i]-'0']++;
//
//	int len = 0,cnt = 0;
//	loop(i,m) {
//		int d = T[len] - '0';
//		if(ctr[d] == 0) d ^= 1;
//		putchar(d + '0');
//		assert(ctr[d] > 0);
//		ctr[d]--;
//		len = GetLen(d + '0',len,T);
//		if(len == n) len = pf[n-1],cnt ++;
//	}
//
//	puts("");
////	cerr << cnt << endl;
//
//	return 0;
//}
