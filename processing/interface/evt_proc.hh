#ifndef EVT_PROC_HH_
#define EVT_PROC_HH_

// C++
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <algorithm>

// ROOT
#include <Math/VectorUtil.h>
#include <Math/LorentzVector.h>
#include <Math/PxPyPzM4D.h>

// Local
#include "feat_comp.hh"

enum Spin{radion=0, graviton=1, nonres=2};

class EvtProc {
	/* Class for extracting and computing required information and returning it expected order */

private:
    // Names
    using LorentzVector = ROOT::Math::LorentzVector<ROOT::Math::PxPyPzM4D<float>>;

	// Variables
    bool _all;
	FeatComp* _feat_comp;
    std::vector<std::string> _requested;

	// Methods
	inline bool _feat_check(std::string);

public:
    // Methods
	EvtProc(bool return_all=true, std::vector<std::string> requested={}, bool use_deep_csv=true);
	~EvtProc();
	std::map<std::string, float> process(const LorentzVector&,  // b_1
										 const LorentzVector&,  // b_2
										 const LorentzVector&,  // l_1
										 const LorentzVector&,  // l_2
										 const LorentzVector&,  // MET
										 const LorentzVector&,  // SVFit
										 const LorentzVector&,  // VBF_1
										 const LorentzVector&,  // VBF_2
										 const float&,          // HH KinFit mass
										 const float&,          // HH KinFit chi2
										 const float&,          // MT2
										 const float&,          // MT total
										 const float&,          // pzeta vis
										 const float&,          // pzeta
										 const float&,          // top 1 mass
										 const float&,          // top 2 mass
										 const float&,          // mT l1
										 const float&,          // mT l2
										 const bool&, 			// Is boosted
										 const float&,			// b_1 CSV
										 const float&,			// b_2 CSV
										 const float&,			// b_1 Deep CSV
										 const float&,			// b_2 Deep CSV
										 Channel,				// Channel
										 Year,	            	// Year
										 const float&,		    // Resonant mass (set to 125 if non-resonant)
										 Spin,   				// Graviton or radion
										 const float&,		    // KLambda coupling (set to 1 if resonant)
										 const int&,			// n_vbf
                                         const bool&,			// svfit_conv
                                         const bool&);			// hh_kinfit_conv
	std::vector<float> process_as_vec(const LorentzVector&,  // b_1
									  const LorentzVector&,  // b_2
									  const LorentzVector&,  // l_1
									  const LorentzVector&,  // l_2
									  const LorentzVector&,  // MET
									  const LorentzVector&,  // SVFit
									  const LorentzVector&,  // VBF_1
									  const LorentzVector&,  // VBF_2
									  const float&,          // HH KinFit mass
									  const float&,          // HH KinFit chi2
									  const float&,          // MT2
									  const float&,          // MT total
									  const float&,          // pzeta vis
									  const float&,          // pzeta
									  const float&,          // top 1 mass
									  const float&,          // top 2 mass
									  const float&,          // mT l1
									  const float&,          // mT l2
									  const bool&, 			 // Is boosted
									  const float&,			 // b_1 CSV
									  const float&,			 // b_2 CSV
									  const float&,			 // b_1 Deep CSV
									  const float&,			 // b_2 Deep CSV
									  Channel,				 // Channel
									  Year,	            	 // Year
									  const float&,		     // Resonant mass (set to 125 if non-resonant)
									  Spin,   				 // Graviton or radion
									  const float&,  	     // KLambda coupling (set to 1 if resonant)
									  const int&,	    	 // n_vbf
                                      const bool&,			 // svfit_conv
                                      const bool&);			 // hh_kinfit_conv
	void process_to_vec(std::vector<std::unique_ptr<float>>&,  // vector to fill
						const LorentzVector&,  // b_1
						const LorentzVector&,  // b_2
						const LorentzVector&,  // l_1
						const LorentzVector&,  // l_2
						const LorentzVector&,  // MET
						const LorentzVector&,  // SVFit
						const LorentzVector&,  // VBF_1
						const LorentzVector&,  // VBF_2
						const float&,          // HH KinFit mass
						const float&,          // HH KinFit chi2
						const float&,          // MT2
						const float&,          // MT total
						const float&,          // pzeta vis
						const float&,          // pzeta
						const float&,          // top 1 mass
						const float&,          // top 2 mass
						const float&,          // mT l1
						const float&,          // mT l2
						const bool&, 		   // Is boosted
						const float&,		   // b_1 CSV
						const float&,		   // b_2 CSV
						const float&,		   // b_1 Deep CSV
						const float&,		   // b_2 Deep CSV
						Channel,			   // Channel
						Year,	               // Year
						const float&,		   // Resonant mass (set to 125 if non-resonant)
						Spin,   			   // Graviton or radion
						const float&,	       // KLambda coupling (set to zero if resonant)
						const int&,			   // n_vbf
                        const bool&,		   // svfit_conv
                        const bool&);		   // hh_kinfit_conv
	std::vector<std::string> get_feats();
};

#endif /* EVT_PROC_HH_ */
