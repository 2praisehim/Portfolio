#include "Matgo.h"

void Add_First(Player *p, int val)
{
	if (p->paelen >= 100)
		printf("Can not add Value in List\n");
	else
	{
		p->pae[p->paelen] = val;
		p->paelen += 1;
	}
}



void Add_Last(Player *p, int val)
{
	if (p->paelen >= 100) {
		printf("Can not add Value in List\n");
		return;
	}
	else
		p->pae[p->paelen] = val;
}

void Add(Player *p, int val, int pos)
{
	if (p->paelen >= 100) {
		printf("Can not add Value in List\n");
		return;
	}
	if (p->paelen < pos) {
		Add_Last(p, val);
	}
	for (int i = p->paelen; i < pos; i--)
		p->pae[i] = p->pae[i - 1];

	p->pae[pos] = val;
	p->paelen += 1;

}
void Erase(Player *p, int pos)
{
	if (p->paelen == 0) {
		printf("List is empty\n");
		return;
	}
	if (pos > p->paelen) {
		printf("%s is not data\n",p->name);
		return;
	}
	for (int i = pos; i < p->paelen - 1; i++)
		p->pae[i] = p->pae[i + 1];
	p->paelen -= 1;
}

void Array_Clear(Player *p)
{
	p->paelen = 0;
}

int Find_Value(Player *p, int val)
{

	for (int i = 0; i < p->paelen; i++)
	{
		if (p->pae[i] == val) {
			//printf(" 값: %d  배열 %d번째 요소\n", val, i);
			return i;
		}
	}

}

int Replace(Player *p, int pos, int val)
{
	p->pae[pos] = val;
	return 0;
}
int return_len(Player *p)
{
	return p->paelen;
}

void Output(Player *p)
{
	if (!strcmp(p->name,"player1")) {
		printf("플레이어 1 가지고 있는 패 : \n");
		for (int i = 0; i < p->paelen; i++)
			printf("%d\t", p->pae[i]);
	}
	else if (!strcmp(p->name, "player2")) {
		printf("플레이어 2 가지고 있는 패 : \n");
		for (int i = 0; i < p->paelen; i++)
			printf("%d\t", p->pae[i]);
	}
	printf("\n\n");
}

void OpenPae_Add(Pae *p,int val)
{
	if (p->openpaelen >= 100)
		printf("Can not add Value in List\n");
	else
	{
		p->Openpae[p->openpaelen] = val;
		p->openpaelen += 1;
	}
}

void OpenPae_Output(Pae *p)
{

	printf("바닥에 깔린 패 : \n");
	for (int i = 0; i < p->openpaelen; i++)
		printf("%d\t", p->Openpae[i]);

	printf("\n\n");
}

int OpenFind_adr(Pae *p,int val)
{
	int j = -1;
	for (int i = 0; i < p->openpaelen ; i++)
	{
		if (p->Openpae[i] == val) {
			//printf("오픈된 패  값: %d  배열 %d번째 요소\n", val, i);
			j = i;			
		}
	}
	return j;

}
int OpenFind_value(Pae *p, int pos)
{
	return p->Openpae[pos];

}
void OpenErase(Pae *p, int pos)
{
	if (p->openpaelen == 0) {
		printf("openpae is empty\n");
		return;
	}
	if (pos > p->openpaelen) {
		printf("openpae is not data\n");
		return;
	}
	for (int i = pos; i < p->openpaelen - 1; i++)
		p->Openpae[i] = p->Openpae[i + 1];
	p->openpaelen -= 1;
}

int OpenReplace(Pae *p, int pos, int val)
{
	p->Openpae[pos] = val;
	return 0;
}

void ScorePae_Add(Player *p, int val)
{
	if (p->scorepalen >= 100)
		printf("Can not add Value in List\n");
	else
	{
		p->Scorepae[p->scorepalen] = val;
		p->scorepalen += 1;
	}
}
int ScorePae_value(Player *p, int pos)
{
	return p->Scorepae[pos];
}
int ScorePae_len(Player *p)
{
	return p->scorepalen;
}
void ScorePae_Del(Player *p)
{
	if (p->scorepalen ==0)
		printf("not Exist in List\n");
	else
	{
		p->scorepalen -= 1;
	}
}
void ScorePae_Output(Player *p)
{

	printf("점수 패 : \n");
	for (int i = 0; i < p->scorepalen; i++)
		printf("%d\t", p->Scorepae[i]);

	printf("\n\n");
}
