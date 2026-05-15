#include "app.hpp"
#include "graphics.hpp"
#include "widgets.hpp"
#include <vector>

using namespace genv;

App::App() {}

void App::event_loop(){
    event ev;
    int focus = -1;
    while(gin >> ev ) {
        if (ev.type == ev_mouse && ev.button==btn_left) {
            for (size_t i=0;i<_w.size();i++) {
                if (_w[i]->is_selected(ev.pos_x, ev.pos_y)) {
                    focus = i;
                }
            }
        }
        if(ev.type == ev_key){
            if(ev.keycode == key_enter){
                action("enter");
            }
        }
        if (focus!=-1) {
            _w[focus]->handle(ev);
        }
        for (Widget * w : _w) {
            w->draw();
        }
        gout << refresh;
    }
}

void App::register_widget(Widget * widget){
    _w.push_back(widget);
}


