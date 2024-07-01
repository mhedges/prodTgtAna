///////////////////////////////////////////////////////////////////////////////
// 
///////////////////////////////////////////////////////////////////////////////
#include "Stntuple/ana/scripts/modules.hh"

def_name prodTgtAna_spmc_001("prodTgtAna_spmc_ana");
def_name prodTgtAna_spmc_002("prodTgtAna_spmc_g4s4_ana");
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
void  prodTgtAna_spmc_ana(int DebugBit = -1) {
  prodTgtAna::m_spmc = (prodTgtAna::TSpmcAnaModule*) g.x->AddModule("prodTgtAna::TSpmcAnaModule",0);  
  if (DebugBit >= 0) prodTgtAna::m_spmc->SetDebugBit(DebugBit,1);
}

//-----------------------------------------------------------------------------
void  prodTgtAna_spmc_g4s4_ana(int DebugBit = -1) {
  prodTgtAna::m_spmc = (prodTgtAna::TSpmcAnaModule*) g.x->AddModule("prodTgtAna::TSpmcAnaModule",0);  
  prodTgtAna::m_spmc->SetSpmcBlockName("SpmcTrackerBlock");
  prodTgtAna::m_spmc->SetVDetBlockName("SpmcVDetBlock");
  if (DebugBit >= 0) prodTgtAna::m_spmc->SetDebugBit(DebugBit,1);
}

