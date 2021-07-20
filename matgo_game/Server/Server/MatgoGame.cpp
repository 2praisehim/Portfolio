#include "Matgo.h"
#include "server.h"

extern int User1;
extern int User2;
extern Player player1;
extern Player player2;
extern Pae Cpae;

 int Totalpae[50];						//��� ��
 int Point = 0;							//�������� ���� ��ġ
void Start_Game()
{
	int overlap;
	srand((unsigned)time(NULL));
	for (int i = 0; i < 50; i++) {
		while (1) {
			Totalpae[i] = rand() % 50;
			overlap = 0;
			for (int j = 0; j < i; ++j)
			{
				if (Totalpae[j] == Totalpae[i])
				{
					overlap = 1;
					break;
				}
			}
			if (!overlap)
				break;
		}
	}
	strcpy(player1.name, "player1");
	strcpy(player2.name, "player2");
	for (int i = 0; i < 10; i++)
		Add_First(&player1, Totalpae[i]);
	for (int i = 10; i < 20; i++)
		Add_First(&player2, Totalpae[i]);
	for (int i = 20; i < 28; i++) 		
		OpenPae_Add(&Cpae, Totalpae[i]);
	
	Output(&player1);
	Output(&player2);
	//OpenPae_Output(&Cpae);
	
	char msg[50];

	sprintf(msg, "%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d","INIT","MINE", player1.pae[0], player1.pae[1], player1.pae[2], player1.pae[3], player1.pae[4],
		player1.pae[5], player1.pae[6], player1.pae[7], player1.pae[8], player1.pae[9]);
	Send_Player1(msg);

	sprintf(msg, "%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d","INIT","MINE", player2.pae[0], player2.pae[1], player2.pae[2], player2.pae[3], player2.pae[4],
		player2.pae[5], player2.pae[6], player2.pae[7], player2.pae[8], player2.pae[9]);

	Send_Player2(msg);

	Point = 28;
	int Bonus1 = 48;
	int Bonus2 = 49;
	if (OpenFind_adr(&Cpae, Bonus1) != -1)
	{
		int k = OpenFind_adr(&Cpae, Bonus1);
		printf("���ʽ�1 ����\n");
		OpenReplace(&Cpae, k, Totalpae[Point]);
		Point++;
		sprintf(msg, "%s,%d","BONUS", Bonus1);
		Sleep(10);
		Send_Player1(msg);
		sprintf(msg, "%s,%d", "OPBONUS", Bonus1);
		Sleep(10);
		Send_Player2(msg);
	}		
	printf("���� �� ����Ʈ= %d\n ",Point);
	if (OpenFind_adr(&Cpae, Bonus2) != -1)
	{
		int k = OpenFind_adr(&Cpae, Bonus2);
		printf("���ʽ�2 ����\n");
		OpenReplace(&Cpae, k, Totalpae[Point]);
		Point++;
		sprintf(msg, "%s,%d", "BONUS", Bonus2);
		Sleep(10);
		Send_Player1(msg);
		sprintf(msg, "%s,%d", "OPBONUS", Bonus2);
		Sleep(10);
		Send_Player2(msg);
	}		
	OpenPae_Output(&Cpae);
	printf("���� �� ����Ʈ= %d\n ", Point);
	sprintf(msg, "%s,%s,%d,%d,%d,%d,%d,%d,%d,%d", "INIT", "OPEN", Cpae.Openpae[0], Cpae.Openpae[1], Cpae.Openpae[2], Cpae.Openpae[3], Cpae.Openpae[4],
		Cpae.Openpae[5], Cpae.Openpae[6], Cpae.Openpae[7]);
	Sleep(100);
	Send_Player1(msg);
	Send_Player2(msg);

	
}

