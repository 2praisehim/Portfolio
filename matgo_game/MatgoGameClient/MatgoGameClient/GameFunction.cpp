#include "stdafx.h"
#include "GameFunction.h"

int *BITmap;
int *Picture;
int *Openpicture;

Player player;											//플레이어 패 구조체
HBITMAP hbit;											//자신의 패 10장 비트맵 핸들
HBITMAP openhbit;										//바닥에 놓일 패 8장 비트맵 핸들
extern CMatgoGameClientDlg *pMainDlg;					//메인 다이얼로그 컨트롤
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
		player.Pae_Add(atoi(split));			//자신의 패 10장 추가
		hbit = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(BITmap[atoi(split)]));		//픽쳐컨트롤를 이용해 비트맵 이미지 출력(자신의 패)
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
		openhbit = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(BITmap[atoi(split)]));		//픽쳐컨트롤를 이용해 비트맵 이미지 출력(바닥에 놓인패)
		CStatic *openpic= (CStatic *)pMainDlg->GetDlgItem(Openpicture[i]);
		openpic->SetBitmap(openhbit);
		split = strtok(NULL, ",");
	}
}

void GameFunction::Add_Bonus(char msg[])					//보너스 받았을때
{
	char *split;
	split = strtok(msg, ",");
	while (split != NULL) {
		ScoreAdd(atoi(split));
		split = strtok(NULL, ",");
	}
	if (player.OpPeascore_len() > 0)			//상대방 피가 존재 할때 피를 한장 가지고 온다
	{
		int pnum=player.OpPeascore_value(player.OpPeascore_len() - 1);
		player.OpPaescore_Del();
		player.oppeacount -= 1;
		if (pnum == 32 || pnum == 41 || pnum == 47 || pnum == 48 || pnum == 49)		//쌍피일때
		{
			player.opssangpea -= 1;
		}
		ScoreAdd(pnum);
	}
	pMainDlg->Invalidate();
}

void GameFunction::Op_Bonus(char msg[])					//상대방이 보너스를 얻었을때 가지고 있는패를 넘김
{
	char *split;
	split = strtok(msg, ",");
	while (split != NULL) {
		OpScoreAdd(atoi(split));
		split = strtok(NULL, ",");
	}
	if (player.Peascore_len() > 0)
	{
		int pnum = player.Peascore_value(player.Peascore_len() - 1);		//상대방 점수패중 피를 1장 가져오며 상대 점수패에 피 1장 삭제
		player.Paescore_Del();
		player.peacount -= 1;
		if (pnum == 32 || pnum == 41 || pnum == 47 || pnum == 48 || pnum == 49)		//쌍피일때
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
	if (check != -1)											//12: 추가 득점 있을때
	{
		//추가 득점
		num2 = player.OpenFind_value(check);
		sprintf(message, "%s,%d,%d", "ADD", num, num2);
		Sleep(10);
		retval = send(sock, message, strlen(message), 0);		//15 ADD,새로운 바닥패1장,기존의 바닥패1장
		player.OpenErase(check);								//14:기존의 바닥패 1장 삭제
		ScoreAdd(num);								//13:기존의 바닥패 1장, 새로운 바닥패 1장 점수패로 추가
		ScoreAdd(num2);
	}
	else {													// 추가 득점 없을때
		player.OpenPae_Add(atoi(msg));						//12-1: 새로운 바닥패 1장을 받은걸로 바닥패에 추가
	}	
	OpenPaeUpdate();
	pMainDlg->Invalidate();
}

void GameFunction::SelectPae(int mine, int open)//플레이어가 선택한 패를 바닥에 깔린 패 삭제 함께 점수 패 추가 
{
	int a = mine;
	int b = open;
		int retval;
	    char msg[20];
		ScoreAdd(mine);				//4:자신의 패를 점수패로 추가
		ScoreAdd(open);				//4:기존의 바닥패를 점수패로 추가
		int pos = player.PaeFind_adr(mine);
		//player.PaeErase(pos);					//3 : 자신의 패 1장삭제
		pos = player.OpenFind_adr(open);
		player.OpenErase(pos);				//3: 기존의 바닥패 1장 삭제	
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
		OpScoreAdd(data[i]);							//9-1:기존의 바닥패, 상대방 소유패 1장씩 상대방 점수패에 추가
		split = strtok(NULL, ",");
	}
	player.OpenErase(player.OpenFind_adr(data[1]));		//9-2 기존의 바닥패를 바닥패에서 삭제
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
		player.OpenPae_Add(atoi(split));				//2-7 새로운 바닥패, 상대방 소유패를 바닥패에 추가
		split = strtok(NULL, ",");
	}
	OpenPaeUpdate();
	pMainDlg->Invalidate();
}

