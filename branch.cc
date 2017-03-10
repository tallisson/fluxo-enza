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

#include "branch.h"
 
#include <math.h>
#include <iostream>

namespace lf
{

Branch::Branch ()
{
}

Branch::~Branch ()
{
}

/*double
Branch::CalcPkm(double vK, double vM,
								double aK, double aM, double theta_km)
{
	m_p_km = m_branch.m_g * 1 / std::pow (m_branch.m_tap, 2) * std::pow (vK, 2) -
						1/m_branch.m_tap * vK * vM *
						( m_branch.m_g * cos (theta_km) + m_branch.m_b * sin (theta_km) );

	return m_p_km;
}

double
Branch::CalcPmk(double vK, double vM,
								double aK, double aM, double theta_km)
{
	m_p_mk = m_branch.m_g * std::pow (vM, 2) -
						1/m_branch.m_tap * vK * vM *
						( m_branch.m_g * cos (theta_km) - m_branch.m_b * sin (theta_km) );

	return m_p_mk;
}

double
Branch::CalcQkm(double vK, double vM,
								double aK, double aM, double theta_km)
{
	m_q_km = -( m_branch.m_b * ( 1 / std::pow (m_branch.m_tap, 2) ) + m_branch.bsh ) *
							std::pow (vK, 2) +
							1/m_branch.m_tap * vK * vM *
							( m_branch.m_b * cos (theta_km) - m_branch.m_g * sin (theta_km) );

	return m_q_km;
}

double
Branch::CalcQmk(double vK, double vM,
								double aK, double aM, double theta_km)
{
	m_q_mk = -( m_branch.m_b + m_branch.bsh ) * std::pow (vM, 2) +
								1/m_branch.m_tap * vK * vM *
								( m_branch.m_b * cos (theta_km) + m_branch.m_g * sin (theta_km) );

	return m_q_mk;
}*/

void
Branch::SetBranch(DBranch_t branch)
{
	m_branch = branch;
}

DBranch_t
Branch::GetBranch(void) const
{
	return m_branch;
}

double
Branch::CalcPkmL(double vK, double vM,
		double aK, double aM)
{
	// s.branch.g(i)*s.bus.v(k)^2 - s.bus.v(k)*s.bus.v(m)*(s.branch.g(i)*cos(akm)+s.branch.b(i)*sin(akm));
	double theta_km = aK - aM;
	m_p_km_L = GetBranch ().m_g * pow(vK, 2) -
			   vK * vM *
			   ( GetBranch ().m_g * cos (theta_km) + GetBranch ().m_b * sin (theta_km ) );

	return m_p_km_L;
}

double
Branch::CalcPmkL(double vK, double vM,
		double aK, double aM)
{
	// s.branch.g(i)*s.bus.v(m)^2 - s.bus.v(k)*s.bus.v(m)*(s.branch.g(i)*cos(akm)-s.branch.b(i)*sin(akm));
	double theta_km = aK - aM;
	m_p_mk_L = GetBranch ().m_g * pow(vM, 2) -
			   vK * vM *
			   (GetBranch ().m_g * cos(theta_km) - GetBranch ().m_b * sin(theta_km) );

	return m_p_mk_L;
}

double
Branch::CalcQkmL(double vK, double vM,
		double aK, double aM)
{
	// -(s.branch.b(i)+s.branch.bsh(i))*s.bus.v(k)^2 + s.bus.v(k)*s.bus.v(m)*(s.branch.b(i)*cos(akm)-s.branch.g(i)*sin(akm))
	double theta_km = aK - aM;
	m_q_km_L = -(GetBranch ().m_b + GetBranch ().m_bsh) * pow(vK, 2) +
				vK * vM *
				( GetBranch ().m_b * cos(theta_km) - GetBranch ().m_g * sin (theta_km) );

	return m_q_km_L;
}

double
Branch::CalcQmkL(double vK, double vM,
		double aK, double aM)
{
	// -(s.branch.b(i)+s.branch.bsh(i))*s.bus.v(m)^2 + s.bus.v(k)*s.bus.v(m)*(s.branch.b(i)*cos(akm)+s.branch.g(i)*sin(akm));
	double theta_km = aK - aM;
	m_q_mk_L = -(GetBranch ().m_b + GetBranch ().m_bsh) *
				pow(vM, 2) + vK * vM *
				( GetBranch ().m_b * cos (theta_km) + GetBranch ().m_g * sin (theta_km) );

	return m_q_mk_L;
}

double
Branch::CalcL (double vK, double vM,
		double aK, double aM)
{
	// s.branch.g(i)*(s.bus.v(k)^2 + s.bus.v(m)^2 - 2*s.bus.v(k)*s.bus.v(m)*cos(akm));
	double theta_km = aK - aM;
	m_l = GetBranch ().m_g *
		  ( pow(vK, 2) + pow(vM, 2) - 2 * vK * vM * cos (theta_km) );

	return m_l;
}

void
Branch::Print(void)
{
	std::cout << "Branch ( " << m_branch.m_ni << ", " << m_branch.m_nf << ") => "
			 	 	 	<< m_branch.m_b << "\t" << m_branch.m_bsh << "\t" << m_branch.m_g
						<< "\t" << m_branch.m_tap << "\t" << m_branch.m_def << std::endl;
}

}