void SelectPae(char msg[], int use)					//�÷��̾ ������ �п� ���и� ���� �� ���÷��̾� �����п� �߰�
{
	char *split;
	int data[2];
	char scpae[30];
	split = strtok(msg, ",");	
	for (int i = 0; i < 2;i++) {
			data[i]=atoi(split);
			split = strtok(NULL, ",");
		}
	if (use == User1)
	{
		ScorePae_Add(&player1, data[0]);					//7: ������ open�п� �ڽ��� ��1���� �����з� �߰�
		ScorePae_Add(&player1, data[1]);
		Erase(&player1, Find_Value(&player1, data[0]));		//6: �ڽ����� 1���� ����
		OpenErase(&Cpae, OpenFind_adr(&Cpae, data[1]));		//6: ������ open�и� 1�� ����
		Output(&player1);
		ScorePae_Output(&player1);
		sprintf(scpae, "%s,%d,%d", "OPSCORE", data[0], data[1]);		//������ ������ �и� ����
		Sleep(10);
		Send_Player2(scpae);								//9: OPSCORE,���� ������, ������ open��
	}
	else if (use == User2)
	{
		ScorePae_Add(&player2, data[0]);
		ScorePae_Add(&player2, data[1]);
		Erase(&player2, Find_Value(&player2, data[0]));
		OpenErase(&Cpae, OpenFind_adr(&Cpae, data[1]));
		Output(&player2);
		ScorePae_Output(&player2);
		sprintf(scpae, "%s,%d,%d", "OPSCORE", data[0], data[1]);		//������ ������ �и� ����
		Sleep(10);
		Send_Player1(scpae);
	}
	OpenPae_Output(&Cpae);
	Openpae_Update(use);												//10: ���ο� open�� 1�� �߰�
}

