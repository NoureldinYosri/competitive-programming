#include <bits/stdc++.h>
using namespace std;
#define MAX_K 40
#define MAX_N 150

static int Q, N, K, A[MAX_N], P[MAX_K];
static long long X;
static int min_wa = MAX_K + 1;

void Anna( int N, long long X, int K, int P[] );
long long Bruno( int N, int A[] );

void WrongAnswer( int e ){
  fprintf( stderr, "Wrong Answer [%d]\n", e );
  exit( 0 );
}

void Set( int pos, int bit ){
  if( !( 0 <= pos && pos < N ) ){
    WrongAnswer( 1 );
  }
  if( A[pos] != -1 ){
    WrongAnswer( 2 );
  }
  if( !( bit == 0 || bit == 1 ) ){
    WrongAnswer( 3 );
  }
  A[pos] = bit;
}

int main( int argc, char** argv ){
  int i, query_cnt;
  long long ans;
srand(time(NULL));
  Q = 100000;
  //scanf( "%d", &Q );

  for( query_cnt = 0; query_cnt < Q; query_cnt++ ){
    //scanf( "%d %lld %d", &N, &X, &K );
    N = 150 ,X = rand() ,K = rand()%40;
    for( i = 0; i < K; i++ ){
      //scanf( "%d", &P[i] );
      P[i] = rand()%N;
    }
    std::sort(P ,P+K);

    cerr << "sending" << endl;
    cerr << N << " " << X << " " << K << endl;
    for( i = 0; i < K; i++ ){
      cerr << P[i] << " ";
    }
    cerr << endl;

    for( i = 0; i < N; i++ ){
      A[i] = -1;
    }

    Anna( N, X, K, P );

    for( i = 0; i < N; i++ ){
      if( A[i] == -1 ){
        WrongAnswer( 4 );
      }
    }

    for( i = 0; i < K; i++ ){
      A[ P[i] ] = 0;
    }

    ans = Bruno( N, A );

    if( ans != X ){
      if( K < min_wa ){
        min_wa = K;
      }
      printf("Wrong Answer\n");
      printf("%lld %lld\n",ans ,X);
    }
  }

  if( min_wa == 1 ){
    if( K < min_wa ){
      min_wa = K;
    }
  }

  fprintf( stderr, "Accepted\n" );
  fprintf( stderr, "L* = %d\n", min_wa - 1 );

  return 0;
}
