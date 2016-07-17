#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define vi vector<int>
#define vl vector<long>
#define vd vector<double>
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

int T,x;


string i2b(int x){
	string ret = x ? "" : "0";
	for(;x;x >>= 1) ret = char((x & 1) + '0') + ret;
	while(sz(ret) < 8) ret = "0" + ret;
	return ret;
}

void make_pal(string & s){
	int i = 0,j = 23;
	for(;i < j;i++,j--){
		if(s[i] == s[j]) continue;
		s[i] = s[j] = '0';
	}
}

string b2i(const char *p){
	int x = 0;
	loop(i,8) x = (x << 1) + p[i] - '0';
	char tmp[8];
	sprintf(tmp,"%d",x);
	return string(tmp);
}

string complete(string ret){
	while(sz(ret) < 3) ret = "0" + ret;
	return ret;
}

int main(){
	freopen("balloons.in","r",stdin);
	cin >> T;
	while(T--){
		string s = "";
		cin >> x; s += i2b(x);
		cin >> x; s += i2b(x);
		cin >> x; s += i2b(x);
		make_pal(s);
		cout << complete(b2i(s.c_str())) << " " << complete(b2i(s.c_str() + 8)) << " " << complete(b2i(s.c_str() + 16)) << endl;	
	}
	return 0;
}