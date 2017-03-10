#ifndef LOAD_FLOW_H_
#define LOAD_FLOW_H_

#include "graph.h"
#include "jacobian.h"
#include "mismatches.h"
#include "utils.h"
#include "report.h"
#include "io-utils.h"

#include <string>

namespace lf
{

class LoadFlow
{
private:
	Graph* m_graph;
	//Control* m_qControl;
	Mismatch* m_mismatches;
	Jacobian* m_jac;
	Report* m_report;
	//Ptr<VControl> m_vControl;

	Sts_t m_sts;

	double m_precision;
	double m_totalL;
	uint32_t m_iter;
	uint32_t m_maxIter;

	vec m_losses;
	vec m_b;

	void InitX0(void);

	void InitJ(void);

	void CalcLosses(void);

	bool m_verbose;

	std::string m_dir;
	std::string m_file;
public:
	LoadFlow(void);
	virtual ~LoadFlow(void);

	Graph* GetGraph(void) const;
	//void SetGraph(Graph* graph);

	//Control* GetQControl(void) const;
	//void SetQControl(Control* qControl);

	//void SetVControl (Ptr<VControl> vControl);

	void Prepare(std::string cdf);

	void Execute();

	void SetPrecision(double precision);

	void SetDir(std::string dir);

	void SetFile(std::string file);

	void Reset (void);
};

}

#endif /* LOAD_FLOW */
