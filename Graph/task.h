#pragma once
#include "Graph.h"
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <stack>
#include <queue>

void task_1a_1(Graph gr) {
	std::cout << "\n\n\tIa - 1.Для данной вершины орграфа вывести все \"выходящие\" соседние вершины:\n";
	bool exitTask = false;
	while (!exitTask) {
		if (gr.getOrient()) {
			std::cout << "Введите вершину: ";
			std::string v;
			std::cin >> v;
			if (!gr.vertExist(v)) {
				std::cout << "Данной вершины в графе нет.";
				std::cout << "\nЗакончить? 1/0: ";
				std::cin >> exitTask;
				continue;
			}
			std::cout << "Выходящие соседние вершины для " << v << ": ";
			std::vector<std::vector<Vertex>> al = gr.getAdjList();
			for (int i = 0; i < al.size(); i++) {
				if (al[i][0].inf == v) {
					for (int j = 1; j < al[i].size(); j++) {
						std::cout << al[i][j].inf << " ";
					}
					break;
				}
			}
			std::cout << "\nЗакончить? 1/0: ";
			std::cin >> exitTask;
		}
		else {
			std::cout << "\nДанный граф неориентированный.";
			break;
		}
	}
}

void task_1a_16(Graph gr) {
	std::cout << "\n\n\tIa - 20.Выяснить, соседствуют ли две заданные вершины графа с одной общей вершиной. Вывести такую вершину:\n";
	bool exitTask = false;
	while (!exitTask) {
		std::cout << "Введите через пробел две вершины: ";
		std::string a, b;
		std::cin >> a >> b;
		if (!gr.vertExist(a) || !gr.vertExist(b)) {
			std::cout << "Как минимум одной из данных вершин не существует.";
			std::cout << "\nЗакончить? 1/0: ";
			std::cin >> exitTask;
			continue;
		}
		std::set<std::string> alist, blist;
		std::vector<std::vector<Vertex>> al = gr.getAdjList();
		al = gr.getAdjList();
		for (int i = 0; i < al.size(); i++) {
			if (al[i][0].inf == a) {
				for (int j = 1; j < al[i].size(); j++) {
					alist.insert(al[i][j].inf);
				}
			}
			if (al[i][0].inf == b) {
				for (int j = 1; j < al[i].size(); j++) {
					blist.insert(al[i][j].inf);
				}
			}
		}
		std::set<std::string> res;
		std::set_intersection(alist.begin(), alist.end(), blist.begin(), blist.end(), std::inserter(res, res.begin()));
		if (res.empty()) {
			std::cout << "Общих вершин для " << a << " и " << b << " не существует.\n";
		}
		else {
			std::cout << "Общие вершины для вершин " << a << " и " << b << ": ";
			for (auto x : res)
				std::cout << " " << x;
		}
	
		std::cout << "\nЗакончить? 1/0: ";
		std::cin >> exitTask;
	}
}

void task_1b_8() {
	std::cout << "Ib - 8. Построить орграф, являющийся пересечением двух заданных.\n";
	std::cout << "Введите названия двух орграфов через пробел: ";
	std::string ogr1, ogr2;
	std::cin >> ogr1 >> ogr2;
	//ogr1 = "ogr1"; ogr2 = "ogr2";

	Graph gr1(ogr1);
	std::cout << "\nПЕРВЫЙ ОРГРАФ:";
	gr1.printGraphToConsole();
	Graph gr2(ogr2);
	std::cout << "\nВТОРОЙ ОРГРАФ:";
	gr2.printGraphToConsole();

	if (!gr1.getOrient() || !gr2.getOrient()) {
		std::cout << "\n\tERROR: как минимум один из графов неориентированный";
		return;
	}

	Graph intr = gr1.intersection(gr2);
	std::cout << "\nРЕЗУЛЬТИРУЮЩИЙ ОРГРАФ:";
	intr.printGraphToConsole();

	std::cout << "\n\nВведите название файла, в котором нужно сохранить орграф-пересечение: ";
	std::string fname;
	std::cin >> fname;

	intr.printGraphToFile(fname);
}