void NSelectPae(char msg[], int use)
{
	char message[50];
	int pnum = atoi(msg);
	if (use == User1)
	{
		Erase(&player1, Find_Value(&player1, pnum));					//2-3�÷��̾� �ڽ��� �� 1���� ����
		OpenPae_Add(&Cpae, pnum);										//2-3�÷��̾� �ڽ��� �� 1���� open�п� �߰�
		if (Totalpae[Point] == 48 || Totalpae[Point] == 49)
		{
			Sleep(10);
			sprintf(msg, "%s,%d", "BONUS", Totalpae[Point]);
			Send_Player1(msg);
			Sleep(10);
			sprintf(msg, "%s,%d", "OPBONUS", Totalpae[Point]);
			Send_Player2(msg);
			int num = ScorePae_value(&player2, ScorePae_len(&player2)-1);			//���� �� ��������
			ScorePae_Del(&player2);
			ScorePae_Add(&player1, num);
			ScorePae_Add(&player1, Totalpae[Point]);
			Point++;
		}	
		printf("���� �� ����Ʈ= %d\n ", Point);
		OpenPae_Add(&Cpae, Totalpae[Point]);							//2-4: ���ο� open �� 1�� �߰�
		Point++;
		OpenPae_Output(&Cpae);
		Sleep(10);
		sprintf(message, "%s,%d", "OPEN", Totalpae[Point - 1]);
		Send_Player1(message);												//2-5: OPEN,���ο� open��
		Sleep(10);
		sprintf(message, "%s,%d,%d", "NOPOPEN",pnum,Totalpae[Point - 1]);
		Send_Player2(message);												//2-6: OPOPEN,���ο� open��
	}
	else if (use == User2)
	{
		Erase(&player2, Find_Value(&player2, pnum));					//2-3�÷��̾� �ڽ��� �� 1���� ����
		OpenPae_Add(&Cpae, pnum);										//2-3�÷��̾� �ڽ��� �� 1���� open�п� �߰�

		if (Totalpae[Point] == 48 || Totalpae[Point] == 49)
		{
			Sleep(10);
			sprintf(msg, "%s,%d", "BONUS", Totalpae[Point]);
			Send_Player2(msg);
			Sleep(10);
			sprintf(msg, "%s,%d", "OPBONUS", Totalpae[Point]);
			Send_Player1(msg);
			int num = ScorePae_value(&player1, ScorePae_len(&player1)-1);			//���� �� ��������
			ScorePae_Del(&player1);
			ScorePae_Add(&player2, num);
			ScorePae_Add(&player2, Totalpae[Point]);
			Point++;
		}
		printf("���� �� ����Ʈ= %d\n ", Point);
		OpenPae_Add(&Cpae, Totalpae[Point]);							//2-4: ���ο� open �� 1�� �߰�
		Point++;
		OpenPae_Output(&Cpae);
		Sleep(10);
		sprintf(message, "%s,%d", "OPEN", Totalpae[Point - 1]);
		Send_Player2(message);												//2-5: OPEN,���ο� open��
		Sleep(10);
		sprintf(message, "%s,%d,%d", "NOPOPEN", pnum,Totalpae[Point - 1]);
		Send_Player1(message);												//2-6: OPOPEN,���ο� open��
	}
	printf("���� �� ����Ʈ= %d\n ", Point);
}
void Openpae_Update(int use)											//���� �п��� 1���� ���� �ٴڿ� ���´�
{
	char msg[20];
	if (Totalpae[Point]==48||Totalpae[Point]==49)							//1���� �̾����� ���ʽ� ���϶�
	{
		if (use == User1) {
			Sleep(10);
			sprintf(msg, "%s,%d", "BONUS", Totalpae[Point]);
			Send_Player1(msg);
			Sleep(10);
			sprintf(msg, "%s,%d", "OPBONUS", Totalpae[Point]);
			Send_Player2(msg);
			int num = ScorePae_value(&player2, ScorePae_len(&player2)-1);			//���� �� ��������
			ScorePae_Del(&player2);
			ScorePae_Add(&player1, num);
			ScorePae_Add(&player1, Totalpae[Point]);
			Point++;
		}
		else if (use == User2)
		{
			Sleep(10);
			sprintf(msg, "%s,%d", "BONUS", Totalpae[Point]);
			Send_Player2(msg);
			Sleep(10);
			sprintf(msg, "%s,%d", "OPBONUS", Totalpae[Point]);
			Send_Player1(msg);
			int num = ScorePae_value(&player1, ScorePae_len(&player1) - 1);			//���� �� ��������
			ScorePae_Del(&player1);
			ScorePae_Add(&player2, num);
			ScorePae_Add(&player2, Totalpae[Point]);
			Point++;
		}
	}
	printf("���� �� ����Ʈ= %d\n ", Point);
		OpenPae_Add(&Cpae, Totalpae[Point]);							//10: ���ο� open �� 1�� �߰�
		Point++;
		OpenPae_Output(&Cpae);
		Sleep(10);
		sprintf(msg, "%s,%d", "OPEN", Totalpae[Point - 1]);
		if (use == User1) {
			Send_Player1(msg);												//11: ���ο� open�� 1�� �÷��̾�� ����
			sprintf(msg, "%s,%d", "OPOPEN", Totalpae[Point - 1]);
			Send_Player2(msg);												//12: ������ �ٴڿ� ���� �߰��� 1���� ����
		}
		else if (use == User2)
		{
			Send_Player2(msg);
			sprintf(msg, "%s,%d", "OPOPEN", Totalpae[Point - 1]);			//������ �ٴڿ� ���� �߰��� 1���� ����
			Send_Player1(msg);
		}
		printf("���� �� ����Ʈ= %d\n ", Point);
}

