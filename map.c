#include "stdio.h"
#include "display.h"
#include "io.h"
#include "common.h"
#include "Windows.h"


typedef //오브젝트 건물
struct {
	char object;
	int color_num;
	int blood;
	int cost;
} OBJECT;

typedef //유닛
struct {
	char object;
	int color_num;
	int cost;
	int people;
	int move;
	int demage;
	int war_time;
	int blood;
	int see;

} UNIT;

typedef //샌드웜
struct {
	char object;
	int color_num;
	int move;
	int war_time;
} SANDWARM;

typedef //돌
struct {
	char object;
	int color_num;
} ROCK;

typedef
struct { //스파이스
	int color_num;
	int much;
} SPICE;


//초기 건물 + 유닛
//player
OBJECT player_B;
UNIT  player_H;

//AI
OBJECT  AI_B;
UNIT  AI_H;

//돌
OBJECT rock;

//장판
OBJECT plate_1;
OBJECT plate_2;

//스파이스
SPICE spice_1;
SPICE spice_2;

//샌드웜
SANDWARM sandwarm_1;
SANDWARM sandwarm_2;

//건물
OBJECT dormitory; //숙소
OBJECT garage; //창고
OBJECT barracks; //병영
OBJECT shelter; //은신처
OBJECT arena; //투기장
OBJECT factory; //공장

//유닛
UNIT premen; //프레멘
UNIT soldier; //보병
UNIT fighter; //투사
UNIT tank; //중전차
