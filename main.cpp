#include <iostream>
#include <cmath>
#include <algorithm>
#define INF 0x7f7f7f7f
using namespace std;
typedef struct 
{
	int x;
	int y;
}Point;
void homeInit(Point * home);
double prim(double matrix[][16],Point *home,int choice);
double prim2(double matrix[][16], Point* home, int choice);
int main() {
	Point home[16];
	double matrix[16][16] = { INF };
	homeInit(home);
	//构造邻接矩阵
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			matrix[i][j] = sqrt((home[i].x - home[j].x) * (home[i].x - home[j].x) + (home[i].y - home[j].y) * (home[i].y - home[j].y));
		}
	}
	double result=prim(matrix, home,1);
	double result2 = prim(matrix, home, 2);
	double result3 = prim(matrix, home, 3);
	double result7 = prim2(matrix, home, 4);
	double result5 = prim2(matrix, home, 2);
	double result6 = prim2(matrix, home, 3);
	double result4 = prim2(matrix, home, 1);
	
	printf("%lf\n", result);
	printf("%lf\n", result2);
	printf("%lf\n", result3);
	printf("%lf\n", result4);
	printf("%lf\n", result5);
	printf("%lf\n", result6);
	printf("%lf\n", result7);
	return 0;
}

void homeInit(Point* home) {
	home[0].x =1 ; home[0].y = 13;
	home[1].x = 2; home[1].y = 19;
	home[2].x = 3; home[2].y = 2;
	home[3].x = 4; home[3].y = 7;
	home[4].x = 5; home[4].y = 4;
	home[5].x = 6; home[5].y = 11;
	home[6].x = 9; home[6].y = 14;
	home[7].x = 10; home[7].y = 3;
	home[8].x = 11; home[8].y = 8;
	home[9].x = 12; home[9].y = 20;
	home[10].x = 13; home[10].y = 17;
	home[11].x = 14; home[11].y = 12;
	home[12].x = 15; home[12].y = 5;
	home[13].x = 18; home[13].y = 3;
	home[14].x = 19; home[14].y = 16;
	home[15].x = 20; home[15].y = 6;
}

double prim(double matrix[][16], Point* home, int choice) {
	int visit[16] = { 0 };
	double dist[16][2];//距离表
	int path[32];//路径表
	int k, num;
	double sum = 0;
	int times = 15;
	for (int i = 0; i < 16; i++) {
		dist[i][0] = INF;
	}
	if (choice == 1) {
		visit[2] = 1;
		visit[7] = 1;
		visit[13] = 1;
		path[0] = 16; path[1] = 2;
		path[2] = 16; path[3] = 7;
		path[4] = 16; path[5] = 13;
		num = 6;
		sum = 8;
		times = 13;
		for (int i = 0; i < 3; i++) {
			int k;
			if (i == 0) {
				k = 2;
			}
			else if (i == 1) {
				k = 7;
			}
			else k = 13;
			for (int j = 0; j < 16; j++) {
				if (!visit[j] && dist[j][0] > matrix[k][j]) {
					dist[j][0] = matrix[k][j];
					dist[j][1] = k;
				}
			}
		}
	}
	if (choice == 2||choice==3) {
		visit[2] = 1;
		visit[7] = 1;
		visit[13] = 1;
		visit[0] = 1;
		visit[1] = 1;
		path[0] = 16; path[1] = 2;
		path[2] = 16; path[3] = 7;
		path[4] = 16; path[5] = 13;
		path[6] = 17; path[7] = 0;
		path[8] = 17; path[9] = 1;
		num = 10;
		sum = 11;
		times = 11;
		for (int i = 0; i < 5; i++) {
			int k;
			if (i == 0) k = 2;
			if (i == 1) k = 7;
			if (i == 2) k = 13;
			if (i == 3) k = 0;
			if (i == 4) k = 1;
			for (int j = 0; j < 16; j++) {
				if (!visit[j] && dist[j][0] > matrix[k][j]) {
					dist[j][0] = matrix[k][j];
					dist[j][1] = k;
				}
			}
		}
	}
	if (choice == 3) {
		visit[14] = 1;
		visit[15] = 1;
		path[num++] = 14;
		path[num++] = 15;
		sum += sqrt((home[14].x - home[15].x) * (home[14].x - home[15].x) + (home[14].y - home[15].y) * (home[14].y - home[15].y));
		for (int j = 0; j < 16; j++) {
			if (!visit[j] && dist[j][0] > matrix[14][j]) {
				dist[j][0] = matrix[14][j];
				dist[j][1] = 14;
			}
		}
		for (int j = 0; j < 16; j++) {
			if (!visit[j] && dist[j][0] > matrix[15][j]) {
				dist[j][0] = matrix[15][j];
				dist[j][1] = 15;
			}
		}
		times = times - 2;
	}
	for (int i = 0; i < times; i++) {
		double min = INF;
		int prev = -1;
		for (int j = 0; j < 16; j++) {
			if (visit[j] == 0 && dist[j][0] < min) {
				min = dist[j][0];
				k = j;
				prev = dist[j][1];
			}
		}
		if (choice == 1) {
			if (dist[k][0] > home[k].y) {
				prev = 16;
				min = home[k].y;
			}
		}
		if (choice == 2||choice==3) {
			if (home[k].x<home[k].y&&home[k].x<dist[k][0]) {
				prev = 17;
				min = home[k].x;
			}
			if (home[k].y < home[k].x && home[k].y < dist[k][0]) {
				prev = 16;
				min = home[k].y;
			}
		}
		visit[k] = 1;
		path[num++] = prev;
		path[num++] = k;
		sum += min;
		for (int j = 0; j < 16; j++) {
			if (!visit[j] && dist[j][0] > matrix[k][j]) {
				dist[j][0] = matrix[k][j];
				dist[j][1] = k;
			}
		}
	}
	if (choice == 3) {
		path[num++] = 15;
		path[num++] = 13;
		sum += sqrt((home[13].x - home[15].x) * (home[13].x - home[15].x) + (home[13].y - home[15].y) * (home[13].y - home[15].y));
	}
	string s = "result";
	if (choice == 1) {
		s += "1b.txt";
	}
	if (choice == 2) {
		s += "1c.txt";
	}
	if (choice == 3) {
		s += "1d.txt";
	}
	FILE* fp;
	fopen_s(&fp, s.c_str(), "w");
	for (int i = 0; i < 32; i++) {
		if (i % 2 == 1) {
			fprintf(fp, "%d\n", path[i]);
		}
		else fprintf(fp, "%d ", path[i]);
	}
	fclose(fp);
	return sum;
}

