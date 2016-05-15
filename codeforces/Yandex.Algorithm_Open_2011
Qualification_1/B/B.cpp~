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
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define pre() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

char line[300]; int L;

int main(){
	fgets(line,300,stdin);	
	L = strlen(line);
	line[--L] = '\0';
	bool c = 0;
	string out = "";
	loop(i,L){
		if(line[i] == ' ') continue;
		else if(line[i] == ',') {
			out += ", ";
			c = 1;
		}
		else if(line[i] == '.'){
			if(i){
				if(!c) out += " ";
				else c = 0;
			}
			out += "...";
			i += 2;
			c = 0;
			continue;
		}
		else {
			out += line[i];
			int j = i;
			for(j = i + 1;j < L && line[j] == ' ';j++);
			if('0' <= line[j] && line[j] <= '9' && j - i > 1) out += ' ';
			i = j - 1;
			c = 0;
		}
	}
	while(out.back() == ' ') out.pop_back();
	cout << out << endl;
	return 0;
}
