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

string V[50];
int n,k;
string name[50];
int to[50];

void generate(){
	int ctr = 0;
	for(char a = 'A';a <= 'Z' && ctr < 50;a++)
		for(char b = 'a';b <= 'z' && ctr < 50;b++){
			char aux[3] = {0};
			aux[0] = a;
			aux[1] = b;
			name[ctr++] = string(aux);
		}
}

int main(){
	generate();
	memset(to,-1,sizeof to);
	scanf("%d %d",&n,&k);
	loop(i,n - k + 1) cin >> V[i];
	int s = 0,e = k - 1,cur = 0;
	loop(i,n - k + 1){
		if(to[s] == -1) to[s] = cur++;
		if(V[i] == "YES") to[e] = cur++;
		else to[e] = to[s];
		s++,e++;
	}
	loop(i,n) if(to[i] == -1) to[i] = cur++;
	assert(cur <= 50);
	loop(i,n) printf("%s%c",name[to[i]].c_str()," \n"[i == n-1]);
	//loop(i,n) cerr << name[to[i]] << endl;
	
	return 0;
}
