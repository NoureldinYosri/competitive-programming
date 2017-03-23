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

const int MAX = (100*1000 + 10)*2,mod = 1e9 + 7;
int F[MAX],r[MAX],f,w,h;

int mul(int x,int y){
	return (x*1LL*y)%mod;
}
int add(int x,int y){
	x += y;
	if(x >= mod) x -= mod;
	return x;
}

int pow_mod(int x,int p){
	if(!p) return 1;
	int y = 1;
	for(;p > 1;p >>= 1){
		if(p & 1) y = mul(x,y);
		x = mul(x,x);
	}
	return mul(x,y);
}

void pre(){
	F[0] = r[0] = 1;
	loop(i,MAX - 1){
		F[i + 1] = mul(F[i],i + 1);
//		r[i + 1] = pow_mod(F[i + 1],mod - 2);
	}
}

void C(int n,int k,int & x,int & y){
	if(k > n){
		x = 0;
		y = 1;
		return;
	}
	x = F[n];
	y = mul(F[k],F[n - k]);
}

void get(int money,int len,int mn,int & x,int & y){
	if(money < mn*1LL*len) {
		x = 0,y = 1;
		return ;
	}
	money -= len * mn;
	C(money + len - 1,money,x,y);
}

int main(){
	pre();
	scanf("%d %d %d",&f,&w,&h);
	if(f && w){
		int x = 0,y = 1;
		loop(i,f+1){
			if(!i) continue;
			range(j,max(i-1,1),min(i+1,w)){
				// C(len + money - 1,money)
				// C(len + (money - len) - 1,money - len)
				// C(money - 1,money - len)
				int a,b; get(f,i,1,a,b);
				int c,d; get(w,j,1,c,d);
				a = mul(a,c);
				b = mul(b,d);
				if(i == j) a = add(a,a);
				x = add(mul(x,b),mul(y,a));
				y = mul(y,b);
			}
		}
		int X = 0,Y = 1;
		loop(i,f+1){
			if(!i) continue;
			range(j,max(i-1,1),min(i+1,w)){
				// C(len + money - 1,money)
				// C(len + (money - len) - 1,money - len)
				// C(money - 1,money - len)
				int a,b; get(f,i,1,a,b);
				int c,d; get(w,j,h + 1,c,d);
				a = mul(a,c);
				b = mul(b,d);
				if(i == j) a = add(a,a);
				X = add(mul(X,b),mul(Y,a));
				Y = mul(Y,b);
			}
		}
		X = mul(X,y);
		Y = mul(Y,x);
		Y = pow_mod(Y,mod - 2);
		X = mul(X,Y);
		cerr << X << endl;
		cout << X << endl;
	}
	else if(w) {
		int x = 0,y = 1,X = 0,Y = 1;
		range(j,1,w){
			int a,b; get(w,j,1,a,b);
			x = add(mul(x,b),mul(y,a));
			y = mul(y,b);		
		}
		range(j,1,w){
			int a,b; get(w,j,h + 1,a,b);
			X = add(mul(X,b),mul(Y,a));
			Y = mul(Y,b);		
		}
		X = mul(X,y);
		Y = mul(Y,x);
		Y = pow_mod(Y,mod - 2);
		X = mul(X,Y);
		cerr << X << endl;
		cout << X << endl;		
	}
	else puts("1");
	return 0;
}
