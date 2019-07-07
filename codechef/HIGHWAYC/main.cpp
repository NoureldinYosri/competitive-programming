#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define popcnt(x) __builtin_popcountll(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
using namespace std;

typedef __int128 bigint;
const int MAX = 10;
int N,S,Y;
int V [MAX],D[MAX],P[MAX],C[MAX];

bigint gcd(bigint a,bigint b) {
	a *= (a < 0) ? -1 : 1;
	b *= (b < 0) ? -1 : 1;
	if(a == 0 && b == 0) return 1;

	while(b){
		a %= b;
		swap(a,b);
	}
	return a;
}


ostream& operator << (ostream & st,bigint v) {
	int mod = 1000000000;
	int r = v%mod;
	if(v >= mod)
		st << (v/mod);
	st << r ;
	return st;
}


struct Ratio{
	bigint x,y;
	Ratio(){
		x = 0;
		y = 1;
	}
	Ratio(bigint a,bigint b) {
		bigint g = gcd(a,b);
		x = a/g;
		y = b/g;
	}
	Ratio operator + (Ratio o) {
		return Ratio(x*o.y + y*o.x,y*o.y);
	}
	Ratio operator - (Ratio o) {
		return Ratio(x*o.y - y*o.x,y*o.y);
	}
	Ratio operator * (Ratio o) {
		return Ratio(x*o.x,y*o.y);
	}
	double doubleValue(){
		return x*1.0/y;
	}
	bool operator < (const Ratio & o) const {
		return x*o.y - y*o.x < 0;
	}
	bool operator <= (const Ratio & o) const {
		return x*o.y - y*o.x <= 0;
	}
	friend ostream & operator << (ostream & st,const Ratio r) {
		st << r.x << "/" << r.y ;
		return st;
	}
};

bigint abs(bigint x) {
	if(x < 0) return -x;
	return x;
}

bool intersect(Ratio s,Ratio e,Ratio l,Ratio r) {
	if(l < s) {
		swap(l,s);
		swap(e,r);
	}
	return l <= e;
}

Ratio work_up(int s,int e,int v,Ratio ct,Ratio cross_time) {
	if(0 < s) return ct + cross_time;
	if(e > 0) e = 0;
	Ratio S (-e,v),E (-s,v);

	Ratio T = ct + cross_time;
	if(intersect(S,E,ct,T)) return E + cross_time;
	return T;
}


Ratio work_down(int s,int e,int v,Ratio ct,Ratio cross_time) {
	if(e < 0) return ct + cross_time;
	if(s < 0) s = 0;
	Ratio S (s,v),E (e,v);
	Ratio T = ct + cross_time;
	if(intersect(S,E,ct,T)) return E + cross_time;
	return T;
}


int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
    int T ; scanf("%d",&T);
    for (int t = 1;t <= T;t++) {
    	scanf("%d %d %d",&N,&S,&Y);
        for (int i = 0;i < N;i++)
        	scanf("%d",V + i);
        for (int i = 0;i < N;i++)
        	scanf("%d",D + i);
        for (int i = 0;i < N;i++)
        	scanf("%d",P + i);
        for (int i = 0;i < N;i++)
        	scanf("%d",C + i);

        Ratio ct = Ratio(0,1);
        Ratio cross_time = Ratio(Y,S);
        for (int i = 0;i < N;i++) {
            if (D[i] == 1)
            	ct = work_up(P[i]-C[i],P[i],V[i],ct,cross_time);
            else
            	ct = work_down(P[i],P[i]+C[i],V[i],ct,cross_time);
        }
        printf("%.10f\n",ct.doubleValue());
    }

	return 0;
}
