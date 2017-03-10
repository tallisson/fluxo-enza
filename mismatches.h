#ifndef MISMATCHES_H_
#define MISMATCHES_H_

#include "graph.h"

#include <armadillo>

using namespace arma;

namespace lf
{

class Mismatch
{
private:
	vec m_mis;

	void CalcPkB(Graph* graph);
	void CalcQkB(Graph* graph);
public:
	Mismatch();
	virtual ~Mismatch();

	vec CalcMismatches(Graph* graph);

	vec GetMis(void);
};

}

#endif  // MISMATCHES_H_
