#include <stdio.h>
#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>
using namespace std;

int days[14] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int main()
{	
	int t, N;
	int m1, d1, m2, d2;
	scanf("%d", &t);
	
	for(int tc = 1; tc <= t; tc++) {
		int sum = 1;
		scanf("%d %d %d %d", &m1, &d1, &m2, &d2);
		
		if(m1 == m2) {
			sum = sum + d2 - d1;
		}
		else {
			sum = sum + (days[m1] - d1) + d2;
			for(int i = m1 + 1; i < m2; i++) {
				sum += days[i];
			}
		}
		printf("#%d %d\n", tc, sum);
	}

    return 0;
}