#include <stdio.h>
#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>
using namespace std;

vector<char> v;

int main()
{	
	int t, N;
	scanf("%d", &t);
	
	int n;
	char ch;
	
	for(int tc = 1; tc <= t; tc++) {
		scanf("%d", &N);

		for(int i = 1; i <= N; i++) {
			cin >> ch >> n;
			for(int j = 1; j <= n; j++) {
				v.push_back(ch);
			}
		}

		printf("#%d\n", tc);
		for(int i = 0; i < v.size(); i++) {
			printf("%c", v[i]);
			if(i % 10 == 9) { printf("\n"); }
		}

		printf("\n");
		v.clear();
	}

    return 0;
}