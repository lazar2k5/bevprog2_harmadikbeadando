#ifndef DROPDOWN_HPP
#define DROPDOWN_HPP

#include "widgets.hpp"
#include <vector>

class Dropdown : public Widget{
protected:
    std::vector<std::string> _options;
    int _selected_index;
    bool _is_open;
    int _item_height;
    int _visible_items;
    int _scroll_pos;
public:
    Dropdown(App* parent, int x, int y, int sx, int sy, std::vector<std::string> options, int visible = 5);

    virtual void draw() override;
    virtual void handle(genv::event ev) override;
    virtual bool is_selected(int mouse_x, int mouse_y) override;
    virtual void addNewItem(std::string);
    virtual void removeItem();
    virtual std::string getSelectedItem();
    virtual int getVSize();
    virtual std::vector<std::string> getVector();
    virtual void set_focus(bool focus) override{
        Widget::set_focus(focus);
        if(!focus){
            _is_open = false;
            _scroll_pos = 0;
        }
    }

    std::string get_value() const {return _options[_selected_index];}
};

#endif // DROPDOWN_HPP
