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

#include <stdlib.h> 
#include <stdio.h> 

#include <cstdlib>                      // standard definitions
#include <iostream>                     // C++ I/O
#include <cstdio>                       // C I/O (for sprintf)
#include <cmath>                        // standard definitions
// #include <cv.h>                         // terminal



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
    glFlush ();
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



/************************************************************************ CLASS DECLERATIONS ************************************************************************/


class Board {
public:
    Board () {
        srand (TimeForRand ()); // illegal!
        // initialize the board
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                board [i][j] = 0;
            }
        }
    }
    static const int WIDTH = 4; // 80
    static const int HEIGHT = 4; // 60
    int board [HEIGHT][WIDTH];
    
    static const int CELL_PIXEL_WIDTH = 25; // 4 // 25
    static const int CELL_PIXEL_HEIGHT = 25; // 4 // 30 // 25
    static const int RANDOM_FACTOR = -1;
    
    int dominoID = 1;
    
    void Seed () {
        if (RANDOM_FACTOR > 0) {
            for (int i = 0; i < HEIGHT; i++) {
                for (int j = 0; j < WIDTH; j++) {
                    // board [i][j] = rand () % 2;
                    if (rand () % RANDOM_FACTOR == 0) {
                        board [i][j] = 1;
                    }
                }
            }
        }
        board [0][0] = -1;
        board [HEIGHT-1][WIDTH-1] = -1;
    }
    void Draw () {
        // draw grid pattern
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                if (board [j][i] >= 0) {
                    if ((i+j) % 2 == 0) {
                        LCD.SetFontColor (GRAY);
                    } else {
                        int DARKDARKGRAY = 0x333333;
                        LCD.SetFontColor (DARKDARKGRAY);
                    }
                    Vector2 point = Vector2 (j * CELL_PIXEL_WIDTH, -i * CELL_PIXEL_HEIGHT);
                    DrawBox (Box (point, CELL_PIXEL_WIDTH, CELL_PIXEL_HEIGHT));
                }
            }
        }
        float DOMINO_PERCENT_TILE_SIZE = 0.8;
        float SHRINK_NUM = 1 - DOMINO_PERCENT_TILE_SIZE;
        // draw dominos
        LCD.SetFontColor (LIGHTGREEN);
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                if (board [i][j] >= 1) { // board [i][j] == 1
                    int currentDominoID = board [i][j];
                    int dominoColor = getColorFromID (currentDominoID);
                    LCD.SetFontColor (dominoColor);
                    
                    Vector2 point = Vector2 (j * CELL_PIXEL_WIDTH + SHRINK_NUM * CELL_PIXEL_WIDTH, -i * CELL_PIXEL_HEIGHT - SHRINK_NUM * CELL_PIXEL_HEIGHT);
                    // draw main bit of domino
                    DrawBox (Box (point, CELL_PIXEL_WIDTH - 2 * SHRINK_NUM * CELL_PIXEL_WIDTH, CELL_PIXEL_HEIGHT - 2 * SHRINK_NUM * CELL_PIXEL_HEIGHT));
                    
                    // draw center bit of domino
                    if (currentDominoID > 0) {
                        int adjacentDominoID;
                        IntVector2 testPos;
                        IntVector2 dir;
                        
                        dir = IntVector2 (0, 1);
                        testPos = IntVector2 (j + dir.x, i + dir.y);
                        if (IsValidTile (testPos)) {
                            adjacentDominoID = board [testPos.y][testPos.x];
                            if (currentDominoID == adjacentDominoID) {
                                Vector2 midpoint = Vector2 (point.x + 0.5 * dir.x * CELL_PIXEL_WIDTH, point.y - 0.5 * dir.y * CELL_PIXEL_HEIGHT);
                                DrawBox (Box (midpoint, CELL_PIXEL_WIDTH - 2 * SHRINK_NUM * CELL_PIXEL_WIDTH, CELL_PIXEL_HEIGHT - 2 * SHRINK_NUM * CELL_PIXEL_HEIGHT));
                            }
                        }
                        
                        dir = IntVector2 (0, -1);
                        testPos = IntVector2 (j + dir.x, i + dir.y);
                        if (IsValidTile (testPos)) {
                            adjacentDominoID = board [testPos.y][testPos.x];
                            if (currentDominoID == adjacentDominoID) {
                                Vector2 midpoint = Vector2 (point.x + 0.5 * dir.x * CELL_PIXEL_WIDTH, point.y - 0.5 * dir.y * CELL_PIXEL_HEIGHT);
                                DrawBox (Box (midpoint, CELL_PIXEL_WIDTH - 2 * SHRINK_NUM * CELL_PIXEL_WIDTH, CELL_PIXEL_HEIGHT - 2 * SHRINK_NUM * CELL_PIXEL_HEIGHT));
                            }
                        }
                        
                        dir = IntVector2 (1, 0);
                        testPos = IntVector2 (j + dir.x, i + dir.y);
                        if (IsValidTile (testPos)) {
                            adjacentDominoID = board [testPos.y][testPos.x];
                            if (currentDominoID == adjacentDominoID) {
                                Vector2 midpoint = Vector2 (point.x + 0.5 * dir.x * CELL_PIXEL_WIDTH, point.y - 0.5 * dir.y * CELL_PIXEL_HEIGHT);
                                DrawBox (Box (midpoint, CELL_PIXEL_WIDTH - 2 * SHRINK_NUM * CELL_PIXEL_WIDTH, CELL_PIXEL_HEIGHT - 2 * SHRINK_NUM * CELL_PIXEL_HEIGHT));
                            }
                        }
                        
                        dir = IntVector2 (-1, 0);
                        testPos = IntVector2 (j + dir.x, i + dir.y);
                        if (IsValidTile (testPos)) {
                            adjacentDominoID = board [testPos.y][testPos.x];
                            if (currentDominoID == adjacentDominoID) {
                                Vector2 midpoint = Vector2 (point.x + 0.5 * dir.x * CELL_PIXEL_WIDTH, point.y - 0.5 * dir.y * CELL_PIXEL_HEIGHT);
                                DrawBox (Box (midpoint, CELL_PIXEL_WIDTH - 2 * SHRINK_NUM * CELL_PIXEL_WIDTH, CELL_PIXEL_HEIGHT - 2 * SHRINK_NUM * CELL_PIXEL_HEIGHT));
                            }
                        }
                    }
                }
            }
        }
    }
    int getColorFromID (int ID) {
        int color = DARKGRAY;
        int colorRange = 3;
        int colorID = ID % colorRange;
        
        switch (colorID) {
            case 0:
                color = INDIANRED;
                break;
            case 1:
                color = LIGHTGREEN;
                break;
            case 2:
                color = LIGHTSKYBLUE;
                break;
            case 3:
                color = ORCHID;
                break;
            case 4:
                color = LIGHTPINK;
                break;
            case 5:
                color = YELLOW;
                break;
            case 6:
                color = ORANGE;
                break;
                
            default:
                break;
        }
        /*
        switch (colorID) {
            case 0:
                color = RED;
                break;
            case 1:
                color = GREEN;
                break;
            case 2:
                color = BLUE;
                break;
            case 3:
                color = VIOLET;
                break;
            case 4:
                color = INDIGO;
                break;
            case 5:
                color = YELLOW;
                break;
            case 6:
                color = ORANGE;
                break;
                
            default:
                break;
        }
        */
        return color;
    }
    void BirthCell (IntVector2 point) {
        point = IntVector2 (point.x / CELL_PIXEL_WIDTH, -point.y / CELL_PIXEL_HEIGHT);
        /*
        IntVector2 newPoint = IntVector2 (0, 0);
        if (point.x < WIDTH   &&  point.x >= 0) {
            newPoint.x = point.x;
            if (point.y < HEIGHT  &&  point.y >= 0) {
                newPoint.y = point.y;
                // IntVector2 dir = IntVector2 (0, 0);
                board [newPoint.y][newPoint.x] = 1;
            }
        }
        */
        IntVector2 dir;
        
        dir = IntVector2 (0, 1);
        TestAndAddDomino (point, dir);
        dir = IntVector2 (1, 0);
        TestAndAddDomino (point, dir);
        dir = IntVector2 (0, -1);
        TestAndAddDomino (point, dir);
        dir = IntVector2 (-1, 0);
        TestAndAddDomino (point, dir);
    }
    void KillCell (IntVector2 point) {
        point = IntVector2 (point.x / CELL_PIXEL_WIDTH, -point.y / CELL_PIXEL_HEIGHT);
        IntVector2 newPoint = IntVector2 (0, 0);
        if (point.x < WIDTH   &&  point.x >= 0) {
            newPoint.x = point.x;
            if (point.y < HEIGHT  &&  point.y >= 0) {
                newPoint.y = point.y;
                board [newPoint.y][newPoint.x] = 0;
            }
        }
    }
    // returns whether the domino was able to be added at the specified position
    bool TestAndAddDomino (IntVector2 pos, IntVector2 dir) {
        bool result = false;
        if (TestDomino (pos, dir) == 1) {
            result = true;
        }
        if (result) {
            AddDomino (pos, dir);
        }
        return result;
    }
    // forcibly adds a domino to the board
    void AddDomino (IntVector2 pos, IntVector2 dir) {
        IntVector2 otherPos = IntVector2 (pos.x + dir.x, pos.y + dir.y);
        board [pos.y][pos.x] = dominoID;
        board [otherPos.y][otherPos.x] = dominoID;
        dominoID ++;
    }
    // forcibly removes a domino from the board
    void RemoveDomino (IntVector2 pos, IntVector2 dir) {
        IntVector2 otherPos = IntVector2 (pos.x + dir.x, pos.y + dir.y);
        board [pos.y][pos.x] = 0;
        board [otherPos.y][otherPos.x] = 0;
    }
    bool TestIfBoardIsSolved () {
        bool result = true;
        for (int i = 0; result && i < HEIGHT; i++) {
            for (int j = 0; result && j < WIDTH; j++) {
                if (board [j][i] == 0) {
                    result = false;
                }
            }
        }
        return result;
    }
    bool solved = false;
    IntVector2 getNextUnoccupiedTile (IntVector2 pos) {
        do {
            if (pos.x + 1 < WIDTH) {
                pos = IntVector2 (pos.x + 1, pos.y);
            } else {
                pos = IntVector2 (0, pos.y + 1);
            }
        } while (pos.y < HEIGHT && board [pos.y][pos.x] > 0); // HEIGHT may be redundant
        
        if (pos.y >= HEIGHT || board [pos.y][pos.x] == -1) {
            pos = IntVector2 (-1, -1);
        }
        
        return pos;
    }
    float timeWhenUpdated = 0;
    bool SolveRestOfBoardAfterPlacingDomino (IntVector2 start, IntVector2 dir) {
        bool result = false;
    
        
        while (TimeNow () - timeWhenUpdated < UPDATE_INTERVAL * 100);
        timeWhenUpdated = TimeNow ();
        Display ();
        
        // (temporary) take screenshot
        string fileName = "sc-" + to_string (timeWhenUpdated) + ".png";
        // string directory = "/Users/wellsfletcher/Documents/OtherCode/Xcode/CheckerboardProblem/CheckerboardProblem/Screenshots/";
        string directory = "/Users/wellsfletcher/Desktop/Sc/";
        string path = directory + fileName;
        bool screenshotSuccessful = TakeScreenshot (path);
  
        // cout << screenshotSuccessful << endl;
        
        // test other ones going onwards
        IntVector2 nextPos = getNextUnoccupiedTile (start);
        // if there are no more unoccupied tiles
        if (nextPos.x == -1) {
            // then test if the board is completed
            if (TestIfBoardIsSolved ()) {
                // and 'return' the result
                result = true;
                cout << "s o l v e d" << endl;
            }
        } else {
            result = Solve (nextPos, dir);
            if (!result) {
                // reset tile (to eventually reset the board)
                RemoveDomino (start, dir);
            }
        }
        
        return result;
    }
    bool Solve (IntVector2 start, IntVector2 dir) {
        bool result = false;
        // add domino starting at position and direction
        // test all possibilities onwards
        // same for other directions
        // if no success, then return false
        if (TestAndAddDomino (start, dir)) {
            result = SolveRestOfBoardAfterPlacingDomino (start, dir);
        }
        if (!result && TestAndAddDomino (start, dir.rotateLeftAndReturnSelf ())) { // (note these statements are identical)
            result = SolveRestOfBoardAfterPlacingDomino (start, dir);
        }
        if (!result && TestAndAddDomino (start, dir.rotateLeftAndReturnSelf ())) {
            result = SolveRestOfBoardAfterPlacingDomino (start, dir);
        }
        if (!result && TestAndAddDomino (start, dir.rotateLeftAndReturnSelf ())) {
            result = SolveRestOfBoardAfterPlacingDomino (start, dir);
        }
        return result;
    }
    
    bool Next () {
        bool result = false;
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                board [i][j] = 0;
            }
        }
        return result;
    }
    // returns whether the domino is in a valid location,
    // where 1 is a valid, 0 is invalid direction, and -1 is invalid position
    int TestDomino (IntVector2 pos, IntVector2 dir) {
        int result = 0;
        if (IsValidUnoccupiedTile (pos)) {
            IntVector2 otherPos = IntVector2 (pos.x + dir.x, pos.y + dir.y);
            if (IsValidUnoccupiedTile (otherPos)) {
                result = 1;
            }
        } else {
            result = -1;
        }
        return result;
    }
    // returns whether the tile within the bounds of the board and unoccupied by another domino
    bool IsValidUnoccupiedTile (IntVector2 pos) {
        bool result = false;
        if (IsValidTile (pos) && board [pos.y][pos.x] == 0) {
            result = true;
        }
        return result;
    }
    // returns whether the tile at the specified position exists (is within the bounds of the board)
    bool IsValidTile (IntVector2 point) {
        bool result = false;
        if (point.x < WIDTH   &&  point.x >= 0) {
            if (point.y < HEIGHT  &&  point.y >= 0) {
                result = true;
            }
        }
        return result;
    }
    
    // takes screenshot of screen
    bool TakeScreenshot (string filename) {
        // string command = "screencapture -R 78,46,320,240 " + filename;
        int xOrigin = 78 / 2;
        int yOrigin = 46 / 2;
        int width = 320 * 3;
        int height = 240 * 3 + 22;
        
        string command = "screencapture -R " + to_string (xOrigin) + "," + to_string (yOrigin) + "," + to_string (width) + "," + to_string (height) + " " + filename;
        char const *dumbCommand = command.data ();
        system (dumbCommand);
        return true;
    }
    /*
    // takes screenshot of screen
    bool TakeScreenshot (string filename, int w, int h) {
        
        //This prevents the images getting padded 
        // when the width multiplied by 3 is not a multiple of 4
        glPixelStorei(GL_PACK_ALIGNMENT, 1);
        
        int nSize = w*h*3;
        // First let's create our buffer, 3 channels per Pixel
        char* dataBuffer = (char*)malloc(nSize*sizeof(char));
        
        if (!dataBuffer) return false;
        
        // Let's fetch them from the backbuffer    
        // We request the pixels in GL_BGR format, thanks to Berzeger for the tip
        glReadPixels((GLint)0, (GLint)0,
                     (GLint)w, (GLint)h,
                     GL_BGR, GL_UNSIGNED_BYTE, dataBuffer);
        
        //Now the file creation
        FILE *filePtr = fopen(filename.c_str(), "wb");
        if (!filePtr) return false;
        
        
        unsigned char TGAheader[12]={0,0,2,0,0,0,0,0,0,0,0,0};
        unsigned char header[6] = { static_cast<unsigned char>(w%256),static_cast<unsigned char>(w/256),
            static_cast<unsigned char>(h%256),static_cast<unsigned char>(h/256),
            24,0};
        // We write the headers
        fwrite(TGAheader,    sizeof(unsigned char),    12,    filePtr);
        fwrite(header,    sizeof(unsigned char),    6,    filePtr);
        // And finally our image data
        fwrite(dataBuffer,    sizeof(GLubyte),    nSize,    filePtr);
        fclose(filePtr);
        
        free(dataBuffer);
        return true;
    }
    */
