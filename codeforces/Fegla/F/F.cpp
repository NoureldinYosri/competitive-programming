#include <bits/stdc++.h>
#define print(v) cout << "(" << v.first << " ," << v.second << ")";
#define sgn(a) ((a > 0) - (a < 0))
using namespace std;

struct state{
	int pos,vel,dir;
public:
	state(){}
	state(int a,int b,int c):pos(a),vel(b),dir(c){}
	bool operator != (const state & o){
		return !(pos == o.pos && vel == o.vel && dir == o.dir);
	}
};

const int offset = 2e5;
state P[1 << 20][20][2];

void insert(state st,state p,queue<state> & q){
	if(st.pos < 0 || st.pos  >= (1 << 20)) return;
	if(st.vel >= 20) return;
	if(P[st.pos ][st.vel][st.dir].pos != 0) return;
	P[st.pos ][st.vel][st.dir] = p;
	q.push(st);
}

int main(){	
	int x;
	cin >> x;
	queue<state> q;
	q.push(state(x + offset,0,0));
	P[x + offset][0][0] = state(x + offset,0,0);	
	state st, t;
	for(;!q.empty();){
		st = q.front(); q.pop();
                if(st.pos == offset) break;
		t = st;
		t.pos -= (1 << t.vel)*(-2*t.dir + 1);
		t.vel ++;
		insert(t,st,q);
		t = st;
		t.vel = 0;
		t.dir = 1 - t.dir;
		insert(t,st,q);
	}
	string path = "";
	while(P[st.pos][st.vel][st.dir] != st){
		t = P[st.pos][st.vel][st.dir];
		if(st.vel != t.vel + 1) path += "R";
		else path += "A";
		st = t;
	}
	//print(t1); cout << "\n";
	reverse(path.begin(),path.end());
	cout << path.length() << "\n" << path << "\n";
	return 0;
}

