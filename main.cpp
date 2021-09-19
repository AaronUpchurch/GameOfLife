#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <random>

using namespace std;
using namespace sf;

class cell : public RectangleShape{
public:

    bool alive;
    bool nextGen;

    cell(int xPos, int yPos, Color color) : RectangleShape({1,1}) {
        alive = false;
        nextGen = false;
        setPosition(xPos, yPos);
        setFillColor(color);
    }

    int update(int& n, bool& a, bool& b, bool& c, bool& d, bool& e, bool& f, bool& g, bool& h) {  //applies change from previous count and gets next status //
        
        int aliveAround = 0;
        if (a) {
            ++aliveAround;
        }
        if (b) {
            ++aliveAround;
        }
        if (c) {
            ++aliveAround;
        }
        if (d) {
            ++aliveAround;
        }
        if (e) {
            ++aliveAround;
        }
        if (f) {
            ++aliveAround;
        }
        if (g) {
            ++aliveAround;
        }
        if (h) {
            ++aliveAround;
        }
       
        if (aliveAround == 3 || (alive && aliveAround == 2)) {
            nextGen = true;
            
        }
        else {
            nextGen = false;
            
        }
        return aliveAround;
        
    }
};
int getAliveCount(vector<cell>& cells) {
    int ret = 0;
    for (int i = 0; i < cells.size(); ++i) {
        if (cells.at(i).alive) {
            ++ret;
        }
    }
    return ret;
}
void random(vector<cell>& cells, int width) {
    
    srand(static_cast <unsigned> (time(0)));
    
    for (int i = 0; i < ( (width*width)/5); ++i) {  //30,000 and 160,000
        int r = (int)((float(rand()) / float((RAND_MAX)) * width * width));
        if (r == width * width) {
            r = width * width - 1;
        }
        
        cells.at(r).alive = true;
        
        
    }
}
void fill(vector<cell>& cells) {
    for (int i = 0; i < cells.size(); ++i) {
        cells.at(i).alive = true;
    }
}
void createAll(vector<cell>& cells, int width) {
    for (int x = 0; x < width; ++x) { // creates all cells //
        for (int y = 0; y < width; ++y) {
            
                cells.push_back(cell(x, y, Color::Green));
            
        }
    }
}
void drawAllCells(vector<cell>& cells, RenderWindow& window, int width) {
    for (int i = width + 1; i < cells.size() - width - 1; ++i) { // draws all alive cells  //
        if (cells.at(i).alive) {
            window.draw(cells.at(i));
        }
    }
}
void applyNextgenToAll(vector<cell>& cells, int width) {
    for (int i = width + 1; i < cells.size() - width - 1; ++i) { //  applies next gen values //
        
        cells.at(i).alive = cells.at(i).nextGen;
    }
}
void updateAllCells(vector<cell>& cells, int width) {
    int sum = 0;
    for (int i = width + 1; i < cells.size() - (width + 1); ++i) {  // updates all cells //


        bool a = cells.at((float)i - 1 - width).alive;


        bool b = cells.at((float)i - (float)width).alive;

        bool c = cells.at((float)i + (float)1 - (float)width).alive;
        bool d = cells.at((float)i - 1).alive;
        bool e = cells.at((float)i + 1).alive;
        bool f = cells.at((float)i - 1 + width).alive;
        bool g = cells.at((float)i + width).alive;
        bool h = cells.at((float)i + 1 + width).alive;

        sum += cells.at(i).update(i, a, b, c, d, e, f, g, h);

    }
    //cout << "Avg: " << (float)sum / (float)(width * width) << endl;
}
void sleepMili(int num) {
    chrono::milliseconds dura(num);
    this_thread::sleep_for(dura);
}
int main()
{
    int width = 400; // want .1 starting alive ratio //
    RenderWindow window(VideoMode(width, width), "SFML works!");
   
    
    vector<cell> cells;
    cout << "Starting program" << endl;
    createAll(cells, width); // fills cells with width * width cells //
    cout << "Created all cells" << endl;
    random(cells, width);  // sets cell values to random //
    cout << "Randomized all cells" << endl;
    int aliveCount = 0;
    int genCounter = 0;
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        aliveCount = getAliveCount(cells);
       
        window.clear();
        
        updateAllCells(cells, width);
        
        drawAllCells(cells, window, width);
       
        applyNextgenToAll(cells, width);
        
        window.display();
        
        ++genCounter;
        
    }
}

