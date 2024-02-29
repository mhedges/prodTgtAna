#include <iostream>
#include <fstream>
#include <experimental/filesystem>

#include "TH1F.h"
#include "TH3F.h"
#include "TString.h"
#include "TFile.h"
#include "TVector3.h"

void concatHists(TString outfile, const int nInputFiles){

    std::unique_ptr<TFile> fOut( TFile::Open(outfile, "RECREATE") );

    int nbinsx = 401;
    float xmin = -200.5;
    float xmax = 200.5;

    int nbinsy = 401;
    float ymin = -200.5;
    float ymax = 200.5;

    int nbinsz = 240;
    float zmin = -0.5;
    float zmax = 240.5;

    TH3F* hCoresHitsXYZEdep       = new TH3F ("hCoresHitsXYZEdep"      ,"Binned EDep (1mm3)",nbinsx,xmin,xmax,nbinsy,ymin,ymax,nbinsz,zmin,zmax);
    TH3F* hFinsHitsXYZEdep        = new TH3F ("hFinsHitsXYZEdep"       ,"Binned EDep (1mm3)",nbinsx,xmin,xmax,nbinsy,ymin,ymax,nbinsz,zmin,zmax);
    TH3F* hEndRingsHitsXYZEdep    = new TH3F ("hEndRingsHitsXYZEdep"   ,"Binned EDep (1mm3)",nbinsx,xmin,xmax,nbinsy,ymin,ymax,nbinsz,zmin,zmax);
    TH3F* hSupportRingHitsXYZEdep = new TH3F ("hSupportRingHitsXYZEdep","Binned EDep (1mm3)",nbinsx,xmin,xmax,nbinsy,ymin,ymax,nbinsz,zmin,zmax);
    TH3F* hSpokeWiresHitsXYZEdep  = new TH3F ("hSpokeWiresHitsXYZEdep" ,"Binned EDep (1mm3)",nbinsx,xmin,xmax,nbinsy,ymin,ymax,nbinsz,zmin,zmax);

    int nReadFiles = 0;
    std::cout << "  Analyzing " << nInputFiles << " input files:" << std::endl;
    for (const auto& entry : std::filesystem::directory_iterator("/exp/mu2e/data/users/mhedges/projects/prodtgt/prodtgt.haymanFast/"))
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

        std::cout << "  Completed file number " << nReadFiles << std::endl;
    }

    fOut->WriteObject(hCoresHitsXYZEdep       ,"hCoresHitsXYZEdep"      );
    fOut->WriteObject(hFinsHitsXYZEdep        ,"hFinsHitsXYZEdep"       );
    fOut->WriteObject(hEndRingsHitsXYZEdep    ,"hEndRingsHitsXYZEdep"   );
    fOut->WriteObject(hSupportRingHitsXYZEdep ,"hSupportRingHitsXYZEdep");
    fOut->WriteObject(hSpokeWiresHitsXYZEdep  ,"hSpokeWiresHitsXYZEdep" );
}

