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
    
    wxButton* button_create_finite;
    wxButton* button_create_infinite;
    wxButton* button_materialize;

    wxTextCtrl* input_param;
    
    wxListBox* output_list_box; 
    wxStaticText* status_label;

    void on_create_finite(wxCommandEvent& event); 
    void on_create_infinite(wxCommandEvent& event);   
    void on_select_sequence(wxCommandEvent& event);      
    
    void on_materialize(wxCommandEvent& event);   

    void update_comboboxes();
    void show_content(); 
    void update_status();
    
    void add_sequence_to_list(const std::shared_ptr<IntLazy>& new_seq);
    int get_n();
    
    std::shared_ptr<IntLazy>& get_active_sequence();
};

int run_gui_new();