#define IS_SIMULATION 1 // also have to define this variable in Simulation.hpp and Classes.hpp
#if IS_SIMULATION // if this is the simulation, then this chunck of code is used. Otherwise, this code is ignored.
/*



 SIMULATION only stuff



 */






// #include "GFWLCD.hpp"
// #include "GFWUtility.hpp" // now lives in "Class.hpp"
#include "GFWFunctions.hpp"
// #include "GFWLCD.hpp"
#include "Classes.hpp"

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include <vector>
using namespace std;

#include <cstdlib>                      // standard definitions
#include <iostream>                     // C++ I/O
#include <cstdio>                       // C I/O (for sprintf)
#include <cmath>                        // standard definitions



// #define ZOOM_SCALE 3 // now lives in GFWLCD.hpp
void Init ();
void mainLoop ();
void DrawEverything ();
bool leftKeyInp;
bool upKeyInp;
bool rightKeyInp;
bool downKeyInp;

#define CALLBACK_DELAY .0001 // in seconds
#define UPDATE_INTERVAL 0.005
// GLint TIMER_DELAY = CALLBACK_DELAY * 1000; // in milleseconds
GLint TIMER_DELAY = 5; // in milleseconds

void Reshape(int w, int h) {
    glViewport (0, 0, w, h);                    // update the viewport
    glMatrixMode(GL_PROJECTION);                // update projection
    glLoadIdentity();
    gluOrtho2D(0.0, 320, 0.0, 240);             // map unit square to viewport
    glMatrixMode(GL_MODELVIEW);
}

void Display (void) {                          // display callback
    DrawEverything ();
    glFlush();
}

void PassiveMouseV2 (int x, int y) {             // updates upon mouse movement when there are mouse clicks/inputs
    if (LCD.touchState) {
        LCD.touchX = x/ZOOM_SCALE;
        LCD.touchY = y/ZOOM_SCALE;
    }
}

void Mouse (int buttonState, int clickState, int x, int y) {      // mouse click callback ... only updates upon mouse click
    if (clickState == GLUT_DOWN && buttonState == GLUT_LEFT_BUTTON) { // was (button == GLUT_LEFT_BUTTON)
        LCD.touchState = true;
        LCD.touchX = x/ZOOM_SCALE; // re-enable these statements if you delete the passive mouse function
        LCD.touchY = y/ZOOM_SCALE;
        // cout << "Touch Y: " << LCD.touchY;
    } if ((buttonState == GLUT_LEFT_BUTTON ) && (clickState == GLUT_UP)) {
        LCD.touchState = false;
        LCD.touchX = -1;
        LCD.touchY = -1;
    }
}

// keyboard callback
void Keyboard (unsigned char c, int x, int y) {
    switch (c) {                                // c is the key that is hit
        case 'a':
            leftKeyInp = true;
            break;
        case 'w':
            upKeyInp = true;
            break;
        case 'd':
            rightKeyInp = true;
            break;
        case 's':
            downKeyInp = true;
            break;
        case 27:                               // 'q' means quit
            exit (0);
            break;
        default:
            break;
    }
}

void KeyboardUp (unsigned char c, int x, int y) {
    switch (c) {                                // c is the key that is hit
        case 'a':
            leftKeyInp = false;
            break;
        case 'w':
            upKeyInp = false;
            break;
        case 'd':
            rightKeyInp = false;
            break;
        case 's':
            downKeyInp = false;
            break;
        default:
            break;
    }
}

void Timer (int id) {
    mainLoop ();

    glutTimerFunc(TIMER_DELAY, Timer, 0);
}

