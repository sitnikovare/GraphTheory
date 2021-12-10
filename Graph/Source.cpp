#include <iostream>
//#include "Graph.h"
#include "task.h"
#include "test.h"


using namespace std;

int main() {

	setlocale(LC_ALL, "RUS");

	bool ans0;
	//ans0 = true;
	cout << "Создать граф из файла (1) или произвести тестовый запуск (0)? Введите 1/0: ";
	cin >> ans0;

	if (ans0) {
		string fname;
		cout << "Введите название файла c графом: ";
		cin >> fname;
		//fname = "graph1";

		Graph gr(fname);
		gr.printGraphToConsole();

		bool exit = false;
		while (!exit) {

			int act;
			cout << "\n\n\tВыберете действие:";
			cout << "\n\t\t1 - добавить вершину";
			cout << "\n\t\t2 - добавить дугу";
			cout << "\n\t\t3 - удалить вершину";
			cout << "\n\t\t4 - удалить дугу";
			cout << "\n\t\t5 - вывести список смежности в файл";
			cout << "\n\t\t6 - вывести список смежности в консоль";
			cout << "\n\t\t7 - задание Ia (1)";
			cout << "\n\t\t8 - задание Ia (16)";
			cout << "\n\t\t9 - задание Ib (8)";
			cout << "\n\t\t10 - задание II (13)";
			cout << "\n\t\t11 - задание II (30)";
			cout << "\n\t\t12 - задание III (Краскал)";
			cout << "\n\t\t13 - задание IVa (2)";
			cout << "\n\t\t14 - задание IVb (8)";
			cout << "\n\t\t15 - задание IVc (13)";
			cout << "\n\t\t16 - задание V";
			cout << "\n\t\t-1 - завершить программу";
			cout << "\nВаш выбор: ";
			cin >> act;
			//act = 11;
			cout << "\nПоследнее изменение графа будет храниться в файле \'progWork_*.txt\'\n\n";

			string beg, end, v;
			Vertex b, e, vert;
			int bNum, eNum, vNum;
			switch (act)
			{
			case 1:
				cout << "\nВведите вершину, которую нужно добавить в граф: ";
				cin >> v;
				gr.addVertex(v);
				gr.printGraphToConsole();
				gr.printGraphToFile("progWork");
				break;
			case 2:
				cout << "\nВведите через пробел начальную и конечные вершины: ";
				cin >> beg >> end;
				
				bNum = gr.getVertNumber(beg);
				eNum = gr.getVertNumber(end);

				b = Vertex(bNum, beg);
				e = Vertex(eNum, end);

				if (gr.getWeighted()) {
					int w;
					cout << "\nВведите вес дуги/ребра: ";
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
				cout << "\nВведите вершину, которую нужно удалить: ";
				cin >> v;
				
				vNum = gr.getVertNumber(v);
				vert = Vertex(vNum, v);

				gr.deleteVertex(vert);
				gr.printGraphToConsole();
				gr.printGraphToFile("progWork");
				break;
			case 4:
				cout << "\nВведите через пробел начальную и конечные вершины: ";
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
				cout << "\nВведите название файла без расширения: ";
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
		cout << "\nЗапуски для ориетнированного графа находятся в файлах с названием orGr_*.txt";
		cout << "\nдля неориетнированного графа - в файлах с названием noOrGr_*.txt\n";
	}

	return 0;
}