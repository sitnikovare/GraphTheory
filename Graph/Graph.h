#include <string>
#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <algorithm>
#include <set>

//Структура для узла графа
struct Vertex {
	int num;		//порядковый номер узла в графе
	std::string inf;	//информация, хранящаяся в вершине
	bool check = false; // для обходов
	int component = 0;	//компонента (для Краскала)
	int metD = INT_MAX; //метка для алгоритма Дейкстры

	Vertex() {}

	Vertex(int x) {
		num = x;
	}

	Vertex(std::string x) {
		inf = x;
	}

	Vertex(int x, std::string str) {
		num = x;
		inf = str;
	}

	bool operator== (const Vertex& right) {
		if (inf == right.inf) {
			return true;
		}
		else {
			return false;
		}
	}

	bool operator< (const Vertex& right) {
		if (inf < right.inf) {
			return true;
		}
		else {
			return false;
		}
	}
};

//Структура для дуги/ребра графа
struct Edge {
	Vertex first;	//начальная вершина
	Vertex second;	//конечная вершина
	int weight = 0;	//вес дуги

	Edge() {}

	Edge(Vertex f, Vertex s) {
		first = f;
		second = s;
	}

	Edge(Vertex f, Vertex s, int w) {
		first = f;
		second = s;
		weight = w;
	}

	bool operator== (const Edge& right) {
		if (first == right.first && second == right.second) {
			return true;
		}
		else {
			return false;
		}
	}

	bool operator< (const Edge& right) {
		if (weight < right.weight)
			return true;
		else if (weight == right.weight) {
			if (first < right.first)
				return true;
			else if (first == right.first) {
				return second < right.second;
			}
			else
				return false;
		}
		else 
			return false;
	}
};

//Класс граф
class Graph {
	int vertexAmount = 0;	//количество вершин
	bool orient = false;	//ориентированный или нет
	bool weighted = false; //взвешенный или нет
	std::vector<std::vector <Vertex>> adjList;	//список смежности
	std::vector<Edge> edgeList;	//список ребер

public:
		//геттеры
	int getVertexAmount() {
		return vertexAmount;
	}

	bool getOrient() {
		return orient;
	}

	bool getWeighted() {
		return weighted;
	}

	std::vector<std::vector <Vertex>> getAdjList() {
		return adjList;
	}

	std::vector<Edge> getEdgeList() {
		return edgeList;
	}

		//сеттеры
	void setVertexAmount(int x) {
		this->vertexAmount = x;
	}

	void setOrient(bool x) {
		this->orient = x;
	}

	void setWeighted(bool x) {
		this->weighted = x;
	}

	void setAdjList(std::vector<std::vector <Vertex>> x) {
		adjList.resize(x.size());
		for (int i = 0; i < adjList.size(); i++) {
			adjList[i].resize(x[i].size());
		}

		for (int i = 0; i < x.size(); i++) {
			for (int j = 0; j < x[i].size(); j++)
				adjList[i][j] = x[i][j];
		}
	}

	void setEdgeList(std::vector<Edge> x) {
		edgeList.resize(x.size());
		for (int i = 0; i < edgeList.size(); i++) {
			edgeList[i] = x[i];
		}
	}

	//пустой конструктор
	Graph() {}

	//конструктор-копия
	Graph(Graph* gr) {
		setVertexAmount(gr->vertexAmount);
		setOrient(gr->orient);
		setAdjList(gr->adjList);
		setWeighted(gr->weighted);
	}

	//конструктор, заполняющий данными из файла
	//тут добавить веса и инф поле вершинам
	Graph(std::string fileName) {
		//файл c вершинами вида : 
		//	1 / 0 (orient)
		//	1 / 0 (weighted)
		//  количество вершин
		//	num inf

		std::string fileName1 = fileName + "_vert.txt";
		std::string fileName2 = fileName + "_edge.txt";

		//файл c дугами вида : 
		//	вершина1  вершнина2 [вес]
		try {
			std::ifstream in(fileName1);

			int o, w, va;
			in >> o >> w >> va;

			setOrient(o);
			setVertexAmount(va);
			setWeighted(w);

			std::vector<Vertex> x0;
			x0.push_back(Vertex(0));
			adjList.resize(vertexAmount + 1, x0); //вектор векторов с узлами, заполненный нулями

			//тут надо пройти по вершинам и заполнить inf
			while (in.peek() != EOF) {
				int n;
				std::string x;
				in >> n >> x;
				adjList[n][0].num = n;
				adjList[n][0].inf = x;
			}

			in.close();
		}
		catch (...) {
			std::cout << "ERROR: cannot open file: " + fileName1;
		}
		try {
			std::ifstream in(fileName2);

			std::queue<std::string> vertexes;

			while (in.peek() != EOF) {
				std::string x;
				in >> x;
				vertexes.push(x);
			}
			in.close();
			createAdjList(vertexes);
		}
		catch (...) {
			std::cout << "ERROR: cannot open file: " + fileName2;
		}
	}

