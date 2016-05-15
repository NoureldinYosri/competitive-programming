#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define vi vector<int>
#define ll long long
#define pi pair<int,int>
#define point pair<double,double>
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cout << #A << ": "; copy(all(A),ostream_iterator<t>(cout," " )); cout << endl
#define prp(p) cout << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cout << #A << ": "; copy(A,A + n,ostream_iterator<t>(cout," " )); cout << endl
#define pre() cin.tie(0),cout.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

string i2s(int x){
	char s[20];
	sprintf(s,"%d",x);
	return string(s);
}


int main(){
	int n,m;
	for(int t = 0;scanf("%d %d",&m,&n) == 2 && n;t++){
		if(t) cout << endl;
		
		string M = i2s(m),N = i2s(n),Z = i2s(m/n);
		auto z = Z.begin(); 
		int p = 0,mm = 0,offset = len(N) + 4;
		while(p < len(M) && (mm < n || (mm%n == 0 && M[p] == '0'))) mm = mm * 10 + M[p++] - '0';
		
		string out = i2s(m/n) + " r " + i2s(m%n);
		out = string(len(N) + 2 + p + 1,' ') + out; 
		cout << out << endl;
		
		out = "+" + string(len(M) + 1,'-'); 
		out = string(len(N) + 2,' ') + out;
		cout << out << endl;
		
		out = " " + N + " | " + M;
		cout << out << endl;
		offset += p;
		while(mm >= n) {
			int x = mm - mm%n; 
			out = i2s(x);
			int L = offset - len(out);
			
			out = string(L,' ') + out;
			cout << out << endl;
		
			cout << string(L,' ') + string(len(out) - L,'-') << endl;			
			
			mm %= n;
			out = string(offset  - len(i2s(mm)),' ') + i2s(mm);
			if(p < len(M)) out += M.substr(p);
			for(auto & c : out){
				if(c == ' ') continue;
				if(c == '0') {
					c = ' ';
					continue;
				}
				break;
			}
			if(out == string(len(out),' ')) out.back() = '0';
			cout << out << endl; 
			
			while (p < len(M) && (mm < n || (mm%n == 0 && M[p] == '0'))) {
				mm = mm * 10 + M[p] - '0';
				p++;
				offset++;
			}
		};
	}
	return 0;
}
