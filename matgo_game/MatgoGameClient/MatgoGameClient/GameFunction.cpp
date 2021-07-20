#include "stdafx.h"
#include "GameFunction.h"

int *BITmap;
int *Picture;
int *Openpicture;

Player player;											//�÷��̾� �� ����ü
HBITMAP hbit;											//�ڽ��� �� 10�� ��Ʈ�� �ڵ�
HBITMAP openhbit;										//�ٴڿ� ���� �� 8�� ��Ʈ�� �ڵ�
extern CMatgoGameClientDlg *pMainDlg;					//���� ���̾�α� ��Ʈ��
extern SOCKET sock;
GameFunction::GameFunction(int bit[],int pic[],int opic[])
{
	BITmap = bit;
	Picture =pic;
	Openpicture = opic;
}


GameFunction::~GameFunction()
{
}

void GameFunction::init_pae(char msg[])
{
	
	
	char *split;
	split = strtok(msg, ",");
	for (int i = 0; i < 10; i++) {
		player.Pae_Add(atoi(split));			//�ڽ��� �� 10�� �߰�
		hbit = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(BITmap[atoi(split)]));		//������Ʈ�Ѹ� �̿��� ��Ʈ�� �̹��� ���(�ڽ��� ��)
		CStatic *pic= (CStatic *)pMainDlg->GetDlgItem(Picture[i]);
		pic->SetBitmap(hbit);
		split = strtok(NULL, ",");
	}
	
	
}

void GameFunction::init_openpae(char msg[])
{
	char *split;
	split = strtok(msg, ",");
	for (int i = 0; i < 8; i++) {
		player.OpenPae_Add(atoi(split));
		openhbit = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(BITmap[atoi(split)]));		//������Ʈ�Ѹ� �̿��� ��Ʈ�� �̹��� ���(�ٴڿ� ������)
		CStatic *openpic= (CStatic *)pMainDlg->GetDlgItem(Openpicture[i]);
		openpic->SetBitmap(openhbit);
		split = strtok(NULL, ",");
	}
}

void GameFunction::Add_Bonus(char msg[])					//���ʽ� �޾�����
{
	char *split;
	split = strtok(msg, ",");
	while (split != NULL) {
		ScoreAdd(atoi(split));
		split = strtok(NULL, ",");
	}
	if (player.OpPeascore_len() > 0)			//���� �ǰ� ���� �Ҷ� �Ǹ� ���� ������ �´�
	{
		int pnum=player.OpPeascore_value(player.OpPeascore_len() - 1);
		player.OpPaescore_Del();
		player.oppeacount -= 1;
		if (pnum == 32 || pnum == 41 || pnum == 47 || pnum == 48 || pnum == 49)		//�����϶�
		{
			player.opssangpea -= 1;
		}
		ScoreAdd(pnum);
	}
	pMainDlg->Invalidate();
}

void GameFunction::Op_Bonus(char msg[])					//������ ���ʽ��� ������� ������ �ִ��и� �ѱ�
{
	char *split;
	split = strtok(msg, ",");
	while (split != NULL) {
		OpScoreAdd(atoi(split));
		split = strtok(NULL, ",");
	}
	if (player.Peascore_len() > 0)
	{
		int pnum = player.Peascore_value(player.Peascore_len() - 1);		//���� �������� �Ǹ� 1�� �������� ��� �����п� �� 1�� ����
		player.Paescore_Del();
		player.peacount -= 1;
		if (pnum == 32 || pnum == 41 || pnum == 47 || pnum == 48 || pnum == 49)		//�����϶�
		{
			player.ssangpea -= 1;
		}
		OpScoreAdd(pnum);
	}
	pMainDlg->Invalidate();
}