	void clearCheck() {
		for (int i = 0; i < adjList.size(); i++) {
			for (int j = 0; j < adjList[i].size(); j++) {
				adjList[i][j].check = false;
			}
		}
	}

	void clearMetD() {
		for (int i = 0; i < adjList.size(); i++) {
			for (int j = 0; j < adjList[i].size(); j++) {
				adjList[i][j].metD = INT_MAX;
			}
		}
	}


	int findVertex(Vertex v) {
		int res = 0;

		for (int i = 1; i < adjList.size(); i++) {
			if (adjList[i][0] == v) {
				res = i;
				break;
			}
		}

		return res;
	}

	int getVertNumber(std::string v) {
		int result = -1;

		for (int i = 1; i < adjList.size(); ++i)
			if (adjList[i][0].inf == v)
				result = i;
		return result;
	}

	bool vertExist(std::string v) {
		for (int i = 0; i < adjList.size(); i++)
			if (adjList[i][0].inf == v)
				return true;
		return false;
	}

	bool edgeExist(Vertex f, Vertex s) {
		for (int i = 0; i < edgeList.size(); i++) {
			if (edgeList[i].first == f && edgeList[i].second == s
				|| edgeList[i].first == s && edgeList[i].second == f)
				return true;
		}
		return false;
	}

	void weightedEdgeSort() {
		sort(edgeList.begin(), edgeList.end());
	}


	int getEdgeWeight(Vertex f, Vertex s) {
		for (int i = 0; i < edgeList.size(); i++) {
			if (edgeList[i].first == f && edgeList[i].second == s)
				return edgeList[i].weight;
			if (!orient) {
				if (edgeList[i].first == s && edgeList[i].second == f)
					return edgeList[i].weight;
			}
		}
		return INT_MIN; //если дуга не нашлась
	}

	void createAdjList(std::queue<std::string> vertexes) {
		while (!vertexes.empty()) {
			std::string beg = vertexes.front();
			vertexes.pop();
			std::string end = vertexes.front();
			vertexes.pop();

			Vertex b = adjList[stoi(beg)][0];
			Vertex e = adjList[stoi(end)][0];

			if (weighted) {
				int weight = stoi(vertexes.front());
				vertexes.pop();
				addEdge(b, e, weight); //++
			}
			else {
				addEdge(b, e, 0);
			}
		}
	};

	//тут добавить инф поле в добавление узла
	void addVertex(std::string str) {
		if (vertExist(str)) {
			std::cout << "ERROR: Vertex " << str << " is already exist\n";
		}
		else {
			std::vector<Vertex> adjV;

			int n = getVertexAmount() + 1;
			adjV.push_back(Vertex(n, str)); //++

			adjList.push_back(adjV);
			setVertexAmount(n + 1);
		}
	};

	void addEdge(Vertex first, Vertex second, int weight) {
		if (vertexAmount == 0) {
			std::cout << "\n\t!!! GRAPH IS EMPTY !!!";
			return;
		}

		if (!vertExist(first.inf)) {
			std::cout << "ERROR: vertex " << first.inf << " doesn't exist";
			return;
		}

		if (!vertExist(second.inf)) {
			std::cout << "ERROR: vertex " << second.inf << " doesn't exist";
			return;
		}

		bool exist = false;
		for (int i = 1; i < adjList[first.num].size(); i++) {
			if (adjList[first.num][i] == second.num)
				exist = true;
		}

		if (exist) {
			std::cout << "ERROR: edge " << first.inf << "->" << second.inf << " already exist";
			return;
		}

		adjList[first.num].push_back(second);
		edgeList.push_back(Edge(first, second, weight));
		if (!orient) {
			adjList[second.num].push_back(first);
			if (!edgeExist(first, second))
				edgeList.push_back(Edge(second, first, weight));
		}
	};

