#include <stdio.h>

typedef //������Ʈ �ǹ�
struct {
	char object;
	int color_num;
	int blood;
	int cost;
} OBJECT;

typedef //����
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

typedef //�����
struct {
	char object;
	int color_num;
	int move;
	int war_time;
} SANDWARM;

typedef //��
struct {
	char object;
	int color_num;
} ROCK;

typedef
struct { //�����̽�
	int color_num;
	int much;
} SPICE;
