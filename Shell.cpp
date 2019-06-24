#include"shell.h"


Shell::Shell()
{
	MandatoryCommands.push_back("init");
	MandatoryCommands.push_back("cr");
	MandatoryCommands.push_back("de");
	MandatoryCommands.push_back("req");
	MandatoryCommands.push_back("rel");
	MandatoryCommands.push_back("to");

	MandatoryCommands.push_back("list ready");
	MandatoryCommands.push_back("list block");
	MandatoryCommands.push_back("list res");

	MandatoryCommands.push_back("pr");

}


Shell::~Shell(){}


void Shell::Shell_Init()
{
	ProcessManager p;
	Shell_Req(1, 8);
	Shell_Req(2, 9);
	Shell_Req(3, 10);
	Shell_Req(4, 11);
	Shell_Cr(0, 0, 1, 1, -1);
	cout << "init process is running"<<endl;
	
}

void Shell::Shell_Cr(PID_TYPE pid, int priority, RID_TYPE NeedResID, unsigned int NeedRes_Num, PID_TYPE Parent_pid)
{
	ProcessManager p;
	p.Create(pid, priority, NeedResID, NeedRes_Num, Parent_pid);
}
void Shell::Shell_De(PID_TYPE pid)
{
	ProcessManager p;
	p.Destroy(pid);
	

}
void Shell::Shell_Req(RID_TYPE rid, unsigned int InitResNum)
{
	ResoureManager r;
	r.Request(rid, InitResNum);
}
void Shell::Shell_Rel(RID_TYPE rid, unsigned int InitResNum)
{
	ResoureManager r;
	r.Release(rid,InitResNum);
}
void Shell::Shell_To(PID_TYPE pid, int priority, int status)
{
	SchedulerManager s(pid,priority,status);
	s.time_out();
}


void Shell::Shell_ListReady()
{
	std::cout << "====�ȴ�����====" << endl;
	for (list<Ready>::iterator ite = Priority_PID_List.begin(); ite != Priority_PID_List.end(); ite++)
	{
		std::cout <<"���ȼ�Ϊ:" <<ite->Priority<<endl;
		for (list<PID_Node>::iterator ites = ite->Priority_PID_Queue.begin(); ites != ite->Priority_PID_Queue.end(); ites++)
		{
			std::cout <<"PID:"<< ites->PID <<" Available:"<<ites->Available<<endl;
		}
	}

}
void Shell::Shell_ListBlock()
{
	std::cout << "====��������====" << endl;
	for (list<Block>::iterator ite = Block_PID_List.begin(); ite != Block_PID_List.end(); ite++)
	{
		std::cout << "PID:" << ite->PID << " Available:" << ite->Available << endl;	
	}

}
void Shell::Shell_ListRes()
{
	std::cout << "====��Դ�б�====" << endl;
	for (list<RCB>::iterator ite = Res_List.begin(); ite != Res_List.end(); ite++)
	{
		std::cout << "��ԴID:" << ite->get_rid() << "  �ȴ�����:" << endl;
		
		for (list<Waiting_PID>::iterator waiting_ites = ite->Waiting_List.begin(); waiting_ites != ite->Waiting_List.end(); waiting_ites++)
		{
			std::cout << "PID:" << (ite->Waiting_List).begin()->pid << " Available:" << (ite->Waiting_List).begin()->Available << " ��Ҫ��Դ��:" << (ite->Waiting_List).begin()->NeedResNumber << endl;
		}
		
	}

}

void Shell::Shell_Pr()
{
	int i = 0;
	std::cout << "====���е�PCB====" << endl;
	for (list<PCB>::iterator ite = Pcb_List.begin(); ite != Pcb_List.end(); ite++)
	{
		i++;
		std::cout << "====PCB"<<i<<"====" << endl;
		std::cout << "PID:" << ite->get_pid() << " Available:" << ite->get_available() << endl;
		std::cout << "״̬:" << ite->get_status() << " ���ȼ�:" << ite->get_priority() << endl;
		std::cout << "������:" << ite->FCTree.Parent_Node << endl;
		std::cout << "�ӽ���:" ;
		for (list<PID_TYPE>::iterator ites = ite->FCTree.Children_Node.begin(); ites != (ite->FCTree.Children_Node).end(); ites++)
		{
			std::cout<< *ites<< endl;
		}
		std::cout << "��Դ:" ;
		for (int i = 0; i<ite->get_ResNodeVec().size(); i++)
		{
			std::cout << "��ԴID:" << (ite->get_ResNodeVec())[i].ResID << " ����Դ��:" << (ite->get_ResNodeVec())[i].Res_Num << endl;
		}
		std::cout << "====��ʺ�ָ���====" << endl;
	}

}

