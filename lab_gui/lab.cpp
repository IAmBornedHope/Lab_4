#include "lab.hpp"

LabFrame::LabFrame() : wxFrame(nullptr, wxID_ANY, wxString::FromUTF8("Лабораторная работа №4"), wxDefaultPosition, wxSize(1200, 800)) {

    wxPanel* main_panel = new wxPanel(this);
    wxBoxSizer* main_sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* left_sizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText* title = new wxStaticText(main_panel, wxID_ANY, wxString::FromUTF8("Активная последовательность:"));
    left_sizer->Add(title, 0, wxLEFT | wxTOP, 5);

    object_selector = new wxComboBox(main_panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, 0, nullptr, wxCB_READONLY);
    object_selector->Bind(wxEVT_COMBOBOX, &LabFrame::on_select_sequence, this);
    left_sizer->Add(object_selector, 0, wxEXPAND | wxALL, 5);

    left_sizer->Add(new wxStaticLine(main_panel), 0, wxEXPAND | wxALL, 10);

    // Создание последовательностей
    wxStaticText* param_title = new wxStaticText(main_panel, wxID_ANY, wxString::FromUTF8("Новая последовательность (N):"));
    left_sizer->Add(param_title, 0, wxLEFT | wxTOP, 5);
    spin_create = new wxSpinCtrl(main_panel, wxID_ANY, wxT("10"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100000, 10);
    left_sizer->Add(spin_create, 0, wxEXPAND | wxALL, 5);

    button_create_finite = new wxButton(main_panel, wxID_ANY, wxString::FromUTF8("Конечная [1..N]"));
    button_create_finite->Bind(wxEVT_BUTTON, &LabFrame::on_create_finite, this);
    left_sizer->Add(button_create_finite, 0, wxEXPAND | wxALL, 5);

    button_create_infinite = new wxButton(main_panel, wxID_ANY, wxString::FromUTF8("Фибоначчи [1..N]"));
    button_create_infinite->Bind(wxEVT_BUTTON, &LabFrame::on_create_infinite, this);
    left_sizer->Add(button_create_infinite, 0, wxEXPAND | wxALL, 5);

    left_sizer->Add(new wxStaticLine(main_panel), 0, wxEXPAND | wxALL, 10);

    // Вставка и очистка
    left_sizer->Add(new wxStaticText(main_panel, wxID_ANY, wxString::FromUTF8("Вставить в конец")), 0, wxLEFT | wxTOP, 5);
    spin_append = new wxSpinCtrl(main_panel, wxID_ANY, wxT("10"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, INT_MIN, INT_MAX, 0);
    left_sizer->Add(spin_append, 0, wxEXPAND | wxALL, 5);

    button_append = new wxButton(main_panel, wxID_ANY, "Append");
    button_append->Bind(wxEVT_BUTTON, &LabFrame::on_append, this);
    left_sizer->Add(button_append, 0, wxEXPAND | wxALL, 5);

    button_clear = new wxButton(main_panel, wxID_ANY, "Clear");
    button_clear->Bind(wxEVT_BUTTON, &LabFrame::on_clear, this);
    left_sizer->Add(button_clear, 0, wxEXPAND | wxALL, 5);

    left_sizer->Add(new wxStaticLine(main_panel), 0, wxEXPAND | wxLEFT | wxRIGHT, 5);

    // Конкатенация
    left_sizer->Add(new wxStaticText(main_panel, wxID_ANY, wxString::FromUTF8("Цель для конкатенации:")), 0, wxLEFT | wxTOP, 5);

    target_selector = new wxComboBox(main_panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, 0, nullptr, wxCB_READONLY);
    target_selector->Bind(wxEVT_COMBOBOX, &LabFrame::on_select_target, this);
    left_sizer->Add(target_selector, 0, wxEXPAND | wxALL, 5);

    button_concat = new wxButton(main_panel, wxID_ANY, "Concat");
    button_concat->Bind(wxEVT_BUTTON, &LabFrame::on_concat, this);
    left_sizer->Add(button_concat, 0, wxEXPAND | wxALL, 5);

    left_sizer->Add(new wxStaticLine(main_panel), 0, wxEXPAND | wxLEFT | wxRIGHT, 5);

    // Сетка мап-скип-тейк
    left_sizer->Add(new wxStaticText(main_panel, wxID_ANY, wxString::FromUTF8("Сколько взять/пропустить?")), 0, wxLEFT | wxTOP, 5);

    spin_take_skip = new wxSpinCtrl(main_panel, wxID_ANY, wxT("10"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100000, 3);
    left_sizer->Add(spin_take_skip, 0, wxEXPAND | wxALL, 5);

    button_grid = new wxGridSizer(2, 2, 5, 5);
    
    button_take = new wxButton(main_panel, wxID_ANY, "Take");
    button_take->Bind(wxEVT_BUTTON, &LabFrame::on_take, this);
    button_grid->Add(button_take, 1, wxEXPAND);

    button_skip = new wxButton(main_panel, wxID_ANY, "Skip");
    button_skip->Bind(wxEVT_BUTTON, &LabFrame::on_skip, this);
    button_grid->Add(button_skip, 1, wxEXPAND);

    button_map = new wxButton(main_panel, wxID_ANY, "Map (x * 2)");
    button_map->Bind(wxEVT_BUTTON, &LabFrame::on_map, this);
    button_grid->Add(button_map, 1, wxEXPAND);

    button_where = new wxButton(main_panel, wxID_ANY, wxString::FromUTF8("Where (x ⫶ 3)"));
    button_where->Bind(wxEVT_BUTTON, &LabFrame::on_where, this);
    button_grid->Add(button_where, 1, wxEXPAND);

    left_sizer->Add(button_grid, 0, wxEXPAND | wxALL, 5);

    left_sizer->Add(new wxStaticLine(main_panel), 0, wxEXPAND | wxLEFT | wxRIGHT, 5);

    // Материализация
    left_sizer->Add(new wxStaticText(main_panel, wxID_ANY, wxString::FromUTF8("Материализовать первые M")), 0, wxLEFT | wxTOP, 5);
    spin_materialize = new wxSpinCtrl(main_panel, wxID_ANY, wxT("10"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100000, 5);
    left_sizer->Add(spin_materialize, 0, wxEXPAND | wxALL, 5);

    button_materialize = new wxButton(main_panel, wxID_ANY, wxString::FromUTF8("Материализовать"));
    button_materialize->Bind(wxEVT_BUTTON, &LabFrame::on_materialize, this);
    left_sizer->Add(button_materialize, 0, wxEXPAND | wxALL, 5);

    left_sizer->AddStretchSpacer();

    status_label = new wxStaticText(main_panel, wxID_ANY, wxString::FromUTF8("Длина: 0 | Кэшировано: 0"));
    status_label->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    left_sizer->Add(status_label, 0, wxEXPAND | wxALL, 5);

    main_sizer->Add(left_sizer, 0, wxEXPAND | wxALL, 10);

    // окно вывода
    output_list_box = new wxListBox(main_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, nullptr, wxLB_SINGLE | wxHSCROLL);
    output_list_box->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Consolas"));
    main_sizer->Add(output_list_box, 1, wxEXPAND | wxALL, 10);

    main_panel->SetSizer(main_sizer);
    
    auto empty_sequence = std::make_shared<IntLazy>();
    sequences.append(empty_sequence);
    update_comboboxes();
    show_content();
    Centre();
}

LabFrame::~LabFrame() {}

void LabFrame::update_comboboxes() {
    int active_index = object_selector->GetSelection();
    int target_index = target_selector->GetSelection();
    object_selector->Clear();
    target_selector->Clear();

    size_t count = sequences.get_length();
    for (size_t number = 0; number < count; ++number) {
        wxString name = wxString::Format(wxString::FromUTF8("Sequence №%zu"), number + 1);
        object_selector->Append(name);
        target_selector->Append(name);

    }
    if (active_index < count) {
        object_selector->SetSelection(active_index);
        current_sequence_id = active_index;
    } else {
        object_selector->SetSelection(0);
        current_sequence_id = 0;
    }

    target_selector->SetSelection(target_index);
    update_concat();
    
}

void LabFrame::show_content() {
    size_t max_elem_length = 4;
    output_list_box->Clear();
    auto sequence = get_active_sequence();
    update_status();
    update_operations();
    update_concat();        

    Cardinal length = sequence->get_length();
    size_t cached = sequence->get_materialized_count();

    if (length.is_infinite()) {
        if (cached > 0) {
             output_list_box->Append(wxString::FromUTF8("Бесконечная последовательность Фибоначчи"));
        }
    } else {
        if (length.get_size() == 0) {
            output_list_box->Append(wxString::FromUTF8("Тут могла бы быть реклама албанского вируса"));
            return;
        }
    }
    size_t limit = std::min(cached, static_cast<size_t>(100));
    
    for(size_t index = 0; index < limit; ++index) {
        int temp = std::to_string(sequence->get(Cardinal(index))).length();
        if(static_cast<size_t>(temp) > max_elem_length) {
            max_elem_length = static_cast<size_t>(temp);
        }
    }

    for (size_t index = 0; index < limit; ++index) {
        int value = sequence->get(Cardinal(index));
        output_list_box->Append(wxString::Format(wxString::FromUTF8(" [%03zu]  | %*d |"), index, static_cast<int>(max_elem_length), value));
    }

    if (!length.is_infinite() && cached < length.get_size()) {
        output_list_box->Append(wxString::Format(wxString::FromUTF8("Конечная последовательность (%zu не закэшировано)"), length.get_size() - cached));
    } else if (length.is_infinite() && cached >= limit) {
         output_list_box->Append(wxString::FromUTF8("Дальше бесконечный хвост"));
    } else if (!length.is_infinite() && cached == length.get_size()) {
        output_list_box->Append(wxString::FromUTF8("Кеш кончился"));
    }
}

void LabFrame::add_sequence_to_list(const std::shared_ptr<IntLazy>& new_seq) {
    sequences.append(new_seq);
    update_comboboxes();
    current_sequence_id = sequences.get_length() - 1;
    object_selector->SetSelection(current_sequence_id);
    show_content();
}

std::shared_ptr<IntLazy>& LabFrame::get_active_sequence() {
    if (current_sequence_id >= sequences.get_length()) {
        throw IndexOutOfRangeException(current_sequence_id, sequences.get_length());
    }
    return sequences.get_reference(current_sequence_id);
}

std::shared_ptr<IntLazy>& LabFrame::get_target_sequence() {
    size_t target_id = target_selector->GetSelection();
    if (target_id == wxNOT_FOUND || target_id >= sequences.get_length()) {
        return get_active_sequence();
    }
    return sequences.get_reference(target_id);
}

void LabFrame::update_status() {
    auto sequence = get_active_sequence();
    Cardinal length = sequence->get_length();
    size_t cached = sequence->get_materialized_count();
    
    wxString length_str = length.is_infinite() ? wxString::FromUTF8("Много)))") : wxString::Format(wxString::FromUTF8("%zu"), length.get_size());
    status_label->SetLabel(wxString::Format(wxString::FromUTF8("Длина: %s\nКэшировано: %zu"), length_str, cached));
}

void LabFrame::update_operations() {
    auto sequence = get_active_sequence();
    Cardinal length = sequence->get_length();
    bool is_infinite = length.is_infinite();

    if (is_infinite) {
        spin_append->Disable();
        button_append->Disable();
        button_clear->Enable();
        button_materialize->Enable();
        spin_materialize->Enable();
        spin_take_skip->Enable();
        button_take->Enable();
        button_skip->Enable();
        button_map->Enable();
        button_where->Enable();
    }
    else {
        button_append->Enable();
    }
    if (!is_infinite) {
        if (length.get_size() == 0) {
            button_clear->Disable();
            button_materialize->Disable();
            spin_materialize->Disable();
            spin_take_skip->Disable();
            button_take->Disable();
            button_skip->Disable();
            button_map->Disable();
            button_where->Disable();
        
        }
        else {
            button_clear->Enable();
            button_materialize->Enable();
            spin_materialize->Enable();
            spin_take_skip->Enable();
            spin_append->Enable();
            button_take->Enable();
            button_skip->Enable();
            button_map->Enable();
            button_where->Enable();
            
        }
    }
}

void LabFrame::update_concat() {
    if (target_selector->GetSelection() == object_selector->GetSelection() || target_selector->GetSelection() == wxNOT_FOUND) {
        button_concat->Disable();
    }
    else {
        button_concat->Enable();
    }
}

void LabFrame::on_create_finite(wxCommandEvent& event) {
    int n = spin_create->GetValue();

    auto array = std::make_shared<MutableArraySequence<int>>();
    for(size_t count = 0; count < n; ++count) {
        array->append(count);
    }

    auto generator = std::make_shared<ContainerGenerator<int, MutableArraySequence>>(*array);
    auto lazy_sequence = std::make_shared<IntLazy>(generator);

    add_sequence_to_list(lazy_sequence);
}

void LabFrame::on_create_infinite(wxCommandEvent& event) {
    auto fibonacci = [](const MutableArraySequence<int>& sequence) -> int {
        if (sequence.get_length() < 2) return 1;
        return sequence[sequence.get_length() - 1] + sequence[sequence.get_length() - 2];
    };

    MutableArraySequence<int> cache;

    auto generator = std::make_shared<RecurrentGenerator<int, MutableArraySequence>>(fibonacci, cache);
    auto infinite_sequence = std::make_shared<IntLazy>(cache, generator);
    add_sequence_to_list(infinite_sequence);
}

void LabFrame::on_append(wxCommandEvent& event) {
    int value = spin_append->GetValue();
    auto sequence = get_active_sequence();

    auto new_elem = std::make_shared<MutableArraySequence<int>>();
    new_elem->append(value);
    auto generator = std::make_shared<ContainerGenerator<int, MutableArraySequence>>(*new_elem);
    auto temp_sequence = std::make_shared<IntLazy>(generator);

    sequences.get_reference(current_sequence_id) = sequence->concat(temp_sequence);

    show_content();
}

void LabFrame::on_concat(wxCommandEvent& event) {
    size_t target_id = target_selector->GetSelection();
    auto result = sequences.get_reference(current_sequence_id)->concat(sequences.get_reference(target_id));
    add_sequence_to_list(result);
}

void LabFrame::on_take(wxCommandEvent& event) {
    int n = spin_take_skip->GetValue();
    auto current_sequence = get_active_sequence();
    auto result = current_sequence->take(n);
    add_sequence_to_list(result);
}

void LabFrame::on_skip(wxCommandEvent& event) {
    int n = spin_take_skip->GetValue();
    auto current_sequence = get_active_sequence();
    auto result = current_sequence->skip(n);
    add_sequence_to_list(result);
}

void LabFrame::on_map(wxCommandEvent& event) {
    auto current_sequence = get_active_sequence();
    auto result = current_sequence->map<int>([](int x) { return x * 2; });
    add_sequence_to_list(result);
}

void LabFrame::on_where(wxCommandEvent& event) {
    auto current_sequence = get_active_sequence();
    auto result = current_sequence->where([](int x) { return x % 3 == 0; });
    add_sequence_to_list(result);
}

void LabFrame::on_clear(wxCommandEvent& event) {
    sequences.get_reference(current_sequence_id) = std::make_shared<IntLazy>();
    show_content();
}

void LabFrame::on_select_target(wxCommandEvent& event) {
    update_concat();
}

void LabFrame::on_select_sequence(wxCommandEvent& event) {
    current_sequence_id = object_selector->GetSelection();
    show_content();
}

void LabFrame::on_materialize(wxCommandEvent& event) {
    int n = spin_materialize->GetValue();
    auto sequence = get_active_sequence();
    Cardinal length = sequence->get_length();
    
    size_t limit = n;
    if (!length.is_infinite() && static_cast<size_t>(n) > length.get_size()) {
        limit = length.get_size();
    }

    for (size_t index = 0; index < limit; ++index) {
        sequence->get(Cardinal(index));
    }
        show_content();
}

