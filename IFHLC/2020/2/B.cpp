#pragma GCC optimize ("O3")
#include <cstdio>
#include <vector>
#include <algorithm>
using vi = std::vector<int>;
#define loop(i,n) for(int i = 0;i < (n);i++)

const int MAXK = 30 * 1000 * 1000;
int Y[MAXK+1];
int C[26][26];

void init(){
	int p = 2;
	for(int i = 3; i <= MAXK; i += 2){
		if(Y[i] == 0){
			Y[i] = p;
			p = i;
			for(long long j = p*(long long)p; j <= MAXK; j += (p << 1))
				Y[j] = p;
		} else {
			Y[i] = p;
		}
	}
	for(int n = 0; n < 26; n++){
		C[n][0] = C[n][n] = 1;
		for(int k = 1; k < n; k++){
			C[n][k] = C[n-1][k] + C[n-1][k-1];
		}
	}
}




int get(int ones, int X){
	if(X == 0) return 0;
//	printf("%d %d\n", X, ones);
	static vi V;
	V.clear();
	int m = 0;
	while(X) {
		m ++;
		V.push_back(X & 1);
		X >>= 1;
	}
	int ret = 0;
//	printf("%d\n", (int)V.size());
	while(!V.empty()){
		int d = V.back(); V.pop_back();
		if(d) {
//			printf("+ C[%lu][%d] = %d\n", V.size(), ones, C[V.size()][ones]);
			ret += C[V.size()][ones];
		}
		ones -= d;
		if(ones == 0) {
			ret++;
			break;
		}
	}
//	printf("ret %d\n", ret);
	return ret;
}



int readInt () {
	bool minus = false;
	int result = 0;
	char ch;
	ch = getchar();
	while (true) {
		if (ch == '-') break;
		if (ch >= '0' && ch <= '9') break;
		ch = getchar();
	}
	if (ch == '-') minus = true; else result = ch-'0';
	while (true) {
		ch = getchar();
		if (ch < '0' || ch > '9') break;
		result = result*10 + (ch - '0');
	}
	if (minus)
		return -result;
	else
		return result;
}


int main(){
	freopen("monster.in", "r", stdin);
#ifndef HOME
	freopen("monster.out", "w", stdout);
#endif
	init();
	int K = readInt(), n = readInt();
	loop(i, n){
		int a = readInt();
		if(a & 1){
//			cerr << a << " " << Y[a] << endl;
			K += Y[a] - 1;
			if(K > MAXK) K = MAXK;
		} else {
			int cnt = 0;
			while(a) {
				cnt += a & 1;
				a >>= 1;
			}
			K -= get(cnt, K);
		}
	}

	printf("%d\n", K);
	return 0;
}