	void deleteVertex(Vertex x) {
		if (vertexAmount == 0) {
			std::cout << "\n\t!!! GRAPH IS EMPTY !!!";
			return;
		}

		if (!vertExist(x.inf)) {
			std::cout << "ERROR: vertex " << x.inf << " doesn't exist";
			return;
		}

		for (int i = 1; i < vertexAmount; i++) {
			if (i != x.num)
				deleteEdge(adjList[i][0], x);
		}

		adjList.erase(adjList.begin() + x.num);
		setVertexAmount(getVertexAmount() - 1);

		for (int i = 1; i < adjList.size(); i++) {
			for (int j = 0; j < adjList[i].size(); j++) {
				if (adjList[i][j].num > x.num) {
					--adjList[i][j].num;
				}
			}
		}
		
		for (int i = 0; i < edgeList.size(); i++) {
			if (edgeList[i].first.num > x.num) {
				--edgeList[i].first.num;
			}
			if (edgeList[i].second.num > x.num) {
				--edgeList[i].second.num;
			}
		}
	};

	void deleteEdge(Vertex first, Vertex second) {
		if (vertexAmount == 0) {
			std::cout << "\n\t!!! GRAPH IS EMPTY !!!";
			return;
		}

		if (!vertExist(first.inf)) {
			std::cout << "ERROR: vertex " << first.inf << " doesn't exist";
			return;
		}

		if (!vertExist(second.inf)) {
			std::cout << "ERROR: vertex " << second.inf << " doesn't exist";
			return;
		}

		bool exist = false;
		for (int i = 1; i < adjList[first.num].size(); i++) {
			if (adjList[first.num][i].num == second.num) {
				adjList[first.num].erase(adjList[first.num].begin() + i);
				exist = true;
			}
		}

		if (!orient) {
			for (int i = 1; i < adjList[second.num].size(); i++) {
				if (adjList[second.num][i].num == first.num) {
					adjList[second.num].erase(adjList[second.num].begin() + i);
					exist = true;
				}
			}
		}

		if (!exist) {
			std::cout << "ERROR: edge " << first.inf << "->" << second.inf << " doesn't exist";
			return;
		}
	};

	//тут разбить на два файла
	void printGraphToFile(std::string fileName) {
		std::string fnameV = fileName + "_vert.txt";
		std::string fnameE = fileName + "_edge.txt";

		try {
			std::ofstream out(fnameV);

			out << (int)orient << "\n";
			out << (int)weighted << "\n";
			out << vertexAmount;

			for (int i = 1; i < adjList.size(); i++) {
				out << "\n" << adjList[i][0].num << " " << adjList[i][0].inf;
			}

			out.close();
		}
		catch (...) {
			std::cout << ("ERROR: cannot open file : " + fnameV);
		}

		try {
			std::ofstream out(fnameE);

			for (int i = 1; i < adjList.size(); i++) {
				for (int j = 1; j < adjList[i].size(); j++) {
					if (!orient && i > adjList[i][j].num)
						continue;
					if (i == 1 && j != 1 || i != 1)
						out << "\n";
					out << adjList[i][0].num << " " << adjList[i][j].num;
					if (weighted) {
						auto iter = find(edgeList.begin(), edgeList.end(), Edge(adjList[i][0], adjList[i][j]));
						if (!orient && iter == edgeList.end())
							iter = find(edgeList.begin(), edgeList.end(), Edge(adjList[i][j], adjList[i][0]));
						out << " " << (*iter).weight;
					}
				}
			}

			out.close();
			printAdjListToFile(fileName + ".txt");
		}
		catch (...) {
			std::cout << ("ERROR: cannot open file : " + fnameE);
		}
	};

