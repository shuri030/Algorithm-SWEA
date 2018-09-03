#include <stdio.h>
#include <iostream>
#include <vector>
#include <string.h>
#include <limits.h>
#include <stack>
#include <algorithm>
using namespace std;

int code[10][7] =
{
	{1, 0, 1, 1, 0, 0, 0},
	{1, 0, 0, 1, 1, 0, 0},
	{1, 1, 0, 0, 1, 0, 0},
	{1, 0, 1, 1, 1, 1, 0},
	{1, 1, 0, 0, 0, 1, 0},
	{1, 0, 0, 0, 1, 1, 0},
	{1, 1, 1, 1, 0, 1, 0},
	{1, 1, 0, 1, 1, 1, 0},
	{1, 1, 1, 0, 1, 1, 0},
	{1, 1, 0, 1, 0, 0, 0}
};
int N, M;
int board[52][102];
vector<int> ans;

int what_num(int x, int y) //코드가 몇번인지 return
{
	int yy = y;
	int flag = 0;

	for (int i = 0; i <= 9; i++) {
		yy = y;
		for (int k = 0; k < 7; k++) {
			if (board[x][yy] != code[i][k]) {
				flag = 1;
				break;
			}
			yy--;
		}
		if (flag == 1) {
			flag = 0;
			continue;
		}
		else if (flag == 0) {
			return i;
		}
	}
}

int num(int x, int y)
{
	int fin = y - 49;
	int yy = y;

	while (yy >= fin) {
		int num = what_num(x, yy);
		ans.push_back(num); //리턴한 숫자 벡터에 넣는다
		yy = yy - 7;
	}

	//코드 확인
	int sum1 = 0, sum2 = 0;
	for (int i = 1; i < 8; i++) {
		if (i % 2 == 1) {
			sum1 += ans[i];
		}
		else {
			sum2 += ans[i];
		}
	}

	int answer = ((sum1 * 3) + sum2 + ans[0]);
	if (answer % 10 == 0) {
		return sum1 + sum2 + ans[0];
	}
	else {
		return 0;
	}
}

int main()
{
	int tc;
	scanf("%d", &tc);

	for (int t = 1; t <= tc; t++) {

		int st_x = 0, st_y = 0;
		cin >> N >> M;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				scanf("%1d", &board[i][j]);
			}
		}



		for (int i = 0; i < N; i++) {
			for (int j = M - 1; j >= 0; j--) {
				if (board[i][j] == 1) {
					st_x = i; st_y = j;
					break;
				}
			}
			if (st_x != 0) {
				break;
			}
		}
		printf("#%d %d\n", t, num(st_x, st_y));
		memset(board, 0, sizeof(board));
		ans.clear();
	}

	return 0;
}
