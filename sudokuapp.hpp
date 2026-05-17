#ifndef SUDOKUAPP_HPP
#define SUDOKUAPP_HPP
#include "app.hpp"
#include "sudokucell.hpp"
#include "sudokulogic.hpp"


class SudokuApp : public App
{
protected:
    SudokuLogic _logic;
    SudokuCell* _cells[9][9];
public:
    SudokuApp();

    void action(std::string) override;
    void check_victory();
    void sync_board();
};

#endif // SUDOKUAPP_HPP
