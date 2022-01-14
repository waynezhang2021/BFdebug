#pragma once
#include<bits/stdc++.h>
//#include<conio.h>
#include<windows.h>
//#include<bigint.h>
//#include<bigfloat.h>
#include<csignal>
#include<pthread.h>
#include<vector>
#include<queue>
#include<stack>
#include<bitset>
#include<string>
#define loop(n) for(int i=1;i<=n;i++)
#define stop while(1) cout<<""
#define pass cout<<""
#define loopv(var,start,stop,step) for(int var=start;var<=stop;var+=step)
#define cls system("cls")
#define cmd(c) system("c")
using namespace std;
/*
void color(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),c);
}
*/
int main()
{
	if(bool(abs(MessageBox(0,"are you sure to uninstall BFdebug tool?","",MB_YESNO+32)-7)))
	{
		system("del C:\\windows\\system32\\BFdebug.exe");
		system("start powershell \"sleep 1&del C:\\windows\\system32\\uninstall_BFdebug.exe&exit\"");
		cout<<"uninstallation successful.\n";
	}
	else
		cout<<"cancelled.\n";
}