int main (int argc, char** argv) {

    glutInit(&argc, argv);                      // OpenGL initializations
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);// double buffering and RGB // was GLUT_DOUBLE
    glutInitWindowSize(320*ZOOM_SCALE, 240*ZOOM_SCALE);               // create a 400x400 window
    glutInitWindowPosition(0, 0);               // ...in the upper left
    glutCreateWindow("Game");                  // create the window

    glutDisplayFunc(Display);                 // setup callbacks
    glutReshapeFunc(Reshape);
    glutMotionFunc(PassiveMouseV2);
    glutMouseFunc(Mouse);
    glutKeyboardFunc(Keyboard);
    glutKeyboardUpFunc(KeyboardUp);
    glutTimerFunc(TIMER_DELAY, Timer, 0);

    Init ();

    glutMainLoop ();                             // start it running

    return 0;                                   // ANSI C expects this
}






#endif
#if !IS_SIMULATION // if this is not the simulation, then this chunck of code is used. Otherwise, this code is ignored.
/*



 NON-simulation only stuff



 */







// include statements

// #include <FEHLCD.h> // this statement lives in Classes.hpp
// #include <FEHUtility.h> // this statement lives in Classes.hpp
#include "stdio.h"
// #include <vector> // if this doesn't work, I'm just gonna make a giant ass array


// priority function declarations
void Init ();
void mainLoop ();
void glutPostRedisplay (); // for simulation compatibility only; this function is never used in non-simulation version

// code control variables
float timeSinceLastCodeCall; // amount of time alotted since the mainLoop code was last called
#define TIMER_DELAY 0.00 // delay before the mainLoop is called; 0 means that the mainloop code is called as soon as it is able to
#define UPDATE_INTERVAL 0.5

// Don't add anything to this main method. If you do, it will mess up the simulation code's behavior.
// Only add stuff to the initialization method (Init) and the main looping method (mainLoop).
// It shouldn't be necessary to add to the main method itself.
int main (void) {
    // call the initilization method (is the first thing that gets called; only gets called once and is used for the purpose of initializing variables)
    Init ();

    while (true) {
        // call the mainLoop code only after a fixed time interval has passed; this is done to better mimic the similution code behavior
        if (TimeNow () - timeSinceLastCodeCall > TIMER_DELAY) {
            timeSinceLastCodeCall = TimeNow ();

            mainLoop ();
        }
    }

    return 0;
}






#endif
/*



 SHARED simulation & non-simulation stuff



 */






/************************************************/
/* Name: MC3                Date: 11/27/18      */
/* Instructor: RJF           10:20              */
/************************************************/

#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <string.h>
using namespace std;



/************************************************************************************************ DECLERATIONS ************************************************************************************************/


/************************************************************************ PRIORITY DECLERATIONS ************************************************************************/


void DrawPixel (Vector2 point);
void DrawBox (Box box);
void DrawBoxBorder (Box box);
void DrawEdge (Edge edge);
void DrawCircle (Circle circle);
void Screenshot ();
#define COOL_RED 0xFD6666
#define COOL_GREEN 0x66FF66
#define COOL_BLUE 0x66CCFF



/************************************************************************ CLASS DECLERATIONS ************************************************************************/


