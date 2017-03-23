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

int n;
string P[100],C[100];
char key[101];
char buffer[101];
int diff[101][101];
int LEN[101];

string cipher(string & in,int len){
	string out;
	for(int i = 0,L = in.size();i < L;i++){
		int x = in[i],y;
		if(i < len) y = key[i];
		else y = out[i - len];
		out.pb(char((x + y)%26 + 'A'));
	}
	return out;
}

bool valid(int len){
	key[len] = 0;
	loop(i,n) if(cipher(P[i],len) != C[i]) return 0;
	return 1; 
}

bool solve(){
	loop(i,n) LEN[i] = P[i].size();
	loop(i,n){
		int len = LEN[i];
		loop(j,len){
			int x = P[i][j],y = C[i][j];
			int d = y - x;
			if(d < 0) d += 26;
			diff[i][j] = d;
		}
	}
	int p = 0;
	for(int j = 1;j <= 100;j++) {
		int eq = 1,target = -1;
		loop(i,n) {
			if(LEN[i] < j) continue;
			target = diff[i][j - 1];
		}
		if(target == -1) break;
		key[j - 1] = target + 'A';
		loop(i,n){
			if(LEN[i] < j) continue;
			eq &= diff[i][j - 1] == target;
		}
		if(eq) p = j;
		else break;
	}
	if(!p) return 0;
	string ret = "";
	for(int i = p;i >= 1;i--) if(valid(i)) ret = string(key);
	strcpy(key,ret.c_str());
	return !ret.empty();
}

int main(){
	while(scanf("%d",&n) == 1 && n){
		loop(i,n) {
			scanf("%s",buffer); P[i] = string(buffer);
			scanf("%s",buffer); C[i] = string(buffer);
		}
		if(solve()) puts(key);
		else puts("Impossible");
	}	
	
	return 0;
}
