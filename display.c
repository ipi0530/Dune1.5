/*
*  display.c:
* 화면에 게임 정보를 출력
* 맵, 커서, 시스템 메시지, 정보창, 자원 상태 등등
* io.c에 있는 함수들을 사용함
*/

#include "stdio.h"
#include "display.h"
#include "io.h"
#include "common.h"
#include "map.c"

// 출력할 내용들의 좌상단(topleft) 좌표
const POSITION resource_pos = { 0, 0 };
const POSITION map_pos = { 1, 0 };

char backbuf[MAP_HEIGHT][MAP_WIDTH] = { 0 };
char frontbuf[MAP_HEIGHT][MAP_WIDTH] = { 0 };
char colorbuf[MAP_HEIGHT][MAP_WIDTH] = { 0 };


//초기 건물 + 유닛
//player
OBJECT player_B = {'B', 17, 50, 0};
UNIT  player_H = {'H', 9, 5, 5, 2000, 0, 0, 70, 0};

//AI
OBJECT  AI_B = {'B', 68, 50, 0};
UNIT  AI_H = {'H', 4, 5, 5, 2000, 0, 0, 70, 0};

//돌
ROCK rock = {'R', 7};

//장판
OBJECT plate_1 = {'P', 8, -1, 10};
OBJECT plate_2 = {'P', 8, -1, 10};

//스파이스
SPICE spice_1 = {6, 9};
SPICE spice_2 = {6, 9};

//샌드웜
SANDWARM sandwarm_1 = {'S', 96, 2500, 10000};
SANDWARM sandwarm_2 = { 'S', 96, 2500, 10000 };

//건물
OBJECT Dormitory = { 'D', 9, 10, 2 }; //숙소
OBJECT Garage = { 'G', 9, 10, 4 }; //창고
OBJECT Barracks = { 'B', 9, 20, 4 }; //병영
OBJECT Shelter = { 'S', 9, 30, 5 }; //은신처
OBJECT Arena = { 'A', 9, 15, 3 }; //투기장
OBJECT Factory = { 'F', 9, 30, 5 }; //공장

//유닛
UNIT Fremen = { 'f', 9, 5, 5, 400, 15, 200, 25, 88 }; //프레멘
UNIT Soldier = { 's', 9, 1, 1, 1000, 5, 800, 15, 1 }; //보병
UNIT Fighter = { 'f', 4, 1, 1, 1200, 6, 600, 10, 1 }; //투사
UNIT Tank = { 't', 4, 12, 5, 3000, 40, 4000, 60, 4 }; //중전차


//맵 배치
void project(char src[N_LAYER][MAP_HEIGHT][MAP_WIDTH], char dest[MAP_HEIGHT][MAP_WIDTH]);
void display_resource(RESOURCE resource);
void display_map(char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH]);
void display_cursor(CURSOR cursor, char colorbuf[MAP_HEIGHT][MAP_WIDTH]);
void display_system_message(void);
void display_commands(void);
void display_now(void);
void display_map_nemo(char colorbuf[MAP_HEIGHT][MAP_WIDTH]); //테두리 색 고정

void display_object_info_player(char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH], OBJECT* player_B, UNIT* player_H, char colorbuf[MAP_HEIGHT][MAP_WIDTH]); //플레이어
void display_object_info_AI(char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH], OBJECT* AI_B, UNIT* AI_H, char colorbuf[MAP_HEIGHT][MAP_WIDTH]); //AI
void display_object_info_Rock(char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH], ROCK* rock, char colorbuf[MAP_HEIGHT][MAP_WIDTH]); //돌
void display_object_info_Plate(char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH], OBJECT* plate_1, OBJECT* plate_2, char colorbuf[MAP_HEIGHT][MAP_WIDTH]); // 장판
void display_object_info_spice(char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH], SPICE* spice_1, SPICE* spice_2, char colorbuf[MAP_HEIGHT][MAP_WIDTH]); // 스파이스
void display_object_info_sandwarm(char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH], SANDWARM* sandwarm_1, SANDWARM* sandwarm_2, char colorbuf[MAP_HEIGHT][MAP_WIDTH]); //샌드웜
void display_first_map(char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH]) { //초기 맵 설정
	display_map_nemo(colorbuf);
	display_object_info_player(map, &player_B, &player_H, colorbuf);
	display_object_info_AI(map, &AI_B, &AI_H, colorbuf);
	display_object_info_Rock(map, &rock, colorbuf);
	display_object_info_Plate(map, &plate_1, &plate_2, colorbuf);
	display_object_info_spice(map, &spice_1, &spice_2, colorbuf);
	display_object_info_sandwarm(map, &sandwarm_1, &sandwarm_2, colorbuf);
}