double prim2(double matrix[][16], Point* home, int choice) {
	int visit[16];
	double dist[18][2];//距离表
	int path[32];//路径表
	int k, num=0;
	double sum = 0;
	int prev;
	dist[16][1] = -1;
	if (choice == 1||choice==2) {
		for (int i = 0; i < 16; i++) {
			dist[i][0] = home[i].y;
			dist[i][1] = 16;
		}
	}
	if (choice == 2) {
		dist[3][0] = INF;
		dist[4][0] = INF;
		dist[9][0] = INF;
		dist[13][0] = INF;
		dist[14][0] = INF;
		dist[15][0] = INF;
	}
	if (choice == 3||choice==4) {
		dist[17][1] = -1;
		for (int i = 0; i < 16; i++) {
			if (home[i].y < home[i].x) {
				dist[i][0] = home[i].y;
				dist[i][1] = 16;
			}
			else
			{
				dist[i][0] = home[i].x;
				dist[i][1] = 17;
			}
		}
	}
	if (choice == 4) {
		dist[2][0] = INF;
		dist[13][0] = INF;
		dist[14][0] = INF;
		dist[15][0] = INF;
	}
	for (int i = 0; i < 16; i++) {
		visit[i] = 0;
	}
	for (int i = 0; i < 16; i++) {
		double min = INF;
		for (int j = 0; j < 16; j++) {
			if (visit[j] == 0 ) {
				if (dist[j][0] < min) {
					min = dist[j][0];
					k = j;
					prev = dist[j][1];
				}
			}
		}
		path[num++] = k;
		path[num++] = prev;
		visit[k] = 1;
		sum += min;
		for (int j = 0; j < 16; j++) {
			if (visit[j] == 0) {
				if ((k == 12 && j == 14)||(k==12&&j==15)) {
					continue;
				}
				if ((k == 14 && j == 12) || (k == 15 && j == 12)) {
					continue;
				}
				double cost = matrix[k][j];
				int j1 = k;
				do {
					int j2 = dist[j1][1];
					if (j2 == 16) {
						cost += home[j1].y;
					}
					else if (j2 == 17) {
						cost += home[j1].x;
					}
					else {
						cost += matrix[j1][j2];
					}
					j1 = j2;
				} while (dist[j1][1] != -1);
				if (cost < dist[j][0]) {
					dist[j][0] = cost;
					dist[j][1] = k;
				}
			}	
		}
	}
	string s = "result";
	if (choice == 1) {
		s += "2b.txt";
	}
	if (choice == 2) {
		s += "2d.txt";
	}
	if (choice == 3) {
		s += "2e.txt";
	}
	if (choice == 4) {
		s += "2f.txt";
	}
	FILE* fp;
	fopen_s(&fp, s.c_str(), "w");
	for (int i = 0; i < 32; i++) {
		if (i % 2 == 1) {
			fprintf(fp, "%d\n", path[i]);
		}
		else fprintf(fp, "%d ", path[i]);
	}
	return sum;
}