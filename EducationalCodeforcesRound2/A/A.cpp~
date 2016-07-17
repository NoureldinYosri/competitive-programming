#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define print(A,t) cout << #A << ": "; copy(all(A),ostream_iterator<t>(cout," " )); cout << endl
#define pi pair<int,int>
#define point pi
#define vi vector<int>
#define ll long long
#define pl pair<ll,ll>
#define pre() cin.tie(0),cout.tie(0),ios_base::sync_with_stdio(0)
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define prp(p) cout << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cout << #A << ": "; copy(A,A + n,ostream_iterator<t>(cout," " )); cout << endl
using namespace std;

int main(){
	string s,u,v;
	cin >> s;
	u = v = "";
	bool z = 0;
	for(int i = 0;i < len(s);){
		int j = i;
		while(j < len(s) && s[j] != ';' && s[j] != ',') j++;
		if(i == j) z = 1;
		else {
			bool c = 1;
			for(int k = i;k < j;k++)
				c &= s[k] <= '9' && s[k] <= '9';
	//		cerr << s.substr(i,j - i) << " " << z << endl;
			if(c) c = (s[i] == '0') ? (j - i == 1) : 1;
			if(c) u = u  + (u.empty() ? "" : ",") +  s.substr(i,j - i) ;
			else {
				v = v + (z ? "," : "") + s.substr(i,j - i);
				z = 1;
			}
		}
		i = j + 1;
	}
	if(s.back() == ';' || s.back() == ',') v += ",";
	if(u.empty()) u = "-";
	else u = "\"" + u + "\"";
	if(v.empty()) v = "-";
	else v = "\"" + v + "\"";
	cout << u << "\n" << v << endl;
	return 0;
}
