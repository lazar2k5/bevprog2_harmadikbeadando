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
        if (ev.type == ev_mouse && ev.button == btn_left) {
            int old_focus = focus;
            focus = -1;
            for (size_t i=0; i<_w.size(); i++) {
                if (_w[i]->is_selected(ev.pos_x, ev.pos_y)) {
                    focus = i;
                }
            }
            if (old_focus != focus) {
                if (old_focus != -1) {
                    _w[old_focus]->set_focus(false);
                }
                if (focus != -1) {
                    _w[focus]->set_focus(true);
                }
            }
        }
        if(ev.type == ev_key){
            if(ev.keycode == key_enter){
                action("enter");
            }
        }
        if (focus != -1) {
            _w[focus]->handle(ev);
        }

        gout << move_to(0,0) << color(0,0,0) << box(1000,1000);

        for (Widget * w : _w) {
            w->draw();
        }

        gout << refresh;
    }
}

void App::register_widget(Widget * widget){
    _w.push_back(widget);
}


