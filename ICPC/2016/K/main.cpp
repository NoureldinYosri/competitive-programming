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

int n,A[100],B[100];

bool valid(int s,int e,int k){
	if(e < s) return 0;
	if(k == 1){
		if(s == e) return B[s] > 1;
		return 1;
	}
	if(s == e){
		if(B[s] >= 2*k){
			B[s] -= 2*k;
			return valid(s,e,k-1);
		}
		else return 0;
	}
	else {
		if(B[s] >= k && B[e] >= k){
			B[s] -= k;
			B[e] -= k;
			if(B[s] == 0) s++;
			if(B[e] == 0) e--;
			return valid(s,e,k-1);
		}
		else return 0;
	}
	return 1;
}

bool check(int k){
	copy(A,A + n,B);
	return valid(0,n-1,k);
}

int main(){
	int x = 0;
	scanf("%d",&n);
	loop(i,n) scanf("%d",A + i),x^= A[i] & 1;
	if(x) puts("no quotation");
	else{
		int k = 0;
		range(i,1,100) if(check(i)) k = i ;
		if(!k) puts("no quotation");
		else if(k == 1) {
			if(n == 1 && A[0] == 2) puts("1");
			else if(n == 2 && A[0] == 1 && A[1] == 1) puts("1");
			else puts("no quotation");
		}		
		else printf("%d\n",k);
		cerr << k << endl;	
	}
	return 0;
}
