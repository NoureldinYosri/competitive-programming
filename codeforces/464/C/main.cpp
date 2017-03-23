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

const int MAX = 1e5 + 1e2,mod = 1e9 + 7;
char num[MAX],buffer[MAX];
string Q[MAX];
int n;
int f[10],len[10];

int add(int x,int y){
	x += y;
	if(x >= mod) x -= mod;
	return x;
}

int mul(int x,int y){
	return (x*1LL*y)%mod;
}

int POW(int x,int p){
	if(!p) return 1;
	int y = 1;
	for(;p > 1;p >>= 1){
		if(p & 1) y = mul(x,y);
		x = mul(x,x);
	}
	return mul(x,y);
}

int main(){
	loop(i,10) f[i] = i,len[i] = 1;
	scanf("%s %d",num,&n);
	loop(i,n) {
		scanf("%s",buffer);
		Q[i] = string(buffer);
	}
	for(int i = n-1;i >= 0;i--){
		int d = Q[i][0] - '0';
		strcpy(buffer,Q[i].c_str() + 3);
		int tmp = 0,sum = 0;
		for(int j = 0,L = strlen(buffer);j < L;j++){
			int c = buffer[j] - '0';			
			tmp = mul(tmp,POW(10,len[c]));
			tmp = add(tmp,f[c]);
			sum += len[c];
			if(sum >= mod - 1) sum -= mod - 1;
		}
		len[d] = sum;
		f[d] = tmp;			
	}
	int ans = 0;	
	for(int j = 0,L = strlen(num);j < L;j++){
		int c = num[j] - '0';			
		ans = mul(ans,POW(10,len[c]));
		ans = add(ans,f[c]);
	}
	cout << ans << endl;
	return 0;
}