void display(
	RESOURCE resource,
	char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH],
	CURSOR cursor)
{

	display_resource(resource);
	display_map(map);
	display_cursor(cursor, colorbuf);
	display_system_message();
	display_commands();
	display_now();

	// ...
}

void display_resource(RESOURCE resource) {
	set_color(COLOR_RESOURCE);
	gotoxy(resource_pos);
	printf("spice = %d/%d, population=%d/%d\n",
		resource.spice, resource.spice_max,
		resource.population, resource.population_max
	);
}

// subfunction of draw_map()
void project(char src[N_LAYER][MAP_HEIGHT][MAP_WIDTH], char dest[MAP_HEIGHT][MAP_WIDTH]) {
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			for (int k = 0; k < N_LAYER; k++) {
				if (src[k][i][j] >= 0) {
					dest[i][j] = src[k][i][j];
				}
			}
		}
	}
}

void display_map(char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH]) {
	project(map, backbuf);
	int color;
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			if (frontbuf[i][j] != backbuf[i][j]) {
				POSITION pos = { i, j };
				color = colorbuf[i][j];
				printc(padd(map_pos, pos), backbuf[i][j], color);
				set_color(COLOR_DEFAULT);
			}
			frontbuf[i][j] = backbuf[i][j];
		}
	}

}

void display_system_message(void) {
	set_color(15);
	POSITION pos = { 19, 0 };
	gotoxy(pos);
	char system_message[5][58] = { " ", " ", " "," ", " " }; //나중에 시스템 메세지가 들어갈 예정
	for (int i = 0; i < 5; i++) {
		printf("#%s\n", system_message[i]);
	}
	for (int j = 0; j < 60; j++) {
		printf("#");
	}
}

void display_commands(void) {
	set_color(15);
	POSITION pos = { 19, 59 };
	gotoxy(pos);
	char commends_message[5][38] = { " ", " ", " "," ", " " }; //나중에 추가


	for (int i = 0; i < 5; i++) { //왼쪽 세로줄 + 명령어 출력창
		pos.row = 19 + i;
		gotoxy(pos);
		printf("#%s\n", commends_message[i]);
	}

	pos.row = 24;
	gotoxy(pos);
	for (int j = 0; j < 40; j++) { //밑줄
		printf("#");
	}

	pos.column = 98;
	for (int i = 0; i < 5; i++) { //오른쪽 세로줄
		pos.row = 19 + i;
		gotoxy(pos);
		printf("#\n");
	}
}

void display_now(void) {
	set_color(15);
	POSITION pos = { 1, 60 };
	gotoxy(pos);
	for (int i = 0; i < 39; i++) { //윗줄
		printf("#");
	}
	char odject_message[16][38] = { 0 };

	for (int i = 0; i < 16; i++) { //상태창
		pos.row = 2 + i;
		gotoxy(pos);
		printf("%s\n", odject_message[i]);
	}

	pos.row = 18;
	pos.column = 59;
	gotoxy(pos);
	for (int i = 0; i < 40; i++) { //아랫줄
		printf("#");
	}

	pos.row = 2;
	pos.column = 98;
	for (int i = 0; i < 16; i++) { //오른쪽 세로줄
		pos.row = 2 + i;
		gotoxy(pos);
		printf("#");
	}
	POSITION pos1 = { 2, 77 };
	gotoxy(pos1);
	printf("상태창");
}



// frontbuf[][]에서 커서 위치의 문자를 색만 바꿔서 그대로 다시 출력
void display_cursor(CURSOR cursor, char colorbuf[MAP_HEIGHT][MAP_WIDTH]) {
	POSITION prev = cursor.previous;
	POSITION curr = cursor.current;
	int color;


	char ch = frontbuf[prev.row][prev.column];
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			if (i == prev.row && j == prev.column) {
				color = colorbuf[i][j];
			}
		}
	}
	printc(padd(map_pos, prev), ch, color);

	ch = frontbuf[curr.row][curr.column];
	printc(padd(map_pos, curr), ch, COLOR_CURSOR);
}


//엔티티

//테두리 색 설정하기
void display_map_nemo(char colorbuf[MAP_HEIGHT][MAP_WIDTH]) {
	for (int i = 0; i < 60; i++) {
		colorbuf[0][i] = COLOR_DEFAULT;
	}

	for (int i = 0; i < 60; i++) {
		colorbuf[17][i] = COLOR_DEFAULT;
	}

	for (int i = 0; i < 18; i++) {
		colorbuf[i][0] = COLOR_DEFAULT;
	}

	for (int i = 0; i < 18; i++) {
		colorbuf[i][59] = COLOR_DEFAULT;
	}
}