void genCSV(TString rootfile, const int nFiles) {
    std::unique_ptr<TFile> infile( TFile::Open(rootfile) );

    TH3F* hCoresHitsXYZEdep       = (TH3F*)infile->Get("hCoresHitsXYZEdep"       );
    TH3F* hFinsHitsXYZEdep        = (TH3F*)infile->Get("hFinsHitsXYZEdep"        );
    TH3F* hEndRingHitsXYZEdep     = (TH3F*)infile->Get("hEndRingsHitsXYZEdep"    );
    TH3F* hSupportRingHitsXYZEdep = (TH3F*)infile->Get("hSupportRingHitsXYZEdep" );
    TH3F* hSpokeWiresHitsXYZEdep  = (TH3F*)infile->Get("hSpokeWiresHitsXYZEdep"  );

    // Declare CSV files
    std::ofstream coresFile;
    coresFile.open("coresEDepWatts.csv");
    coresFile << "x,y,z,W/mm^3,uncert\n";

    std::ofstream finsFile;
    finsFile.open("finsEDepWatts.csv");
    finsFile << "x,y,z,W/mm^3,uncert\n";

    std::ofstream endRingsFile;
    endRingsFile.open("endRingsEDepWatts.csv");
    endRingsFile << "x,y,z,W/mm^3,uncert\n";

    std::ofstream supportRingFile;
    supportRingFile.open("supportRingEDepWatts.csv");
    supportRingFile << "x,y,z,W/mm^3,uncert\n";

    std::ofstream spokesFile;
    spokesFile.open("spokesEDepWatts.csv");
    spokesFile << "x,y,z,W/mm^3,MeV/POT,uncert\n";

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
    Double_t endRingsEdep,     endRingsEdepErr;
    Double_t supportRingEdep, supportRingEdepErr;
    Double_t spokesEdep,      spokesEdepErr;

    float perPOT = 1. / (nFiles * 1000); // 1e3 POT per file
    float wattsFromMeV = 1e6*perPOT * 3.9e7/1.695*1.6e-19*1e6; // Instantaneous power / pulse: (1e6 eV/MeV) / (# POT) * (3.9e7 POT /1.6 us) * (1.6e-19 J/eV) * (1e6 us/s)

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
                if (coresEdep>0) {
                    testVec.SetXYZ(x,y,-(z-110));
                    testVec.RotateY(14.*TMath::DegToRad());
                    coresFile << testVec.X() << "," << testVec.Y() << "," << testVec.Z() << "," << coresEdep << "," << coresEdepErr << "\n";
                    //std::cout<<"Bin number, x, y, z and edep: "<<bin<<" "<<testVec.X()<<" "<<testVec.Y()<<" "<<testVec.Z()<<" "<<edep<<std::endl;
                }
                if (finsEdep>0) {
                    testVec.SetXYZ(x,y,-(z-110));
                    testVec.RotateY(14.*TMath::DegToRad());
                    finsFile << testVec.X() << "," << testVec.Y() << "," << testVec.Z() << "," << finsEdep << "," << finsEdepErr << "\n";
                }
                if (endRingsEdep>0) {
                    testVec.SetXYZ(x,y,-(z-110));
                    testVec.RotateY(14.*TMath::DegToRad());
                    endRingsFile << testVec.X() << "," << testVec.Y() << "," << testVec.Z() << "," << endRingsEdep << "," << endRingsEdepErr << "\n";
                }
                if (supportRingEdep>0) {
                    testVec.SetXYZ(x,y,-(z-110));
                    testVec.RotateY(14.*TMath::DegToRad());
                    supportRingFile << testVec.X() << "," << testVec.Y() << "," << testVec.Z() << "," << supportRingEdep << "," << supportRingEdepErr << "\n";
                }
                if (spokesEdep>0) {
                    testVec.SetXYZ(x,y,-(z-110));
                    testVec.RotateY(14.*TMath::DegToRad());
                    spokesFile << testVec.X() << "," << testVec.Y() << "," << testVec.Z() << "," << spokesEdep << "," << spokesEdepErr << "\n";
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

    // Watts and errors
    coresFile       << "0,0,0," << coresEdep       * wattsFromMeV << "," << coresEdepErr       * wattsFromMeV << "\n";
    finsFile        << "0,0,0," << finsEdep        * wattsFromMeV << "," << finsEdepErr        * wattsFromMeV << "\n";
    endRingsFile    << "0,0,0," << endRingsEdep    * wattsFromMeV << "," << endRingsEdepErr    * wattsFromMeV << "\n";
    supportRingFile << "0,0,0," << supportRingEdep * wattsFromMeV << "," << supportRingEdepErr * wattsFromMeV << "\n";
    spokesFile      << "0,0,0," << spokesEdep      * wattsFromMeV << "," << spokesEdepErr      * wattsFromMeV << "\n";

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
    TString rootfile = "xyzEdepHists.root";
    const int nFiles = 100;
    //concatHists(rootfile,nFiles);
    genCSV(rootfile,nFiles);
}
