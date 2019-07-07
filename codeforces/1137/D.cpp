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

string groups [] = {"01","1","23456789","0123456789"};
int ctr[3];
int pos[10];


int Next(string s) {
	cout << "next";
	for(char c : s) cout << " " << c;
	cout << endl;

	int k; cin >> k;
	loop(i,k) {
		cin >> s;
		for(char c : s) pos[c - '0'] = i;
	}
	return k;
}




int main(int argc,char **argv){
	int heir = 0,tortoise = 0;

	int k = 0;
	do{
		tortoise ++;
		Next("01");
		k = Next("1");
		heir += 2;
	}while(pos[0] != pos[1]);


	while(k != 1)
		k = Next("0123456789");
	cout << "done" << endl;

	return 0;
}
