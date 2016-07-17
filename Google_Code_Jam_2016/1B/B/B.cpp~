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

int T;
char A[20],B[20];
string best_A,best_B;
int L;
ll p10[18];
int AAA[20],BBB[20];

void init(char *Z,ll & X){
	X = 0;
	loop(i,L){
		X *= 10;
		if(Z[i] == '?') X += 9;
		else X += Z[i] - '0';
	}
}

void solve(){
	ll X = 0,Y = 0;
	L = strlen(A);
	init(A,X);
	init(B,Y);
	loop(i,L){
		if(AAA[i] && BBB[i]){
			int c1 = (A[i] == '?') ? 9 : (A[i] - '0'),
				c2 = (B[i] == '?') ? 9 : (B[i] - '0');			
			loop(j,10) loop(k,10){
				ll nX = X - c1 * p10[L - i - 1] + j*p10[L - i - 1];
				ll nY = Y - c2 * p10[L - i - 1] + k*p10[L - i - 1];
				if(abs(nX - nY) < abs(X - Y)){
					c1 = j,c2 = k;
					X = nX,Y = nY;
				}
				else if(abs(nX - nY) == abs(X - Y) && nX < X){
					c1 = j,c2 = k;
					X = nX,Y = nY;
				}
				else if(abs(nX - nY) == abs(X - Y) && nX == X && nY < Y){
					c1 = j,c2 = k;
					X = nX,Y = nY;
				}
			}
			A[i] = c1 + '0';
			B[i] = c2 + '0';
		}
		else if(AAA[i]){
			int c = (A[i] == '?') ? 9 : (A[i] - '0');			
			loop(j,10){
				ll nX = X - c * p10[L - i - 1] + j*p10[L - i - 1];
				if(abs(nX - Y) < abs(X - Y)) {
					c = j;
					X = nX;
				}
				else if(abs(nX - Y) == abs(X - Y) && nX < X){
					c = j;
					X = nX;
				}
			}
			A[i] = c + '0';
		}
		else if(BBB[i]){
			int c = (B[i] == '?') ? 9 : (B[i] - '0'); 
			loop(j,10){
				ll nY = Y - c * p10[L - i - 1] + j*p10[L - i - 1];
				if(abs(X - nY) < abs(X - Y)) {
					c = j;
					Y = nY;
				}
				else if(abs(X - nY) == abs(X - Y) && nY < Y){
					c = j;
					Y = nY;
				}
			}
			B[i] = c + '0';			
		}
	}
	best_A = string(A);
	best_B = string(B);	
}

int main(){	
	p10[0] = 1;
	loop(i,17) p10[i + 1] = p10[i] * 10;
	scanf("%d",&T); 
	loop(t,T){
		scanf("%s %s",A,B);
		L = strlen(A);
		fill(AAA,AAA + L,0);
		fill(BBB,BBB + L,0);
		loop(i,L) AAA[i] = A[i] == '?';
		loop(i,L) BBB[i] = B[i] == '?';
		solve();
		printf("Case #%d: %s %s\n",t + 1,best_A.c_str(),best_B.c_str());
	}	
	return 0;
}
