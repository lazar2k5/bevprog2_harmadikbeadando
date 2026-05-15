#include "graphics.hpp"
#include "widgets.hpp"
#include <vector>
#include "app.hpp"
#include "iostream"
using namespace std;
using namespace genv;

class MyApp : public App{
protected:
    vector<Widget *> _w;
public:
    MyApp(){

    }

    void action(){}

    vector<Widget *> getw(){
        return _w;
    }
};


int main()
{
    gout.open(600,800);

    MyApp app;

    for (Widget * wg : app.getw()) {
        wg->draw();
    }
    gout << refresh;
    app.event_loop();
    return 0;
}