void Add_Score(char msg[], int use)									//���Ӱ� �ٴڿ� ���� �а� �߰� ������ �����Ѱ��
{
	char *split;
	int data[2];
	char message[20];
	split = strtok(msg, ",");
	for (int i = 0; i < 2; i++) {
		data[i] = atoi(split);
		split = strtok(NULL, ",");
	}

	if (use == User1)
	{
		for (int i = 0; i < 2; i++)
		{
			ScorePae_Add(&player1, data[i]);								//17: �÷��̾� �����п� ������ open��, ���ο� open�� 1�� �߰�
			OpenErase(&Cpae, OpenFind_adr(&Cpae, data[i]));					//16: ���ο� open��, ������ open�� 1�� ����
		}		
		sprintf(message, "%s,%d,%d", "OPADD", data[0], data[1]);					//������ �߰� ������ ��� ������ ���� �и� ����
		Sleep(10);
		Send_Player2(message);												//18 OPADD,���ο� open��, ������ open�� 
		Output(&player1);
		ScorePae_Output(&player1);
	}
	else if (use == User2)
	{
		for (int i = 0; i < 2; i++)
		{
			ScorePae_Add(&player2, data[i]);
			OpenErase(&Cpae, OpenFind_adr(&Cpae, data[i]));
		}
		sprintf(message, "%s,%d,%d", "OPADD", data[0], data[1]);					//������ �߰� ������ ��� ������ ���� �и� ����	
		Sleep(10);
		Send_Player1(message);
		Output(&player2);
		ScorePae_Output(&player2);
	}
	OpenPae_Output(&Cpae);
}

void SelectBonus(char msg[], int use)
{
	char message[50];
	int bnum = atoi(msg);
	if (use == User1)
	{
		Erase(&player1, Find_Value(&player1, bnum));
		ScorePae_Add(&player1, bnum);
		Add_First(&player1, Totalpae[Point]);
		int num = ScorePae_value(&player2, ScorePae_len(&player2) - 1);			//���� �� ��������
		ScorePae_Del(&player2);
		ScorePae_Add(&player1, num);
		sprintf(message, "%s,%d,%d","NEWPAE", Totalpae[Point],bnum);
		Sleep(10);
		Send_Player1(message);
		sprintf(message, "%s,%d", "OPBONUS", bnum);
		Sleep(10);
		Send_Player2(message);
		Point++;
		Output(&player1);
		ScorePae_Output(&player1);
	}
	else if (use == User2)
	{
		Erase(&player2, Find_Value(&player2, bnum));
		ScorePae_Add(&player2, bnum);
		Add_First(&player2, Totalpae[Point]);
		int num = ScorePae_value(&player1, ScorePae_len(&player1) - 1);			//���� �� ��������
		ScorePae_Del(&player1);
		ScorePae_Add(&player2, num);
		sprintf(message, "%s,%d,%d","NEWPAE", Totalpae[Point],bnum);
		Sleep(10);
		Send_Player2(message);
		sprintf(message, "%s,%d", "OPBONUS", bnum);
		Sleep(10);
		Send_Player1(message);
		Point++;
		Output(&player2);
		ScorePae_Output(&player2);
	}
	printf("���� �� ����Ʈ= %d\n ", Point);
}

void Stop(int use)
{
	char msg[10];
	char win[] = "WIN";
	char lose[] = "LOSE";
	if (use == User1)
	{
		Sleep(10);
		sprintf(msg, "%s", win);
		Send_Player1(msg);
		Sleep(10);
		sprintf(msg, "%s", lose);
		Send_Player2(msg);
	}
	else if (use == User2)
	{
		Sleep(10);
		sprintf(msg, "%s", win);
		Send_Player2(msg);
		Sleep(10);
		sprintf(msg, "%s", lose);
		Send_Player1(msg);
	}
}

void Gobak(int use)
{
	char msg[10];
	char win[] = "WIN";
	char lose[] = "LOSE";
	if (use == User1)
	{
		Sleep(10);
		sprintf(msg, "%s", lose);
		Send_Player1(msg);
		Sleep(10);
		sprintf(msg, "%s", win);
		Send_Player2(msg);
	}
	else if (use == User2)
	{
		Sleep(10);
		sprintf(msg, "%s", lose);
		Send_Player2(msg);
		Sleep(10);
		sprintf(msg, "%s", win);
		Send_Player1(msg);
	}
}