#include <iostream>
#include <fstream>
#include <experimental/filesystem>

#include "TH1F.h"
#include "TH3F.h"
#include "TString.h"
#include "TFile.h"
#include "TVector3.h"

void concatHists(TString outfile, const int nInputFiles, std::string fpath){

    std::unique_ptr<TFile> fOut( TFile::Open(outfile, "RECREATE") );

    int nbinsx = 401;
    float xmin = -200.5;
    float xmax = 200.5;

    int nbinsy = 401;
    float ymin = -200.5;
    float ymax = 200.5;

    int nbinsz = 241;
    float zmin = -120.5;
    float zmax = 120.5;

    TH3F* hCoresHitsXYZEdep       = new TH3F ("hCoresHitsXYZEdep"      ,"Binned EDep (1mm3)",nbinsx,xmin,xmax,nbinsy,ymin,ymax,nbinsz,zmin,zmax);
    TH3F* hFinsHitsXYZEdep        = new TH3F ("hFinsHitsXYZEdep"       ,"Binned EDep (1mm3)",nbinsx,xmin,xmax,nbinsy,ymin,ymax,nbinsz,zmin,zmax);
    TH3F* hEndRingsHitsXYZEdep    = new TH3F ("hEndRingsHitsXYZEdep"   ,"Binned EDep (1mm3)",nbinsx,xmin,xmax,nbinsy,ymin,ymax,nbinsz,zmin,zmax);
    TH3F* hSupportRingHitsXYZEdep = new TH3F ("hSupportRingHitsXYZEdep","Binned EDep (1mm3)",nbinsx,xmin,xmax,nbinsy,ymin,ymax,nbinsz,zmin,zmax);
    TH3F* hSpokeWiresHitsXYZEdep  = new TH3F ("hSpokeWiresHitsXYZEdep" ,"Binned EDep (1mm3)",nbinsx,xmin,xmax,nbinsy,ymin,ymax,nbinsz,zmin,zmax);

    int nReadFiles = 0;
    std::cout << "  Analyzing " << nInputFiles << " input files:" << std::endl;
    //for (const auto& entry : std::filesystem::directory_iterator("/exp/mu2e/data/users/mhedges/projects/prodtgt/prodtgt.haymanFast/"))
    for (const auto& entry : std::filesystem::directory_iterator(fpath))
    {
        if (nReadFiles >= nInputFiles) break;
        //TFile* fEDep = new TFile(entry.path().c_str());
        std::unique_ptr<TFile> fEDep( TFile::Open(entry.path().c_str()) );

        // Cores
        TH3F* hCores           = (TH3F*)fEDep->Get("prodCore/_hHitsXYZEdep");
        hCoresHitsXYZEdep->Add(hCores);
        delete hCores;
        TH3F* hCoresStarts     = (TH3F*)fEDep->Get("prodStartingCore/_hHitsXYZEdep");
        hCoresHitsXYZEdep->Add(hCoresStarts);
        delete hCoresStarts;

        // Fins
        TH3F* hFins            = (TH3F*)fEDep->Get("prodFinSection/_hHitsXYZEdep");
        hFinsHitsXYZEdep->Add(hFins);
        delete hFins;
        TH3F* hFinsStarts      = (TH3F*)fEDep->Get("prodStartingFin/_hHitsXYZEdep");
        hFinsHitsXYZEdep->Add(hFinsStarts);
        delete hFinsStarts;
        TH3F* hFinsTops        = (TH3F*)fEDep->Get("prodFinTopSection/_hHitsXYZEdep");
        hFinsHitsXYZEdep->Add(hFinsTops);
        delete hFinsTops;
        TH3F* hFinsTopsStarts  = (TH3F*)fEDep->Get("prodFinTopStartingSection/_hHitsXYZEdep");
        hFinsHitsXYZEdep->Add(hFinsTopsStarts);
        delete hFinsTopsStarts;

        // End Rings
        TH3F* hPositiveEndRing = (TH3F*)fEDep->Get("prodPositiveEndRing/_hHitsXYZEdep");
        hEndRingsHitsXYZEdep->Add(hPositiveEndRing);
        delete hPositiveEndRing;
        TH3F* hNegativeEndRing = (TH3F*)fEDep->Get("prodNegativeEndRing/_hHitsXYZEdep");
        hEndRingsHitsXYZEdep->Add(hNegativeEndRing);
        delete hNegativeEndRing;

        // Support Wheel
        TH3F* hSupportWheel    = (TH3F*)fEDep->Get("prodSupportWheel/_hHitsXYZEdep");
        hSupportRingHitsXYZEdep->Add(hSupportWheel);
        delete hSupportWheel;

        // Spokes
        TH3F* hSpokeWire       = (TH3F*)fEDep->Get("prodSpokeWire/_hHitsXYZEdep");
        hSpokeWiresHitsXYZEdep->Add(hSpokeWire);
        delete hSpokeWire;

        fEDep.reset(); // same as "delete" for a unique_ptr

        ++nReadFiles;

        std::cout << "  Completed file " << nReadFiles << std::endl;
    }

    fOut->WriteObject(hCoresHitsXYZEdep       ,"hCoresHitsXYZEdep"      );
    fOut->WriteObject(hFinsHitsXYZEdep        ,"hFinsHitsXYZEdep"       );
    fOut->WriteObject(hEndRingsHitsXYZEdep    ,"hEndRingsHitsXYZEdep"   );
    fOut->WriteObject(hSupportRingHitsXYZEdep ,"hSupportRingHitsXYZEdep");
    fOut->WriteObject(hSpokeWiresHitsXYZEdep  ,"hSpokeWiresHitsXYZEdep" );
}

