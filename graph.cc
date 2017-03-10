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

#include "graph.h"

namespace lf
{

Graph::Graph () :
	m_numBus(0), m_numBranch(0),
	m_numPQ (0), m_numPV (0),
	m_numSlack (0)
{
}

Graph::~Graph ()
{
	m_buses.clear ();
	m_numBus = 0;
	m_numBranch = 0;
	m_numPQ = 0;
	m_numPV = 0;
	m_numSlack = 0;
}

void
Graph::AddBus(Bus* bus)
{
	int id = bus->GetBus ().m_nin;
	m_buses.insert (std::pair<int, Bus* > (id, bus));
	m_numBus++;

	if (bus->GetBus ().m_tipo == Bus::SLACK)
		{
			bus->SetType (Bus::SLACK);
			bus->SetVCalc (bus->GetBus ().m_v);
			bus->SetACalc (bus->GetBus ().m_ang);
			m_numSlack++;
		}

	if (bus->GetBus ().m_tipo == Bus::GENERATION)
		{
			bus->SetType (Bus::GENERATION);
			bus->SetVCalc (bus->GetBus ().m_v);
			bus->SetPCalc (bus->GetBus ().m_pg);
			m_numPV++;
		}

	if (bus->GetBus ().m_tipo == Bus::LOAD
			|| bus->GetBus ().m_tipo == Bus::LOSS_CONTROL_REACT)
		{
			if (bus->GetBus ().m_tipo == 0)
				{
					bus->SetType (Bus::LOAD);
				}
			else if(bus->GetBus ().m_tipo == 4)
				{
					bus->SetType (Bus::LOSS_CONTROL_REACT);
				}
			bus->SetPCalc (bus->GetBus ().m_pg);
			bus->SetQCalc (bus->GetBus ().m_qg);
			m_numPQ++;
		}

}

void
Graph::Assoc(Branch* branch)
{
	int idK = branch->GetBranch ().m_nf;
	int idM = branch->GetBranch ().m_ni;

	std::map<int, Bus* >::iterator itK, itM;
	Bus* busK = m_buses.find(idK)->second;
	Bus* busM = m_buses.find(idM)->second;

	busK->AddBranch (branch, busM);
	busM->AddBranch (branch, busK);

	m_branches.push_back (branch);
	m_numBranch++;
}

std::map<int, Bus* >
Graph::GetBuses() const
{
	return m_buses;
}

int
Graph::GetNumBus() const
{
	return m_numBus;
}

int
Graph::GetNumBranch() const
{
	return m_numBranch;
}

Bus*
Graph::GetBus(int idBus)
{
	std::map<int, Bus* >::iterator it = m_buses.find (idBus);
	Bus* bus = 0;
	if (it != m_buses.end ())
		{
			bus = it->second;
		}

	return bus;
}

std::vector<Branch* >
Graph::GetBranches() const
{
	return m_branches;
}

int
Graph::GetPosSlack(void) const
{
	return m_posSlack;
}

void
Graph::SetPosSlack (int posSlack)
{
	m_posSlack = posSlack;
}

int
Graph::GetNumPQ () const
{
	return m_numPQ;
}

void
Graph::SetNumPQ (int numPQ)
{
	m_numPQ = numPQ;
}

int
Graph::GetNumPV () const
{
	return m_numPV;
}

void
Graph::SetNumPV (int numPV)
{
	m_numPV = numPV;
}

}