private:
};



/************************ MISCELLANEOUS VARIABLES ************************/

Vector2 touch = Vector2 ();
bool touchState = false;
float timeSinceLastFrameUpdate;
float timeWhenBoardUpdated;
#define BOARD_UPDATE_RATE 0.05
bool boardIsSolved = false;

Vectors Vector;
Board board;


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

    // initialize buttons
    char charPtr [100];
    strcpy (charPtr, "++"); // use charPtr to set the text of the button
    actionButt0 = Button (  Box ( Vector2 (BUTT_X_POS, -BUTT_Y_POS - BUTT_HEIGHT*0 - BUTT_Y_MARGIN*0), 45, BUTT_HEIGHT ), charPtr, 0  ); // -150
    strcpy (charPtr, "GO");
    actionButt1 = Button (  Box ( Vector2 (BUTT_X_POS + 55, -BUTT_Y_POS - BUTT_HEIGHT*0 - BUTT_Y_MARGIN*0), 45, BUTT_HEIGHT ), charPtr, 0  );
    strcpy (charPtr, "X");
    actionButt2 = Button (  Box ( Vector2 (BUTT_X_POS + 55*2, -BUTT_Y_POS - BUTT_HEIGHT*0 - BUTT_Y_MARGIN*0), 45, BUTT_HEIGHT ), charPtr, 0  );

    // create board
    board = Board ();
    board.Seed ();
    
    timeWhenBoardUpdated = TimeNow ();
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
    
    // LCD.SetFontColor (LIGHTGREEN);
    board.Draw ();
}


