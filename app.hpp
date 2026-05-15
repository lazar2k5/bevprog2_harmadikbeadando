#ifndef APP_HPP
#define APP_HPP

#include "widgets.hpp"
#include <vector>

class App
{
protected:
    std::vector<Widget *> _w;
public:
    App();
    virtual void event_loop();
    virtual void register_widget(Widget * widget);

    virtual void action(std::string id) = 0;
};

#endif // APP_HPP
