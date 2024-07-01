///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
#include "Stntuple/scripts/global_vars.h"
#include "Stntuple/ana/scripts/modules.hh"

def_name prodTgtAna_helix_001("prodTgtAna_helix_ana");
def_name prodTgtAna_helix_002("prodTgtAna_helix_ana_old");


//-----------------------------------------------------------------------------
void  prodTgtAna_helix_ana(int DebugBit = -1) {
  prodTgtAna::m_hel = (prodTgtAna::THelixAnaModule*) g.x->AddModule("prodTgtAna::THelixAnaModule",0);  

  if (DebugBit >= 0)prodTgtAna::m_hel->SetDebugBit(DebugBit,1);
}
//-----------------------------------------------------------------------------
void  prodTgtAna_helix_ana_old(int DebugBit = -1) {
  prodTgtAna::m_hel = (prodTgtAna::THelixAnaModule*) g.x->AddModule("stntupel::THelixAnaModule",0);

  prodTgtAna::m_hel->SetHelixBlockName("HelixBlock");

  if (DebugBit >= 0) prodTgtAna::m_hel->SetDebugBit(DebugBit,1);
}