class Life {
public:
    Life () {
        srand (TimeForRand ()); // illegal!
        // initialize the biome
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                biome [i][j] = 0;
            }
        }
    }
    static const int WIDTH = 80; // 80
    static const int HEIGHT = 60; // 60
    int biome [HEIGHT][WIDTH];
    
    static const int CELL_PIXEL_WIDTH = 4; // 4
    static const int CELL_PIXEL_HEIGHT = 4; // 4
    static const int RANDOM_FACTOR = 99999999;
    
    void Seed () {
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                // biome [i][j] = rand () % 2;
                if (rand () % RANDOM_FACTOR == 0) {
                    biome [i][j] = 1;
                }
            }
        }
    }
    void Draw () {
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                if (biome [i][j] == 1) {
                    Vector2 point = Vector2 (j * CELL_PIXEL_WIDTH, -i * CELL_PIXEL_HEIGHT);
                    // DrawPixel (point);
                    DrawBox (Box (point, CELL_PIXEL_WIDTH, CELL_PIXEL_HEIGHT));
                }
            }
        }
    }
    void BirthCell (IntVector2 point) {
        point = IntVector2 (point.x / CELL_PIXEL_WIDTH, -point.y / CELL_PIXEL_HEIGHT);
        IntVector2 newPoint = IntVector2 (0, 0);
        if (point.x < WIDTH   &&  point.x >= 0) {
            newPoint.x = point.x;
            if (point.y < HEIGHT  &&  point.y >= 0) {
                newPoint.y = point.y;
                biome [newPoint.y][newPoint.x] = 1;
            }
        }
    }
    void KillCell (IntVector2 point) {
        point = IntVector2 (point.x / CELL_PIXEL_WIDTH, -point.y / CELL_PIXEL_HEIGHT);
        IntVector2 newPoint = IntVector2 (0, 0);
        if (point.x < WIDTH   &&  point.x >= 0) {
            newPoint.x = point.x;
            if (point.y < HEIGHT  &&  point.y >= 0) {
                newPoint.y = point.y;
                biome [newPoint.y][newPoint.x] = 0;
            }
        }
    }
    void CoolDraw () {
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                if (biome [i][j] == 1) {
                    IntVector2 point = IntVector2 (j, i);
                    int neighborCount = getNeighborCount (point);
                    
                    switch (neighborCount) {
                        case 0:
                            LCD.SetFontColor (INDIGO);
                            break;
                        case 1:
                            LCD.SetFontColor (BLUE);
                            break;
                        case 2:
                            LCD.SetFontColor (GREEN);
                            break;
                        case 3:
                            LCD.SetFontColor (GOLD);
                            break;
                        case 4:
                            LCD.SetFontColor (LIGHTCORAL);
                            break;
                        case 5:
                            LCD.SetFontColor (RED);
                            break;
                        case 6:
                            LCD.SetFontColor (ORCHID);
                            break;
                        case 7:
                            LCD.SetFontColor (WHITE);
                            break;
                        case 8:
                            LCD.SetFontColor (WHITE);
                            break;
                        default:
                            LCD.SetFontColor (LIGHTGRAY);
                            break;
                    }
                    /*
                    switch (neighborCount) {
                        case 0:
                            LCD.SetFontColor (INDIGO);
                            break;
                        case 1:
                            LCD.SetFontColor (BLUE);
                            break;
                        case 2:
                            LCD.SetFontColor (GREEN);
                            break;
                        case 3:
                            LCD.SetFontColor (GOLD);
                            break;
                        case 4:
                            LCD.SetFontColor (ORANGE);
                            break;
                        case 5:
                            LCD.SetFontColor (RED);
                            break;
                        case 6:
                            LCD.SetFontColor (HOTPINK);
                            break;
                        case 7:
                            LCD.SetFontColor (WHITE);
                            break;
                        case 8:
                            LCD.SetFontColor (WHITE);
                            break;
                        default:
                            LCD.SetFontColor (LIGHTGRAY);
                            break;
                    }
                    */
                    /*
                    switch (neighborCount) {
                        case 0:
                            LCD.SetFontColor (LAVENDER);
                            break;
                        case 1:
                            LCD.SetFontColor (LIGHTBLUE);
                            break;
                        case 2:
                            LCD.SetFontColor (LIGHTGREEN);
                            break;
                        case 3:
                            LCD.SetFontColor (LIGHTGOLDENRODYELLOW);
                            break;
                        case 4:
                            LCD.SetFontColor (ORANGE); // LIGHTCORAL // orchid
                            break;
                        case 5:
                            LCD.SetFontColor (INDIANRED);
                            break;
                        case 6:
                            LCD.SetFontColor (PINK);
                            break;
                        case 7:
                            LCD.SetFontColor (WHITE);
                            break;
                        case 8:
                            LCD.SetFontColor (WHITE);
                            break;
                        default:
                            LCD.SetFontColor (LIGHTGRAY);
                            break;
                    }
                    */
                    /*
                    switch (neighborCount) {
                        case 0:
                            LCD.SetFontColor (INDIGO);
                            break;
                        case 1:
                            LCD.SetFontColor (BLUE);
                            break;
                        case 2:
                            LCD.SetFontColor (BLUE);
                            break;
                        case 3:
                            LCD.SetFontColor (GREEN);
                            break;
                        case 4:
                            LCD.SetFontColor (GREEN);
                            break;
                        case 5:
                            LCD.SetFontColor (INDIGO);
                            break;
                        case 6:
                            LCD.SetFontColor (INDIGO);
                            break;
                        case 7:
                            LCD.SetFontColor (LIGHTCORAL);
                            break;
                        case 8:
                            LCD.SetFontColor (WHITE);
                            break;
                        default:
                            LCD.SetFontColor (LIGHTGRAY);
                            break;
                    }
                    */
                     
                    Vector2 pos = Vector2 (j * CELL_PIXEL_WIDTH, -i * CELL_PIXEL_HEIGHT);
                    DrawBox (Box (pos, CELL_PIXEL_WIDTH, CELL_PIXEL_HEIGHT));
                }
            }
        }
    }
    void PrettyCoolDraw () {
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                if (biome [i][j] == 1) {
                    IntVector2 point = IntVector2 (j, i);
                    int neighborCount = getNeighborCount (point);
                    
                    switch (neighborCount) {
                        case 0:
                            LCD.SetFontColor (COOL_BLUE);
                            break;
                        case 1:
                            LCD.SetFontColor (COOL_BLUE);
                            break;
                        case 2:
                            LCD.SetFontColor (COOL_BLUE);
                            break;
                        case 3:
                            LCD.SetFontColor (COOL_GREEN);
                            break;
                        case 4:
                            LCD.SetFontColor (COOL_GREEN);
                            break;
                        case 5:
                            LCD.SetFontColor (COOL_RED);
                            break;
                        case 6:
                            LCD.SetFontColor (COOL_RED);
                            break;
                        case 7:
                            LCD.SetFontColor (COOL_RED);
                            break;
                        case 8:
                            LCD.SetFontColor (COOL_RED);
                            break;
                        default:
                            LCD.SetFontColor (WHITE);
                            break;
                    }
                    Vector2 pos = Vector2 (j * CELL_PIXEL_WIDTH, -i * CELL_PIXEL_HEIGHT);
                    DrawBox (Box (pos, CELL_PIXEL_WIDTH, CELL_PIXEL_HEIGHT));
                }
            }
        }
    }
    void Next () {
        // make next biome equal to biome
        int fact = 1;
        int nextBiome [HEIGHT][WIDTH];
        for (int i = 0; i < HEIGHT; i++) { // fight me
            for (int j = 0; j < WIDTH; j++) {
                nextBiome [i][j] = 0;
            }
        }
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                IntVector2 point = IntVector2 (j, i);
                int neighborCount = getNeighborCount (point);
                if (biome [i][j] == 1) {
                    if (neighborCount < 2 * fact || neighborCount > 3 * fact) {
                        nextBiome [i][j] = 0;
                    } else {
                        nextBiome [i][j] = 1;
                    }
                } else if (biome [i][j] == 0) {
                    if (neighborCount == 3 * fact) {
                        nextBiome [i][j] = 1;
                    }
                }
            }
        }
        // make biome equal to next biome
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                biome [i][j] = nextBiome [i][j];
            }
        }
    }
    int getNeighborCount (IntVector2 pos) {
        int radius = 1;
        int neighborCount = 0;
        for (int i = -radius; i <= radius; i++) {
            for (int j = -radius; j <= radius; j++) {
                if (!(i == 0 && j == 0)) {
                    IntVector2 disp = IntVector2 (0, 0); // displacement for wrapping over
                    if (i + pos.y < 0) {
                        disp.y = HEIGHT;
                    } else if (i + pos.y >= HEIGHT) {
                        disp.y = -HEIGHT;
                    }
                    if (j + pos.x < 0) {
                        disp.x = WIDTH;
                    } else if (j + pos.x >= WIDTH) {
                        disp.x = -WIDTH;
                    }
                    if (biome [pos.y + i + disp.y][pos.x + j + disp.x] == 1) {
                        neighborCount++;
                    }
                }
            }
        }
        return neighborCount;
    }
