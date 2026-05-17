#include "graphics.hpp"
#include "widgets.hpp"
#include <vector>
#include "app.hpp"
#include "iostream"
#include "sudokuapp.hpp"
using namespace std;
using namespace genv;


int main()
{
    SudokuApp app;
    string a = "";
    app.action(a);

    app.event_loop();
    return 0;
}