/*
void rdfFillHist(TString outfile){
    std::unique_ptr<TFile> fOut( TFile::Open(outfile, "RECREATE") );

    ROOT::RDataFrame prodCoreDf("prodCore/nt","/exp/mu2e/data/users/mhedges/projects/prodtgt/prodtgt.haymanFast/nts.mhedges.prodtgt.hayman01.001000_00000000.root");
    //ROOT::RDataFrame prodStartingCoreDf("prodStartingCore/nt","/exp/mu2e/data/users/mhedges/projects/prodtgt/prodtgt.haymanFast/nts.mhedges.prodtgt.hayman01.001000_00000000.root");
    //ROOT::RDataFrame prodFinSectionDf("prodFinSection/nt","/exp/mu2e/data/users/mhedges/projects/prodtgt/prodtgt.haymanFast/nts.mhedges.prodtgt.hayman01.001000_00000000.root");
    //ROOT::RDataFrame prodStartingFinDf("prodStartingFin/nt","/exp/mu2e/data/users/mhedges/projects/prodtgt/prodtgt.haymanFast/nts.mhedges.prodtgt.hayman01.001000_00000000.root");
    //ROOT::RDataFrame prodFinTopSectionDf("prodFinTopSection/nt","/exp/mu2e/data/users/mhedges/projects/prodtgt/prodtgt.haymanFast/nts.mhedges.prodtgt.hayman01.001000_00000000.root");
    //ROOT::RDataFrame prodFinTopStartingSectionDf("prodFinTopStartingSection/nt","/exp/mu2e/data/users/mhedges/projects/prodtgt/prodtgt.haymanFast/nts.mhedges.prodtgt.hayman01.001000_00000000.root");
    //ROOT::RDataFrame prodPositiveEndRingDf("prodPositiveEndRing/nt","/exp/mu2e/data/users/mhedges/projects/prodtgt/prodtgt.haymanFast/nts.mhedges.prodtgt.hayman01.001000_00000000.root");
    //ROOT::RDataFrame prodNegativeEndRingDf("prodNegativeEndRing/nt","/exp/mu2e/data/users/mhedges/projects/prodtgt/prodtgt.haymanFast/nts.mhedges.prodtgt.hayman01.001000_00000000.root");
    //ROOT::RDataFrame prodSupportWheelDf("prodSupportWheel/nt","/exp/mu2e/data/users/mhedges/projects/prodtgt/prodtgt.haymanFast/nts.mhedges.prodtgt.hayman01.001000_00000000.root");
    //ROOT::RDataFrame prodSpokeWireDf("prodSpokeWire/nt","/exp/mu2e/data/users/mhedges/projects/prodtgt/prodtgt.haymanFast/nts.mhedges.prodtgt.hayman01.001000_00000000.root");

    //auto prodCoreCenteredDf = prodCoreDf.Define("xPrime","hits.x-3904").Define("zPrime","hits.z+6164.5-2.75");
    //auto prodStartingCoreCenteredDf = prodStartingCoreDf.Define("xPrime","hits.x-3904").Define("zPrime","hits.z+6164.5-2.75");
    //auto prodFinSectionCenteredDf = prodFinSectionDf.Define("xPrime","hits.x-3904").Define("zPrime","hits.z+6164.5-2.75");
    //auto prodStartingFinCenteredDf = prodStartingFinDf.Define("xPrime","hits.x-3904").Define("zPrime","hits.z+6164.5-2.75");
    //auto prodFinTopSectionCenteredDf = prodFinTopSectionDf.Define("xPrime","hits.x-3904").Define("zPrime","hits.z+6164.5-2.75");
    //auto prodFinTopStartingSectionCenteredDf = prodFinTopStartingSectionDf.Define("xPrime","hits.x-3904").Define("zPrime","hits.z+6164.5-2.75");
    //auto prodPositiveEndRingCenteredDf = prodPositiveEndRingDf.Define("xPrime","hits.x-3904").Define("zPrime","hits.z+6164.5-2.75");
    //auto prodNegativeEndRingCenteredDf = prodNegativeEndRingDf.Define("xPrime","hits.x-3904").Define("zPrime","hits.z+6164.5-2.75");
    //auto prodSupportWheelCenteredDf = prodSupportWheelDf.Define("xPrime","hits.x-3904").Define("zPrime","hits.z+6164.5-2.75");
    //auto prodSpokeWireCenteredDf = prodSpokeWireDf.Define("xPrime","hits.x-3904").Define("zPrime","hits.z+6164.5-2.75");

    //int nbinsx = 401;
    int nbinsx = 801;
    float xmin = -200.5;
    float xmax = 200.5;

    //int nbinsy = 401;
    int nbinsy = 801;
    float ymin = -200.5;
    float ymax = 200.5;

    int nbinsz = 241;
    //int nbinsz = 481;
    float zmin = -120.5;
    float zmax = 120.5;

    auto hCoresHitsXYZEdep = prodCoreDf.Define("xPrime","hits.x-3904").Define("zPrime","hits.z+6164.5-2.75").Histo3D({"hCoresXYZEdep","hCoresXYZEdep",
                             nbinsx,xmin,xmax,
                             nbinsy,ymin,ymax,
                             nbinsz,zmin,zmax},
                             "hits.x","hits.y","hits.z","hits.totalEDep"
                             );
    //auto hStartingCoresXYZEdep = prodStartingCoreCenteredDf.Histo3D({"hStartingCoresXYZEdep","hStartingCoresXYZEdep",
    //                             nbinsx,xmin,xmax,
    //                             nbinsy,ymin,ymax,
    //                             nbinsz,zmin,zmax,},
    //                             "xPrime","hits.y","zPrime","hits.totalEDep"
    //                             );
    //auto hFinsHitsXYZEdep = prodFinSectionCenteredDf.Histo3D({"hFinsXYZEdep","hFinsXYZEdep",
    //                        nbinsx,xmin,xmax,
    //                        nbinsy,ymin,ymax,
    //                        nbinsz,zmin,zmax,},
    //                        "xPrime","hits.y","zPrime","hits.totalEDep"
    //                        );
    //auto hStartingFinXYZEdep = prodStartingFinCenteredDf.Histo3D({"hStartingFinXYZEdep","hStartingFinXYZEdep",
    //                           nbinsx,xmin,xmax,
    //                           nbinsy,ymin,ymax,
    //                           nbinsz,zmin,zmax,},
    //                           "xPrime","hits.y","zPrime","hits.totalEDep"
    //                           );
    //auto hTopFinXYZEdep = prodFinTopSectionCenteredDf.Histo3D({"hFinTopSectionXYZEdep","hFinTopSectionXYZEdep",
    //                      nbinsx,xmin,xmax,
    //                      nbinsy,ymin,ymax,
    //                      nbinsz,zmin,zmax,},
    //                      "xPrime","hits.y","zPrime","hits.totalEDep"
    //                      );
    //auto hStartingTopFinXYZEdep = prodFinTopStartingSectionCenteredDf.Histo3D({"hprodFinTopStartingSectionXYZEdep","hprodFinTopStartingSectionXYZEdep",
    //                              nbinsx,xmin,xmax,
    //                              nbinsy,ymin,ymax,
    //                              nbinsz,zmin,zmax,},
    //                              "xPrime","hits.y","zPrime","hits.totalEDep"
    //                              );
    //auto hEndRingsHitsXYZEdep = prodPositiveEndRingCenteredDf.Histo3D({"hPositiveEndRingXYZEdep","hPositiveEndRingXYZEdep",
    //                            nbinsx,xmin,xmax,
    //                            nbinsy,ymin,ymax,
    //                            nbinsz,zmin,zmax,},
    //                            "xPrime","hits.y","zPrime","hits.totalEDep"
    //                            );
    //auto hNegativeEndRingXYZEdep = prodPositiveEndRingCenteredDf.Histo3D({"hNegativeEndRingXYZEdep","hNegativeEndRingXYZEdep",
    //                               nbinsx,xmin,xmax,
    //                               nbinsy,ymin,ymax,
    //                               nbinsz,zmin,zmax,},
    //                               "xPrime","hits.y","zPrime","hits.totalEDep"
    //                               );
    //auto hSupportRingHitsXYZEdep = prodSupportWheelCenteredDf.Histo3D({"hSupportWheelXYZEdep","hSupportWheelXYZEdep",
    //                               nbinsx,xmin,xmax,
    //                               nbinsy,ymin,ymax,
    //                               nbinsz,zmin,zmax,},
    //                               "xPrime","hits.y","zPrime","hits.totalEDep"
    //                               );
    //auto hSpokeWiresHitsXYZEdep = prodSpokeWireCenteredDf.Histo3D({"hSpokeWireXYZEdep","hSpokeWireXYZEdep",
    //                              nbinsx,xmin,xmax,
    //                              nbinsy,ymin,ymax,
    //                              nbinsz,zmin,zmax,},
    //                              "xPrime","hits.y","zPrime","hits.totalEDep"
    //                              );

    //hCoresHitsXYZEdep->Add(hStartingCoresXYZEdep);

    //hFinsHitsXYZEdep->Add(hStartingFinXYZEdep);
    //hFinsHitsXYZEdep->Add(hTopFinXYZEdep);
    //hFinsHitsXYZEdep->Add(hStartingTopFinXYZEdep);

    //hEndRingsHitsXYZEdep->Add(hNegativeEndRingXYZEdep);

    //hCoresHitsXYZEdep->Draw();
    hCoresHitsXYZEdep->Write();
    //hFinsHitsXYZEdep->Write();
    //hEndRingsHitsXYZEdep->Write();
    //hSupportRingHitsXYZEdep->Write();
    //hSpokeWiresHitsXYZEdep->Write();
    //fOut->WriteObject(hCoresHitsXYZEdep       ,"hCoresHitsXYZEdep"      );
    //fOut->WriteObject(hFinsHitsXYZEdep        ,"hFinsHitsXYZEdep"       );
    //fOut->WriteObject(hEndRingsHitsXYZEdep    ,"hEndRingsHitsXYZEdep"   );
    //fOut->WriteObject(hSupportRingHitsXYZEdep ,"hSupportRingHitsXYZEdep");
    //fOut->WriteObject(hSpokeWiresHitsXYZEdep  ,"hSpokeWiresHitsXYZEdep" );
}
*/