void Shell::sh(string Commands)
{
	PID_TYPE pid;
	int priority;
	RID_TYPE NeedResID;
	unsigned int NeedRes_Num;
	PID_TYPE Parent_pid;
	RID_TYPE rid;
	unsigned int InitResNum;
	int status;
	
	MandatoryCommands.push_back("de");
	MandatoryCommands.push_back("req");
	MandatoryCommands.push_back("rel");
	MandatoryCommands.push_back("to");

	MandatoryCommands.push_back("list ready");
	MandatoryCommands.push_back("list block");
	MandatoryCommands.push_back("list res");

	MandatoryCommands.push_back("pr");

	


	if (Commands == MandatoryCommands[0])
	{
		Shell_Init();//��ʼ������
	}
	else if (Commands == MandatoryCommands[1])
	{
		

		cout << "====��������===="<<endl;
		//PID_TYPE pid, int priority, RID_TYPE NeedResID, unsigned int NeedRes_Num, PID_TYPE Parent_pid
		cout << "�������ID&���ȼ�|��ԴID|��Դ��|��ID:";
		cin >> pid >> priority >> NeedResID >> NeedRes_Num >> Parent_pid;
		Shell_Cr(pid, priority, NeedResID, NeedRes_Num, Parent_pid);//��������
		cout << "====�������̳ɹ�====" << endl;
	}
	else if (Commands == MandatoryCommands[2])
	{
		cout << "====ɾ������====" << endl;
		cout << "�������ID:";
		cin >> pid;
		Shell_De(pid);//ɾ������
		cout << "====ɾ�����̳ɹ�====" << endl;
		
	}

	else if (Commands == MandatoryCommands[3])
	{
		cout << "====��ȡ��Դ====" << endl;
		cout << "������ԴID&��Դ��ʼֵ:";
		cin >> rid >> InitResNum;
		Shell_Req(rid, InitResNum);//��ȡ��Դ
		cout << "====��ȡ��Դ�ɹ�====" << endl;
	}

	else if (Commands == MandatoryCommands[4])
	{
		cout << "====�ͷ���Դ====" << endl;
		cout << "������ԴID&��Դ��ʼֵ:";
		cin >> rid >> InitResNum;
		Shell_Rel(rid,InitResNum);//�ͷ���Դ
		cout << "====�ͷ���Դ�ɹ�====" << endl;
	}
	else if (Commands == MandatoryCommands[5])
	{
		cout << "====ʱ��Ƭ��ת====" << endl;
		cout << "�������ID&�������ȼ�&����״̬:";
		cin >> pid >> priority >> status;
		Shell_To(pid, priority, status);//ʱ��Ƭ��ת
		cout << "====ʱ��Ƭ��ת�ɹ�====" << endl;
	}
	else if (Commands == MandatoryCommands[6])
	{
		cout << "====�鿴�������������н���====" << endl;
		Shell_ListReady();//�鿴�������������н���
		cout << "====�鿴�������������н��̳ɹ�====" << endl;
	}
	else if (Commands == MandatoryCommands[7])
	{
		cout << "====�鿴�������������н���====" << endl;
		Shell_ListBlock();//�鿴�������������н���
		cout << "====�鿴�������������н��̳ɹ�====" << endl;
	}
	else if (Commands == MandatoryCommands[8])
	{
		cout << "====�鿴���п�����Դ====" << endl;
		Shell_ListRes();//�鿴���п�����Դ
		cout << "====�鿴���п�����Դ�ɹ�====" << endl;
	}
	else if (Commands == MandatoryCommands[9])
	{
		cout << "====��ӡ�ͷŽ��̵�PCB��Ϣ====" << endl;
		Shell_Pr();//��ӡ�ͷŽ��̵�PCB��Ϣ
		cout << "====��ӡ�ͷŽ��̵�PCB��Ϣ�ɹ�====" << endl;
	}
	else
	{
		cout << "����������   ����:��������" << endl;
	}

}