void display_object_info_player(char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH], OBJECT* player_B, UNIT* player_H, char colorbuf[MAP_HEIGHT][MAP_WIDTH]) { //플레이어
	//위치
	for (int i = 15; i <= 16; i++) {
		for (int j = 1; j <= 2; j++) {
			map[0][i][j] = player_B->object; //본진
		}
	}
	map[1][14][1] = player_H->object; //하베스터

	//색
	for (int i = 15; i <= 16; i++) {
		for (int j = 1; j <= 2; j++) {
			colorbuf[i][j] = player_B->color_num; //본진
		}
	}

	colorbuf[14][1] = player_H->color_num; //하베스터

}

void display_object_info_AI(char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH], OBJECT* AI_B, UNIT* AI_H, char colorbuf[MAP_HEIGHT][MAP_WIDTH]) { //AI
	//위치
	for (int i = 1; i <= 2; i++) {
		for (int j = 57; j <= 58; j++) {
			map[0][i][j] = AI_B->object; //본진
		}
	}
	map[1][3][58] = AI_H->object; //하베스터

	//색
	for (int i = 1; i <= 2; i++) {
		for (int j = 57; j <= 58; j++) {
			colorbuf[i][j] = AI_B->color_num; //본진
		}
	}

	colorbuf[3][58] = AI_H->color_num;
}

void display_object_info_Rock(char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH], ROCK* rock, char colorbuf[MAP_HEIGHT][MAP_WIDTH]) { //돌
	//위치
	for (int i = 10; i <= 11; i++) { //돌1
		for (int j = 30; j <= 31; j++) {
			map[0][i][j] = rock->object;
		}
	}

	for (int i = 5; i <= 6; i++) { //돌2
		for (int j = 15; j <= 16; j++) {
			map[0][i][j] = rock->object;
		}
	}

	map[0][14][42] = rock->object; //돌3
	map[0][5][50] = rock->object; //돌4
	map[0][11][10] = rock->object; //돌5

	//색
	for (int i = 10; i <= 11; i++) { //돌1
		for (int j = 30; j <= 31; j++) {
			colorbuf[i][j] = rock->color_num;
		}
	}

	for (int i = 5; i <= 6; i++) { //돌2
		for (int j = 15; j <= 16; j++) {
			colorbuf[i][j] = rock->color_num;
		}
	}

	colorbuf[14][42] = rock->color_num; //돌3
	colorbuf[5][50] = rock->color_num; //돌4
	colorbuf[11][10] = rock->color_num; //돌5
}

void display_object_info_Plate(char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH], OBJECT* plate_1, OBJECT* plate_2, char colorbuf[MAP_HEIGHT][MAP_WIDTH]) { //장판
	//위치
	for (int i = 15; i <= 16; i++) {
		for (int j = 3; j <= 4; j++) {
			map[0][i][j] = plate_1->object; //장판1 플레이어 옆
		}
	}

	for (int i = 1; i <= 2; i++) {
		for (int j = 55; j <= 56; j++) {
			map[0][i][j] = plate_2->object; //장판2 AI옆

		}
	}

	//색
	for (int i = 15; i <= 16; i++) {
		for (int j = 3; j <= 4; j++) {
			colorbuf[i][j] = plate_1->color_num; //장판1 플레이어 옆
		}
	}

	for (int i = 1; i <= 2; i++) {
		for (int j = 55; j <= 56; j++) {
			colorbuf[i][j] = plate_2->color_num; //장판2 AI옆

		}
	}

}

void display_object_info_spice(char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH], SPICE* spice_1, SPICE* spice_2, char colorbuf[MAP_HEIGHT][MAP_WIDTH]) { //스파이스
	//위치
	map[0][11][1] = spice_1->much + '0';
	map[0][6][58] = spice_2->much + '0';

	//색
	colorbuf[11][1] = spice_1->color_num;
	colorbuf[6][58] = spice_2->color_num;
}

void display_object_info_sandwarm(char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH], SANDWARM* sandwarm_1, SANDWARM* sandwarm_2, char colorbuf[MAP_HEIGHT][MAP_WIDTH]) { //샌드웜
	//위치
	map[1][4][10] = sandwarm_1->object; //1
	map[1][9][39] = sandwarm_2->object; //2

	//색
	colorbuf[4][10] = sandwarm_1->color_num; //1
	colorbuf[9][39] = sandwarm_2->color_num; //2
}