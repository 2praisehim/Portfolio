#pragma once
class Player
{

private:
	int Pae[20];				//������ �ִ� ��
	int paelen = 0;
	int Openpae[20];			//�ٴڿ� �� ��
	int openpaelen = 0;
	
	int	Gwangscore[5];			//������( ��, ��, ��, ��)
	int Gwanglen = 0;
	int Danscore[10];
	int Danlen = 0;
	int Mungscore[7];
	int Munglen = 0;
	int Peascore[30];
	int Pealen = 0;

	int	OpGwangscore[5];			//��� ������( ��, ��, ��, ��)
	int OpGwanglen = 0;
	int OpDanscore[10];
	int OpDanlen = 0;
	int OpMungscore[8];
	int OpMunglen = 0;
	int OpPeascore[30];
	int OpPealen = 0;

	
public:
	Player();
	~Player();
	int gwangcount=0;				//���� ���� �� ī��Ʈ
	int dancount = 0;;				
	int chodancount = 0;;
	int chungdancount = 0;;
	int hongdancount = 0;;
	int godoricount = 0;;
	int mungcount = 0;
	int peacount = 0;
	int ssangpea = 0;
	bool bigwang=false;
	bool chodan = false;
	bool chungdan = false;
	bool hongdan = false;
	bool godori = false;

	int opgwangcount = 0;			//���� ���� ���� �� ī��Ʈ
	int opdancount = 0;;
	int opchodancount = 0;;
	int opchungdancount = 0;;
	int ophongdancount = 0;;
	int opgodoricount = 0;;
	int opmungcount = 0;
	int oppeacount = 0;
	int opssangpea = 0;
	bool opbigwang = false;
	bool opchodan = false;
	bool opchungdan = false;
	bool ophongdan = false;
	bool opgodori = false;

	int mygwang = 0;
	int mydan = 0;
	int mymung = 0;
	int mypea = 0;
	int opgwang = 0;
	int opdan = 0;
	int opmung = 0;
	int oppea = 0;
	int Myscroe=0;
	int Opscore=0;

	void Pae_Add(int val);						//�ڽ��� �� �߰�
	int PaeFind_adr(int val);					//�ڽ��� �� ã��
	int PaeFind_value(int pos);					//�ڽ��� �� ��������
	void PaeErase(int pos);
	void PaeReplace(int val, int pos);			//�ڽ����� ����
	
	void OpenPae_Add(int val);					//�ٴڿ� ���� �� �߰�
	int OpenFind_adr(int val);					//�ڽ��� �� ���� ������ �ٴڿ� ������ �� ��Ī�� �� ã��
	int OpenFind_value(int pos);				//��Ī�� �� ��������
	void OpenErase(int pos);					//�ٴڿ� ������ ����
	int OpenPae_len();
	int OpenPaeFindCount(int val);			//�ٴڿ� ���� ���� �а� 2���̻� �����Ҷ� �� 2�϶� 2���� ���� �ϳ��� �����и� ����
	int *OpenPaeFind_adr(int val);			//�ٴڿ� ���� ���� �а� 2�� �̻� �����Ҷ� �� �ּҰ� ��������

	void Gwang_Add(int val);					//�ڽ� ���� ��(��) �߰�
	int Gwang_len();							//�ڽ� ���� ��(��) ���� 
	int Gwang_value(int pos);					//�ڽ� ���� ��(��) ��������
	void OpGwang_Add(int val);					//��� ���� ��(��) �߰�
	int OpGwang_len();							//��� ���� ��(��) ���� 
	int OpGwang_value(int pos);					//��� ���� ��(��) ��������

	void Dan_Add(int val);						//�ڽ� ���� ��(��) �߰�
	int Dan_len();								//�ڽ� ���� ��(��) ���� 
	int Dan_value(int pos);						//�ڽ� ���� ��(��) ��������
	void OpDan_Add(int val);					//��� ���� ��(��) �߰�
	int OpDan_len();							//��� ���� ��(��) ���� 
	int OpDan_value(int pos);					//��� ���� ��(��) ��������

	void Mung_Add(int val);						//�ڽ� ���� ��(��) �߰�
	int Mung_len();								//�ڽ� ���� ��(��) ���� 
	int Mung_value(int pos);						//�ڽ� ���� ��(��) ��������
	void OpMung_Add(int val);					//��� ���� ��(��) �߰�
	int OpMung_len();							//��� ���� ��(��) ���� 
	int OpMung_value(int pos);					//��� ���� ��(��) ��������

	void Peascore_Add(int val);					//�ڽ� ���� ��(��) �߰�
	int Peascore_len();							//�ڽ� ���� ��(��) ���� 
	int Peascore_value(int pos);				//�ڽ� ���� ��(��) ��������
	void Paescore_Del();
	void OpPeascore_Add(int val);				//��� ���� ��(��) �߰�
	int OpPeascore_len();						//��� ���� ��(��) ���� 
	int OpPeascore_value(int pos);				//��� ���� ��(��) ���
	void OpPaescore_Del();						//��� ���� ��(��) ����
};

