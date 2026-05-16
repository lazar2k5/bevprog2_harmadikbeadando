#ifndef SUDOKULOGIC_HPP
#define SUDOKULOGIC_HPP

#include <string>

class SudokuLogic
{
protected:
    int _board[9][9];
    bool _fixed[9][9];
    bool _conflict[9][9];
public:
    SudokuLogic();
    void _update_conflicts();
    bool load_from_file(const std::string& filename);
    bool set_value(int row, int col, int value);
    void clear_value(int row, int col);
    int get_value(int row, int colt) const;
    bool is_fixed(int tow, int col) const;
    bool has_conflict(int row, int col) const;
    bool is_solved() const;
};

#endif // SUDOKULOGIC_HPP
