#include <stdio.h>

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
