#include "stdafx.h"
#include "Player.h"


Player::Player()
{
}


Player::~Player()
{
}

void Player::Pae_Add(int val)							//�ڽ��� �� �߰�
{
	if (paelen >= 100)
		AfxMessageBox(L"Can not Pae add Value in List");
	else
	{
		Pae[paelen] = val;
		paelen += 1;
	}
}

int Player::PaeFind_adr(int val)						//�ڽ��� ���� ã���� �ϴ� �� ������ �ּҰ� ��ȯ
{
	for (int i = 0; i < paelen; i++)
	{
		if (Pae[i] == val) {
			return i;
		}
	}
	
}

int Player::PaeFind_value(int pos)					//�ּҰ��� �ش��ϴ� �ڽ��� �� �����Ͱ� ��ȯ
{
	return Pae[pos];
}

void Player::PaeErase(int pos)						//�ڽ��� ���� ���ϴ� ������ ����
{
	if (paelen == 0) {
		AfxMessageBox(L"MyPaeList is empty");
		return;
	}
	if (pos >paelen) {
		AfxMessageBox(L"MyPae is not data");
		return;
	}
	for (int i = pos; i < paelen - 1; i++)
		Pae[i] = Pae[i + 1];
	paelen -= 1;
}

void Player::PaeReplace(int val, int pos)		//�ڽ��� ���� ������ ��ȯ
{
	Pae[pos] = val;
}


void Player::OpenPae_Add(int val)				//�ٴ��� �߰�
{
	if (openpaelen >= 100)
		AfxMessageBox(L"Can not OpenPae add Value in List");
	else
	{
	    Openpae[openpaelen] = val;
		openpaelen += 1;
	}
}

int Player::OpenFind_adr(int val)				//�ٴ����� ���ϴ� ������ �ּҰ� ��ȯ
{	
	int j = -1;
		for (int i = 0; i < openpaelen; i++)
		{
			if (Openpae[i] / 4 == val / 4) {
				j = i;
			}
		}
	return j;
}

int Player::OpenFind_value(int pos)				//�ٴ����� �ּҰ��� �ش��ϴ� �����Ͱ� ��ȯ
{
	return Openpae[pos];
}

void Player::OpenErase(int pos)					//�ٴ����� �ּҰ��� �ش��ϴ� ������ ����
{
	if (openpaelen == 0) {
		AfxMessageBox(L"OpenPae List is empty");
		return;
	}
	if (pos >openpaelen) {
		AfxMessageBox(L"Openpae is not data");
		return;
	}
	for (int i = pos; i <openpaelen - 1; i++)
		Openpae[i] = Openpae[i + 1];
	openpaelen -= 1;
}

int Player::OpenPae_len()						//�ٴ��� ���� ��ȯ
{
	return openpaelen;
}

int Player::OpenPaeFindCount(int val)			//���� ������ �ٴ��� ���� ��ȯ
{
	int j=0;
	for (int i = 0; i < openpaelen; i++)
	{
		if (Openpae[i] / 4 == val / 4) {
			j++;
		}
	}
	return j;
}

int * Player::OpenPaeFind_adr(int val)			//������ ������ ��� �ٴ��� �����Ͱ� ��ȯ
{
	static int tempdata[2];
	static int data[2];
	int count = 0;
	for (int i = 0; i < openpaelen; i++)
	{
		if (Openpae[i] / 4 == val / 4) {
			tempdata[count] = i;
			data[count] = OpenFind_value(tempdata[count]);
			count++;
		}
	}
	return data;
}

void Player::Gwang_Add(int val)					//������ �߰�(��)
{
	if (Gwanglen >= 100)
		AfxMessageBox(L"Can not MyGWangScorePae add Value in List");
	else
	{
		Gwangscore[Gwanglen] = val;
		Gwanglen += 1;
	}
}

int Player::Gwang_len()						//������ ����(��)
{
	return Gwanglen;
}

int Player::Gwang_value(int pos)			//������ �� �ּҰ��� �ش��ϴ� ������ (��)
{
	return Gwangscore[pos];
}

void Player::OpGwang_Add(int val)			//���� ������ �߰�(��)
{
	if (OpGwanglen >= 100)
		AfxMessageBox(L"Can not OpGWangScorePae add Value in List");
	else
	{
		OpGwangscore[OpGwanglen] = val;
		OpGwanglen += 1;
	}
}

int Player::OpGwang_len()					//���� ������ ����(��)
{
	return OpGwanglen;
}

int Player::OpGwang_value(int pos)			//���� �������� �ּҰ��� �ش��ϴ� ������(��)
{
	return OpGwangscore[pos];
}

void Player::Dan_Add(int val)
{
	if (Danlen >= 100)
		AfxMessageBox(L"Can not MyDanScorePae add Value in List");
	else
	{
		Danscore[Danlen] = val;
		Danlen += 1;
	}
}

int Player::Dan_len()
{
	return Danlen;
}

int Player::Dan_value(int pos)
{
	return Danscore[pos];
}

void Player::OpDan_Add(int val)
{
	if (OpDanlen >= 100)
		AfxMessageBox(L"Can not OpDanScorePae add Value in List");
	else
	{
		OpDanscore[OpDanlen] = val;
		OpDanlen += 1;
	}
}

int Player::OpDan_len()
{
	return OpDanlen;
}

int Player::OpDan_value(int pos)
{
	return OpDanscore[pos];
}

void Player::Mung_Add(int val)
{
	if (Munglen >= 100)
		AfxMessageBox(L"Can not MyMungScorePae add Value in List");
	else
	{
		Mungscore[Munglen] = val;
		Munglen += 1;
	}
}

int Player::Mung_len()
{
	return Munglen;
}

int Player::Mung_value(int pos)
{
	return Mungscore[pos];
}

void Player::OpMung_Add(int val)
{
	if (OpMunglen >= 100)
		AfxMessageBox(L"Can not OpMungScorePae add Value in List");
	else
	{
		OpMungscore[OpMunglen] = val;
		OpMunglen += 1;
	}
}

int Player::OpMung_len()
{
	return OpMunglen;
}

int Player::OpMung_value(int pos)
{
	return OpMungscore[pos];
}

void Player::Peascore_Add(int val)
{
	if (Pealen >= 100)
		AfxMessageBox(L"Can not MyPeaScorePae add Value in List");
	else
	{
		Peascore[Pealen] = val;
		Pealen += 1;
	}
}

int Player::Peascore_len()
{
	return Pealen;
}

int Player::Peascore_value(int pos)
{
	return Peascore[pos];
}

void Player::Paescore_Del()				//�ڽ��� �� 1�� ����
{
	Pealen -= 1;
}

void Player::OpPeascore_Add(int val)
{
	if (OpPealen >= 100)
		AfxMessageBox(L"Can not OpposePeaScorePae add Value in List");
	else
	{
		OpPeascore[OpPealen] = val;
		OpPealen += 1;
	}
}

int Player::OpPeascore_len()
{
	return OpPealen;
}

int Player::OpPeascore_value(int pos)
{
	return OpPeascore[pos];
}

void Player::OpPaescore_Del()			//���� �� 1�� ����
{
	OpPealen -= 1;
}




