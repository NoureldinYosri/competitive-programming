#include "Annalib.h"
#include <bits/stdc++.h>
using namespace std;
 
void buildH(int H[256][256],int len) {
	if(len == 1)  {
		H[0][0] = 1;
		return;
	}
	buildH(H,len / 2);
	int n = len/2;
	for(int i = 0;i < n;i++)
		for(int j = 0;j < n;j++) 
			H[i][j + n] = H[i + n][j] = H[i][j];
}
 
 
 
void gauss(int A[256][256],int B[256],int S[256],int N) {
	int P[256],X[256] = {0};
	int rank = 0;
	for(int i = 0;i < N;i++) P[i] = i;
	for(int pivot = 0,cr = 0;pivot < N;pivot++) {
		int tr = cr;
		while(tr < N && A[tr][pivot] == 0) tr++;
		if(tr == N) {
			continue;
		}
		// cerr << cr << ": " << pivot << endl;
		rank++;
		for(int c = 0;c < N;c++) swap(A[cr][c],A[tr][c]);
		swap(P[cr],P[tr]);
		swap(B[cr],B[tr]);
 
		for(int r = cr+1;r < N;r++) {
			if(!A[r][pivot]) continue;
			for(int c = pivot;c < N;c++)
				A[r][c] ^= A[cr][c];
			B[r] ^= B[cr];
		}
		cr++;
	}
	cerr << "rank = " << rank << endl;
	for(int i = N-1;i >= 0;i--) {
		int ctr = 0,c = -1;
		for(int j = 0;j < N;j++) {
			if(A[i][j]) {
				ctr++;
				c = j;
			}
		}
		cerr << "ones " << i << ": ";
		for(int j = 0;j < N;j++)
			if(A[i][j]) cerr << j << " ";
		cerr << endl;
		assert(ctr <= 1);
		if(!ctr) continue;
		for(int j = 0;j < i;j++)
			if(A[j][c]) {
				for(int k = 0;k < N;k++)
					A[j][k] ^= A[i][k];
				B[j] ^= B[i];
			}
	}
	for(int i = 0;i < N;i++) {
		int ctr2 = 0;
		for(int j = 0;j < N;j++)
			ctr2 += A[i][j];
		int c = 0;
		while(c < N && !A[i][c]) c++;
		if(c == N) continue;
		X[c] = B[i];
	}
	for(int i = 0;i < N;i++) {
		int v = 0;
		for(int j = 0;j < N;j++) 
			v ^= A[i][j] * X[j];
		cerr << i << " " << v << " " << B[i] << endl;
		assert(v == B[i]);
	}
	for(int i = 0;i < N;i++)
		S[i] = X[P[i]];
}
 
void Anna( int N, long long X, int K, int P[] ){
	int H[256][256] = {0};
	buildH(H,256);
	for(int i = 0;i < K;i++) {
		int b = P[i];
		for(int r = 0;r < N;r++)
			H[r][b] = 0;
	}
	int B[256] = {0};
	for(int i = 0;i < N;i++) {
		B[i] = X & 1;
		X >>= 1;
	}
 
	int S[256] = {0};
	// for(int i = 0;i < N;i++)
	// 	cerr << B[i] << " ";
	// cerr << endl;
	gauss(H,B,S,N);
	// for(int i = 0;i < N;i++)
	// 	cerr << S[i] << " ";
	// cerr << endl;
	for(int i = 0;i < N;i++) 
		Set(i,S[i]);
}	
