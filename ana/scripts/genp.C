///////////////////////////////////////////////////////////////////////////////
// 
///////////////////////////////////////////////////////////////////////////////
#include "modules.hh"

def_name prodTgtAna_genp_001("prodTgtAna_genp_ana");
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
void  prodTgtAna_genp_ana(int DebugBit = -1) {
  prodTgtAna::m_gen = (prodTgtAna::TGenAnaModule*) g.x->AddModule("prodTgtAna::TGenAnaModule",0);  
  if (DebugBit >= 0) prodTgtAna::m_gen->SetDebugBit(DebugBit,1);
}
