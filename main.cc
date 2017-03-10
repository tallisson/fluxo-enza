#include "bus.h"
#include <iostream>

using namespace std;
using namespace lf;

/*int main(int argc, char const *argv[])
{
	DBus_t data;
	data.m_nin = 1;
	data.m_tipo = Bus::LOAD;
	data.m_pc = 80;
	data.m_qc = 20;
	data.m_pg = 0;
	data.m_qg = 0;
	data.m_v = 0;
	data.m_ang = 0;

	Bus* b = new Bus();
	b->SetBus(data);

	DBus_t data1;
	data1.m_nin = 2;
	data1.m_tipo = Bus::LOAD;
	data1.m_pc = 0;
	data1.m_qc = 10;
	data1.m_pg = 0;
	data1.m_qg = 0;
	data1.m_v = 0;
	data1.m_ang = 0;

	Bus* b1 = new Bus();
	b1->SetBus(data1);

	std::cout << b->GetBus().m_pc << std::endl;
	std::cout << b1->GetBus().m_pc << std::endl;

	DBranch_t dataBranch;
	dataBranch.m_ni = 1;
	dataBranch.m_nf = 2;
	dataBranch.m_r = 0.02;
	dataBranch.m_x = 0.06;
	dataBranch.m_tipo = 0;

	lf::Branch* branch = new Branch();
	branch->SetBranch(dataBranch);

	return 0;
}*/
