#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0,_ = (n);i < _;i++)
#define range(i,a,b) for(int i = (a),_ = (b);i <= _;i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b),_ = (a);i >= _;i--)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define vi vector<int>
#define vl vector<long>
#define vd vector<double>
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

string S[] = {"","","ABC","DEF", "GHI","JKL", "MNO","PQRS", "TUV","WXYZ"};
int Z[26];

int T;
char A[50];
int B[50],C[50];

int main(){
	loop(i,10) loop(j,sz(S[i])) Z[S[i][j] - 'A'] = i;
	scanf("%d",&T);
	while(T--){
		scanf("%s",A);
		loop(i,strlen(A)) B[i] = Z[toupper(A[i]) - 'A'];
		copy(B,B + strlen(A),C);
		reverse(C,C + strlen(A));
		bool c = 1;
		loop(i,strlen(A)) c &= B[i] == C[i];
		puts(c ? "YES" : "NO");
	}
	return 0;
}