// do all of the stuff for the main game loop that gets repeated
void mainLoop () {
    touchState = LCD.Touch (&touch.x, &touch.y); // get the user's touch input coordinates, and store whether or not the user is touching the screen in the variable touchState
    touch = Vector2 (touch.x, -touch.y); // standardize the touch coordinates so they're effectively in the fourth quadrant

    // add dominos to the board if the user clicks the screen
    if (touchState) {
        if (eraseMode) {
            board.KillCell (IntVector2 (touch.x, touch.y));
        } else {
            board.BirthCell (IntVector2 (touch.x, touch.y));
        }
    }
    // this chunk is basically useless
    if (isGoing) {
        if (TimeNow () - timeWhenBoardUpdated > BOARD_UPDATE_RATE) {
            board.Next ();
            
            timeWhenBoardUpdated = TimeNow ();
        }
    }
    
    // try to solve the board if the user presses action button 0
    if (actionButt0.WasPressed (touch, touchState)) { // checks if the button was pressed and updates the state of the button
        IntVector2 startPosition = IntVector2 (1, 0);
        IntVector2 startDirection = IntVector2 (1, 0);
        bool isBoardSolved = board.Solve (startPosition, startDirection);
        if (isBoardSolved) {
            cout << "Board can be solved." << endl;
        } else {
            cout << "Board cannot be solved." << endl;
        }
    }
    // these two chunks are basically useless
    if (actionButt1.WasPressed (touch, touchState)) { // checks if the button was pressed and updates the state of the button
        isGoing = !isGoing;
    }
    if (actionButt2.WasPressed (touch, touchState)) { // checks if the button was pressed and updates the state of the button
        eraseMode = !eraseMode;
    }

    // update the LCD screen only after a fixed time interval has passed
    if (TimeNow () - timeSinceLastFrameUpdate > UPDATE_INTERVAL) { // I've heard TimeNow is bad, so the game may break after a certain amount of time has passed
        timeSinceLastFrameUpdate = TimeNow ();
        
        // (note that IS_SIMULATION does in fact equal 1)
        if (IS_SIMULATION) {
            // basically just calls the DrawEverything function, which draws everything and updates the screen
            glutPostRedisplay (); // SIMULATION code chunk
        } else {
            DrawEverything (); // NON-simulation code chunk
        }
    }

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

