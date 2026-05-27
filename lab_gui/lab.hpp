#pragma once
#include <wx/wx.h>
#include <wx/listbox.h>
#include <wx/statline.h>
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
    
    wxTextCtrl* input_param;
    wxTextCtrl* input_append_value;
    wxTextCtrl* input_take_skip_n;
    wxTextCtrl* input_materialize_n;
    
    wxListBox* output_list_box; 
    wxStaticText* status_label;

    void on_create_finite(wxCommandEvent& event); 
    void on_create_infinite(wxCommandEvent& event);  
    void on_concat(wxCommandEvent& event);
    void on_take(wxCommandEvent& event);
    void on_skip(wxCommandEvent& event);
    void on_select_sequence(wxCommandEvent& event);  
    void on_select_target(wxCommandEvent& event);   
    
    void on_materialize(wxCommandEvent& event);   

    void update_comboboxes();
    void show_content(); 
    void update_status();
    
    void add_sequence_to_list(const std::shared_ptr<IntLazy>& new_seq);
    int get_n();
    
    std::shared_ptr<IntLazy>& get_active_sequence();
};

int run_gui_new();