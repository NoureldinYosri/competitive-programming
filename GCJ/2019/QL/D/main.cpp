#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
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
using namespace std;

struct seq{
	int real_s,real_e;
	int res_s,res_e;
	int B;
public:
	seq(){memset(this,0,sizeof *this);}
	seq(int reals,int reale,int ress,int c) {
		real_s = reals;
		real_e = reale;
		res_s = ress;
		res_e = ress + c - 1;
		B = (real_e - real_s + 1) - c;
	}
	int getLen() const {
		return real_e - real_s + 1;
	}
	int getRLen() const {
		return res_e - res_s + 1;
	}
	int getMid() const {
		return real_s + getLen()/2;
	}
};

string res;
vector<seq> R,aux;
int N,B,F;




void ask(){
	string Q = string(N,'0');
	for(const seq & s : R) {
		if(s.B == 0) continue;
		if(s.getLen() <= B+1) {
			int m = s.getMid();
			for(int i = m;i <= s.real_e;i++)
				Q[i] = '1';
		}
		else {
			int L = s.getLen();
			int m = (L + B)/(B+1);
			for(int i = 0;i < m;i++) {
				int S = s.real_s + i*(B+1),E = min(s.real_e+1,S + B + 1);
				for(int j = S;j < E;j++)
					Q[j] = '0' + (i&1);
			}
		}
	}
	cout << Q << endl;
	flush(cout);
}

ostream& operator << (ostream & st,const seq & s) {
	st << "[(" << s.real_s << ", " << s.real_e << "), ";
	st << "(" << s.res_s << ", " << s.res_e << "), ";
	st << s.B << "]";
	return st;
}

void split(seq s,vector<seq> & V) {
	if(s.getLen() <= B+1) {
		int m = s.getMid();
		int c = 0;
		for(int i = s.res_s;i <= s.res_e;i++)
			c += res[i] == '0';
		V.push_back(seq(s.real_s,m-1,s.res_s,c));
		V.push_back(seq(m,s.real_e,s.res_s+c,s.res_e-s.res_s+1-c));
		return;
	}
	int m = (s.getLen() + B)/(B+1);
	static vi cnts;
	cnts.clear();
	for(int i = s.res_s;i <= s.res_e;){
		int j = i;
		while(j <= s.res_e && res[i] == res[j]) j++;
		cnts.push_back(j-i);
		i = j;
	}
//	cerr << "ceil " << s.getLen() << " / " << B+1 << " = " <<  m << ": " ;
//	print(cnts,int);
	assert(sz(cnts) == m || sz(cnts) == m-1);
	if(sz(cnts) == m-1) cnts.push_back(0);
//	cerr << s << " -> ";
	for(int i = 0,r = s.res_s;i < m;i++) {
		int S = s.real_s + i*(B+1);
		int E = min(S+B,s.real_e);
		V.push_back(seq(S,E,r,cnts[i]));
		r += cnts[i];
//		cerr << V.back() << " ";
	}
//	cerr << endl;

}

void read(){
	cin >> res;
	if(res == "-1") exit(0);
}

seq I(){
	seq r;
	r.res_s = 0;
	r.res_e = N-B-1;
	r.real_s = 0;
	r.real_e = N-1;
	r.B = B;
	return r;
}


int main(int argc,char **argv){
	int T; cin >> T;
	for(int t = 1;t <= T;t++) {
		cin >> N >> B >> F;
		R.clear();
		R.push_back(I());
		bool done = 0;
		while(F >= 0){
			F--;
			done = 1;
			aux.clear();
			for(const seq & s : R) {
				assert(s.B == s.getLen() - s.getRLen());
				if(s.B == 0) continue;
				if(s.res_e-s.res_s+1 == 0) continue;
				done = 0;
			}
			if(done) break;
			ask();
			read();
			for(const seq & s : R) {
				bool do_split = 1;
				if(s.B == 0) do_split = 0;
				if(s.res_e-s.res_s+1 == 0) do_split = 0;

				if(do_split) split(s,aux);
				else aux.push_back(s);
			}
			R.swap(aux);
//			for(seq s : R)
//				cerr << s << " ";
//			cerr << endl;
		}
//		assert(F >= 0);
//		cerr << "found ans" << endl;
		bool f = 1;
		for(const seq & s : R){
			if(s.B == 0) continue;
			if(s.getLen() != s.B) cerr << s << endl;
			assert(s.getLen() == s.B);
			for(int j = s.real_s;j <= s.real_e;j++){
				if(!f) cout << " ";
				f = 0;
				cout << j ;
			}
		}
		cout << endl;
		flush(cout);
		read();
	}
	return 0;
}