private:
};



/************************ MISCELLANEOUS VARIABLES ************************/

Vector2 touch = Vector2 ();
bool touchState = false;
float timeSinceLastFrameUpdate;
float timeWhenLifeUpdated;
#define LIFE_UPDATE_RATE 0.05

Vectors Vector;
Life life;


/************************ MISCELLANEOUS VARIABLES ************************/

bool eraseMode;
bool isGoing;


/************************ GUI VARIABLES ************************/

// sample variables for button declaration
#define BUTT_WIDTH 100
#define BUTT_HEIGHT 30
#define BUTT_Y_POS 205 // 195
#define BUTT_X_POS 160 // 205
#define BUTT_X_MARGIN 15
#define BUTT_Y_MARGIN 10
Button actionButt0;
Button actionButt1;
Button actionButt2;
Button actionButt3;


/************************ Just some sample colors ************************/

#define ABYSS                   0x1a1a1a
#define BACKGROUNDCOLOR         0x1a1a1a     // 0x6495ed //- 0xCDDDF9 // 0x444243 // 0xAB7D5C // 0xFDF2E9
#define WALLCOLOR               0x1a1a1a     // 0x2f4f4f
#define WALLWALLCOLOR           0x8a715c     // 0x708090 // 0x418E88 // 0x9b704b // 0x8a715c
#define SHADOWCOLOR             0x000000
#define SHADOW_ALPHA            0.5          // between 0 and 1