	void printAdjListToFile(std::string fileName) {
		try {
			std::ofstream out(fileName);

			out << "\n Граф " << (orient ? "ориентированный" : "неориентированный") << "\n";
			out << " Граф " << (weighted ? "взвешенный" : "невзвешенный") << "\n";
			out << "Количество вершин: " << vertexAmount;

			for (int i = 1; i < adjList.size(); i++) {
				out << "\n Вершина " << adjList[i][0].inf << " связана с вершинами: ";
				for (int j = 1; j < adjList[i].size(); j++) {
					out << " " << adjList[i][j].inf;
					if (weighted) {
						auto iter = find(edgeList.begin(), edgeList.end(), Edge(adjList[i][0], adjList[i][j]));
						if (!orient && iter == edgeList.end())
							iter = find(edgeList.begin(), edgeList.end(), Edge(adjList[i][j], adjList[i][0]));
						out << "(вес: " << (*iter).weight << ") ";
					}
				}
			}

			out.close();
		}
		catch (...) {
			std::cout << ("ERROR: cannot open file : " + fileName);
		}
	};

	void printGraphToConsole() {
		std::cout << "\n Граф " << (orient ? "ориентированный" : "неориентированный") << "\n";
		std::cout << " Граф " << (weighted ? "взвешенный" : "невзвешенный") << "\n";
		std::cout << "Количество вершин: " << vertexAmount;

		for (int i = 1; i < adjList.size(); i++) {
			std::cout << "\n Вершина " << adjList[i][0].inf << " связана с вершинами: ";
			for (int j = 1; j < adjList[i].size(); j++) {
				std::cout << " " << adjList[i][j].inf;
				if (weighted) {
					auto iter = find(edgeList.begin(), edgeList.end(), Edge(adjList[i][0], adjList[i][j]));
					if (!orient && iter == edgeList.end())
						iter = find(edgeList.begin(), edgeList.end(), Edge(adjList[i][j], adjList[i][0]));
					std::cout << "(вес: " << (*iter).weight << ") ";
				}
			}
		}
	};

	Graph intersection(Graph gr2) {
		std::set<std::string> vert;
		std::vector<std::vector<Vertex>> algr1 = getAdjList();
		std::vector<std::vector<Vertex>> algr2 = gr2.getAdjList();
		std::vector<std::vector<Vertex>> algrR;

		for (int i = 0; i < algr1.size(); i++) {
			for (int j = 0; j < algr2.size(); j++)
				if (algr1[i][0].inf == algr2[j][0].inf)
					vert.insert(algr1[i][0].inf);
		}

		int count = 1;
		std::vector<Vertex> x0;
		x0.push_back(Vertex(0));
		algrR.push_back(x0);
		std::vector<Vertex> vertX; // для нумерации

		for (int i = 1; i < algr1.size(); i++) {
			auto it1 = find(vert.begin(), vert.end(), algr1[i][0].inf); //берем первую вершину
			if (it1 != vert.end()) {
				for (int k = 1; k < algr2.size(); k++) {
					auto it2 = find(vert.begin(), vert.end(), algr2[k][0].inf); //ищем вторую вершину
					if (it2 != vert.end()) {
						if (algr1[i][0].inf == algr2[k][0].inf) {
							//тут добавить строку в algrR
							std::vector<Vertex> x0;
							Vertex x = Vertex(count++, algr2[k][0].inf);
							x0.push_back(x);
							algrR.push_back(x0); //добавлена строка для новой общей вершины
							vertX.push_back(x); //добавили для нумерации

							//ищем дугу
							for (int j = 1; j < algr1[i].size(); j++) {
								for (int m = 1; m < algr2[k].size(); m++) {
									if (algr1[i][j].inf == algr2[k][m].inf) {
										//тут добавить конечную общую вершину
										auto it3 = find(vert.begin(), vert.end(), algr1[i][j].inf);
										if (it3 != vert.end()) {
											algrR[count - 1].push_back(Vertex(0, algr2[k][m].inf));
										}
									}
								}
								//break;
							}
						}
					}
				}
			}
		}

		//расставить номера вершинам
		for (int k = 0; k < vertX.size(); k++) {
			for (int i = 1; i < algrR.size(); i++) {
				for (int j = 1; j < algrR[i].size(); j++) {
					if (algrR[i][j].inf == vertX[k].inf)
						algrR[i][j].num = vertX[k].num;
				}
			}
		}

		//создание орграфа-пересечения
		Graph res;
		res.setVertexAmount(vert.size()-1);
		res.setOrient(true);
		res.setWeighted(false);
		res.setAdjList(algrR);

		return res;
	}

