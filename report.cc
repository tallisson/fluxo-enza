/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2016 UFPI (Universidade Federal do Piauí)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Thiago Allisson <allissonribeiro02@gmail.com>
 * Author: Enza Rafaela <enzasampaiof@hotmail.com>
 */

#include "report.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>

namespace lf
{

Report::Report(void)
{
}

Report::~Report(void)
{
}

void
Report::StoreData(Graph* graph, double base)
{
	for(int i = 0; i < graph->GetNumBus (); i++)
		{
			Bus* bus = graph->GetBus (i + 1);
			double a, v, pg, qg;
			a = bus->GetACalc();
			v = bus->GetVCalc();
			pg = bus->GetPCalc();
			qg = bus->GetQCalc();

			DBus_t dataBus = bus->GetBus ();
			dataBus.m_ang = a * M_PI;
			dataBus.m_v = v;
			dataBus.m_pc = dataBus.m_pc * base;
			dataBus.m_qc = dataBus.m_qc * base;
			dataBus.m_pg = pg * base;
			dataBus.m_qg = qg * base;
			dataBus.m_crt = bus->GetCrt ();

			std::map<int, std::vector<TBus_t> >::iterator it =
						m_states.find (dataBus.m_nin);
			std::vector<TBus_t> vector;
			if(it != m_states.end ())
				{
					vector = it->second;
					TBus_t bt;
					bt.m_data = dataBus;
					bt.m_crt = bus->GetCrt ();
					vector.push_back (bt);
					it->second = vector;
				}
			else
				{
					TBus_t bt;
					bt.m_data = dataBus;
					bt.m_crt = bus->GetCrt ();
					vector.push_back (bt);
					m_states.insert (std::pair<int, std::vector<TBus_t> > (dataBus.m_nin, vector));
				}
		}
}

void
Report::StoreL(double l)
{
	m_l.push_back (l);
}

void
Report::Save (Graph* graph)
{
	/******************************************************/
	std::ofstream fileV, fileVL, fileQg, fileCrt;
	std::ostringstream osV, osQg, osVL, osCrt;
	fileV.open (m_fileV.c_str ());
	fileQg.open (m_fileQg.c_str ());
	fileVL.open (m_fileVL.c_str ());
	fileCrt.open(m_fileCrt.c_str ());

	if (fileV.is_open ())
		{
			std::cout << "Size = " << m_states.size () << std::endl;
			for(int i = 1; i <= m_states.size (); i++)
				{
					std::vector<TBus_t> vector = m_states.find(i)->second;
					if (vector.at(0).m_data.m_tipo != Bus::LOAD)
						{
							osV << i << "=>\t";
							osQg << i << "=>\t";
							for(int j = 0; j < vector.size (); j++)
								{
									osV << IOUtils::Format (vector.at (j).m_data.m_v) << " ";
									osQg << IOUtils::Format (vector.at (j).m_data.m_qg) << " ";
								}
							osV << "\n";
							osQg << "\n";
						}
					if (graph->GetBus (i)->IsControlled ())
						{
							osVL << i << "=>\t";
							for (int j = 0; j < vector.size (); j++)
								{
									osVL << IOUtils::Format (vector.at (j).m_data.m_v) << " ";
								}
							osVL << "\n";
						}
					if(graph->GetBus (i)->GetType () != Bus::LOAD)
						{
							osCrt << i << "=>\t";
							for (int j = 0; j < vector.size (); j++)
								{
									osCrt << IOUtils::Format (vector.at (j).m_data.m_crt, 10, 12) << " ";
								}
							osCrt << "\n";
						}
				}
			fileV << osV.str ();
			fileQg << osQg.str ();
			fileVL << osVL.str ();
			fileCrt << osCrt.str ();
			fileV.close ();
			fileQg.close ();
			fileVL.close ();
			fileCrt.close ();
		}
	/******************************************************/
	std::ofstream fileState;
	std::ostringstream osS;
	//fileState.open (m_fileState.c_str (), std::ofstream::app);
	fileState.open (m_fileState.c_str ());

	if (fileState.is_open ())
		{
			for(int i = 1; i <= m_states.size (); i++)
				{
					std::vector<TBus_t> vector = m_states[i];
					for(int j = 0; j < vector.size (); j++)
						{
							osS << i << "=>\t"
									<< "[ " << IOUtils::Format (vector.at (j).m_data.m_v, 8, 10) << " "
									//<< IOUtils::Format (vector.at (j).m_data.m_ang) << " "
									<< IOUtils::Format(vector.at (j).m_data.m_pc) << " "
									<< IOUtils::Format(vector.at (j).m_data.m_qc) << " "
									<< IOUtils::Format(vector.at (j).m_data.m_pg) << " "
									<< IOUtils::Format(vector.at (j).m_data.m_qg) << " ]\n"
						 ;
						}
					osS << "\n";
				}
			fileState << osS.str ();
			fileState.close ();
		}
	/******************************************************/
	std::ofstream fileL;
	std::ostringstream osL;
	//fileL.open (m_fileLTotal.c_str (), std::ofstream::app);
	fileL.open (m_fileLTotal.c_str ());

	if (fileL.is_open ())
		{
			for(int j = 0; j < m_l.size (); j++)
				{
					osL << (j+1) << IOUtils::Format(m_l.at (j)) << "\n";
				}

			fileL << osL.str ();
			fileL.close ();
		}
	/******************************************************/
}

void
Report::SetFileV (std::string fileV)
{
	m_fileV = fileV;
	m_fileVL = fileV;
	m_fileVL.append("l");
}

void
Report::SetFileQg (std::string fileQg)
{
	m_fileQg = fileQg;
}

void
Report::SetFileState(std::string fileState)
{
	m_fileState = fileState;
}

void
Report::SetFileLTotal(std::string fileLTotal)
{
	m_fileLTotal = fileLTotal;
}

void
Report::SetFileCrt(std::string crt)
{
	m_fileCrt = crt;
}

}