/************************************************************************************************ MAIN FUNCTION ************************************************************************************************/


// do all the stuff that comes before the mainLoop
void Init () {
    // initialize some constants (that are only used in the initialization method)
    const double sqrt3 = pow (3.0, 0.5);
    eraseMode = false;
    isGoing = false;
    // int rightButtMargin = 15; // y-pos: -15, -60, -105, -150, -195

    // initialize buttons
    char charPtr [100];
    strcpy (charPtr, "++"); // use charPtr to set the text of the button
    actionButt0 = Button (  Box ( Vector2 (BUTT_X_POS, -BUTT_Y_POS - BUTT_HEIGHT*0 - BUTT_Y_MARGIN*0), 45, BUTT_HEIGHT ), charPtr, 0  ); // -150
    strcpy (charPtr, "GO");
    actionButt1 = Button (  Box ( Vector2 (BUTT_X_POS + 55, -BUTT_Y_POS - BUTT_HEIGHT*0 - BUTT_Y_MARGIN*0), 45, BUTT_HEIGHT ), charPtr, 0  );
    strcpy (charPtr, "X");
    actionButt2 = Button (  Box ( Vector2 (BUTT_X_POS + 55*2, -BUTT_Y_POS - BUTT_HEIGHT*0 - BUTT_Y_MARGIN*0), 45, BUTT_HEIGHT ), charPtr, 0  );

    // create life
    life = Life ();
    life.Seed ();
    
    timeWhenLifeUpdated = TimeNow ();
    timeSinceLastFrameUpdate = TimeNow (); // initialize the time since the last screen/frame update
}


// draws everything; all drawing functions should go here
// It's important to put all LCD functions here. It's critical for the simulation to work properly and
// is good coding practice for graphical computing, especially when you have limited computing capactity
// like you do on the Proteus.
void DrawEverything () {
    LCD.Clear (BACKGROUNDCOLOR); // clear the screen (for animation purposes)
    
    // sample button drawing function implementation
    actionButt0.DrawButton();
    actionButt1.DrawButton();
    actionButt2.DrawButton();
    
    LCD.SetFontColor (LIGHTGREEN);
    // life.Draw ();
    life.PrettyCoolDraw ();
}


