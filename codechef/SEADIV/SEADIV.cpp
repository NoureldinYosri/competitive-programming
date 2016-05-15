#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define print(A,t) cout << #A << ": "; copy(all(A),ostream_iterator<t>(cout," " )); cout << endl
#define pi pair<int,int>
#define point pi
#define vi vector<int>
#define ll long long
#define pl pair<ll,ll>
#define pre() cin.tie(0),cout.tie(0),ios_base::sync_with_stdio(0)
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define prp(p) cout << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cout << #A << ": "; copy(A,A + n,ostream_iterator<t>(cout," " )); cout << endl
using namespace std;

char A[1 << 20],B[1 << 20],C[1 << 20];
int n;

int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		scanf(" %s %s %d",A,B,&n);
		reverse(A,A + strlen(A));  int LA = strlen(A);
		reverse(B,B + strlen(B));  int LB = strlen(B);
		int r = 0;
		loop(i,n){
			int a = 0,b = 0;
			if(i < LA) a = A[i] - '0';
			if(i < LB) b = B[i] - '0';
			int d = a - r; d %= 7; if(d < 0) d += 7;
			int j;
			for(j = 0;j < 7;j++) if((j*b)%7 == d) break;
			C[i] = j + '0';
		}
		while(n && C[n - 1] == '0') n--;
		if(n == 0) C[n++] = '0';
		reverse(C,C + n);
		C[n] = '\0';
		puts(C);
	}
	return 0;
}
