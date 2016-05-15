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

#define MAX 1000010
char pat[MAX];
char text[MAX];
int pre[MAX];
vector<int> res;
int getlen(int l, char c) {
	while (l && pat[l] != c)
		l = pre[l - 1];
	if (pat[l] == c)
	l++;
	return l;
}
void compute_pre() {
	pre[0] = 0;
	int l = 0;	
	if (pat[0])
		for (int i = 1; pat[i]; ++i) {
			l = getlen(l, pat[i]);
			pre[i] = l;
		}
}
bool match() {
	compute_pre();
	res.clear();
	int l = 0;
	for (int i = 0; text[i]; ++i) {
		l = getlen(l, text[i]);
		if (!pat[l]) {
			return 1;
			l = pre[l - 1]; //l=0 if no overlap is allowed
		}
	}
	return 0;
}

bool is_pal(int i,int j,string & z){
	int s = i,e = j;
	while(s < e)
		if(z[s++] != z[e--])
			return 0;
	return 1;
}

int main(){
	string s,out;
	cin >> s >> text;
	for(int i = 0;i < len(s);i++)
		for(int j = i;j < len(s);j++){
			for(int k = 0;k < (j - i + 1);k++) pat[k] = s[i + k];
			pat[j - i + 1] = '\0';
			if(is_pal(i,j,s) && match() && (j - i + 1) > (int)len(out)) out = string(pat);
		}
	cout << out << endl;
	return 0;
}
