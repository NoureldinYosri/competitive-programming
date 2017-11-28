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

int n;
string name[10],str;

struct team{
	int first,second;
	int attacker,defender;
public:
	team(){

	}
	team(int a,int b){
		first = attacker = a;
		second = defender = b;
	}
	void do_switch(){
		swap(attacker,defender);
	}
	pi get_name(){
		return mp(first,second);
	}
	void put(int x){
		if(second == defender) {
			second = x;
		}
		else {
			first = x;
			swap(first,second);
		}
		defender = x;
		swap(attacker,defender);
	}
};

ostream & operator << (ostream & st,const team & t){
	st << "(" << name[t.attacker] << " ," << name[t.defender] << ")";
	return st;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	while(cin >> n){
		loop(i,n) cin >> name[i];
		cin >> str;
		team white = team(0,2),black = team(1,3);
		queue<int> q;
		for(int i = 4;i < n;i++) q.push(i);
		map<int,set<pair<int,pi> > > M;
		int ti = 0,cnt = 0;
		pi lst = mp(-1,-1);
		for(char & c: str){
			if(c == 'W') {
				if(lst == white.get_name()) cnt++;
				else {
					if(lst != mp(-1,-1)) M[cnt].insert(mp(ti++,lst));
					lst = white.get_name();
					cnt = 1;
				}
			}
			else {
				if(lst == black.get_name()) cnt++;
				else {
					if(lst != mp(-1,-1)) M[cnt].insert(mp(ti++,lst));
					lst = black.get_name();
					cnt = 1;
				}
			}
			if(c == 'W') {
				white.do_switch();
				q.push(black.defender);
				black.put(q.front());
				q.pop();
			}
			else {
				black.do_switch();
				q.push(white.defender);
				white.put(q.front());
				q.pop();
			}
		//	cerr << white << " " << black << " " << name[q.front()] << endl;
		}
		M[cnt].insert(mp(ti++,lst));
//		cerr << (M.rbegin()->xx) << endl;
		for(auto p : M.rbegin()->yy){
			int x = p.yy.xx,y = p.yy.yy;
			printf("%s %s\n",name[x].c_str(),name[y].c_str());
		}
//		break;
	}

	return 0;
}