void GameFunction::Open_Updatae(char msg[])
{
	int retval;
	int num = atoi(msg);
	int num2;
	char message[20];
	int check = player.OpenFind_adr(num);
	if (check != -1)											//12: �߰� ���� ������
	{
		//�߰� ����
		num2 = player.OpenFind_value(check);
		sprintf(message, "%s,%d,%d", "ADD", num, num2);
		Sleep(10);
		retval = send(sock, message, strlen(message), 0);		//15 ADD,���ο� �ٴ���1��,������ �ٴ���1��
		player.OpenErase(check);								//14:������ �ٴ��� 1�� ����
		ScoreAdd(num);								//13:������ �ٴ��� 1��, ���ο� �ٴ��� 1�� �����з� �߰�
		ScoreAdd(num2);
	}
	else {													// �߰� ���� ������
		player.OpenPae_Add(atoi(msg));						//12-1: ���ο� �ٴ��� 1���� �����ɷ� �ٴ��п� �߰�
	}	
	OpenPaeUpdate();
	pMainDlg->Invalidate();
}

void GameFunction::SelectPae(int mine, int open)//�÷��̾ ������ �и� �ٴڿ� �� �� ���� �Բ� ���� �� �߰� 
{
	int a = mine;
	int b = open;
		int retval;
	    char msg[20];
		ScoreAdd(mine);				//4:�ڽ��� �и� �����з� �߰�
		ScoreAdd(open);				//4:������ �ٴ��и� �����з� �߰�
		int pos = player.PaeFind_adr(mine);
		//player.PaeErase(pos);					//3 : �ڽ��� �� 1�����
		pos = player.OpenFind_adr(open);
		player.OpenErase(pos);				//3: ������ �ٴ��� 1�� ����	
		sprintf(msg, "%s,%d,%d", "SELECT", mine, open);
		retval = send(sock, msg, strlen(msg), 0);
		pMainDlg->Invalidate();
}

void GameFunction::OP_SCore(char msg[])
{
	char *split;
	split = strtok(msg, ",");
	int data[2];
	for (int i = 0; i < 2; i++)
	{
		data[i] = atoi(split);
		OpScoreAdd(data[i]);							//9-1:������ �ٴ���, ���� ������ 1�徿 ���� �����п� �߰�
		split = strtok(NULL, ",");
	}
	player.OpenErase(player.OpenFind_adr(data[1]));		//9-2 ������ �ٴ��и� �ٴ��п��� ����
	pMainDlg->Invalidate();
}

void GameFunction::OP_open(char msg[])
{
	player.OpenPae_Add(atoi(msg));
	OpenPaeUpdate();
	pMainDlg->Invalidate();
}

void GameFunction::NOP_open(char msg[])
{
	char *split;
	split = strtok(msg, ",");
	for (int i = 0; i < 2; i++)
	{
		player.OpenPae_Add(atoi(split));				//2-7 ���ο� �ٴ���, ���� �����и� �ٴ��п� �߰�
		split = strtok(NULL, ",");
	}
	OpenPaeUpdate();
	pMainDlg->Invalidate();
}

void GameFunction::OP_add(char msg[])					//������ �߰� ���� �Ҷ�
{
	char *split;
	split = strtok(msg, ",");
	int data;
	for (int i = 0; i < 2; i++)
	{
		data = atoi(split);
		OpScoreAdd(data);
		player.OpenErase(player.OpenFind_adr(data));
		split = strtok(NULL, ",");
	}
	pMainDlg->Invalidate();
	OpenPaeUpdate();
}

void GameFunction::NSelectPae(int mine)
{
	int retval;
	char msg[50];
	player.OpenPae_Add(mine);				//2-1 �ڽ��� ��1���� open�� �߰�
	//player.PaeErase(player.PaeFind_value(mine));//2-1 �ڽ����� 1���� ����
	sprintf(msg, "%s,%d", "NSELECT", mine);
	Sleep(10);
	retval = send(sock, msg, strlen(msg), 0);//2-2 NSELECT,�ڽ����� 1��
	pMainDlg->Invalidate();
}

void GameFunction::SelectBonus(int bonus)				//������ �а� ���ʽ����϶�, ������ ����
{
	char msg[20];
	sprintf(msg, "%s,%d", "SELBONUS", bonus);
	int retval = send(sock, msg, strlen(msg), 0);
	pMainDlg->Invalidate();
}

