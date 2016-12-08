//Aswin Nair
//Assignment 7: Buffon's Needle
#define _USE_MATH_DEFINES
#include <iostream>
#include <sstream>
#include "Simple_window.h"
#include "GUI.h"
#include "Graph.h"
#include "Window.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
using namespace Graph_lib;
using namespace std;

struct Lines_window : Graph_lib::Window {
	    Lines_window(Point xy, int w, int h, const string& title );
	    //Needle variables
	    vector <Point*> midpoints, points1, points2;
	    vector <Line*> needles;
	    stringstream countText;
	    Text message {Point{500,500}, countText.str()};
	    Lines parallelLines;
	private:
	    //Buttons and Menus (Widgets)
	    Button quitButton, dropButton, menuButton;
	    In_box dropCountInput;
	    Menu motionMenu;

	    //Callback functions
	    static void cb_count(Address, Address);
	    static void cb_rotate(Address, Address);
	    static void cb_unlist(Address, Address);
        static void cb_menu(Address, Address);
	    static void cb_quit(Address, Address);
	    static void cb_drop(Address, Address);

	    //Actions invoked by callback functions
	    void hide_menu() { motionMenu.hide(); menuButton.show(); }
	    void count_pressed();
	    void rotate_pressed();
	    void unlist_pressed();
	    void menu_pressed() { menuButton.hide(); motionMenu.show(); }
	    void quit();
	    void drop();
	};

Lines_window::Lines_window(Point xy, int w, int h, const string& title)
    :Window(xy,w,h,title),
    quitButton(Point(x_max()-70,0), 70, 20, "Quit", cb_quit),
	dropButton(Point(x_max()-150,0), 70, 20, "Drop", cb_drop),
	menuButton(Point(x_max()-90,30), 90, 20, "Motion Menu", cb_menu),
	dropCountInput(Point(x_max()-230,0), 70, 20, "Enter Drop Count:"),
	motionMenu(Point(x_max()-70,30),70,20,Menu::vertical,"Motion")
{
		//Attaching menus
		attach(dropCountInput);
    	attach(quitButton);
    	attach(dropButton);
    	motionMenu.attach(new Button(Point(0,0),0,0,"Count",cb_count));
    	motionMenu.attach(new Button(Point(0,0),0,0,"Rotate",cb_rotate));
    	motionMenu.attach(new Button(Point(0,0),0,0,"(Un)List",cb_unlist));
        attach(motionMenu);
    	motionMenu.hide();
    	attach(menuButton);

    	//Constant Parallel Lines
        for (int a = 200; a <= 1200; a += 200){
        	parallelLines.add(Point{a,25}, Point{a,675});
        }
        attach (parallelLines);

}

void Lines_window::cb_drop(Address, Address pw) { reference_to<Lines_window>(pw).drop(); }
void Lines_window::cb_quit(Address, Address pw) { reference_to<Lines_window>(pw).quit(); }
void Lines_window::cb_count(Address, Address pw) { reference_to<Lines_window>(pw).count_pressed(); }
void Lines_window::cb_rotate(Address, Address pw) { reference_to<Lines_window>(pw).rotate_pressed(); }
void Lines_window::cb_unlist(Address, Address pw) { reference_to<Lines_window>(pw).unlist_pressed(); }
void Lines_window::cb_menu(Address, Address pw) { reference_to<Lines_window>(pw).menu_pressed(); }

//Functions
void Lines_window::quit() { hide(); }
void Lines_window::drop() {
	int dropCount = dropCountInput.get_int();
	for (int a = 0; a < needles.size(); ++a){ detach(*needles[a]); delete needles[a]; }
	needles.clear(); midpoints.clear();

	int x, y; double x1, y1, x2, y2, theta = 0;
	for(int a = 0; a < dropCount; ++a){
		theta = (rand()%360) * (M_PI/180);
		x = rand() % 1200 + 100; y = rand() % 700 + 100;
		Point* midpoint = new Point(x,y); midpoints.push_back(midpoint);
		x1 = x + 100*cos(theta); y1 = y + 100*sin(theta);
		Point* p1 = new Point(x1,y1); points1.push_back(p1);
		x2 = x - (100 * cos(theta)); y2 = y - (100 * sin(theta));
	    Point* p2 = new Point (x2,y2); points2.push_back(p2);
		Line* needle = new Line(Point(x1,y1), Point(x2,y2));
		needles.push_back(needle);
		attach(*needle);
	}
	redraw();
}
void Lines_window::count_pressed() {
	countText << "PI IS EQUAL TO: ";
	Text message {Point{500,500}, countText.str()};
	message.set_color(Color::black);
	attach(message);
	redraw();
	hide_menu();
}
void Lines_window::rotate_pressed() {
	hide_menu();
}
void Lines_window::unlist_pressed() {
	hide_menu();
}

int main() {
	try {
		srand(unsigned(time(0)));
		Lines_window mainWindow(Point(100,100),1400,700,"Assignment 7: Buffon's Needle");
		gui_main(); //Runs the program
	}
	catch(exception& e) {
	    cerr << "exception: " << e.what() << '\n';
	    return 1;
	}
	catch (...) {
	    cerr << "Some exception\n";
	    return 2;
	}
}
