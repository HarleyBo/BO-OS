#include<iostream>
#include<string>
#include<list>
#include"shell.h"
#include"ProcessManager.h"
#include"ResoureManager.h"
#include"SchedulerManager.h"

using namespace std;


list<Ready> Priority_PID_List;//��������
list<Block> Block_PID_List;//��������
list<RCB> Res_List;//��Դ����
list<PCB> Pcb_List;//PCB����


int main()
{
	ResoureManager RM;
	Shell shell;
	shell.Shell_Init();
	string Commands;
	while (getline(cin, Commands))
	{
		
		shell.sh(Commands);
		cin.sync();

	}
	return 0;
}