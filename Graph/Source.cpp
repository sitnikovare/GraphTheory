#include <iostream>
//#include "Graph.h"
#include "task.h"
#include "test.h"


using namespace std;

int main() {

	setlocale(LC_ALL, "RUS");

	bool ans0;
	//ans0 = true;
	cout << "������� ���� �� ����� (1) ��� ���������� �������� ������ (0)? ������� 1/0: ";
	cin >> ans0;

	if (ans0) {
		string fname;
		cout << "������� �������� ����� c ������: ";
		cin >> fname;
		//fname = "graph1";

		Graph gr(fname);
		gr.printGraphToConsole();

		bool exit = false;
		while (!exit) {

			int act;
			cout << "\n\n\t�������� ��������:";
			cout << "\n\t\t1 - �������� �������";
			cout << "\n\t\t2 - �������� ����";
			cout << "\n\t\t3 - ������� �������";
			cout << "\n\t\t4 - ������� ����";
			cout << "\n\t\t5 - ������� ������ ��������� � ����";
			cout << "\n\t\t6 - ������� ������ ��������� � �������";
			cout << "\n\t\t7 - ������� Ia (1)";
			cout << "\n\t\t8 - ������� Ia (16)";
			cout << "\n\t\t9 - ������� Ib (8)";
			cout << "\n\t\t10 - ������� II (13)";
			cout << "\n\t\t11 - ������� II (30)";
			cout << "\n\t\t12 - ������� III (�������)";
			cout << "\n\t\t13 - ������� IVa (2)";
			cout << "\n\t\t14 - ������� IVb (8)";
			cout << "\n\t\t15 - ������� IVc (13)";
			cout << "\n\t\t16 - ������� V";
			cout << "\n\t\t-1 - ��������� ���������";
			cout << "\n��� �����: ";
			cin >> act;
			//act = 11;
			cout << "\n��������� ��������� ����� ����� ��������� � ����� \'progWork_*.txt\'\n\n";

			string beg, end, v;
			Vertex b, e, vert;
			int bNum, eNum, vNum;
			switch (act)
			{
			case 1:
				cout << "\n������� �������, ������� ����� �������� � ����: ";
				cin >> v;
				gr.addVertex(v);
				gr.printGraphToConsole();
				gr.printGraphToFile("progWork");
				break;
			case 2:
				cout << "\n������� ����� ������ ��������� � �������� �������: ";
				cin >> beg >> end;
				
				bNum = gr.getVertNumber(beg);
				eNum = gr.getVertNumber(end);

				b = Vertex(bNum, beg);
				e = Vertex(eNum, end);

				if (gr.getWeighted()) {
					int w;
					cout << "\n������� ��� ����/�����: ";
					cin >> w;
					gr.addEdge(b, e, w);
				}
				else {
					gr.addEdge(b, e, 0);
				}
				gr.printGraphToConsole();
				gr.printGraphToFile("progWork");
				break;
			case 3:
				cout << "\n������� �������, ������� ����� �������: ";
				cin >> v;
				
				vNum = gr.getVertNumber(v);
				vert = Vertex(vNum, v);

				gr.deleteVertex(vert);
				gr.printGraphToConsole();
				gr.printGraphToFile("progWork");
				break;
			case 4:
				cout << "\n������� ����� ������ ��������� � �������� �������: ";
				cin >> beg >> end;

				bNum = gr.getVertNumber(beg);
				eNum = gr.getVertNumber(end);

				b = Vertex(bNum, beg);
				e = Vertex(eNum, end);

				gr.deleteEdge(b, e);
				gr.printGraphToConsole();
				gr.printGraphToFile("progWork");
				break;
			case 5:
				cout << "\n������� �������� ����� ��� ����������: ";
				cin >> fname;
				gr.printGraphToFile(fname);
				break;
			case 6:
				gr.printGraphToConsole();
				break;
			case 7:
				task_1a_1(gr);
				break;
			case 8:
				task_1a_16(gr);
				break;
			case 9:
				task_1b_8();
				break;
			case 10:
				task_2_13();
				break;
			case 11:
				task_2_30();
				break;
			case 12:
				task_3_k();
				break;
			case 13:
				task_4_2();
				break;
			case 14:
				task_4_8();
				break;
			case 15:
				task_4_13();
				break;
			case 16:
				task_5();
				break;
			case -1:
				exit = true;
				break;
			default:
				break;
			}
		}
	}
	else {
		testOrientGraph();
		testNoOrientGraph();
		cout << "\n������� ��� ���������������� ����� ��������� � ������ � ��������� orGr_*.txt";
		cout << "\n��� ������������������ ����� - � ������ � ��������� noOrGr_*.txt\n";
	}

	return 0;
}