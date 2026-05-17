#include "sudokuapp.hpp"
#include <iostream>
using namespace std;
using namespace genv;

SudokuApp::SudokuApp() {
    gout.open(550, 550);

    int cell_size = 50;
    int offset_x = 50;
    int offset_y = 50;

    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            int gap_x = (col / 3)*5;
            int gap_y = (row / 3) * 5;
            int x = offset_x + col * cell_size + gap_x;
            int y = offset_y + row * cell_size + gap_y;
            _cells[row][col] = new SudokuCell(this, x, y, cell_size);
        }
    }

    _logic.set_value(0,0,5); _cells[0][0] ->set_value(5); _cells[0][0] ->set_fixed(true);
    _logic.set_value(0,1,3); _cells[0][1] ->set_value(3); _cells[0][1]->set_fixed(true);

    if(_logic.load_from_file("palya1.txt")){
        for (int row = 0; row < 9; ++row) {
            for (int col = 0; col < 9; ++col) {
                int var = _logic.get_value(row, col);
                _cells[row][col]->set_value(var);

                if(var != 0){
                    _cells[row][col]->set_fixed(true);
                } else{
                    _cells[row][col]->set_fixed(false);
                }
            }
        }
    } else
        std::cout << "Hiba: Nem talalhato a palya1.txt fajl!" << std::endl;
}

void SudokuApp::action(std::string id){
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            int widget_value = _cells[row][col]->get_value();

            if(widget_value != _logic.get_value(row, col))
                _logic.set_value(row, col, widget_value);
        }
    }

    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            bool is_bad = _logic.has_conflict(row, col);
            _cells[row][col]->set_conflict(is_bad);
        }
    }
}
