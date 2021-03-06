// NQueen.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"


class Node {
public:
	std::vector<int> Row = {};
	int heuristic = 0;
	int Size;

public:
	Node() {
		HeuristicCalculate();
	}
	Node(int planeSize) {
		Size = planeSize;
		Row.assign(planeSize, -1);
		HeuristicCalculate();
	}

	Node(int planeSize, int firstvalue) {
		Size = planeSize;
		Row.assign(planeSize, firstvalue);
		HeuristicCalculate();
	}

	Node(const Node& curr, int N) {
		Size = N;
		Row = curr.Row;
		HeuristicCalculate();
	}

	~Node() {};

	void HeuristicCalculate() {
		heuristic = 0;
		for (int i = 0; i<Size; ++i) {
			if (Row[i] == -1) {
				heuristic += 1;
			}
			for (int j = 0; j < Size; ++j) {
				if (i != j) {
					if (Row[i] == Row[j]) {
						heuristic++;
					}
					if (abs(Row[i] - Row[j]) == abs(i - j)) {
						heuristic++;
					}
				}
			}
		}
	};
};


void SearchAStar(int planeSize);
void SearchHillC(int planeSize);
void SearchRandomRestartHillC(int planeSize);


int main()
{
	int planeSize = 0;
	int searchType = 0;
	bool loop = true;

	while (loop)
	{
		std::cout << " input N" << std::endl;
		std::cin >> planeSize;

		if (planeSize <= 4) planeSize = 4;

		std::cout << std::endl;

		std::cout << "검색 타입" << std::endl;
		std::cout << "1. A*" << std::endl;
		std::cout << "2. Hill" << std::endl;
		std::cout << "3. Random" << std::endl;
		std::cout << "4. Exit" << std::endl;
		std::cin >> searchType;

		switch (searchType)
		{
		case 1:
			SearchAStar(planeSize);
			break;
		case 2:
			SearchHillC(planeSize);
			break;
		case 3:
			SearchRandomRestartHillC(planeSize);
			break;
		case 4:
			loop = false;
			break;
		default:
			break;
		}
	}

    return 0;
}

void SearchAStar(int planeSize)
{
	Node* Dest = nullptr;

	std::vector<Node*>	m_Visited;

	std::vector<int>	m_GCosts;
	std::vector<int>	m_FCosts;

	m_GCosts.assign(MAXSIZE, 0);
	m_FCosts.assign(MAXSIZE, 0);

	IndexedPriorityQLow<int> pq(m_FCosts, MAXSIZE);

	//put the source node on the queue
	pq.insert(0);

	m_Visited.push_back(new Node(planeSize));

	//while the queue is not empty
	while (!pq.empty())
	{
		//get lowest cost node from the queue
		int NextClosestNode = pq.Pop();

		//move this node from the frontier to the spanning tree
		Node* m_CurrNode = m_Visited[NextClosestNode];

		//if the target has been found exit
		if (m_CurrNode->heuristic == 0) {
			Dest = new Node(*m_CurrNode, planeSize);
			break;
		}

		for (int i = 0; i < planeSize; ++i)
		{
			if (m_CurrNode->Row[i] == -1) {
				for (int j = 0; j < planeSize; ++j) {
					Node* NextNode = new Node(*m_CurrNode, planeSize);

					NextNode->Row[i] = j;
					NextNode->HeuristicCalculate();

					int HCost = NextNode->heuristic;
					int GCost = m_GCosts[NextClosestNode] + 1;

					m_Visited.push_back(NextNode);

					m_FCosts[m_Visited.size() - 1] = GCost + HCost;
					m_GCosts[m_Visited.size() - 1] = GCost;

					pq.insert(m_Visited.size() - 1);
				}
				break;
			}
		}
	}

	for (int i = 0; i < planeSize; ++i) {
		for (int j = 0; j < planeSize; ++j) {
			if (Dest->Row[i] == j) std::cout << "★";
			else std::cout << "□";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void SearchHillC(int planeSize) {
	Node* Dest = nullptr;

	std::vector<Node*>	m_Visited;
	std::vector<int>	m_FCosts;

	m_FCosts.assign(MAXSIZE, 0);

	IndexedPriorityQLow<int> pq(m_FCosts, MAXSIZE);

	//put the source node on the queue
	pq.insert(0);

	m_Visited.push_back(new Node(planeSize, 0));

	//while the queue is not empty
	while (!pq.empty())
	{
		//get lowest cost node from the queue
		int NextClosestNode = pq.Pop();

		//move this node from the frontier to the spanning tree
		Node* m_CurrNode = m_Visited[NextClosestNode];

		//if the target has been found exit
		if (m_CurrNode->heuristic == 0) {
			Dest = new Node(*m_CurrNode, planeSize);
			break;
		}

		for (int i = 0; i < planeSize; ++i)
		{
			for (int j = 0; j < planeSize; ++j) {
				Node* NextNode = new Node(*m_CurrNode, planeSize);

				NextNode->Row[i] = j;
				NextNode->HeuristicCalculate();

				int HCost = NextNode->heuristic;

				if (NextNode->heuristic < m_Visited[NextClosestNode]->heuristic) {
					m_Visited.push_back(NextNode);

					m_FCosts[m_Visited.size() - 1] = HCost;

					pq.insert(m_Visited.size() - 1);
				}
			}
		}
	}

	for (int i = 0; i < planeSize; ++i) {
		for (int j = 0; j < planeSize; ++j) {
			if (Dest->Row[i] == j) std::cout << "★";
			else std::cout << "□";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void SearchRandomRestartHillC(int planeSize) {
	Node* Dest = nullptr;
	int sideway = 0;

	std::vector<Node*>	m_Visited;
	std::vector<int>	m_FCosts;

	m_FCosts.assign(MAXSIZE, 0);

	IndexedPriorityQLow<int> pq(m_FCosts, MAXSIZE);

	//put the source node on the queue
	pq.insert(0);

	m_Visited.push_back(new Node(planeSize, 0));

	//while the queue is not empty
	while (!pq.empty())
	{
		//get lowest cost node from the queue
		int NextClosestNode = pq.Pop();

		//move this node from the frontier to the spanning tree
		Node* m_CurrNode = m_Visited[NextClosestNode];

		//if the target has been found exit
		if (m_CurrNode->heuristic == 0) {
			Dest = new Node(*m_CurrNode, planeSize);
			break;
		}

		for (int i = 0; i < planeSize; ++i)
		{
			for (int j = 0; j < planeSize; ++j) {
				Node* NextNode = new Node(*m_CurrNode, planeSize);

				NextNode->Row[i] = j;
				NextNode->HeuristicCalculate();

				int HCost = NextNode->heuristic;

				if (NextNode->heuristic == m_Visited[NextClosestNode]->heuristic) {
					sideway++;

					if (sideway > 10)
					{
						m_Visited.push_back(new Node(planeSize));

						pq.insert(m_Visited.size() - 1);

						sideway = 0;
					}
				}

				if (NextNode->heuristic < m_Visited[NextClosestNode]->heuristic) {
					m_Visited.push_back(NextNode);

					m_FCosts[m_Visited.size() - 1] = HCost;

					pq.insert(m_Visited.size() - 1);
				}
			}
		}
	}

	for (int i = 0; i < planeSize; ++i) {
		for (int j = 0; j < planeSize; ++j) {
			if (Dest->Row[i] == j) std::cout << "★";
			else std::cout << "□";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}