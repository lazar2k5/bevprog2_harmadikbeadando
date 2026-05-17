#include "dropdown.hpp"
#include "graphics.hpp"
#include "widgets.hpp"
#include "app.hpp"
#include <algorithm>

using namespace genv;

Dropdown::Dropdown(App* parent, int x, int y, int sx, int sy, std::vector<std::string> options, int visible)
    : Widget(parent, x, y, sx, sy), _options(options), _selected_index(0), _is_open(false), _visible_items(visible), _scroll_pos(0) {
    _item_height = sy;
}

void Dropdown::draw() {
    gout << move_to(_x, _y) << color(255, 255, 255) << box(_size_x, _size_y);
    gout << move_to(_x + 2, _y + 2) << color(0, 0, 0) << box(_size_x - 4, _size_y - 4);


    if(_options.size() > 0){
        gout << color(255, 255, 255) << move_to(_x + 10, _y + _size_y / 2 + 5) << text(_options[_selected_index]);
    }
    else{
        gout << color(255, 255, 255) << move_to(_x + 10, _y + _size_y / 2 + 5);
    }


    int nyiltartomany = 30;
    gout << move_to(_x + _size_x - nyiltartomany, _y + 2) << color(255, 255, 255) << box(nyiltartomany - 2, _size_y - 4);
    gout << move_to(_x + _size_x - nyiltartomany + 10, _y + _size_y / 2 + 5) << color(0, 0, 0) << text("V");

    if (_is_open) {
        int draw_count = std::min((int)_options.size(), _visible_items);

        for (int i = 0; i < draw_count; i++) {
            int actual_index = i + _scroll_pos;

            if (actual_index >= (int)_options.size()) break;

            int iy = _y + _size_y + (i * _item_height);

            gout << move_to(_x, iy) << color(255, 255, 255) << box(_size_x, _item_height);
            if (actual_index == _selected_index) gout << color(100, 100, 100);
            else gout << color(40, 40, 40);

            gout << move_to(_x + 2, iy + 2) << box(_size_x - 4, _item_height - 4);
            gout << color(255, 255, 255) << move_to(_x + 10, iy + _item_height / 2 + 5) << text(_options[actual_index]);
        }

        if (_options.size() > (size_t)_visible_items) {
            gout << color(200, 200, 200) << move_to(_x + _size_x - 5, _y + _size_y) << box(5, draw_count * _item_height);
        }
    }
}

void Dropdown::handle(event ev) {
    if (ev.type == ev_mouse) {
        if (_is_open) {
            if (ev.button == btn_wheelup && _scroll_pos > 0) _scroll_pos--;
            if (ev.button == btn_wheeldown && _scroll_pos < (int)_options.size() - _visible_items) _scroll_pos++;
        }

        if (ev.button == btn_left) {
            if (ev.pos_y >= _y && ev.pos_y < _y + _size_y) {
                _is_open = !_is_open;
            }
            else if (_is_open) {
                int relative_y = ev.pos_y - (_y + _size_y);
                int clicked_view_index = relative_y / _item_height;

                if (clicked_view_index >= 0 && clicked_view_index < _visible_items) {
                    int actual_index = clicked_view_index + _scroll_pos;
                    if (actual_index < (int)_options.size()) {
                        _selected_index = actual_index;
                        _is_open = false;

                        _parent->action("palya_valasztas");
                    }
                }
            }
        }
    }
}

bool Dropdown::is_selected(int mouse_x, int mouse_y) {
    if (!_is_open) return Widget::is_selected(mouse_x, mouse_y);

    int draw_count = std::min((int)_options.size(), _visible_items);
    int total_h = _size_y + (draw_count * _item_height);

    return mouse_x >= _x && mouse_x <= _x + _size_x && mouse_y >= _y && mouse_y <= _y + total_h;
}

void Dropdown::addNewItem(std::string item){
    _options.push_back(item);
}
std::string Dropdown::getSelectedItem(){
    return _options[_selected_index];
}
void Dropdown::removeItem(){
    _options.erase(_options.begin() + _selected_index);
}
int Dropdown::getVSize(){
    return _options.size();
}
std::vector<std::string> Dropdown::getVector(){
    return _options;
}
