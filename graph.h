#ifndef GRAPH_H_
#define GRAPH_H_

#include "branch.h"
#include "bus.h"

#include <string>
#include <map>

namespace lf {

class Graph
{
private:
	int m_numBus;
	int m_numBranch;

	int m_numPQ;
	int m_numPV;
	int m_numSlack;
	int m_posSlack;
	//int m_noSlack;

	std::map<int, Bus* > m_buses;
	std::vector<Branch* > m_branches;

public:
	Graph();
	virtual ~Graph();

	void AddBus(Bus* bus);
	void Assoc(Branch* branch);

	int GetPosSlack(void) const;
	void SetPosSlack (int posSlack);

	std::map<int, Bus* > GetBuses() const;
	Bus* GetBus(int idBus);

	std::vector<Branch* > GetBranches() const;

	int GetNumBus() const;
	int GetNumBranch() const;

	int GetNumPQ() const;
	void SetNumPQ (int numPQ);

	void SetNumPV (int numPV);
	int GetNumPV() const;
};

}

#endif  // GRAPH_H_
