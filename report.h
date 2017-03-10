#ifndef REPORT_H_
#define REPORT_H_

#include "graph.h"
#include <map>
#include <string>
#include <vector>

namespace lf
{

struct TBus {
public:
	DBus_t m_data;
	double m_crt;
};

typedef TBus TBus_t;

class Report {
public:
	Report(void);

	~Report(void);

	void StoreData(Graph* graph, double base);

	void StoreL(double l);

	void Save(Graph* graph);

	void SetFileLTotal(std::string fileLTotal);

	void SetFileCrt(std::string crt);

	void SetFileQg(std::string fileQg);

	void SetFileV(std::string fileV);

	void SetFileState(std::string fileState);
private:
	std::string m_fileV;

	std::string m_fileQg;

	std::string m_fileState;

	std::string m_fileL_km;

	std::string m_fileLTotal;

	std::string m_fileCrt;

	std::string m_fileVL;

	std::map<int, std::vector<TBus_t> > m_states;

	std::vector<double> m_l;
};

}

#endif /*REPORT_H_*/
