#pragma once
#include "common.h"
#include "player_field_gui.h"
#include "formation.h"
#include <vector>

namespace SCM24
{

class FormationEditGui : public PlayerFieldGui
{
public:
    // const float _FORMATION_DETAILS_HEIGHT = 115f;
    // const float _AFFECTED_PLAYER_CHECKBOX_SPACING = 10;
    // const float _LIST_BOX_WIDTH = 200.0f;    
    std::vector<Player> _field_players;
    std::vector<Player> _mof_players;
    std::vector<Player> _boundary_players;
    // SCMGui _scm_gui;
    // float _menubar_height;

    // int _formations_list_selection_index;
    FormationLibrary* _formation_library;
    std::string _formation_library_path;
    std::string _formation_library_save_message;
    // std::vector<std::string[]> _formation_listbox_items;   
    std::string _formation_name = "";
    std::string _formation_tags = "";
    bool _lt_affected;
    bool _lg_affected;
    bool _oc_affected;
    bool _rg_affected;
    bool _rt_affected;
    bool _oq_affected;
    bool _s1_affected;
    bool _s2_affected;
    bool _s3_affected;
    bool _s4_affected;
    bool _s5_affected;

    FormationEditGui(/*SCMGui scm_gui,*/ FormationLibrary* formation_library/*, std::string formation_library_path, std::string formation_library_save_message*/);
};

}