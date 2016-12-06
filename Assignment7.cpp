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
	    //Open_polyline lines;
	    Lines parallelLines, needles;
	    Line needle;
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
	    void count_pressed() { /*Do function, then:*/ hide_menu(); }
	    void rotate_pressed() { /*Do function, then:*/ hide_menu(); }
	    void unlist_pressed() { /*Do function, then:*/ hide_menu(); }
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
    	attach(needles);

    	//Constant Parallel Lines
        for (int a = 200; a <= 1200; a += 200){
        	parallelLines.add(Point{a,25}, Point{a,675});
        }
        attach (parallelLines);

}

void Lines_window::cb_drop(Address, Address pw) { reference_to<Lines_window>(pw).drop(); }
void Lines_window::cb_quit(Address, Address pw) { reference_to<Lines_window>(pw).quit(); }
void Lines_window::quit() { hide(); }
void Lines_window::drop() {
	int dropCount = dropCountInput.get_int();
	for (int a = 0; a < dropCount; ++a){
		int x = rand() % 1400, y = rand() % 700;
		needles.add(Point{x, y}, Point{x + 200, y + 200});
	}
	redraw();
}
void Lines_window::cb_count(Address, Address pw) { reference_to<Lines_window>(pw).count_pressed(); }
void Lines_window::cb_rotate(Address, Address pw) { reference_to<Lines_window>(pw).rotate_pressed(); }
void Lines_window::cb_unlist(Address, Address pw) { reference_to<Lines_window>(pw).unlist_pressed(); }
void Lines_window::cb_menu(Address, Address pw) { reference_to<Lines_window>(pw).menu_pressed(); }

int main() {
	srand(unsigned(time(0)));
	Lines_window mainWindow(Point(100,100),1400,700,"Assignment 7: Buffon's Needle");
	gui_main(); //Runs the program
}