	int shortestPath(Vertex u, Vertex v, int n) {
		int res = -1;

		std::queue<Vertex> order;

		int curVertNum = findVertex(u);
		order.push(adjList[curVertNum][0]); //считаем от u

		bool find = false;
		std::vector<int> paths;
		int count = 0;
		paths.resize(n, 0);

		while (!order.empty()) {
			curVertNum = findVertex(order.front());
			order.pop();

			if (adjList[curVertNum][0].check)			//если уже смотрели этот узел, продолжаем просматривать без текущего
				continue;
			else
				adjList[curVertNum][0].check = true;			//иначе помечаем, что узел был просмотрен

			for (int k = 1; k < adjList[curVertNum].size(); k++) {
				if (adjList[curVertNum][k] == v) {
					find = true;
					paths[curVertNum] = count + 1;
				}
				order.push(adjList[curVertNum][k]);			//добавляем все последующие узлы
			}
			++count;
		}

		clearCheck(); //очищаем метки просмотра узлов

		if (!find) {
			std::cout << "\nERROR:  this path doesn't exist";
			return -1;
		}
		else {
			//кратчайший путь - минимум из вектора
			res = INT_MAX;
			for (int i = 0; i < paths.size(); i++) {
				if (paths[i] < res && paths[i] != 0)
					res = paths[i];
			}
			paths.clear();
		}

		return res;
	}

	std::vector<std::vector<Vertex>> countStrongConnectedComponents() {
		std::vector <std::vector <Vertex>> paths; //хранит все возможные пути из всех вершин
		paths.resize(adjList.size());

		for (int i = 1; i < adjList.size(); i++) {	//собираем пути для каждого узла
			std::vector<Vertex> gaps;
			deepOrderForOneVert(adjList[i][0], i, gaps);
			paths[i] = gaps;
		}

		clearCheck();

		//просмотреть все пути

		//просматриваем первый узел:
		//для каждого из его gaps ищем в том gaps текущий узел. если есть путь обратно - двигаемся дальше

		for (int i = 1; i < paths.size(); i++) {	//для каждого узла u
			if (adjList[i][0].check) //если смотрели, то пропускаем шаг
				continue;

			bool ok = false;
			for (int j = 0; j < paths[i].size(); j++) {		//проверяем его пути v
				int n = paths[i][j].num; // есть путь u->v, ищем путь v->u
				for (int k = 0; k < paths[n].size(); k++) {
					if (paths[n][k] == adjList[i][0]) {		//если есть путь v->u
						ok = true;
						//отметить, что просмотрели
						adjList[n][0].check = true;
					}
				}
			}
			if (ok) {
				ok = false; //опускаем флаг для след вершины
			}
			else {
				paths[i].resize(0);
			}
		}

		return paths;
	}

	//обход в глубину от одного узла, gaps - все узлы, в которые есть пути от этого одного узла
	void deepOrderForOneVert(Vertex curVert, int curV, std::vector<Vertex>& gaps) {
		if (adjList[curV][0].check) {	//если узел просмотрен, не работаем с ним
			return;
		}

		adjList[curV][0].check = true; //отмечаем, что посмотрели узел, в котором мы сейчас
		for (int i = 1; i < adjList[curV].size(); i++) {
			gaps.push_back(adjList[curV][i]); //помечаем, в какой узел смогли попасть
			deepOrderForOneVert(adjList[curV][i], adjList[curV][i].num, gaps);
		}
	}

	Graph kruskal(Graph gr) {
		Graph mst; //минимальное остовное дерево из текущего графа

		if (orient) {
			std::cout << "\n\tERROR: oriented graph";
			return mst;
		};

		if (!weighted) {
			std::cout << "\n\tERROR: unweighted graph";
			return mst;
		};

		mst = Graph(gr);

		//для каждого узла раздать свою компоненту
		for (int i = 1; i < adjList.size(); i++) {
			mst.adjList[i][0].component = i;
		}

		std::vector<Edge> tmp; //временный список дуг

		weightedEdgeSort();	//сортировка списка дуг по возрастанию весов

		for (int i = 0; i < edgeList.size(); i++) { //проходим по списку дуг
			int f_num = findVertex(edgeList[i].first);  //извлекаем номер первого узла
			int s_num = findVertex(edgeList[i].second); //извлекаем номер второго узла

			int f_cmp = mst.adjList[f_num][0].component; //извлекаем компоненту первого узла
			int s_cmp = mst.adjList[s_num][0].component; //извлекаем компоненту второго узла

			if (f_cmp != s_cmp) { //если лежат в разных компонентах, добавляем в mst
				tmp.push_back(edgeList[i]);

				//объединяем в одну компоненту
				for (int i = 1; i < mst.adjList.size(); i++) {
					if (mst.adjList[i][0].component == s_cmp)
						mst.adjList[i][0].component = f_cmp;
				}
			}
			else {
				mst.deleteEdge(edgeList[i].first, edgeList[i].second); //эта дуга не нужна в mst
			}
		}

		//восстановить mst
		mst.setEdgeList(tmp);

		return mst;
	}

