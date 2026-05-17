#include "button.hpp"
#include "widgets.hpp"
#include "graphics.hpp"
#include "app.hpp"

using namespace genv;

Button::Button(App* parent, int x, int y, int sx, int sy, std::string label, std::string action_id)
    : Widget(parent, x, y, sx, sy), _label(label), _action_id(action_id){
    _clicked = false;
}

void Button::draw() {
    gout << move_to(_x,_y) << color(255,255,255) << box(_size_x, _size_y);

    if (_clicked) {
        gout << move_to(_x+2, _y+2) << color(100,100,100) << box(_size_x-4, _size_y-4);
    } else {
        gout << move_to(_x+2, _y+2) << color(0,0,0) << box(_size_x-4, _size_y-4);
    }

    gout << move_to(_x + 15, _y + _size_y / 2 + 5) << color(255,255,255) << text(_label);
}

void Button::handle(event ev) {
    if(ev.type == ev_mouse) {
        bool is_hover = (ev.pos_x >= _x && ev.pos_x <= _x + _size_x &&
                         ev.pos_y >= _y && ev.pos_y <= _y + _size_y);

        if(ev.button == btn_left && is_hover) {
            _clicked = true;

            _parent->action(_action_id);
        }
        else if(ev.button == -btn_left) {
            _clicked = false;
        }
    }
}