void task_2_13() {
	std::cout << "II - 13. Подсчитать количество сильно связных компонент орграфа.\n";
	std::cout << "Введите название графа: ";
	std::string grstr;
	std::cin >> grstr;
	//grstr = "2gr_13";
	Graph gr(grstr);
	gr.printGraphToConsole();

	//обход в глубину
	std::vector<std::vector<Vertex>> adjl = gr.getAdjList();
	std::vector<std::vector<Vertex>> components = gr.countStrongConnectedComponents(); //хранит количество сильно связных компонент
	int count = 0;

	std::vector<std::string> comp;

	for (int i = 0; i < components.size(); i++) {
		if (components[i].size() != 0) {
			count++;
			std::set<std::string> temp;
			temp.insert(adjl[i][0].inf);
			for (int j = 0; j < components[i].size(); j++) {
				temp.insert(components[i][j].inf);
			}

			std::string tmp;
			for (auto t : temp) {
				tmp += t + " ";
			}

			comp.push_back(tmp);
		}
	}

	std::cout << "\n\nКоличество сильно связных компонент: " << count;

	if (count != 0) 
		for (int i = 0; i < comp.size(); i++) {
			std::cout << "\n\n Компонента " << i + 1 << ": " << comp[i];
		}

}

void task_2_30() {
	std::cout << "II - 30. Определить, от какой из вершин u1 и u2 путь до v короче (по числу дуг).\n";
	std::cout << "Введите название графа: ";
	std::string grstr;
	std::cin >> grstr;
	//grstr = "graph1";
	Graph gr(grstr);
	gr.printGraphToConsole();

	std::cout << "\n\nЧерез пробел введите вершины u1, u2, v: ";
	std::string u1, u2, v;
	std::cin >> u1;
	std::cin >> u2;
	std::cin >> v;
	//обход в ширину

	std::vector<std::vector<Vertex>> al = gr.getAdjList();
	int n = al.size();

	Vertex vv = Vertex(v);
	int u1v = gr.shortestPath(Vertex(u1), vv, n);
	int u2v = gr.shortestPath(Vertex(u2), vv, n);

	if (u1v != -1 && u2v != -1) {
		if (u1v < u2v) {
			std::cout << "\nКратчайший путь: [" << u1 << " -> " << v << "] = " << u1v;
			std::cout << "\n[" << u2 << " -> " << v << "] = " << u2v;
		}
		else if (u2v < u1v) {
			std::cout << "\nКратчайший путь: [" << u2 << " -> " << v << "] = " << u2v;
			std::cout << "\n[" << u1 << " -> " << v << "] = " << u1v;
		}
		else
			std::cout << "\nКратчайшие пути от обеих вершин равны: " << u1v;
	}
	else {
		if (u1v == -1)
			std::cout << "\nПути между вершинами [" << u1 << " -> " << v << "] не существует ";
		else
			std::cout << "\nПути между вершинами [" << u2 << " -> " << v << "] не существует ";
	}
}

void task_3_k() {
	std::cout << "III - Каркас. Дан взвешенный неориентированный граф из N вершин и M ребер. Требуется найти в нем каркас минимального веса.\n";
	std::cout << "Введите название графа: ";
	std::string grstr;
	std::cin >> grstr;
	//grstr = "3gr";
	Graph gr(grstr);
	gr.printGraphToConsole();

	Graph mst = gr.kruskal(gr);
	std::cout << "\nРЕЗУЛЬТАТ:\n";

	if (mst.getVertexAmount() > 0) {
		mst.printGraphToConsole();
	}
	else {
		std::cout << "\nЧто-то пошло не так :(";
	}
}

void task_4_2() {
	std::cout << "IV - Веса. Определить, есть ли в графе вершина, минимальные стоимости путей от которой до остальных в сумме не превосходят P.\n";
	std::cout << "Введите название графа: ";
	std::string grstr;
	std::cin >> grstr;
	//grstr = "4or";
	Graph gr(grstr);
	gr.printGraphToConsole();

	std::cout << "\n\nВведите P: ";
	int p = 0;
	std::cin >> p;

	int n = gr.getVertexAmount(); //количество вершин
	std::vector<std::vector<Vertex>> adj = gr.getAdjList();	//список смежности

	std::vector<std::vector<int>> costs;
	costs.resize(n);
	for (int i = 0; i < n; i++) {	//матрица NxN с ценами путей для каждой вершины графа
		costs[i].resize(n);
	}

	for (int i = 1; i < adj.size(); i++) {	//Дейкстра для каждой из вершин графа
		gr.clearMetD();
		gr.clearCheck();
		gr.dijkstra(adj[i][0]);
		adj = gr.getAdjList();				//обновление списка смежности
		for (int j = 0; j < n; j++) {		//сохраняем цен вершин
			costs[i - 1][j] = adj[j + 1][0].metD;
		}
	}

	std::cout << "\nВершины, удовлетворяющие условию задачи: ";
	bool exists = false;								//проверяет, существует ли хотя бы одна подходящая вершин
	//проверка условия задачи
	for (int i = 0; i < costs.size(); i++) {			//проверяем каждую вершину
		bool checkCur = true;							//отметка для текущей вершины
		int curCost = 0;
		for (int j = 0; j < costs[i].size(); j++) {		//проходим по всем стоимостям
			if (costs[i][j] == INT_MAX)
				curCost += p + 1;
			else 
				curCost += costs[i][j];
		}
		if (curCost > p)							//если хотя бы одна стоимость не подходит
			checkCur = false;						//отмечаем, что текущая вершина не подходит
		if (checkCur) {									//если вершина подошла
			exists = true;
			std::cout << "\nВершина " << adj[i+1][0].inf << ". Стоимости путей: ";
			for (int j = 0; j < costs[i].size(); j++)
				if (j != i)
					std::cout << adj[j + 1][0].inf << "[" << costs[i][j] << "] ";
			std::cout << " Сумма: " << curCost;
		}
	}
	if (!exists)
		std::cout << " Подходящих вершин в данном графе нет.";
}