	void dijkstraIN(std::queue<Vertex> order) {
		while (!order.empty()) {	//цикл по всему графу
			int vVertNum = findVertex(order.front());

			if (adjList[vVertNum][0].check) { //если уже посещали, выходим
				order.pop();
				continue;
			}

			adjList[vVertNum][0].check = true;	//отмечаем, что вершина была пройдена
			order = {};							//очищаем очередь, она сформируется снова

			std::vector<std::pair<Vertex, int>> sv; //хранит смежные вершины и вес дуги
			std::vector<int> sw;				//хранит веса до смежных вершин

			for (int i = 1; i < adjList[vVertNum].size(); i++) {					//ходим по конечным вершинам от данной и раздаем новые метки
				int w = getEdgeWeight(adjList[vVertNum][0], adjList[vVertNum][i]);  //ищем вес дуги
				int newMetDendV = adjList[vVertNum][0].metD + w;					// новая метка следующей вершины
				int endVNum = findVertex(adjList[vVertNum][i]);						//получаем номер конечной вершины
				if (newMetDendV < adjList[endVNum][0].metD)
					adjList[endVNum][0].metD = newMetDendV;							//устанавливаем новую метку для конечной вершины

				sv.push_back(std::make_pair(adjList[vVertNum][i], w));
				sw.push_back(w);
			}


			//переход к ближайшей вершине
			std::sort(sw.begin(), sw.end());	//сортируем по весам
			for (int i = 0; i < sw.size(); i++) {
				for (int j = 0; j < sv.size(); j++) {
					if (sv[j].second == sw[i]) {
						order.push(sv[j].first);
						sv.erase(sv.begin() + j);
						break;
					}
				}
			}
		}
	}

	void dijkstra(Vertex v) {
		int vVertN = findVertex(v);

		//каждая след вершина = мет пред + вес
		adjList[vVertN][0].metD = 0; //устанавливаем метку первой вершины в обходе = 0
		std::queue<Vertex> order;		//проход по графу
		order.push(adjList[vVertN][0]);

		dijkstraIN(order);
		order = {};

		//проверка непосещенных вершин не нужна в данном случае, 
		//т.к. если вершина не получила метку, то пути из u до нее нет

		for (int i = 1; i < adjList[vVertN].size(); i++) {
			if (!adjList[vVertN][i].check) {
				order.push(adjList[vVertN][i]);
				dijkstraIN(order);
				order = {};
			}
		}

		for (int i = 1; i < adjList.size(); i++) {	//исключение забытых вершин
			adjList[i][0].check = false;
			order.push(adjList[i][0]);
			dijkstraIN(order);
			order = {};
		}
	}

	void fordBellman(Vertex v, Vertex u) {
		std::vector<int> d(vertexAmount, INT_MAX);
		d[v.num - 1] = 0;
		std::vector<int> p(vertexAmount, -1);
		for (;;) {
			bool any = false;
			for (int j = 0; j < edgeList.size(); ++j)
				if (d[edgeList[j].first.num-1] < INT_MAX && d[edgeList[j].second.num - 1] != 0)
					if (d[edgeList[j].second.num - 1] > d[edgeList[j].first.num - 1] + edgeList[j].weight) {
						d[edgeList[j].second.num - 1] = d[edgeList[j].first.num - 1] + edgeList[j].weight;
						p[edgeList[j].second.num - 1] = edgeList[j].first.num - 1;
						any = true;
					}
			if (!any)  break;
		}

		if (d[u.num-1] == INT_MAX)
			std::cout << "Нет пути из " << v.inf << " в " << u.inf << ".";
		else {
			std::vector<int> path;
			for (int cur = u.num-1; cur != -1; cur = p[cur])
				path.push_back(cur);
			reverse(path.begin(), path.end());

			std::cout << "\nПуть из вершины u в вершину v: ";
			for (size_t i = 0; i < path.size(); ++i)
				std::cout << adjList[path[i]+1][0].inf << ' ';
			std::cout << " Стоимость: " << d[u.num-1];
		}

		for (int j = 0; j < edgeList.size(); ++j)
			if (d[edgeList[j].second.num - 1] > d[edgeList[j].first.num - 1] + edgeList[j].weight) {
					std::cout << "\nВ графе есть цикл отрицатеьного веса.";
			}
	}

