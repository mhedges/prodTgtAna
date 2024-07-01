///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
#include "Stntuple/scripts/global_vars.h"
#include "modules.hh"

def_name prodTgtAna_crv_001("prodTgtAna_crv_ana");

//-----------------------------------------------------------------------------
void  prodTgtAna_crv_ana(int UseAllPulses = 0, int DebugBit = -1) {
  prodTgtAna::m_crv = (prodTgtAna::TCrvAnaModule*) g.x->AddModule("prodTgtAna::TCrvAnaModule",0);  

  prodTgtAna::m_crv->SetUseAllPulses(UseAllPulses);

  if (DebugBit >= 0)prodTgtAna::m_crv->SetDebugBit(DebugBit,1);
}
