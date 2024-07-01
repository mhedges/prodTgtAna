///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
#include "Stntuple/scripts/global_vars.h"
#include "Stntuple/ana/scripts/modules.hh"

def_name prodTgtAna_trs_001("prodTgtAna_trs_ana");

void prodTgtAna_trs_ana(int DebugBit = -1, int PdgCode = 11, int GeneratorCode = 2) {
//-----------------------------------------------------------------------------
// configure validation module
//-----------------------------------------------------------------------------
  prodTgtAna::m_trs = (prodTgtAna::TTrackSeedAnaModule*) g.x->AddModule("prodTgtAna::TTrackSeedAnaModule",0);  
  prodTgtAna::m_trs->SetPdgCode      (PdgCode);
  prodTgtAna::m_trs->SetGeneratorCode(GeneratorCode);

  if (DebugBit >= 0) prodTgtAna::m_trs->SetDebugBit(DebugBit,1);
}
