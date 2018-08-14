#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;

int A[20], B[20];
int N, M;

int main()
{	
	int t;
	scanf("%d", &t);
	for(int tc = 1; tc <= t; tc++) {
		scanf("%d %d", &N, &M);

		for(int i = 0; i < N; i++) {
			scanf("%d", &A[i]);
		}
		for(int i = 0; i < M; i++) {
			scanf("%d", &B[i]);
		}
		int ans = 0, sum = 0;

		if(N < M) {
			for(int i = 0; i <= M - N; i++) {
				sum = 0;
				for(int j = 0; j < N; j++) {
					sum += B[i + j] * A[j];
				}
				ans = max(sum, ans);
			}
		}
		else {
			for(int i = 0; i <= N - M; i++) {
				sum = 0;
				for(int j = 0; j < M; j++) {
					sum += A[i + j] * B[j];
				}
				ans = max(sum, ans);
			}
			
		}
		printf("#%d %d\n", tc, ans);

		memset(A, 0, sizeof(A));
		memset(B, 0, sizeof(B));
	}
    return 0;
}