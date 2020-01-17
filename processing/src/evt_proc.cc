#include "cms_hh_proc_interface/processing/interface/evt_proc.hh"

EvtProc::EvtProc(bool return_all, std::set<std::string> requested, bool use_deep_csv) {
    _all = return_all;
    _requested = requested;
    _feat_comp = new FeatComp(return_all, requested, use_deep_csv);
}

EvtProc::~EvtProc() {}

std::map<std::string, float> EvtProc::process(const LorentzVector& b_1,
                                              const LorentzVector& b_2,
                                              const LorentzVector& l_1,
                                              const LorentzVector& l_2,
                                              const LorentzVector& met,
                                              const LorentzVector& svfit,
                                              const float& hh_kinfit_mass,
                                              const float& hh_kinfit_chi2,
                                              const float& mt2,
                                              const float& mt_tot,
                                              const float& p_zetavisible,
                                              const float& p_zeta,
                                              const float& top_1_mass,
                                              const float& top_2_mass,
                                              const float& l_1_mt,
                                              const float& l_2_mt,
                                              const bool& is_boosted,
                                              const float& b_1_csv,
                                              const float& b_2_csv,
                                              const float& b_1_deepcsv,
                                              const float& b_2_deepcsv,
                                              Channel channel,
                                              const float& res_mass) {
    /* Processes (requested) features for an event and returns a map of features->values (in order of requested features) */

    std::map<std::string, float> feats = _feat_comp->process(b_1, b_2, l_1, l_2, met, svfit, hh_kinfit_mass, is_boosted,
                                                             b_1_csv, b_2_csv, b_1_deepcsv, b_2_deepcsv, channel);
    // Non-comp extra HL
    if (EvtProc::_feat_check("hh_kinfit_chi2")) feats["hh_kinfit_chi2"] = hh_kinfit_chi2;
    if (EvtProc::_feat_check("mt2"))            feats["mt2"]            = mt2;
    if (EvtProc::_feat_check("mt_tot"))         feats["mt_tot"]         = mt_tot; 
    if (EvtProc::_feat_check("res_mass"))       feats["res_mass"]       = res_mass;
    if (EvtProc::_feat_check("p_zetavisible"))  feats["p_zetavisible"]  = p_zetavisible;
    if (EvtProc::_feat_check("p_zeta"))         feats["p_zeta"]         = p_zeta;
    if (EvtProc::_feat_check("top_1_mass"))     feats["top_1_mass"]     = top_1_mass;
    if (EvtProc::_feat_check("top_2_mass"))     feats["top_2_mass"]     = top_2_mass;
    

    // Non-comp extra LL
    if (EvtProc::_feat_check("l_1_mt")) feats["l_1_mt"] = l_1_mt;
    if (EvtProc::_feat_check("l_2_mt")) feats["l_2_mt"] = l_2_mt;
    if (EvtProc::_feat_check("l_1_E"))  feats["l_1_E"]  = l_1.E();
    if (EvtProc::_feat_check("l_2_E"))  feats["l_2_E"]  = l_2.E();
    if (EvtProc::_feat_check("l_1_pT")) feats["l_1_pT"] = l_1.Pt();
    if (EvtProc::_feat_check("l_2_pT")) feats["l_2_pT"] = l_2.Pt();
    if (EvtProc::_feat_check("b_1_E"))  feats["b_1_E"]  = b_1.E();
    if (EvtProc::_feat_check("b_2_E"))  feats["b_2_E"]  = b_2.E();
    if (EvtProc::_feat_check("b_1_pT")) feats["b_1_pT"] = b_1.Pt();
    if (EvtProc::_feat_check("b_2_pT")) feats["b_2_pT"] = b_2.Pt();
    if (EvtProc::_feat_check("met_pT")) feats["met_pT"] = met.Pt();

    return _all ? feats : EvtProc::_sort_feats(feats);
}

inline bool EvtProc::_feat_check(std::string feat) {return (_all ? true : _requested.find(feat) != _requested.end());}

std::map<std::string, float> EvtProc::_sort_feats(std::map<std::string, float> feats) {
    std::map<std::string, float> sf;
    for (auto const& f : _requested) sf[f] = feats[f];
    return sf;
}