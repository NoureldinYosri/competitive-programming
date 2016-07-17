#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define vi vector<int>
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
#define pre() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

char line[50],aux[50];

void convert(int n,int offset){
	int L = 0;
	while(n){
		aux[L++] = (n & 1) + '0';
		n >>= 1;
	}
	loop(i,8 - L) line[offset++] = '0';
	L--;
	while(L >= 0) line[offset++] = aux[L--];
}

void PRINT(int s,int e){
	int v = 0;
	while(s < e){
		v = (v << 1) + line[s] - '0';
		s ++;
	}
	if(v < 100) putchar('0');
	if(v < 10) putchar('0');
	printf("%d",v);
}

int main(){
	int T,a;
	scanf("%d",&T);
	while(T--){
		scanf("%d",&a); convert(a,0);
		scanf("%d",&a); convert(a,8);
		scanf("%d",&a); convert(a,16);
		int s = 0,e = 23;
		while(s < e){
			if(line[s] != line[e])line[s] = line[e] = '0';
			s ++,e--;
		}
		PRINT(0,8); putchar(' ');
		PRINT(8,16); putchar(' ');
		PRINT(16,24); putchar('\n');
	}
	return 0;
}