void task_4_8() {
	std::cout << "IV - Веса. Определить множество вершин орграфа, расстояние от которых до заданной вершины не более N.\n";
	std::cout << "Введите название графа: ";
	std::string grstr;
	std::cin >> grstr;
	//grstr = "4or";
	Graph gr(grstr);
	gr.printGraphToConsole();

	std::cout << "\n\nВведите вершину: ";
	std::string v;
	std::cin >> v;

	int vnum = gr.findVertex(Vertex(0, v));	//получаем номер вершины

	std::cout << "\nВведите N: ";
	int N = 0;
	std::cin >> N;

	int n = gr.getVertexAmount(); //количество вершин
	std::vector<std::vector<Vertex>> adj = gr.getAdjList();	//список смежности

	std::vector<std::vector<int>> d = gr.floyd();	//флойд для всего графа

	std::cout << "\nИндекс вершины " << v << " = " << vnum-1;
	std::cout << "\nВершины, удовлетворяющие условию задачи: ";
	std::vector<Vertex> exVert;					//хранит подходящие вершины
	for (int i = 0; i < n; i++) {
		if (i != vnum - 1) {					//проходим по всем вершинам, кроме данной
			if (d[i][vnum - 1] <= N)			//если расстояние подходит
				exVert.push_back(adj[i+1][0]);	//добавляем вершину в результирующий список
		}
	}

	if (exVert.empty()) {
		std::cout << " Подходящих вершин в данном графе нет.";
	}
	else {
		for (int i = 0; i < exVert.size(); i++) {
			std::cout << exVert[i].inf << "[" << d[exVert[i].num - 1][vnum-1] << "] ";
		}

		std::cout << "\n Матрица, полученная в результате работы алгоритма Флойда:\n";
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (d[i][j] == INT_MAX || d[i][j] == INT_MIN)
					std::cout << "inf ";
				else
					std::cout << d[i][j] << " ";
			}
			std::cout << "\n";
		}
	}
	
}

void task_4_13() {
	std::cout << "IV - Веса. Вывести кратчайшие пути из вершины u до v1 и v2.\n";
	std::cout << "Введите название графа: ";
	std::string grstr;
	std::cin >> grstr;
	//grstr = "4noor";
	Graph gr(grstr);
	gr.printGraphToConsole();

	std::cout << "\n\nВведите вершины u, v1, v2 через пробел: ";
	std::string ustr, v1str, v2str;

	std::cin >> ustr;
	std::cin >> v1str;
	std::cin >> v2str;

	/*ustr = "1";
	v1str = "3";
	v2str = "5";*/

	int unum = gr.getVertNumber(ustr);
	if (unum == -1) {
		std::cout << "\nERROR: вершина u (" << ustr << ") отсутствует в графе";
		return;
	}
	int v1num = gr.getVertNumber(v1str);
	if (v1num == -1) {
		std::cout << "\nERROR: вершина v1 (" << v1str << ") отсутствует в графе";
		return;
	}
	int v2num = gr.getVertNumber(v2str);
	if (v2num == -1) {
		std::cout << "\nERROR: вершина v2 (" << v2str << ") отсутствует в графе";
		return;
	}

	std::cout << '\n';
	std::vector<std::vector<Vertex>> adj = gr.getAdjList();

	gr.fordBellman(adj[unum][0], adj[v1num][0]);
	std::cout << "\n";
	gr.fordBellman(adj[unum][0], adj[v2num][0]);

}

void task_5() {
	std::cout << "V - Максимальный поток (Форд-Фалкерсон)\n";
	std::cout << "Введите название графа: ";
	std::string grstr;
	std::cin >> grstr;
	//grstr = "task5";
	Graph gr(grstr);
	gr.printGraphToConsole();

	int s, t;
	std::cout << "\nВведите индексы истока и стока через пробел: ";
	std::cin >> s >> t;
	auto mx = gr.adjListToMatrix();
	std::cout << "\nМаксимальный поток: " << gr.fordFulkerson(mx, s, t);
}