void GameFunction::NewPae(char msg[])				//������ �а� ���ʽ����϶� �����κ��� �����и� 1���� �޾� �ڽ��� �з� �߰�
{
	char *split;
	int data[2];
	split = strtok(msg, ",");
	for (int i = 0; i < 2; i++)
	{
		data[i]= atoi(split);
		split = strtok(NULL, ",");
	}
	int pos = player.PaeFind_adr(data[1]);
	player.PaeReplace(data[0], pos);
	ScoreAdd(data[1]);
	hbit = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(BITmap[data[0]]));		//������Ʈ�Ѹ� �̿��� ��Ʈ�� �̹��� ���(�ڽ��� ��)
	CStatic *pic = (CStatic *)pMainDlg->GetDlgItem(Picture[pos]);
	pic->SetBitmap(hbit);
	if (player.OpPeascore_len() > 0)			//���� �ǰ� ���� �Ҷ� �Ǹ� ���� ������ �´�
	{
		int pnum = player.OpPeascore_value(player.OpPeascore_len() - 1);
		player.OpPaescore_Del();
		player.oppeacount -= 1;
		if (pnum == 32 || pnum == 41 || pnum == 47 || pnum == 48 || pnum == 49)		//�����϶�
		{
			player.opssangpea -= 1;
		}
		ScoreAdd(pnum);
	}
	pMainDlg->Invalidate();
}

void GameFunction::Stop()
{
	char STOP[] = "STOP";
	char msg[10];
	sprintf(msg, "%s",STOP);
	int retval = send(sock, msg, strlen(msg), 0);
}

void GameFunction::Gobak()
{
	char GOBAK[] = "GOBAK";
	char msg[10];
	sprintf(msg, "%s", GOBAK);
	int retval = send(sock, msg, strlen(msg), 0);
}




void GameFunction::ScoreAdd(int pae)					//������ �ڽ��� ������ �߰�
{
	if (pae == 0 || pae == 8 || pae == 28 || pae == 40 || pae == 44)			//���϶�
	{
		player.Gwang_Add(pae);
		player.gwangcount++;
		if (pae == 44)
			player.bigwang = true;
	}
	
	else if (pae == 1 || pae == 5 || pae == 9 || pae == 13 || pae == 17 || pae == 21 || pae == 25 || pae == 33 || pae == 37 || pae == 45)		//���϶�
	{
		player.Dan_Add(pae);
		player.dancount++;
		if (pae == 1 || pae == 5 || pae == 9) {		//ȫ���� �϶�
			player.hongdancount++;
			if (player.hongdancount == 3)
				player.hongdan = true;
		}
		else if (pae == 13 || pae == 17 || pae == 25)			//�ʴ��� �϶�
		{
			player.chodancount++;
			if (player.chodancount == 3)
				player.chodan = true;
		}
		else if (pae == 21 || pae == 33 || pae == 37)			//û���� �϶�
		{
			player.chungdancount++;
			if (player.chungdancount == 3)
				player.chungdan = true;
		}
	}
	
	else if (pae == 4 || pae == 12 || pae == 16 || pae == 20 || pae == 24 || pae == 29 || pae == 36 || pae == 46)	//��(����)�� �϶�
	{
		player.Mung_Add(pae);
		player.mungcount++;
		if (pae == 4 || pae == 12 || pae == 29)		//���� �� �϶�
		{
			player.godoricount++;
			if (player.godoricount == 3)
				player.godori = true;
		}
	}
	
	else
	{														//�� �ϴ�
		player.Peascore_Add(pae);
		player.peacount++;
		if (pae == 32 || pae == 41 || pae == 47 || pae == 48 || pae == 49)		//���� �϶�
			player.ssangpea++;
	}
}

