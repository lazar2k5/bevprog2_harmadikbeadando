#include "sudokucell.hpp"
#include "graphics.hpp"
#include <string>
#include "app.hpp"

using namespace genv;

SudokuCell::SudokuCell(App* parent, int x, int y, int size)
    :Widget(parent, x, y, size, size), _value(0), _is_fixed(false), _has_conflict(false)
{
}

void SudokuCell::draw() {
    if(_has_conflict){
        gout << color(255,100,100);
    } else if(_is_fixed){
        gout << color(200,200,200);
    }else if(_focused) {
        gout << color(255,255,200);
    } else{
        gout << color(255,255,255);
    }

    gout << move_to(_x, _y) << box(_size_x, _size_y);
    gout << move_to(_x +1, _y +1) << color(0,0,0) << box(_size_x - 2, _size_y-2);

    if(_has_conflict) gout << color(255,100,100);
    else if(_is_fixed) gout << color(200,200,200);
    else if(_focused) gout << color(255,255,200);
    else gout << color(255,255,255);
    gout << move_to(_x+2, _y+2) << box(_size_x - 4, _size_y -4);

    if(_value != 0){
        std::string s = std::to_string(_value);

        if(_is_fixed) gout << color(0,0,150);
        else gout << color(0,0,0);

        int tx = _x + _size_x / 2 - gout.twidth(s) / 2;
        int ty = _y + _size_y / 2 + (gout.cascent() - gout.cdescent() / 2);

        gout << move_to(tx, ty) << text(s);
    }
}

void SudokuCell::handle(event ev){
    if(_is_fixed) return;
    if(ev.type == ev_key){
        bool changed = false;
        if(ev.keycode >= '1' && ev.keycode <= '9'){
            _value = ev.keycode - '0';
            changed = true;
        }
        else if(ev.keycode == key_backspace || ev.keycode == key_delete || ev.keycode == '0'){
            _value = 0;
            changed = true;
        }

        if(changed){
            _parent->action("valtozas_tortent");
        }

    }
}