void genCSV(TString rootfile, const int nFiles, std::string csvPath) {
    std::unique_ptr<TFile> infile( TFile::Open(rootfile) );

    TH3F* hCoresHitsXYZEdep       = (TH3F*)infile->Get("hCoresHitsXYZEdep"       );
    TH3F* hFinsHitsXYZEdep        = (TH3F*)infile->Get("hFinsHitsXYZEdep"        );
    TH3F* hEndRingHitsXYZEdep     = (TH3F*)infile->Get("hEndRingsHitsXYZEdep"    );
    TH3F* hSupportRingHitsXYZEdep = (TH3F*)infile->Get("hSupportRingHitsXYZEdep" );
    TH3F* hSpokeWiresHitsXYZEdep  = (TH3F*)infile->Get("hSpokeWiresHitsXYZEdep"  );

    // Declare CSV files
    std::ofstream coresFile;
    coresFile.open(csvPath+"coresEDepMeVperPOT.csv");
    coresFile << "x,y,z,MeV/POT,uncert\n";

    std::ofstream finsFile;
    finsFile.open(csvPath+"finsEDepMeVperPOT.csv");
    finsFile << "x,y,z,MeV/POT,uncert\n";

    std::ofstream endRingsFile;
    endRingsFile.open(csvPath+"endRingsEDepMeVperPOT.csv");
    endRingsFile << "x,y,z,MeV/POT,uncert\n";

    std::ofstream supportRingFile;
    supportRingFile.open(csvPath+"supportRingEDepMeVperPOT.csv");
    supportRingFile << "x,y,z,MeV/POT,uncert\n";

    std::ofstream spokesFile;
    spokesFile.open(csvPath+"spokesEDepMeVperPOT.csv");
    spokesFile << "x,y,z,MeV/POT,uncert\n";

    std::cout << "  Writing CSV files for cores, fins, endRings, supportRing, and spokes..." << std::endl;

    /* Blatantly copying ROOT's TH1::Print() function to loop over a TH3F and get bin contents*/
    Int_t bin, binx, biny, binz;
    Int_t firstx = hCoresHitsXYZEdep->GetXaxis()->GetFirst(); Int_t lastx = hCoresHitsXYZEdep->GetXaxis()->GetLast();
    Int_t firsty = hCoresHitsXYZEdep->GetYaxis()->GetFirst(); Int_t lasty = hCoresHitsXYZEdep->GetYaxis()->GetLast();
    Int_t firstz = hCoresHitsXYZEdep->GetZaxis()->GetFirst(); Int_t lastz = hCoresHitsXYZEdep->GetZaxis()->GetLast();

    Double_t edep,err;
    Double_t x,y,z;

    Double_t coresEdep,       coresEdepErr;
    Double_t finsEdep,        finsEdepErr;
    Double_t endRingsEdep,    endRingsEdepErr;
    Double_t supportRingEdep, supportRingEdepErr;
    Double_t spokesEdep,      spokesEdepErr;

    float perPOT = 1. / (nFiles * 1000); // 1e3 POT per file
    //float wattsFromMeV = 1e6*perPOT * 3.9e7/1.695*1.6e-19*1e6; // Instantaneous power / pulse: (1e6 eV/MeV) / (# POT) * (3.9e7 POT /1.6 us) * (1.6e-19 J/eV) * (1e6 us/s)
    //float wattsFromMeV = 1e6*perPOT * 8e12/0.380*1.6e-19; // Instantaneous power / MI cycle (on-spill): (1e6 eV/MeV) / (# POT) * (8e12 POT /0.380 s) * (1.6e-19 J/eV)

    float wattsFromMeV = perPOT; // MeV / POT

    TVector3 testVec;
    for (binz=firstz;binz<=lastz;binz++) {
        z = hCoresHitsXYZEdep->GetZaxis()->GetBinCenter(binz);
        for (biny=firsty;biny<=lasty;biny++) {
            y = hCoresHitsXYZEdep->GetYaxis()->GetBinCenter(biny);
            for (binx=firstx;binx<=lastx;binx++) {
                bin = hCoresHitsXYZEdep->GetBin(binx,biny,binz);
                x = hCoresHitsXYZEdep->GetXaxis()->GetBinCenter(binx);

                coresEdep          = hCoresHitsXYZEdep->GetBinContent(bin) * wattsFromMeV;
                coresEdepErr       = hCoresHitsXYZEdep->GetBinError(bin) * wattsFromMeV;

                finsEdep           = hFinsHitsXYZEdep->GetBinContent(bin) * wattsFromMeV;
                finsEdepErr        = hFinsHitsXYZEdep->GetBinError(bin) * wattsFromMeV;

                endRingsEdep       = hEndRingHitsXYZEdep->GetBinContent(bin) * wattsFromMeV;
                endRingsEdepErr    = hEndRingHitsXYZEdep->GetBinError(bin) * wattsFromMeV;

                supportRingEdep    = hSupportRingHitsXYZEdep->GetBinContent(bin) * wattsFromMeV;
                supportRingEdepErr = hSupportRingHitsXYZEdep->GetBinError(bin) * wattsFromMeV;

                spokesEdep         = hSpokeWiresHitsXYZEdep->GetBinContent(bin) * wattsFromMeV;
                spokesEdepErr      = hSpokeWiresHitsXYZEdep->GetBinError(bin) * wattsFromMeV;
                testVec.SetXYZ(x,y,z);
                //testVec.RotateY(180.*TMath::Pi());
                //testVec.RotateY(14.*TMath::DegToRad());
                if (coresEdep>0) {
                    coresFile << -testVec.X() << "," << testVec.Y() << "," << -testVec.Z() << "," << coresEdep << "," << coresEdepErr << "\n";
                }
                if (finsEdep>0) {
                    finsFile << -testVec.X() << "," << testVec.Y() << "," << -testVec.Z() << "," << finsEdep << "," << finsEdepErr << "\n";
                }
                if (endRingsEdep>0) {
                    endRingsFile << -testVec.X() << "," << testVec.Y() << "," << -testVec.Z() << "," << endRingsEdep << "," << endRingsEdepErr << "\n";
                }
                if (supportRingEdep>0) {
                    supportRingFile << -testVec.X() << "," << testVec.Y() << "," << -testVec.Z() << "," << supportRingEdep << "," << supportRingEdepErr << "\n";
                }
                if (spokesEdep>0) {
                    spokesFile << -testVec.X() << "," << testVec.Y() << "," << -testVec.Z() << "," << spokesEdep << "," << spokesEdepErr << "\n";
                }
            }
        }
    }

    /* Create summary lines for integrated energy deposition in entire sub-volume */

    // Integrated MeV
    coresEdep       = hCoresHitsXYZEdep      ->IntegralAndError(-1,1000,-1,1000,-1,1000,coresEdepErr);
    finsEdep        = hFinsHitsXYZEdep       ->IntegralAndError(-1,1000,-1,1000,-1,1000,finsEdepErr);
    endRingsEdep    = hEndRingHitsXYZEdep    ->IntegralAndError(-1,1000,-1,1000,-1,1000,endRingsEdepErr);
    supportRingEdep = hSupportRingHitsXYZEdep->IntegralAndError(-1,1000,-1,1000,-1,1000,supportRingEdepErr);
    spokesEdep      = hSpokeWiresHitsXYZEdep ->IntegralAndError(-1,1000,-1,1000,-1,1000,spokesEdepErr);

    //// Watts and errors
    //coresFile       << "x,y,z,Watts,uncert\n";
    //coresFile       << "0,0,0," << coresEdep       * wattsFromMeV << "," << coresEdepErr       * wattsFromMeV << "\n";
    //finsFile        << "x,y,z,Watts,uncert\n";
    //finsFile        << "0,0,0," << finsEdep        * wattsFromMeV << "," << finsEdepErr        * wattsFromMeV << "\n";
    //endRingsFile    << "x,y,z,Watts,uncert\n";
    //endRingsFile    << "0,0,0," << endRingsEdep    * wattsFromMeV << "," << endRingsEdepErr    * wattsFromMeV << "\n";
    //supportRingFile << "x,y,z,Watts,uncert\n";
    //supportRingFile << "0,0,0," << supportRingEdep * wattsFromMeV << "," << supportRingEdepErr * wattsFromMeV << "\n";
    //spokesFile      << "x,y,z,Watts,uncert\n";
    //spokesFile      << "0,0,0," << spokesEdep      * wattsFromMeV << "," << spokesEdepErr      * wattsFromMeV << "\n";

    // MeV / POT and errors
    coresFile       << "x,y,z,MeV/POT,uncert\n";
    coresFile       << "0,0,0," << coresEdep       * perPOT << "," << coresEdepErr       * perPOT ;
    finsFile        << "x,y,z,MeV/POT,uncert\n";
    finsFile        << "0,0,0," << finsEdep        * perPOT << "," << finsEdepErr        * perPOT ;
    endRingsFile    << "x,y,z,MeV/POT,uncert\n";
    endRingsFile    << "0,0,0," << endRingsEdep    * perPOT << "," << endRingsEdepErr    * perPOT ;
    supportRingFile << "x,y,z,MeV/POT,uncert\n";
    supportRingFile << "0,0,0," << supportRingEdep * perPOT << "," << supportRingEdepErr * perPOT ;
    spokesFile      << "x,y,z,MeV/POT,uncert\n";
    spokesFile      << "0,0,0," << spokesEdep      * perPOT << "," << spokesEdepErr      * perPOT ;
}

void prodTgtEDep(){

    //rdfFillHist(rootfile);
    //rdfFillHist(rootfile,fpath);

    const int nFiles = 100;

    //std::string fpath = "/exp/mu2e/data/users/mhedges/projects/prodtgt/prodtgt.hayman.0010000/";
    //TString rootfile = "results/prodtgt.hayman.0010000.xyzEdepHists.root";
    //std::string csvPath = "results/csv/hayman.0010000/hayman.0010000.";

    std::string fpath = "/exp/mu2e/data/users/mhedges/projects/prodtgt/prodtgt.grayman.0010000/";
    TString rootfile = "prodtgt.grayman.0010000.xyzEdepHists.root";
    std::string csvPath = "csv/grayman.0010000/grayman.0010000.";

    concatHists(rootfile,nFiles,fpath);
    genCSV(rootfile,nFiles,csvPath);
}
