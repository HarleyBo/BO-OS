#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<list>
#include"ProcessManager.h"
#include"ResoureManager.h"
#include"SchedulerManager.h"
using namespace std;

typedef int RID_TYPE;
typedef int PID_TYPE;

extern list<Ready> Priority_PID_List;
extern list<Block> Block_PID_List;
extern list<RCB> Res_List;
extern list<PCB> Pcb_List;

class Shell
{
public:
	std::vector<std::string>  MandatoryCommands;
	Shell();
	~Shell();

	//���̲�����������
	void Shell_Init();//��ʼ������
	void Shell_Cr(PID_TYPE pid, int priority, RID_TYPE NeedResID, unsigned int NeedRes_Num, PID_TYPE Parent_pid);//��������
	void Shell_De(PID_TYPE pid);//ɾ������
	void Shell_Req(RID_TYPE rid, unsigned int InitResNum);//��ȡ��Դ
	void Shell_Rel(RID_TYPE rid, unsigned int InitResNum);//�ͷ���Դ
	void Shell_To(PID_TYPE pid, int priority, int status);//ʱ��Ƭ��ת
	
	//�鿴����״̬����Դ������
	void Shell_ListReady();//�鿴�������������н���
	void Shell_ListBlock();//�鿴�������������н���
	void Shell_ListRes();//�鿴���п�����Դ
    
	//��ӡ�ͷŽ��̵�PCB��Ϣ
	void Shell_Pr();

	void sh(string Commands);

};