// do all of the stuff for the main game loop that gets repeated
void mainLoop () {
    touchState = LCD.Touch (&touch.x, &touch.y); // get the user's touch input coordinates, and store whether or not the user is touching the screen in the variable touchState
    touch = Vector2 (touch.x, -touch.y); // standardize the touch coordinates so they're effectively in the fourth quadrant

    if (touchState) {
        if (eraseMode) {
            life.KillCell (IntVector2 (touch.x, touch.y));
        } else {
            life.BirthCell (IntVector2 (touch.x, touch.y));
        }
    }
    if (isGoing) {
        if (TimeNow () - timeWhenLifeUpdated > LIFE_UPDATE_RATE) {
            life.Next ();
            Screenshot ();
            
            
            timeWhenLifeUpdated = TimeNow ();
        }
    }
    
    if (actionButt0.WasPressed (touch, touchState)) { // checks if the button was pressed and updates the state of the button
        life.Next ();
        // Screenshot ();
    }
    if (actionButt1.WasPressed (touch, touchState)) { // checks if the button was pressed and updates the state of the button
        isGoing = !isGoing;
    }
    if (actionButt2.WasPressed (touch, touchState)) { // checks if the button was pressed and updates the state of the button
        eraseMode = !eraseMode;
    }

    // update the LCD screen only after a fixed time interval has passed
    if (TimeNow () - timeSinceLastFrameUpdate > UPDATE_INTERVAL) { // I've heard TimeNow is bad, so the game may break after a certain amount of time has passed
        timeSinceLastFrameUpdate = TimeNow ();
        
        if (IS_SIMULATION) {
            // basically just calls the DrawEverything function, which draws everything and updates the screen
            glutPostRedisplay (); // SIMULATION code chunk
        } else {
            DrawEverything (); // NON-simulation code chunk
        }
    }

}

void Screenshot () {
    string directory = "/Users/wellsfletcher/Documents/OtherCode/Xcode/Life/Life/Screenshots/";
    // string directory = "/Users/wellsfletcher/Desktop/Sc/";
    
    char buff [100];
    float currentTime = TimeNow ();
    int timeStamp = currentTime * 1000;
    snprintf (buff, sizeof (buff), "%08d", timeStamp);
    string currentTimeString = buff;
    
    cout << currentTimeString << endl;
    string fileName = "sc-" + currentTimeString + ".png";
    
    string path = directory + fileName;
    bool screenshotSuccessful = LCD.TakeCroppedScreenshot (path);
}


// draws a box with the given box object
void DrawPixel (Vector2 point) {
    LCD.DrawPixel ( (int)(point.x), -(int)(point.y));
}
// draws a box with the given box object
void DrawBox (Box box) {
    LCD.FillRectangle ( (int)(box.points[0].x), -(int)(box.points[0].y), box.width, box.height);
}
// draws a box's border with the given box object
void DrawBoxBorder (Box box) {
    LCD.DrawRectangle ( (int)(box.points[0].x), -(int)(box.points[0].y), box.width, box.height);
}

// draws given edge
void DrawEdge (Edge edge) {
    LCD.DrawLine (  (int)(edge.points[0].x), -(int)(edge.points[0].y), (int)(edge.points[1].x), -(int)(edge.points[1].y)  );
}

// draws given cricle
void DrawCircle (Circle circle) {
    LCD.FillCircle (  (int)(circle.points[0].x), -(int)(circle.points[0].y), circle.radius  );
}

// draws given cricle
void DrawPolygon (Polygon poly) {
    for (int k = 0; k < poly.length-1; k++) {
        LCD.DrawLine (  (int)(poly.points[k].x), -(int)(poly.points[k].y), (int)(poly.points[k+1].x), -(int)(poly.points[k+1].y)  );
    }
    LCD.DrawLine (  (int)(poly.points[poly.length].x), -(int)(poly.points[poly.length].y), (int)(poly.points[0].x), -(int)(poly.points[0].y)  );
}

