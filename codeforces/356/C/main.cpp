#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0,_ = (n);i < _;i++)
#define range(i,a,b) for(int i = (a),_ = (b);i <= _;i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b),_ = (a);i >= _;i--)
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


vi P{2,3,5,7,11,13,17,19,23,29,31,37,41,43,47};

int main(){
	string res;
	int ctr = 0,v;
	loop(i,sz(P)){
		cout << P[i] << endl;
		cin >> res;
		if(res == "yes"){
			++ctr;
			v = P[i];
			if(ctr == 2) {
				cout << "composite" << endl;
				return 0;
			}
		}
	}
	if(ctr){
		if(v > 10){
			cout << "prime" << endl;
			return 0;
		}		
		cout << v*v << endl;
		cin >> res;
		if(res == "yes") cout << "composite" << endl;
		else cout << "prime" << endl;
	}
	else cout << "prime" << endl;
	return 0;
}
