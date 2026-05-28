#pragma once
#include <wx/wx.h>
#include <wx/listbox.h>
#include <wx/statline.h>
#include <wx/spinctrl.h>
#include <string>
#include <memory>
#include <algorithm>
#include "../lazy_sequence/LazySequence.hpp"
#include "../libs/Lab_3/array_sequence/MutableArraySequence.hpp"
#include "../libs/Lab_3/exceptions/Exceptions.hpp"
#include "../generators/RecurrentGenerator.hpp"
#include "../generators/ContainerGenerator.hpp"

using IntLazy = LazySequence<int, MutableArraySequence>;

class LabFrame : public wxFrame {
public:
    LabFrame();
    ~LabFrame();

private:
    MutableArraySequence<std::shared_ptr<IntLazy>> sequences;
    size_t current_sequence_id = 0;

    wxComboBox* object_selector;
    wxComboBox* target_selector;
    
    wxButton* button_create_finite;
    wxButton* button_create_infinite;
    wxButton* button_materialize;
    wxButton* button_append;
    wxButton* button_clear;
    wxButton* button_concat;
    wxButton* button_take;
    wxButton* button_skip;
    wxButton* button_map;
    wxButton* button_where;
    
    wxGridSizer* button_grid;
    
    wxSpinCtrl* spin_create;
    wxSpinCtrl* spin_take_skip;
    wxSpinCtrl* spin_materialize;
    wxSpinCtrl* spin_append;
    
    wxListBox* output_list_box; 
    wxStaticText* status_label;

    void on_create_finite(wxCommandEvent& event); 
    void on_create_infinite(wxCommandEvent& event);  
    void on_concat(wxCommandEvent& event);
    void on_take(wxCommandEvent& event);
    void on_skip(wxCommandEvent& event);
    void on_clear(wxCommandEvent& event);
    void on_append(wxCommandEvent& event);
    void on_select_sequence(wxCommandEvent& event);  
    void on_select_target(wxCommandEvent& event);   
    
    void on_materialize(wxCommandEvent& event);   

    void update_comboboxes();
    void show_content(); 
    void update_status();
    void update_operations();
    void update_concat();
    
    void add_sequence_to_list(const std::shared_ptr<IntLazy>& new_seq);
    
    std::shared_ptr<IntLazy>& get_active_sequence();
    std::shared_ptr<IntLazy>& get_target_sequence();
};

int run_gui_new();