#ifndef BUTTON_HPP
#define BUTTON_HPP
#include "widgets.hpp"
#include <string>

class Button : public Widget
{
protected:
    std::string _label;
    std::string _action_id;
    bool _clicked;
public:
    Button(App* parent, int x, int y, int sx, int sy, std::string, std::string);
    virtual void draw() override;
    virtual void handle(genv::event ev) override;
};

#endif // BUTTON_HPP
