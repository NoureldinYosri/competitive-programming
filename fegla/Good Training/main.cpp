#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcountll(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
using namespace std;

string names[10*1000 + 10];
int N;
char buffer[1 << 20];

bool is_student(string & s){
	for(char c : s)
		if(islower(c))
			return 1;
	return 0;
}

string trim(){
	int s = 0,e = strlen(buffer);
	while(s < e && (buffer[s] == ' ' || buffer[s] == '\n')) s++;
	while(s < e && (buffer[e-1] == ' ' || buffer[e-1] == '\n')) e--;
	buffer[e] = 0;
	return string(buffer + s);
}

int main(){
	freopen("coaches.in", "r", stdin);
	int T;
	fgets(buffer,1 << 20,stdin);
	sscanf(buffer,"%d",&T);
	while(T--){
		scanf("%d",&N);
		map<string,int> MAP;
		fgets(buffer,1 << 20,stdin);
		sscanf(buffer,"%d",&N);
		int id = 1;
		loop(i,N) {
			fgets(buffer,1 << 20,stdin);
			names[i] = trim();
			if(is_student(names[i])) {
				if(!MAP[names[i]] || MAP[names[i]] == id) MAP[names[i]] = id;
				else MAP[names[i]] = -1;
			}
			else id++;
		}
		vector<pair<int,string> > V;
		for(int i = 0;i < N;) {
			int j = i + 1,ctr = 0;
			while(j < N && is_student(names[j])) {
				ctr += MAP[names[j]] != -1;
				j++;
			}
			V.pb(mp(-ctr,names[i]));
			i = j;
		}
		sort(all(V));
		for(auto p : V) printf("%s %d\n",p.yy.c_str(),-p.xx);
	}
	return 0;
}
