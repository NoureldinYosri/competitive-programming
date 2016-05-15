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
#define print(A,t) cout << #A << ": "; copy(all(A),ostream_iterator<t>(cout," " )); //cout << endl
#define pi pair<int,int>
#define point pi
#define vi vector<int>
#define ll long long
#define pl pair<ll,ll>
#define pre() cin.tie(0),cout.tie(0),ios_base::sync_with_stdio(0)
#define popcnt(x) __builtin_popcount(x)
using namespace std;

int A[100],B[100];
int P[100];
double D[100];

bool cmp(const int & a,const int & b){
	return D[a] > D[b];
}

#define f(x) (y*A[x] - P[x]*m)

int main(){
	pre();
	int n,m,y,ctr = 0;
	cin >> n >> m >> y;
	loop(i,n) cin >> P[i],A[i] = m * P[i]/y,ctr += A[i],D[i] = abs(P[i]*1.0/y - (A[i] + 1)*1.0/m),B[i] = i;
	sort(B,B + n);
	loop(i,m - ctr) A[B[i]]++;
	loop(i,n) cout << (i ? " " : "") << A[i];
	cout << endl;
	return 0;
}
