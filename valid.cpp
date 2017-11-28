#include "testlib.h"
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
#define popcnt(x) __builtin_popcount(x)
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


const int million = 1000*1000,billion = million*1000;
const int hundredthousand = million/10;




const char *create_message(string s,int line){
	s += " in line " + to_string(line);
	return s.c_str();
}


void readeofl(int & line){
	inf.readEoln();
	line++;
}

/*
n = inf.readInt(1,hundredthousand,create_message("n",line));
		inf.readSpace();
		k = inf.readInt(1,n,create_message("n",line));
		readeofl(line);
		ensuref(sz(s) == n,create_message("sz(s) vs n",line));
		*/


int main(int argc,char **argv){
	registerValidation(argc,argv);
	int line = 1;
	int T = inf.readInt(1,100,create_message("T",line));
	readeofl(line);
	for(int t = 1;t <= T;t++) {
		string s;
		string s = inf.readWord();
		for(char & c : s) ensuref(c == '0' || c == '1' || c == '?',create_message("illegal char",line));
		readeofl(line);
	}
	inf.readEof();
	return 0;
}

