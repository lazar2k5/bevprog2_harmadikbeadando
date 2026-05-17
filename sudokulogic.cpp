#include "sudokulogic.hpp"
#include "fstream"

SudokuLogic::SudokuLogic() {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            _board[i][j] = 0;
            _fixed[i][j] = false;
            _conflict[i][j] = false;
        }
    }
}

bool SudokuLogic::load_from_file(const std::string& filename){
    std::ifstream file(filename);
    if(!file.is_open()){
        return false;
    }

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            int var;
            file >> var;
            _board[i][j] = var;

            if(var != 0){
                _fixed[i][j] = true;
            } else {
                _fixed[i][j] = false;
            }
        }
    }
    file.close();
    _update_conflicts();
    return true;
}

bool SudokuLogic::set_value(int row, int col, int value){
    if(_fixed[row][col]){
        return false;
    }

    _board[row][col] = value;
    _update_conflicts();
    return true;
}

void SudokuLogic::clear_value(int row, int col){
    if(!_fixed[row][col]){
        _board[row][col] = 0;
        _update_conflicts();
    }
}

void SudokuLogic::_update_conflicts() {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            _conflict[i][j] = false;
        }
    }

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            int var = _board[i][j];
            if(var == 0) continue;

            for (int k = 0; k < 9; ++k) {
                if(k != j && _board[i][k] == var)
                    _conflict[i][j] = true;
            }

            for (int k = 0; k < 9; ++k) {
                if(k != i && _board[k][j] == var)
                    _conflict[i][j] = true;
            }

            int start_i = (i / 3) * 3;
            int start_j = (j / 3) * 3;

            for (int k = start_i; k < start_i +3; ++k) {
                for (int l = start_j; l < start_j + 3; ++l) {
                    if((k != i || l != j) && _board[k][l] == var)
                        _conflict[i][j] = true;
                }
            }
        }
    }
}

int SudokuLogic::get_value(int row, int col) const {
    return _board[row][col];
}

bool SudokuLogic::is_fixed(int row, int col) const {
    return _fixed[row][col];
}

bool SudokuLogic::has_conflict(int row, int col) const {
    return _conflict[row][col];
}

bool SudokuLogic::is_solved() const {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if(_board[i][j] == 0 || _conflict[i][j])
                return false;
        }
    }
    return true;
}

















