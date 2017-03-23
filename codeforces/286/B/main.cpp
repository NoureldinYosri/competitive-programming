#pragma GCC optimize("O3")
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
#define popcnt(x) __builtin_popcountll(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

const int MAX = 1000*1000 + 10;
int n,blkSize;


int A[MAX << 1];



int main(){
	scanf("%d",&n) ;

	for(int i = 0;i < n;i++) A[i] = i+1;
	int st = 0;
	//prArr(A + st,n,int);
	for(int k = 2;k <= n;k++){
		A[st + n] = A[st++];
		int val = -1,vise = 0;
		for(int e = k - 1;e < n;e += k)
			swap(A[st + e],val),vise = e == n-1;
		if(!vise) swap(A[st + n - 1],val);
		swap(A[st + k - 1],val);
		//prArr(A + st,n,int);
	}	
	loop(i,n) printf("%d%c",A[st + i]," \n"[i==n-1]);
	return 0;
}
