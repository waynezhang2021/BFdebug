#pragma once
#include<iostream>
#include<fstream>
#include<conio.h>
#include<windows.h>
#include<cstdio>
#include<csignal>
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
#define size 26
using namespace std;
int ptr = 0;
string out_str;
int mem[size + 1];
int addr = size / 2;
int fg_color = 0x4, df_color = 0x3, nm_color = 0xb, er_color = 0x40 + nm_color;
void color(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void end(int val)
{
	if (val == 0)
		exit(0);
	else
	{
		color(er_color);
		cout << "\nBF debug:exit " << val;
		color(nm_color);
		exit(val);
	}
}
void exec(char cmd, bool debug, bool b_sup)
{
	if (cmd == ',')
	{
		if (debug)
			cout << "input a character:";
		char i;
		i = getchar();
		mem[addr] = int(i);
		cout << "\n";
		return;
	}
	if (cmd == '.')
	{
		if (!debug)
			cout << char(mem[addr]);
		else
			out_str = out_str + char(mem[addr]);
		return;
	}
	if (cmd == '+')
	{
		mem[addr]++;
		if (mem[addr] == 256 && (!b_sup))
			mem[addr] = 0;
		return;
	}
	if (cmd == '-')
	{
		mem[addr]--;
		if (mem[addr] == -1 && (!b_sup))
			mem[addr] = 255;
		return;
	}
	if (cmd == '>')
	{
		if (addr != 26)
			addr++;
		else
		{
			if (debug)
			{
				color(fg_color);
				cout << "error:out of memory(right)";
				color(nm_color);
			}
			end(4);
		}
		return;
	}
	if (cmd == '<')
	{
		if (addr != 1)
			addr--;
		else
		{
			if (debug)
			{
				color(fg_color);
				cout << "error:out of memory(left)";
				color(nm_color);
			}
			end(5);
		}
		return;
	}
	if (cmd == ';')
	{
		if (debug)
			cout << "input an integer:";
		cin >> mem[addr];
		return;
	}
	if (cmd == ':')
	{
		cout << mem[addr];
		char s[64];
		itoa(mem[addr], s, 10);
		out_str = out_str + s;
		return;
	}
	if (cmd == '*')
	{
		if (debug)
		{
			color(fg_color);
			cout << "error:program crashed(error thrown)";
			color(nm_color);
		}
		end(3);
		return;
	}
	if (cmd == '!')
	{
		color(nm_color);
		end(0);
		return;
	}
	if (cmd == '/')
	{
		if (mem[addr + 1] == 0)
		{
			if (debug)
			{
				color(fg_color);
				cout << "error:program crashed(division by 0)";
				color(nm_color);
			}
			end(1);
		}
		mem[addr + 2] = mem[addr] / mem[addr + 1];
		return;
	}
	if (cmd == '%')
	{
		if (mem[addr + 1] == 0)
		{
			if (debug)
			{
				color(fg_color);
				cout << "error:program crashed(modulo by 0)";
				color(nm_color);
			}
			end(2);
		}
		mem[addr + 2] = mem[addr] % mem[addr + 1];
		return;
	}
	if (cmd == '=')
	{
		mem[addr + 1] = mem[addr];
		return;
	}
	if (cmd == '_')
	{
		if (mem[addr] = mem[addr + 1])
			mem[addr + 2] = 2;
		else
		{
			if (mem[addr] > mem[addr + 1])
				mem[addr + 2] = 1;
			else
				mem[addr + 2] = 3;
		}
		return;
	}
	if (cmd == '\\')
	{
		cout << endl;
		out_str = out_str + '\n';
		return;
	}
	if (cmd != '[' && cmd != ']' && cmd != '{' && cmd != '}' && cmd != '(' && cmd != ')' && cmd != '?')
	{
		if ((cmd >= 65 && cmd <= 90) || (cmd >= 97 && cmd <= 122) || (cmd >= 48 && cmd <= 57) || (cmd == 32))
			return;
		color(fg_color);
		cout << "error:invalid instruction at position " << ptr;
		color(nm_color);
		end(9);
	}
}
string fill(int n)
{
	char c[15];
	string str;
	itoa(n, c, 10);
	str = c;
	if (str.length() == 1)
		str = " " + str + " ";
	if (str.length() == 2)
		str = " " + str;
	if (str.length() == 3)
		str = str;
	return str;
}
HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
void clrscr()
{
	SetConsoleCursorPosition(handle, { 0,0 });
}
void exec(string bf, bool debug, bool b_sup, int delay)
{
	CONSOLE_CURSOR_INFO cci = { 10,0 };
	if (debug)
	{
		SetConsoleCursorInfo(handle, &cci);
		system("cls");
	}
	out_str = "";
	ptr = 0;
	int brac;
	while (ptr <= bf.length() - 1)
	{
		if (debug)
		{
			cout << "instruction:";
			for (int i = 0; i <= bf.length() - 1; i++)
			{
				if (i == ptr)
					color(fg_color);
				else
					color(df_color);
				cout << bf[i];
			}
			color(df_color);
			cout << "\nmemory:";
			for (int i = 1; i <= size; i++)
			{
				if (i == addr)
					color(fg_color);
				else
					color(df_color);
				cout << fill(mem[i]);
				color(df_color);
				if (i != size)
					cout << "|";
			}
			color(df_color);
			cout << endl << "output:\n" << out_str << endl;
			Sleep(delay);
		}
		if (bf[ptr] != '[' && bf[ptr] != ']' && bf[ptr] != '(' && bf[ptr] != '{' && bf[ptr] != '?')
			exec(bf[ptr], debug, b_sup);
		else
		{
			if (bf[ptr] == '[')
			{
				if (mem[addr] == 0)
				{
					brac = 1;
					while (brac != 0)
					{
						ptr++;
						if (ptr == bf.length())
						{
							if (debug)
							{
								color(fg_color);
								cout << "error:mismatched \"[]\"";
								color(nm_color);
							}
							end(8);
						}
						if (bf[ptr] == '[')
							brac++;
						else
						{
							if (bf[ptr] == ']')
								brac--;
						}
					}
				}
			}
			else
			{
				if (bf[ptr] == ']')
				{
					if (mem[addr] != 0)
					{
						brac = -1;
						while (brac != 0)
						{
							ptr--;
							if (ptr == -1)
							{
								if (debug)
								{
									color(fg_color);
									cout << "error:mismatched \"[]\"";
									color(nm_color);
									end(8);
								}
							}
							if (bf[ptr] == '[')
								brac++;
							else
							{
								if (bf[ptr] == ']')
									brac--;
							}
						}
						ptr--;
					}
				}
				else
				{
					if (bf[ptr] == '(')
					{
						if (mem[addr] == 0)
						{
							brac = 1;
							while (brac != 0)
							{
								ptr++;
								if (ptr == bf.length())
								{
									if (debug)
									{
										color(fg_color);
										cout << "error:mismatched \"()\"";
										color(nm_color);
									}
									end(7);
								}
								if (bf[ptr] == '(')
									brac++;
								else
								{
									if (bf[ptr] == ')')
										brac--;
								}
							}
							ptr--;
						}
					}
					else
					{
						if (bf[ptr] == '{')
						{
							if (mem[addr] != 0)
							{
								brac = 1;
								while (brac != 0)
								{
									ptr++;
									if (ptr == bf.length())
									{
										if (debug)
										{
											color(fg_color);
											cout << "error:mismatched \"{}\"";
											color(nm_color);
										}
										end(6);
									}
									if (bf[ptr] == '{')
										brac++;
									else
									{
										if (bf[ptr] == '}')
											brac--;
									}
								}
								ptr--;
							}
						}
						else
						{
							if (bf[ptr] == '?')
							{
								brac = 1;
								while (brac != 0)
								{
									if (ptr == bf.length())
									{
										if (debug)
										{
											color(fg_color);
											cout << "error:mismatched \"[]\"";
											color(nm_color);
										}
										end(8);
									}
									ptr++;
									if (bf[ptr] == '[')
										brac++;
									else
									{
										if (bf[ptr] == ']')
											brac--;
									}
								}
							}
							else
							{
								cout << "\ninvalid instruction at position " << ptr;
								end(0);
							}
						}
					}
				}
			}
		}
		ptr++;
		if (debug)
			clrscr();
	}
	if (debug)
	{
		system("cls");
		CONSOLE_CURSOR_INFO cci2 = { 10,1 };
		SetConsoleCursorInfo(handle, &cci2);
		cout << out_str;
	}
}
void help()
{
	cout << "invalid number of parameters\n\n";
	cout << "brainfuck++ execution and debugging system made by wayne_zhang(email:wayne_zhang@126.com)\n";
	cout << "parameters:\n";
	cout << "\t/c\texecutes the command after it\n\t-c\n\n";
	cout << "\t/d\tdebuggs the command after it\n\t-d\n\n";
	cout << "\t/f\texecutes a file\n\t-f\n\n";
	cout << "\t/?\tshows this help document\n\t-?\n\t/h\n\t-h\n\tnone\n\n";
	cout << "\t/t\tdebuggs a file\n\t-t\n\n";
	cout << "\t/b\tturns on big number support\n\t-b\n\n";
	cout << "\t/i\tlaunches interactive shell\n\t-i\n";
	cout << "instructions:\n";
	cout << "\t:  output current byte\n";
	cout << "\t;  input a number to current byte\n";
	cout << "\t,  input a character and store ASCII value in current byte\n";
	cout << "\t.  output the character form of current byte\n";
	cout << "\t\\  output an \"\\n\" character\n";
	cout << "\t+  increment current byte\n";
	cout << "\t-  decrement current byte\n";
	cout << "\t>  move pointer to next byte\n";
	cout << "\t<  move pointer to previous byte\n";
	cout << "\t=  copy current byte to next byte\n";
	cout << "\t() execute sentences inside when current byte is not 0\n";
	cout << "\t{} execute sentences inside when current byte is 0\n";
	cout << "\t[] loop the sentences inside when current byte is not 0\n";
	cout << "\t/  divide current byte with next byte and store integer result in the byte next to next byte\n";
	cout << "\t%  modulo,acts like \"/\"\n";
	cout << "\t_  comparison,compares current byte with the next and stores result in the byte next to next byte\n";
	color(nm_color);
	cout << "\t   here's a table of possible results:\n";
	cout << "\t\t   0 current byte<next byte\n";
	cout << "\t\t   1 current byte=next byte\n";
	cout << "\t\t   2 current byte>next byte\n";
	color(df_color);
	cout << "\t?  jump out of loop\n";
	cout << "\t!  end program immediately\n";
	cout << "\t*  throw an error and crash program\n";
	cout << "return values:\n";
	cout << "\t0  normal program end\n";
	color(fg_color);
	cout << "\tcrash:\n";
	cout << "\t\t1  division by 0\n";
	cout << "\t\t2  modulo by 0\n";
	cout << "\t\t3  error thrown(\"*\" instruction)\n";
	cout << "\t\t4  out of memory(right)\n";
	cout << "\t\t5  out of memory(left)\n";
	cout << "\t\t6  mismatched \"{}\"\n";
	cout << "\t\t7  mismatched \"()\"\n";
	cout << "\t\t8  mismatched \"[]\"\n";
	cout << "\t\t9  invalid instruction\n";
	cout << "\t\t10 invalid filename\n";
	cout << "\t\t11 invalid parameter(s)\n";
	color(nm_color);
	end(0);
}
int main(int argc, char** argv)
{
	system("title BF_debug");
	int d = 1;
	string c = "";
	bool debug = 0, b_sup = 0;
	color(df_color);
	for (int i = 0; i < argc; i++)
		if ((strcmp(argv[i], "-b") == 0) || (strcmp(argv[i], "/b") == 0))
		{
			b_sup = 1;
			argc--;
			break;
		}
	if (argc == 1)
		help();
	if (argc == 2)
	{
		string str = argv[1];
		if (str == "/?" || str == "/h" || str == "-h" || str == "-?")
			help();
		else
		{
			if (str == "/i" || str == "-i")
			{
				cout << "Brainfuck interactive shell\nBF code:";
				cin >> c;
				cout << "debug?";
				cin >> debug;
				cout << "big number support?";
				cin >> b_sup;
				if (debug)
				{
					cout << "delay(ms) for debugging?";
					cin >> d;
				}
			}
			else
			{
				cout << "invalid parameter received:" << str << "\n\n";
				end(11);
			}
		}
	}
	if (argc == 3)
	{
		string s1 = argv[1], s2 = argv[2];
		if (s1 == "/c" || s1 == "-c")
		{
			c = s2;
		}
		else
		{
			if (s1 == "/d" || s1 == "-d")
			{
				c = s2;
				debug = true;
			}
			else
			{
				if (s1 == "/f" || s1 == "-f")
				{
					ifstream fin(s2.c_str());
					if (!fin)
						end(10);
					fin >> c;
				}
				else
				{
					if (s1 == "/t" || s1 == "-t")
					{
						ifstream fin(s2.c_str());
						if (!fin)
							end(10);
						fin >> c;
						debug = true;
					}
					else
					{
						cout << "invalid parameters:" << s1 << " " << s2 << endl;
						end(11);
					}
				}
			}
		}
	}
	if (argc != 2 && argc != 3)
	{
		cout << "invalid number of parameters" << endl;
		end(11);
	}
	exec(c, debug, b_sup, d);
	color(nm_color);
}
