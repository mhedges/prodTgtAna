///////////////////////////////////////////////////////////////////////////////
// 
///////////////////////////////////////////////////////////////////////////////
#include "Stntuple/scripts/global_vars.h"
#include "Stntuple/ana/scripts/modules.hh"

def_name prodTgtAna_trigger_0010("prodTgtAna_trigger_ana");
///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
void  prodTgtAna_trigger_ana(int PdgCode = 11, int ProcessCode = 7, int DebugBit = -1) {
//-----------------------------------------------------------------------------
// configure analysis module
//-----------------------------------------------------------------------------
  prodTgtAna::m_trig = (prodTgtAna::TTriggerAnaModule*) g.x->AddModule("prodTgtAna::TTriggerAnaModule",0);
  prodTgtAna::m_trig->SetPdgCode(PdgCode);
  prodTgtAna::m_trig->SetProcessCode(ProcessCode);
  if (DebugBit >= 0) {
    prodTgtAna::m_trig->SetDebugBit(DebugBit,1);
  }
}