	std::vector<std::vector<int>> floyd() {
		std::vector<std::vector<int>> d;	//матрица кратчайших путей от вершины v до остальных
		d.resize(vertexAmount);
		for (int i = 0; i < vertexAmount; i++)
			d[i].resize(vertexAmount);

		for (int i = 0; i < vertexAmount; i++) {		//заполнение матрицы сначала INT_MAX значениями
			for (int j = 0; j < vertexAmount; j++) {
				d[i][j] = INT_MAX;
			}
		}

		for (int i = 0; i < edgeList.size(); i++) {		//заполнение существующих весов в графе
			d[edgeList[i].first.num - 1][edgeList[i].second.num - 1] = edgeList[i].weight;
		}

		for (int i = 0; i < vertexAmount; i++) {
			for (int u = 0; u < vertexAmount; u++) {
				for (int v = 0; v < vertexAmount; v++) {
					if (d[u][i] != INT_MAX && d[i][v] != INT_MAX)
					d[u][v] = std::min(d[u][v], d[u][i] + d[i][v]);
				}
			}
		}

		return d;
	}

	std::vector<std::vector<int>> adjListToMatrix() {
		std::vector<std::vector<int>> adjMx(vertexAmount);
		for (int i = 0; i < vertexAmount; i++)
			adjMx[i].resize(vertexAmount, 0);

		for (int i = 0; i < edgeList.size(); i++) {
			adjMx[edgeList[i].first.num - 1][edgeList[i].second.num - 1] = edgeList[i].weight;
		}

		return adjMx;
	}

	//обход в ширину для Форда_Фалкерсона
	bool bfsForFordFulkerson(std::vector<std::vector<int>>& flows, int s, int t, std::vector<int>& parent) {
		std::vector<bool> checked(vertexAmount, false);

		std::queue<int> q;	// очередь для обхода в ширину
		q.push(s);			// добавляем вершину в очередь
		checked[s] = true;	// помечаем вершину, как посещенную
		parent[s] = -1;		// у истока нет предка

		while (!q.empty()) {	// пока очередь не пуста
			int u = q.front();	// достаем из нее элемент
			q.pop();

			for (int v = 0; v < vertexAmount; v++) {			// проходим по всем вершинам
				if (checked[v] == false && flows[u][v] > 0) {	// если вершина не посещена, и поток не исчерпался
					q.push(v);									// добавляем ее в очередь
					parent[v] = u;								// добавляем предка
					checked[v] = true;							// помечаем, что вершина пройдена
				}
			}
		}

		bool lastIter = (checked[t] == true);
		return lastIter;							// функция возвращает отметку о том, была ли пройдена вершина
	}

	//Форд-Фалкерсон
	int fordFulkerson(std::vector<std::vector<int>> flows, int s, int t) {
		int u, v;

		std::vector<int> p(vertexAmount);						// вектор с предками
		int maxFlow = 0;										

		bool lastIter = bfsForFordFulkerson(flows, s, t, p);
		while (lastIter) {		// пока были хоть какие-то изменения
			int pathFlow = INT_MAX;
			for (v = t; v != s; ) {				// идем по предкам от стока к истоку
				u = p[v];									// для определения начала дуги
				pathFlow = std::min(pathFlow, flows[u][v]);
				v = p[v];
			}

			for (v = t; v != s; ) {				// изменяем потоки и пропускные способности
				u = p[v];
				flows[u][v] -= pathFlow;
				flows[v][u] += pathFlow;
				v = p[v];
			}

			maxFlow += pathFlow;
			lastIter = bfsForFordFulkerson(flows, s, t, p);
		}

		return maxFlow;
	}

};
