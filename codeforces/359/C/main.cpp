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

int n,m,ln,lm;


void get_lg(int q,int & l){
	l = 0;
	while(q){
		l++;
		q /= 7;
	}	
	l = max(l,1);
}

string i2q(ll a,int l){
	string s = a ? "" : "0";
	while(a){
		s = char(a%7 + '0') + s;
		a /= 7;
	}
	while(sz(s) < l) s = "0" + s;
	return s;
}

bool are_dist(ll a,ll b){
	string A = i2q(a,ln),B = i2q(b,lm);
	set<char> S;
	for(auto c : A){
		if(S.find(c) != S.end()) return 0;
		S.insert(c);
	}
	for(auto c : B){
		if(S.find(c) != S.end()) return 0;
		S.insert(c);
	}
	return 1;
}

int gen(){
	int ctr = 0;
	loop(i,n) loop(j,m) ctr += are_dist(i,j);
	
	return ctr;
}


int main(){
	cin >> n >> m;
	get_lg(n - 1,ln);
	get_lg(m - 1,lm);
	if(ln + lm > 7){
		cout << "0" << endl;
		return 0;
	}
	cout << gen() << endl;
	return 0;
}
