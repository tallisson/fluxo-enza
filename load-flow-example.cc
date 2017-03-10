/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#include <iostream>
#include "load-flow.h"

using namespace lf;
using namespace std;

int 
main (int argc, char *argv[])
{
  bool verbose = true;

  LoadFlow* load = new LoadFlow;
  //lf->Prepare("/home/thiago/pwns-ns-3/scratch/4_bus.txt");
  load->Prepare("/home/thiago/pwns-ns-3/scratch/4_bus1.txt");
  load->SetDir ("/home/thiago/pwns-ns-3/resultados-fluxo");
  load->SetFile ("teste_4_bus.cdf");


  //std::cout << lf->GetGraph()->GetBus(2)->GetBus ().m_ord << std::endl;
  load->Execute();

  /* ... */

  /*Simulator::Run ();
  Simulator::Destroy ();*/
  delete load;
  return 0;
}


