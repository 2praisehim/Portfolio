#pragma once
#include "Player.h"
#include "MatgoGameClientDlg.h"
class GameFunction
{
public:
	GameFunction(int bit[],int pic[],int opic[]);
	~GameFunction();
	void init_pae(char msg[]);
	void init_openpae(char msg[]);
	void Add_Bonus(char msg[]);
	void Op_Bonus(char msg[]);
	void Open_Updatae(char msg[]);
	void SelectPae(int mine, int open);
	void OP_SCore(char msg[]);
	void OP_open(char msg[]);
	void NOP_open(char msg[]);
	void OP_add(char msg[]);
	void NSelectPae(int mine);
	void SelectBonus(int bonus);
	void NewPae(char msg[]);
	void Stop();
	void Gobak();

	void ScoreAdd(int pae);
	void OpScoreAdd(int pae);
	void OpenPaeUpdate();
	int myscore();
	int opscore();
};

