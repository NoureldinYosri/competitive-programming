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
using namespace std;

char line[10000];



int main(){
	scanf("%s",line);
	int L = strlen(line);
	stack<int> S;
	loop(i,L){
		if(isalpha(line[i])){
			if(S.empty()) putchar(line[i]);
			else if(S.top()) putchar(toupper(line[i]));
			else putchar(tolower(line[i]));
		}
		else{
			if(line[i + 1] == '/') {
				S.pop();
				if(line[i + 2] == 'U') i += 4;
				else i += 6;
			}
			else {
				if(line[i + 1] == 'U') S.push(1),i += 3;
				else S.push(0),i += 5;
							
			}  
		}
	}
	puts("");
}
