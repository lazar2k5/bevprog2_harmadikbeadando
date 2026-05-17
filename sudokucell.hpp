#ifndef SUDOKUCELL_HPP
#define SUDOKUCELL_HPP

#include "widgets.hpp"

class SudokuCell : public Widget
{
protected:
    int _value;
    bool _is_fixed;
    bool _has_conflict;
    bool _is_won;
public:
    SudokuCell(App* parent, int, int, int);
    virtual void draw() override;
    virtual void handle(genv::event ev) override;
    int get_value() const {return _value;}
    void set_value(int v) {_value = v;}
    bool is_fixed() const {return _is_fixed;}
    void set_fixed(bool f){_is_fixed = f;}
    bool has_conflict() const{return _has_conflict;}
    void set_conflict(bool c){_has_conflict = c;}
    void set_won(bool won) {_is_won = won;}
};

#endif // SUDOKUCELL_HPP
