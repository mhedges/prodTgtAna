///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
#include "Stntuple/scripts/global_vars.h"
#include "Stntuple/ana/scripts/modules.hh"

def_name prodTgtAna_trk_001("prodTgtAna_trk_ana");
def_name prodTgtAna_trk_002("prodTgtAna_trk_ana_05");

void prodTgtAna_trk_ana(const char* TrackBlockName = "TrackBlock", int PdgCode = 11, int GeneratorCode = 56) {
//-----------------------------------------------------------------------------
// configure validation module
//-----------------------------------------------------------------------------
  prodTgtAna::m_trk = (prodTgtAna::TTrackAnaModule*) g.x->AddModule("prodTgtAna::TTrackAnaModule",0);  

  prodTgtAna::m_trk->SetTrackBlockName(TrackBlockName);
  prodTgtAna::m_trk->SetPdgCode       (PdgCode);
  prodTgtAna::m_trk->SetGeneratorCode (GeneratorCode);
}


void prodTgtAna_trk_ana_05(const char* TrackBlockName = "TrackBlock", int PdgCode = 11, int GeneratorCode = 56) {
//-----------------------------------------------------------------------------
// configure validation module
//-----------------------------------------------------------------------------
  prodTgtAna::m_trk = (prodTgtAna::TTrackAnaModule*) g.x->AddModule("prodTgtAna::TTrackAnaModule",0);  

  prodTgtAna::m_trk->SetTrackBlockName(TrackBlockName);
  prodTgtAna::m_trk->SetPdgCode       (PdgCode);
  prodTgtAna::m_trk->SetGeneratorCode (GeneratorCode);

  prodTgtAna::m_trk->SetBField (0.5);
}
