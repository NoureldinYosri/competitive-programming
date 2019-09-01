#include "Brunolib.h"
#include <bits/stdc++.h>
using namespace std;
 
void bH(int H[256][256],int len) {
	if(len == 1)  {
		H[0][0] = 1;
		return;
	}
	bH(H,len / 2);
	int n = len/2;
	for(int i = 0;i < n;i++)
		for(int j = 0;j < n;j++) 
			H[i][j + n] = H[i + n][j] = H[i][j];
}
 
 
long long Bruno( int N, int A[] ){
	int H[256][256] = {0};
	bH(H,256);
	long long x = 0;
	for(int i = 0;i < 60;i++) {
		long long v = 0;
		// cerr << i << ": ";
		for(int j = 0;j < N;j++) {
			// if(H[i][j]*A[j])
				// cerr << "(" << i << ", " << j << ")" ;
			v ^= H[i][j]*A[j];
		}
		// cerr << endl;
		// cerr << v << endl;
		x |= v << i;
	}
	// cerr << "return " << x << endl;
	return x;
}
