#include "stdio.h"
#include "display.h"
#include "io.h"
#include "common.h"
#include "Windows.h"


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


//�ʱ� �ǹ� + ����
//player
OBJECT player_B;
UNIT  player_H;

//AI
OBJECT  AI_B;
UNIT  AI_H;

//��
OBJECT rock;

//����
OBJECT plate_1;
OBJECT plate_2;

//�����̽�
SPICE spice_1;
SPICE spice_2;

//�����
SANDWARM sandwarm_1;
SANDWARM sandwarm_2;

//�ǹ�
OBJECT dormitory; //����
OBJECT garage; //â��
OBJECT barracks; //����
OBJECT shelter; //����ó
OBJECT arena; //������
OBJECT factory; //����

//����
UNIT premen; //������
UNIT soldier; //����
UNIT fighter; //����
UNIT tank; //������
