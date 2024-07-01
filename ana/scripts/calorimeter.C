///////////////////////////////////////////////////////////////////////////////
// 
///////////////////////////////////////////////////////////////////////////////
#include "Stntuple/scripts/global_vars.h"
#include "Stntuple/ana/scripts/modules.hh"

def_name prodTgtAna_cal_001("prodTgtAna_cluster_ana");
///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
// configure jobs
//-----------------------------------------------------------------------------
void  prodTgtAna_cluster_ana(int DebugBit = -1) {
  prodTgtAna::m_cls = (prodTgtAna::TClusterAnaModule*) g.x->AddModule("prodTgtAna::TClusterAnaModule",0);  
  if (DebugBit >= 0) prodTgtAna::m_cls->SetDebugBit(DebugBit,1);
}





