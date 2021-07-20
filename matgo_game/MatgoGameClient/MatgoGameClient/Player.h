#pragma once
class Player
{

private:
	int Pae[20];				//가지고 있는 패
	int paelen = 0;
	int Openpae[20];			//바닥에 깔린 패
	int openpaelen = 0;
	
	int	Gwangscore[5];			//점수패( 광, 단, 멍, 피)
	int Gwanglen = 0;
	int Danscore[10];
	int Danlen = 0;
	int Mungscore[7];
	int Munglen = 0;
	int Peascore[30];
	int Pealen = 0;

	int	OpGwangscore[5];			//상대 점수패( 광, 단, 멍, 피)
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
	int gwangcount=0;				//득점 종류 패 카운트
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

	int opgwangcount = 0;			//상대방 득점 종류 패 카운트
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

	void Pae_Add(int val);						//자신의 패 추가
	int PaeFind_adr(int val);					//자신의 패 찾기
	int PaeFind_value(int pos);					//자신의 패 가져오기
	void PaeErase(int pos);
	void PaeReplace(int val, int pos);			//자신의패 변경
	
	void OpenPae_Add(int val);					//바닥에 놓일 패 추가
	int OpenFind_adr(int val);					//자신의 패 한장 선택후 바닥에 놓인패 중 매칭된 패 찾기
	int OpenFind_value(int pos);				//매칭된 패 가져오기
	void OpenErase(int pos);					//바닥에 놓인패 제거
	int OpenPae_len();
	int OpenPaeFindCount(int val);			//바닥에 같은 달의 패가 2장이상 존재할때 즉 2일때 2장의 패중 하나를 먹을패를 선정
	int *OpenPaeFind_adr(int val);			//바닥에 같은 달의 패가 2장 이상 존재할때 패 주소값 가져오기

	void Gwang_Add(int val);					//자신 점수 패(광) 추가
	int Gwang_len();							//자신 점수 패(광) 개수 
	int Gwang_value(int pos);					//자신 점수 패(광) 가져오기
	void OpGwang_Add(int val);					//상대 점수 패(광) 추가
	int OpGwang_len();							//상대 점수 패(광) 개수 
	int OpGwang_value(int pos);					//상대 점수 패(광) 가져오기

	void Dan_Add(int val);						//자신 점수 패(단) 추가
	int Dan_len();								//자신 점수 패(단) 개수 
	int Dan_value(int pos);						//자신 점수 패(단) 가져오기
	void OpDan_Add(int val);					//상대 점수 패(단) 추가
	int OpDan_len();							//상대 점수 패(단) 개수 
	int OpDan_value(int pos);					//상대 점수 패(단) 가져오기

	void Mung_Add(int val);						//자신 점수 패(단) 추가
	int Mung_len();								//자신 점수 패(단) 개수 
	int Mung_value(int pos);						//자신 점수 패(단) 가져오기
	void OpMung_Add(int val);					//상대 점수 패(단) 추가
	int OpMung_len();							//상대 점수 패(단) 개수 
	int OpMung_value(int pos);					//상대 점수 패(단) 가져오기

	void Peascore_Add(int val);					//자신 점수 패(피) 추가
	int Peascore_len();							//자신 점수 패(피) 개수 
	int Peascore_value(int pos);				//자신 점수 패(피) 가져오기
	void Paescore_Del();
	void OpPeascore_Add(int val);				//상대 점수 패(피) 추가
	int OpPeascore_len();						//상대 점수 패(피) 개수 
	int OpPeascore_value(int pos);				//상대 점수 패(피) 출력
	void OpPaescore_Del();						//상대 점수 패(피) 제거
};

