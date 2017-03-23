#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
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

const int MAX = 100'000 + 10;
int L[MAX],R[MAX],A[MAX],n;
int LD[MAX],RD[MAX];

int dist(int x,int y){
	if(x < y) return y - x;
	else return n - (x - y);
}

void work1(int *keep,int *who){
	vi ST;
	loop(i,n){
		while(!ST.empty() && A[ST.back()] >= A[i]) ST.pop_back();
		ST.pb(i);
	}
	loop(i,n){		
		while(!ST.empty() && A[ST.back()] >= A[i]) ST.pop_back();
		if(!ST.empty()){
			keep[i] = dist(ST.back(),i);
			who[i] = ST.back();
		}
		else keep[i] = MAX;
		ST.pb(i);
	}
}
void work2(int *keep,int *who){
	vi ST;
	for(int i = n - 1;i >= 0;i--){
		while(!ST.empty() && A[ST.back()] >= A[i]) ST.pop_back();
		ST.pb(i);
	}
	for(int i = n - 1;i >= 0;i--){		
		while(!ST.empty() && A[ST.back()] >= A[i]) ST.pop_back();
		if(!ST.empty()){
			keep[i] = dist(i,ST.back());
			who[i] = ST.back();
		}
		else keep[i] = MAX;
		ST.pb(i);
	}
}

int main(){
	scanf("%d",&n);
	loop(i,n) scanf("%d",A + i);
	work1(LD,L);
	work2(RD,R);
	int mn = INT_MAX,a,b,c;
	loop(i,n) if(mn > LD[i] + RD[i]) {
		mn = LD[i] + RD[i];
		a = L[i] + 1;
		b = i + 1;
		c = R[i] + 1;
	} 
	cerr << a << " " << b << " " << c << endl;
	cout << a << " " << b << " " << c << endl;
	return 0;
}
