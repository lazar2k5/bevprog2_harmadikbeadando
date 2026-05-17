#include "sudokuapp.hpp"
#include <iostream>
#include "button.hpp"
using namespace std;
using namespace genv;

SudokuApp::SudokuApp() {
    gout.open(750, 550);

    int cell_size = 50;
    int offset_x = 50;
    int offset_y = 50;

    new Button(this, 520, 40,  200, 40, "1. Palya (Konnyu)",  "palya_1");
    new Button(this, 520, 100, 200, 40, "2. Palya (Kozepes)", "palya_2");
    new Button(this, 520, 160, 200, 40, "3. Palya (Nehez)",   "palya_3");

    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            int gap_x = (col / 3)*5;
            int gap_y = (row / 3) * 5;
            int x = offset_x + col * cell_size + gap_x;
            int y = offset_y + row * cell_size + gap_y;
            _cells[row][col] = new SudokuCell(this, x, y, cell_size);
        }
    }

    if(_logic.load_from_file("palya1.txt")){
        sync_board();
    }
}

void SudokuApp::action(std::string id) {

    if (id == "palya_1" || id == "palya_2" || id == "palya_3") {

        std::string selected_file = "";
        if (id == "palya_1") selected_file = "palya1.txt";
        if (id == "palya_2") selected_file = "palya2.txt";
        if (id == "palya_3") selected_file = "palya3.txt";

        if(_logic.load_from_file(selected_file)) {
            sync_board();
        } else {
            std::cout << "Nem talalom a filet: " << selected_file << std::endl;
        }
    }
    else if(id == "valtozas_tortent") {
        for (int row = 0; row < 9; ++row) {
            for (int col = 0; col < 9; ++col) {
                int widget_value = _cells[row][col]->get_value();
                if(widget_value != _logic.get_value(row, col))
                    _logic.set_value(row, col, widget_value);
            }
        }
        for (int row = 0; row < 9; ++row) {
            for (int col = 0; col < 9; ++col) {
                _cells[row][col]->set_conflict(_logic.has_conflict(row, col));
            }
        }
    }
}

void SudokuApp::sync_board(){
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            int var = _logic.get_value(row, col);
            _cells[row][col]->set_value(var);
            _cells[row][col]->set_fixed(var != 0);
            _cells[row][col]->set_conflict(_logic.has_conflict(row, col));
        }
    }
}
