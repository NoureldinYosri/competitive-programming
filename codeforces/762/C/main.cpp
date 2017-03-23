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

char P[1<<20],T[1<<20];
int f[1<<20];
int n,m;

void preprocess(){
	int i = n-1,j = m-1;
	for(;j >= 0;j--){
		while(i >= 0 && P[i] != T[j]) i--;
		f[j] = i;
		i--;
		
	}
	f[m] = n;
}

bool valid(int len,int & i){
	int s = 0;
	for(i = 0;i < m - len + 1;i++) {
		//cerr << i << " " << i + len << " " << f[i + len] << " " << s << endl;
		if(f[i + len] >= s) return 1;
		while(s < n && P[s] != T[i]) s++;
		if(s == n) return 0;
		s++;
	}
	return 0;
}

int main(){
	scanf("%s %s",P,T);
	n = strlen(P);
	m = strlen(T);
	preprocess();
	//prArr(f,m,int);
	if(f[0] >= 0){
		puts(T);
		return 0;
	}
	int s = 1,e = m,i;
	while(s < e){
		int mid = (s + e) >> 1;
		if(valid(mid,i)) e = mid;
		else s = mid + 1;
	}
	if(s == m) puts("-");
	else {
		valid(s,i);
		loop(j,i) putchar(T[j]);
		i += s;
		while(i < m) putchar(T[i++]);
		puts("");
	}
	return 0;
}
