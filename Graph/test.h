#pragma once
#include <string>
//#include "Graph.h"

void testOrientGraph() {
	Graph orGr("orGr");

	orGr.addVertex("6");
	orGr.printGraphToFile("orGr_add6");

	int bNum = orGr.getVertNumber("6");
	int eNum = orGr.getVertNumber("5");
	Vertex b = Vertex(bNum, "6");
	Vertex e = Vertex(eNum, "5");
	orGr.addEdge(b, e, 10);
	orGr.printGraphToFile("orGr_addE6-5");

	bNum = orGr.getVertNumber("5");
	eNum = orGr.getVertNumber("2");
	b = Vertex(bNum, "5");
	e = Vertex(eNum, "2");
	orGr.deleteEdge(b, e);
	orGr.printGraphToFile("orGr_delE5-2");

	int vNum = orGr.getVertNumber("4");
	Vertex v = Vertex(vNum, "4");
	orGr.deleteVertex(v);
	orGr.printGraphToFile("orGr_delV4");

	Graph orGrCopy = Graph(orGr);
	orGrCopy.printGraphToFile("orGr_Copy");
}

void testNoOrientGraph() {
	Graph noOrGr("noOrGr");

	noOrGr.addVertex("6");
	noOrGr.printGraphToFile("noOrGr_add6");

	int bNum = noOrGr.getVertNumber("6");
	int eNum = noOrGr.getVertNumber("3");
	Vertex b = Vertex(bNum, "6");
	Vertex e = Vertex(eNum, "3");
	noOrGr.addEdge(b, e, 0);
	noOrGr.printGraphToFile("noOrGr_addE6-3");

	bNum = noOrGr.getVertNumber("2");
	eNum = noOrGr.getVertNumber("4");
	b = Vertex(bNum, "2");
	e = Vertex(eNum, "4");
	noOrGr.deleteEdge(b, e);
	noOrGr.printGraphToFile("noOrGr_delE2-4.txt");

	int vNum = noOrGr.getVertNumber("3");
	Vertex v = Vertex(vNum, "3");
	noOrGr.deleteVertex(3);
	noOrGr.printGraphToFile("noOrGr_delV3");

	Graph noOrGrCopy = Graph(noOrGr);
	noOrGrCopy.printGraphToFile("noOrGr_Copy");
}