void GameFunction::OpScoreAdd(int pae)						//���� ������ �߰�
{
	if (pae == 0 || pae == 8 || pae == 28 || pae == 40 || pae == 44)
	{
		player.OpGwang_Add(pae);
		player.opgwangcount++;
		if (pae == 44)
			player.opbigwang = true;
	}
	else if (pae == 1 || pae == 5 || pae == 9 || pae == 13 || pae == 17 || pae == 21 || pae == 25 || pae == 33 || pae == 37 || pae == 45)
	{
		player.OpDan_Add(pae);
		player.opdancount++;
		if (pae == 1 || pae == 5 || pae == 9) {
			player.ophongdancount++;
			if (player.ophongdancount == 3)
				player.ophongdan = true;
		}
		else if (pae == 13 || pae == 17 || pae == 25)
		{
			player.opchodancount++;
			if (player.opchodancount == 3)
				player.opchodan = true;
		}
		else if (pae == 21 || pae == 33 || pae == 37)
		{
			player.opchungdancount++;
			if (player.opchungdancount == 3)
				player.opchungdan = true;
		}
	}
	else if (pae == 4 || pae == 12 || pae == 16 || pae == 20 || pae == 24 || pae == 29 || pae == 36 || pae == 46)
	{
		player.OpMung_Add(pae);
		player.opmungcount++;
		if (pae == 4 || pae == 12 || pae == 29)
		{
			player.opgodoricount++;
			if (player.opgodoricount == 3)
				player.opgodori = true;
		}
	}
	else
	{
		player.OpPeascore_Add(pae);
		player.oppeacount++;
		if (pae == 32 || pae == 41 || pae == 47 || pae == 48 || pae == 49)
			player.opssangpea++;
	}
}

void GameFunction::OpenPaeUpdate()					//�ٴ��а� ���Ӱ� ������Ʈ �ɶ� �ֽ�ȭ �Լ�	
{
	for (int i = 0; i < 11; i++)
	{
		CStatic *pic = (CStatic *)pMainDlg->GetDlgItem(Openpicture[i]);
		pic->SetBitmap(NULL);
	}
	for (int i = 0; i < player.OpenPae_len(); i++)
	{
		openhbit = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(BITmap[player.OpenFind_value(i)]));		//������Ʈ�Ѹ� �̿��� ��Ʈ�� �̹��� ���(�ٴڿ� ������)
		CStatic *openpic = (CStatic *)pMainDlg->GetDlgItem(Openpicture[i]);
		openpic->SetBitmap(openhbit);
	}
	pMainDlg->Invalidate();
}

int GameFunction::myscore()					//������ ���
{
	player.mygwang = 0;
	if (player.gwangcount == 3)
	{
		if (player.bigwang)
			player.mygwang = 2;
		else
			player.mygwang = 3;
	}
	else if (player.gwangcount == 4)
		player.mygwang = 4;
	else if (player.gwangcount == 5)
		player.mygwang = 15;

	player.mydan = 0;
	if (player.chodan)
		player.mydan += 3;
	if (player.chungdan)
		player.mydan += 3;
	if (player.hongdan)
		player.mydan += 3;
	if (player.dancount>4)
		player.mydan += player.dancount - 4;

	player.mymung = 0;
	if (player.godori)
		player.mymung += 5;
	if (player.mungcount > 4)
		player.mymung += player.mungcount - 4;

	player.mypea = 0;
	player.mypea += player.ssangpea * 2;
	int temp = player.peacount - player.ssangpea;
	player.mypea += temp;
	if (player.mypea >= 10)
		player.mypea -= 9;
	else
		player.mypea = 0;

	return (player.mygwang+player.mymung+player.mydan+player.mypea);
}

int GameFunction::opscore()						//��� ���� ���
{
	player.opgwang = 0;
	if (player.opgwangcount == 3)
	{
		if (player.opbigwang)
			player.opgwang = 2;
		else
			player.opgwang = 3;
	}
	else if (player.opgwangcount == 4)
		player.opgwang = 4;
	else if (player.opgwangcount == 5)
		player.opgwang = 15;

	player.opdan = 0;
	if (player.opchodan)
		player.opdan += 3;
	if (player.opchungdan)
		player.opdan += 3;
	if (player.ophongdan)
		player.opdan += 3;
	if (player.opdancount>4)
		player.opdan += player.opdancount - 4;

	player.opmung = 0;
	if (player.opgodori)
		player.opmung += 5;
	if (player.opmungcount > 4)
		player.opmung += player.opmungcount - 4;

	player.oppea = 0;
	player.oppea += player.opssangpea * 2;
	int temp = player.oppeacount - player.opssangpea;
	player.oppea += temp;
	if (player.oppea >= 10)
		player.oppea -= 9;
	else
		player.oppea = 0;

	return (player.opgwang + player.opmung + player.opdan + player.oppea);
}



