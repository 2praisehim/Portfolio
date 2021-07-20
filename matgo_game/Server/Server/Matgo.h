#pragma once
#include <stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>

void Start_Game();
void SelectPae(char msg[], int use);
void NSelectPae(char msg[], int use);
void Openpae_Update(int use);
void Add_Score(char msg[], int use);
void SelectBonus(char msg[], int use);
void Stop(int use);
void Gobak(int use);



struct Pae {
	 int Openpae[20];							//¹Ù´Ú¿¡ ±ò¸° ÆÐ
	 int openpaelen = 0;
	 
};

struct Player {
	char name[8];
	int pae[10];				//ÇÃ·¹ÀÌ¾î ÆÐ
	int paelen = 0;	
	int	Scorepae[50];			//Á¡¼öÆÐ( ±¤, ´Ü, ¿­²ý, ÇÇ)
	int scorepalen = 0;
};



void Add_First(Player *p, int val);
void Erase(Player *p, int pos);
int Find_Value(Player *p, int val);
int return_len(Player *p);
void OpenPae_Add(Pae *p, int val);
int OpenFind_adr(Pae *p, int val);
int OpenFind_value(Pae *p, int pos);
void OpenErase(Pae *p, int pos);
int OpenReplace(Pae *p, int pos, int val);
void ScorePae_Add(Player *p, int val);
void ScorePae_Output(Player *p);
int ScorePae_value(Player *p, int pos);
int ScorePae_len(Player *p);
void ScorePae_Del(Player *p);


void Array_Clear(Player *p);
int Replace(Player *p, int pos, int val);
void Output(Player *p);
void Add_Last(Player *p, int val);
void Add(Player *p, int val, int pos);


void OpenPae_Output(Pae *p);



