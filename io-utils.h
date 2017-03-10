#ifndef IO_UTILS_H_
#define IO_UTILS_H_

#include "graph.h"

#include <vector>
#include <string>

namespace lf
{

struct data
{
public:
	std::string m_label;
	double m_value;
};

typedef data Data_t;

class IOUtils {
public:
	IOUtils();
	virtual ~IOUtils();

	static std::string Print(std::vector<Data_t> values, int numSpace = 8);

	static std::string Format(double v, int p = 5, int maxS = 10);

	static std::string Format (std::string v, int maxS = 9);

	static std::string WriteCdf(Graph* graph, double getBase);

	static std::string WriteCnz(Graph* graph, double getBase);

	static void WriteFile (std::string filename, int choose, Graph* graph, double base = 100);

	static const std::string SEP;
};

}

#endif /* BRANCH_H_ */
