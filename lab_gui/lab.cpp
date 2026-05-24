#include "lab.hpp"

LabFrame::LabFrame() : wxFrame(nullptr, wxID_ANY, wxString::FromUTF8("Лабораторная работа №4"), wxDefaultPosition, wxSize(1200, 800)) {

    wxPanel* main_panel = new wxPanel(this);
    wxBoxSizer* main_sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* left_sizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText* title = new wxStaticText(main_panel, wxID_ANY, wxString::FromUTF8("Активная последовательность:"));
    left_sizer->Add(title, 0, wxLEFT | wxTOP, 5);

    object_selector = new wxComboBox(main_panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, 0, nullptr, wxCB_READONLY);
    //object_selector->Bind(wxEVT_COMBOBOX, &LabFrame::on_select_sequence, this);
    left_sizer->Add(object_selector, 0, wxEXPAND | wxALL, 5);

    left_sizer->Add(new wxStaticLine(main_panel), 0, wxEXPAND | wxALL, 10);

    wxStaticText* param_title = new wxStaticText(main_panel, wxID_ANY, wxString::FromUTF8("N"));
    left_sizer->Add(param_title, 0, wxLEFT | wxTOP, 5);
    input_param = new wxTextCtrl(main_panel, wxID_ANY, "10");
    input_param->SetHint(wxString::FromUTF8("Введите целое число"));
    left_sizer->Add(input_param, 0, wxEXPAND | wxALL, 5);

    button_create_finite = new wxButton(main_panel, wxID_ANY, wxString::FromUTF8("Конечная [1..N]"));
    //button_create_finite->Bind(wxEVT_BUTTON, &LabFrame::on_create_finite, this);
    left_sizer->Add(button_create_finite, 0, wxEXPAND | wxALL, 5);

    button_create_infinite = new wxButton(main_panel, wxID_ANY, wxString::FromUTF8("Фибоначчи [1..N]"));
    //button_create_infinite->Bind(wxEVT_BUTTON, &LabFrame::on_create_infinite, this);
    left_sizer->Add(button_create_infinite, 0, wxEXPAND | wxALL, 5);

    left_sizer->Add(new wxStaticLine(main_panel), 0, wxEXPAND | wxALL, 10);

    button_materialize = new wxButton(main_panel, wxID_ANY, wxString::FromUTF8("Получить N"));
    //button_materialize->Bind(wxEVT_BUTTON, &LabFrame::on_materialize, this);
    left_sizer->Add(button_materialize, 0, wxEXPAND | wxALL, 5);

    left_sizer->AddStretchSpacer();

    status_label = new wxStaticText(main_panel, wxID_ANY, wxString::FromUTF8("Длина: 0 | Кошировано: 0"));
    status_label->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    left_sizer->Add(status_label, 0, wxEXPAND | wxALL, 5);

    main_sizer->Add(left_sizer, 0, wxEXPAND | wxALL, 10);

    output_list_box = new wxListBox(main_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, nullptr, wxLB_SINGLE | wxHSCROLL);
    output_list_box->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Consolas"));
    main_sizer->Add(output_list_box, 1, wxEXPAND | wxALL, 10);

    main_panel->SetSizer(main_sizer);
    
    // auto empty_sequence = std::make_shared<IntLazy>();
    // sequences.append(empty_sequence);
    // update_comboboxes();
    // //show_content();
    // Centre();
}

LabFrame::~LabFrame() {}

void LabFrame::update_comboboxes() {
    int active_index = object_selector->GetSelection();
    object_selector->Clear();

    size_t count = sequences.get_length();
    for (size_t number = 0; number < count; ++number) {
        object_selector->Append(wxString::Format(wxString::FromUTF8("Sequence №%zu"), number + 1));
    }
    if (active_index < count) {
        object_selector->SetSelection(active_index);
        current_sequence_id = active_index;
    } else {
        object_selector->SetSelection(0);
        current_sequence_id = 0;
    }
}
