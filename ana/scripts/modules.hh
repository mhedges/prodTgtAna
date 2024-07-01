#ifndef prodTgtAna_ana_scripts_modules_hh
#define prodTgtAna_ana_scripts_modules_hh

#include "prodTgtAna/ana/TClusterAnaModule.hh"
#include "prodTgtAna/ana/TCrvAnaModule.hh"
#include "prodTgtAna/ana/TGenAnaModule.hh"
#include "prodTgtAna/ana/THelixAnaModule.hh"
#include "prodTgtAna/ana/TSpmcAnaModule.hh"
#include "prodTgtAna/ana/TTrackAnaModule.hh"
#include "prodTgtAna/ana/TTrackSeedAnaModule.hh"
#include "prodTgtAna/ana/TTriggerAnaModule.hh"

namespace prodTgtAna {
  prodTgtAna::TClusterAnaModule* m_cls     = nullptr;
  prodTgtAna::TCrvAnaModule*     m_crv     = nullptr;
  prodTgtAna::TGenAnaModule*     m_gen     = nullptr;
  prodTgtAna::THelixAnaModule*   m_hel     = nullptr;
  prodTgtAna::TSpmcAnaModule*    m_spmc    = nullptr;
  prodTgtAna::TTrackAnaModule*   m_trk     = nullptr;
  prodTgtAna::TTrackSeedAnaModule* m_trs     = nullptr;
  prodTgtAna::TTriggerAnaModule* m_trig    = nullptr;
}
#endif
