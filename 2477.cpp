#include <stdio.h>
#include <iostream>
#include <string.h>
#include <queue>
#include <algorithm>
using namespace std;

int a[11][3];
int b[11][3];

struct person {
	int rec; //이용한 접수
	int rep; //이용한 정비
	int sec; //등장 시간
};
person p[1001];

int main()
{	
	int t, st_s;
	int N, M, K, A, B;
	queue<int> q;
	queue<int> repair; //정비 대기
	queue<int> recept; //접수 대기
	scanf("%d", &t);

	for(int tc = 1; tc <= t; tc++) {

		scanf("%d %d %d %d %d", &N, &M, &K, &A, &B);
		memset(a, -1, sizeof(a));
		memset(b, -1, sizeof(b));
		

		//input
		for(int i = 1; i <= N; i++) {
			scanf("%d", &a[i][0]);
		}
		for(int i = 1; i <= M; i++) {
			scanf("%d", &b[i][0]);
		}
		for(int i = 1; i <= K; i++) {
			scanf("%d", &p[i].sec);
			q.push(i);
			if(i == 1) { st_s = p[i].sec; }
		}

		int total = K;
		int tt = st_s;

		while(total > 0) {
			
			//정비 끝난 애들 처리
			for(int i = 1; i <= M; i++) {
				if(b[i][2] == tt) { //정비 끝났으면
					b[i][1] = -1; //자리 비우고
					b[i][2] = -1; //시간 비우고
					total--; //전체 명수에서 뺀다
				}
			}

			int w;
			//정비 대기 하던 애들이 있으면 먼저 배정하기
			if(repair.size() > 0) {
				for(int i = 1; i <= M; i++) {
					if(b[i][1] == -1) {
						w = repair.front();
						repair.pop();

						b[i][1] = w;
						p[w].rep = i;
						b[i][2] = tt + b[i][0];
						if(repair.size() == 0) { break; } //대기 없으면 나가기
					}
				}
			}

			//접수 끝난 애들 정비 대기할지, 정비 배정할지
			for(int i = 1; i <= N; i++) {
				if(a[i][2] == tt) { //접수 끝났으면
					if(repair.size() > 0) { //정비대기자있으면 대기
						repair.push(a[i][1]);
					}
					else { //정비대기자 없으면 배정
						int flag2 = 0;
						for(int j = 1; j <= M; j++) {
							if(b[j][1] == -1) {
								w = a[i][1];
								b[j][1] = w;
								p[w].rep = j;
								b[j][2] = tt + b[j][0];
								flag2 = 1;
								break; //작은거 배정했으면 포문 탈출
							}
						}
						if(flag2 == 0) { repair.push(a[i][1]); } //대기도 없고 자리도 없다.
					}
					a[i][1] = -1; a[i][2] = -1; //자리 비워주기
				}
			}

			//접수 대기 하던 애들이 있으면 먼저 배정하기
			//자리가 없으면 배정하지못함
			if(recept.size() > 0) {
				for(int i = 1; i <= N; i++) {
					if(a[i][1] == -1) {
						w = recept.front();
						recept.pop();
						a[i][1] = w;
						p[w].rec = i;
						a[i][2] = tt + a[i][0];
						if(recept.size() == 0) { break; } //대기 없으면 나가기
					}
				}
			}

			//시간맞춰 등장한애들 접수 대기할지 접수 배정할지
			while(!q.empty()) {
				int ps = q.front();
				if(p[ps].sec == tt) { //tt초때 오는 손님 등장
					q.pop();
					if(recept.size() == 0) { //접수 대기줄이 없으면
						int flag = 0;
						for(int i = 1; i <= N; i++) {
							if(a[i][1] == -1) { //창구에 아무도 없으면
								a[i][1] = ps; // 이 창구에 손님
								p[ps].rec = i; //손님 정보에 접구 창구 번호 넣기
								a[i][2] = tt + a[i][0]; //나갈 시간 정하기
								flag = 1;
								break;
							}
						}
						if(flag == 0) { //대기없는데 자리도없을때
							recept.push(ps);
						}
					}
					else {
						recept.push(ps); //대기 있으면 대기에 넣기
					}
				}

				else { break; } 
			}
			tt++;

		}
		
		int sum = 0;

		for(int i = 1; i <= K; i++) {
			if((p[i].rec == A) && (p[i].rep == B)) {
				sum += i;
			}
		}

		printf("#%d ",tc);
		if(sum == 0) {
			printf("-1\n");
		}
		else {
			printf("%d\n", sum);
		}
		
		//초기화
		for(int i = 1; i <= K; i++) {
			p[i].rec = p[i].rep = p[i].sec = 0;
		}
	}
    return 0;
}