void GameFunction::OP_add(char msg[])					//상대방이 추가 득점 할때
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
	player.OpenPae_Add(mine);				//2-1 자신의 패1장을 open패 추가
	//player.PaeErase(player.PaeFind_value(mine));//2-1 자신의패 1장을 삭제
	sprintf(msg, "%s,%d", "NSELECT", mine);
	Sleep(10);
	retval = send(sock, msg, strlen(msg), 0);//2-2 NSELECT,자신의패 1장
	pMainDlg->Invalidate();
}

void GameFunction::SelectBonus(int bonus)				//선택한 패가 보너스패일때, 서버로 전송
{
	char msg[20];
	sprintf(msg, "%s,%d", "SELBONUS", bonus);
	int retval = send(sock, msg, strlen(msg), 0);
	pMainDlg->Invalidate();
}

void GameFunction::NewPae(char msg[])				//선택한 패가 보너스패일때 서버로부터 묶음패를 1장을 받아 자신의 패로 추가
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
	hbit = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(BITmap[data[0]]));		//픽쳐컨트롤를 이용해 비트맵 이미지 출력(자신의 패)
	CStatic *pic = (CStatic *)pMainDlg->GetDlgItem(Picture[pos]);
	pic->SetBitmap(hbit);
	if (player.OpPeascore_len() > 0)			//상대방 피가 존재 할때 피를 한장 가지고 온다
	{
		int pnum = player.OpPeascore_value(player.OpPeascore_len() - 1);
		player.OpPaescore_Del();
		player.oppeacount -= 1;
		if (pnum == 32 || pnum == 41 || pnum == 47 || pnum == 48 || pnum == 49)		//쌍피일때
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




void GameFunction::ScoreAdd(int pae)					//득점시 자신의 점수패 추가
{
	if (pae == 0 || pae == 8 || pae == 28 || pae == 40 || pae == 44)			//광일때
	{
		player.Gwang_Add(pae);
		player.gwangcount++;
		if (pae == 44)
			player.bigwang = true;
	}
	
	else if (pae == 1 || pae == 5 || pae == 9 || pae == 13 || pae == 17 || pae == 21 || pae == 25 || pae == 33 || pae == 37 || pae == 45)		//단일때
	{
		player.Dan_Add(pae);
		player.dancount++;
		if (pae == 1 || pae == 5 || pae == 9) {		//홍단패 일때
			player.hongdancount++;
			if (player.hongdancount == 3)
				player.hongdan = true;
		}
		else if (pae == 13 || pae == 17 || pae == 25)			//초단패 일때
		{
			player.chodancount++;
			if (player.chodancount == 3)
				player.chodan = true;
		}
		else if (pae == 21 || pae == 33 || pae == 37)			//청단패 일때
		{
			player.chungdancount++;
			if (player.chungdancount == 3)
				player.chungdan = true;
		}
	}
	
	else if (pae == 4 || pae == 12 || pae == 16 || pae == 20 || pae == 24 || pae == 29 || pae == 36 || pae == 46)	//멍(열끗)패 일때
	{
		player.Mung_Add(pae);
		player.mungcount++;
		if (pae == 4 || pae == 12 || pae == 29)		//고도리 패 일때
		{
			player.godoricount++;
			if (player.godoricount == 3)
				player.godori = true;
		}
	}
	
	else
	{														//피 일대
		player.Peascore_Add(pae);
		player.peacount++;
		if (pae == 32 || pae == 41 || pae == 47 || pae == 48 || pae == 49)		//쌍피 일때
			player.ssangpea++;
	}
}

void GameFunction::OpScoreAdd(int pae)						//상대방 점수패 추가
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

void GameFunction::OpenPaeUpdate()					//바닥패가 새롭게 업데이트 될때 최신화 함수	
{
	for (int i = 0; i < 11; i++)
	{
		CStatic *pic = (CStatic *)pMainDlg->GetDlgItem(Openpicture[i]);
		pic->SetBitmap(NULL);
	}
	for (int i = 0; i < player.OpenPae_len(); i++)
	{
		openhbit = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(BITmap[player.OpenFind_value(i)]));		//픽쳐컨트롤를 이용해 비트맵 이미지 출력(바닥에 놓인패)
		CStatic *openpic = (CStatic *)pMainDlg->GetDlgItem(Openpicture[i]);
		openpic->SetBitmap(openhbit);
	}
	pMainDlg->Invalidate();
}

int GameFunction::myscore()					//내점수 계산
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

int GameFunction::opscore()						//상대 점수 계산
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



