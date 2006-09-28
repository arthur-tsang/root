// @(#)root/spectrum:$Name:  $:$Id: TSpectrum2.h,v 1.6 2006/01/18 15:38:54 brun Exp $
// Author: Miroslav Morhac   17/01/2006

/*************************************************************************
 * Copyright (C) 1995-2006, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/
#ifndef ROOT_TSpectrum2
#define ROOT_TSpectrum2

#ifndef ROOT_TH1
#include "TH1.h"
#endif

class TSpectrum2 : public TNamed {
protected:
   Int_t         fMaxPeaks;       //Maximum number of peaks to be found
   Int_t         fNPeaks;         //number of peaks found
   Float_t      *fPosition;       //[fNPeaks] array of current peak positions
   Float_t      *fPositionX;      //[fNPeaks] X position of peaks
   Float_t      *fPositionY;      //[fNPeaks] Y position of peaks
   Float_t       fResolution;     //resolution of the neighboring peaks
   TH1          *fHistogram;      //resulting histogram

public:
   enum {
       kBackIncreasingWindow =0,
       kBackDecreasingWindow =1,
       kBackSuccessiveFiltering =0,
       kBackOneStepFiltering =1
   };

   TSpectrum2();
   TSpectrum2(Int_t maxpositions, Float_t resolution=1);
   virtual ~TSpectrum2();
   virtual const char *Background(const TH1 *hist,int niter, Option_t *option="goff");
   TH1          *GetHistogram() const {return fHistogram;}
   Int_t         GetNPeaks() const {return fNPeaks;}
   Float_t      *GetPositionX() const {return fPositionX;}
   Float_t      *GetPositionY() const {return fPositionY;}
   virtual void  Print(Option_t *option="") const;
   virtual Int_t Search(const TH1 *hist, Double_t sigma=2, Option_t *option="goff", Double_t threshold=0.05);
   void          SetResolution(Float_t resolution=1);

   //new functions January 2006
   const char   *Background(float **spectrum,Int_t ssizex, Int_t ssizey,Int_t numberIterationsX,Int_t numberIterationsY,Int_t direction,Int_t filterType);   
   const char   *SmoothMarkov(float **source, Int_t ssizex, Int_t ssizey, Int_t averWindow);   
   const char   *Deconvolution(float **source, float **resp, Int_t ssizex, Int_t ssizey,Int_t numberIterations, Int_t numberRepetitions, Double_t boost);
   Int_t         SearchHighRes(float **source,float **dest, Int_t ssizex, Int_t ssizey, Double_t sigma, Double_t threshold, Bool_t backgroundRemove,Int_t deconIterations, Bool_t markov, Int_t averWindow);

   static Int_t        StaticSearch(const TH1 *hist, Double_t sigma=2, Option_t *option="goff", Double_t threshold=0.05);

   ClassDef(TSpectrum2,1)  //Peak Finder, background estimator, Deconvolution for 2-D histograms
};

#endif

