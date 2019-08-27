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

bool spaceKeyInp = false;
bool spaceKeyDownInp = false;

/*
bool oneKeyInp;
bool twoKeyInp;
bool threeKeyInp;

bool oneKeyDownInp;
bool twoKeyDownInp;
bool threeKeyDownInp;
*/

bool numKeyInp[10];
bool numKeyDownInp[10];

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

/*
void PassiveMouseV2 (int x, int y) {             // updates upon mouse movement when there are mouse clicks/inputs
    if (LCD.touchState) {
        LCD.touchX = x/ZOOM_SCALE;
        LCD.touchY = y/ZOOM_SCALE;
    }
}
*/
void PassiveMouseV2 (int x, int y) {             // updates upon mouse movement when there are mouse clicks/inputs
    LCD.touchX = x/ZOOM_SCALE;
    LCD.touchY = y/ZOOM_SCALE;
}

/*
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
*/
void Mouse (int buttonState, int clickState, int x, int y) {      // mouse click callback ... only updates upon mouse click
    LCD.touchX = x/ZOOM_SCALE; // re-enable these statements if you delete the passive mouse function
    LCD.touchY = y/ZOOM_SCALE;
    if (clickState == GLUT_DOWN && buttonState == GLUT_LEFT_BUTTON) { // was (button == GLUT_LEFT_BUTTON)
        LCD.touchState = true;
    } if ((buttonState == GLUT_LEFT_BUTTON ) && (clickState == GLUT_UP)) {
        LCD.touchState = false;
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
        case ' ':
            spaceKeyInp = true;
            spaceKeyDownInp = true;
            break;
        case 27:                               // 'q' means quit
            exit (0);
            break;
        default:
            break;
    }
    if (c >= '0' && c <= '9') {
        numKeyInp [c - '0'] = true;
        numKeyDownInp [c - '0'] = true;
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
        case ' ':
            spaceKeyInp = false;
            break;
        default:
            break;
    }
    if (c >= '0' && c <= '9') {
        numKeyInp [c - '0'] = false;
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
    glutPassiveMotionFunc(PassiveMouseV2);
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
void DrawPolygon (Polygon poly);
void DrawVector (Vector2 start, Vector2 dir, float scale);
void DrawClampedVector (Vector2 start, Vector2 dir, float scale);



/************************************************************************ CLASS DECLERATIONS ************************************************************************/


class Enums {
public:
    Enums () {
        
    }
    
    enum State {
        VOID = 0,
        POWDER,
        SOLID,
        LIQUID,
        GAS,
        DESTROYER
    };
    
    enum Attributes {
        NONE = 0,
        WHAT
    };
    
    enum ElementID {
        EMPTY = 0,
        SAND,
        eSNOW,
        DUST,
        eGAS,
        MYSTERY,
        WALL,
        DARKNESS
    };
    
    enum BoundarySetting {
        DESTROY = 0,
        INFINITE,
        BOUNDARIES
    };
    
    enum CursorStyle {
        RECTANGULAR = 0,
        CIRCULAR
    };
};
Enums enums;


class Cursor {
public:
    Cursor () {
        Zero ();
        // SetRectangle (1, 1);
        FillRectangle ();
    }
    static const int MAX_WIDTH = 128;
    static const int MAX_HEIGHT = 128;
    int tiles [MAX_HEIGHT][MAX_WIDTH];
    IntVector2 size = IntVector2 (1, 1);
    
    void Zero () {
        for (int i = 0; i < MAX_HEIGHT; i++) {
            for (int j = 0; j < MAX_WIDTH; j++) {
                tiles [i][j] = 0;
            }
        }
    }
    
    void SetSize (int width, int height) {
        size = IntVector2 (width, height);
    }
    void SetDiameter (int diameter) {
        size = IntVector2 (diameter, diameter);
    }
    IntVector2 getSize () {
        return IntVector2 (size.x, size.y);
    }
    float getDiameter () {
        return size.x;
    }
    int getTile (int x, int y) {
        return tiles [y][x];
    }
    bool isTileOccupied (int x, int y) {
        return getTile (x, y) == 1;
    }
    
    void SetRectangle (int width, int height) {
        SetSize (width, height);
        FillRectangle ();
    }
    void SetRectangle (int diameter) {
        SetDiameter (diameter);
        FillRectangle ();
    }
    void SetCircle (int diameter) {
        Zero ();
        SetDiameter (diameter);
        FillCircle ();
    }
    void SetCircleOutline (int diameter) {
        Zero ();
        SetDiameter (diameter);
        FillCircleOutline ();
    }
    void FillRectangle () {
        for (int i = 0; i < size.y; i++) {
            for (int j = 0; j < size.x; j++) {
                tiles [i][j] = 1;
            }
        }
    }
    void FillCircle () {
        int radius = getDiameter () / 2;
        Vector2 center = Vector2 (size.x - radius - 1, size.y - radius - 1);
        
        for (int i = 0; i < size.y; i++) {
            for (int j = 0; j < size.x; j++) {
                float distance = Vector2::Distance (Vector2 (j, i), center);
                if (distance <= radius) {
                    tiles [i][j] = 1;
                }
            }
        }
    }
    void FillCircleOutline () {
        int radius = getDiameter () / 2;
        Vector2 center = Vector2 (size.x - radius - 1, size.y - radius - 1);
        
        for (int i = 0; i < size.y; i++) {
            for (int j = 0; j < size.x; j++) {
                float distance = Vector2::Distance (Vector2 (j, i), center);
                int tolerance = 1;
                if (abs (distance - radius) < tolerance) {
                    tiles [i][j] = 1;
                }
            }
        }
    }
};


class Element {
public:
    /*
    Element (char charPtr[], int attribute, int stateTmp = enums.SOLID, float massTmp = 1.0, int colorTmp = WHITE) {
        strcpy (symbol, charPtr);
        state = stateTmp;
        mass = massTmp;
        color = colorTmp;
        
        attributes = attribute;
    }
    Element (char charPtr[], int stateTmp = enums.SOLID, float massTmp = 1.0, int colorTmp = WHITE) {
        strcpy (symbol, charPtr);
        state = stateTmp;
        mass = massTmp;
        color = colorTmp;
    }
    */
    Element (char charPtr[], int attribute, int stateTmp, float massTmp, int colorTmp) {
        strcpy (symbol, charPtr);
        state = stateTmp;
        mass = massTmp;
        color = colorTmp;
        
        attributes = attribute;
    }
    Element (char charPtr[], int stateTmp, float massTmp, int colorTmp) {
        strcpy (symbol, charPtr);
        state = stateTmp;
        mass = massTmp;
        color = colorTmp;
    }
    Element () {
        
    }
    const static int symbolLength = 5; // the amount of the characters within the symbol character array, including the null character
    char symbol [symbolLength];
    
    int state;
    float mass;
    int color = WHITE;
    
    int attributes = 0;
    
    char* getSymbol () {
        return symbol;
    }
};


class ElementTable {
public:
    ElementTable () {
        Initialize ();
        length = enums.DARKNESS + 1;
    }

    const static int MAX_ELEMENTS = 128;
    Element *elements [MAX_ELEMENTS];
    int length; // the length of the element array
    
    /*
    // adds an element
    void Add (Element *newElement) { // takes an State struct as an argument
        elements [length++] = newElement;
    }
    */
    Element* getElement (int ID) {
        return elements [ID];
    }
private:
    void Initialize () {
        /*
        char charPtr [5];
        strcpy (charPtr, "EMPT");
        elements [enums.EMPTY] = new Element (charPtr, 0, 0, 0);
        elements [enums.SAND] = new Element (charPtr, 1, 1.0, GOLD); // elements [EMPTY]->POWDER
        elements [enums.eSNOW] = new Element (charPtr, 1, 1.0, WHITE);
        
        elements [enums.WALL] = new Element (charPtr, enums.SOLID, 0, BROWN);
        elements [enums.DARKNESS] = new Element (charPtr, enums.DESTROYER, 0, GRAY);
        */
        elements [enums.EMPTY] = new Element ("EMPT", enums.VOID, 0, 0);
        elements [enums.SAND] = new Element ("SAND", enums.POWDER, 1.3, GOLD); // elements [EMPTY]->POWDER
        elements [enums.eSNOW] = new Element ("SNOW", enums.POWDER, 1.0, WHITE);
        elements [enums.DUST] = new Element ("DUST", enums.POWDER, 0.2, KHAKI); // LIGHTGOLDENRODYELLOW
        elements [enums.eGAS] = new Element ("GAS ", enums.POWDER, 0.05, LIGHTGREEN);
        elements [enums.MYSTERY] = new Element ("??? ", enums.WHAT, enums.POWDER, 1.0, LIGHTSKYBLUE);
        
        elements [enums.WALL] = new Element ("WALL", enums.SOLID, 999, BROWN); // 0
        elements [enums.DARKNESS] = new Element ("DARK", enums.DESTROYER, 999, GRAY);
    }
};
ElementTable ET;


class Particle {
public:
    Particle (int elementIDTmp, int posX, int posY) {
        elementID = elementIDTmp;
        elem = ET.getElement (elementID);
        
        pos = Vector2 (posX, posY);
    }
    Particle (int elementIDTmp, IntVector2 position) {
        elementID = elementIDTmp;
        elem = ET.getElement (elementID);
        
        pos = Vector2 (position.x, position.y);
    }
    Particle (int elementIDTmp) {
        elementID = elementIDTmp;
        elem = ET.getElement (elementID);
    }
    Particle (Particle *particleToCopy) {
        // Particle (particleToCopy->elementID, (int)(particleToCopy->pos.x), (int)(particleToCopy->pos.y));
        elementID = particleToCopy->elementID;
        elem = ET.getElement (elementID);
        
        // pos = Vector2 ((int)(particleToCopy->pos.x), (int)(particleToCopy->pos.y));
        pos = Vector2 (particleToCopy->pos.x, particleToCopy->pos.y);
        vel = Vector2 (particleToCopy->vel.x, particleToCopy->vel.y);
        debugVect = Vector2 (particleToCopy->debugVect.x, particleToCopy->debugVect.y);
    }
    Particle () {
        
    }
    int elementID = enums.EMPTY;
    Element *elem; // the element associated with the particle
    Vector2 pos; // the particle's position
    Vector2 vel = Vector2 (0, 0); // the particle's velocity
    Vector2 debugVect = Vector2 (0, 0); // vector used for debugging via drawing
    
    constexpr static float AIRF = 0.30; // .30
    
    Element* getElement () {
        return elem;
    }
    // sets the element type
    void SetElement (int elementIDTmp) {
        elementID = elementIDTmp;
        elem = ET.getElement (elementID);
    }
    // resets the particles velocity and decimal position
    void Reset () {
        pos = Vector2 ((int)(pos.x), (int)(pos.y));
        vel = Vector2 (0, 0);
    }
    /*
    // also changes the particles element type
    void Reset (int elementIDTmp) {
        
    }
    */
    // updates the particle's velocity by applying air friction
    void ApplyAirFriction () {
        // vel = Vector2 (vel.x - vel.x * AIRF / elem->mass, vel.y - vel.y * AIRF / elem->mass);
        Vector2 force = Vector2 (-vel.x * AIRF, -vel.y * AIRF);
        ApplyForce (force);
    }
    // updates the particle's velocity by applying the given force
    void ApplyForce (Vector2 force) {
        Vector2 accel = Vector2 (force.x / elem->mass, force.y / elem->mass);
        vel = Vector2 (vel.x + accel.x, vel.y + accel.y);
    }
    // updates the particle's velocity by applying the given acceleration
    void Accelerate (Vector2 accel) {
        vel = Vector2 (vel.x + accel.x, vel.y + accel.y);
        // vel = Vector2 (Vector2::getSmallest (vel.x + accel.x, 1), Vector2::getSmallest (vel.y + accel.y, 1));
    }
    // applies the particles velocity to its position vector
    void UpdatePosition () {
        // pos = Vector2 (vel.x + pos.x, vel.y + pos.y);
        // float maxSpeed = 0.1;
        // pos = Vector2 (Vector2::getSmallest (vel.x, maxSpeed) + pos.x, Vector2::getSmallest (vel.y, maxSpeed) + pos.y);
        float maxSpeed = 1;
        vel.CapMagnitude (maxSpeed);
        pos = Vector2 (vel.x + pos.x, vel.y + pos.y);
    }
    void SetPosition (Vector2 newPos) {
        pos = Vector2 (newPos.x, newPos.y);
    }
    void SetVelocity (Vector2 newVel) {
        vel = Vector2 (newVel.x, newVel.y);
    }
};


/*
class Cell {
public:
    Cell (int particleID, IntVector2 position) {
        particle = Particle (particleID);
        particle.pos = Vector2 (position.x, position.y);
    }
    Cell (int particleID) {
        particle = Particle (particleID);
    }
    Cell () {
        particle = Particle (0);
    }
    Particle particle;
    Vector2 GRAVITY = Vector2 (0, -2.1);
    float temperature = 1;
    float pressure = 0;
    
    Element* getElement () {
        int ID = particle.elementID;
        return ET.getElement (ID);
    }
    Particle* getParticle () {
        return &particle;
    }
};
*/

#define SCREEN_CELL_RATIO 2 // 1
class Simulation {
public:
    Simulation () {
        srand (TimeForRand ()); // illegal!
        cursor.SetSize (3, 3);
        UpdateCursor ();
    }
    static const int WIDTH = 80 * SCREEN_CELL_RATIO;
    static const int HEIGHT = 60 * SCREEN_CELL_RATIO;
    Particle canvas [HEIGHT][WIDTH];
    float gravityMask [HEIGHT][WIDTH];
    
    static const int CELL_PIXEL_WIDTH = 4 / SCREEN_CELL_RATIO;
    static const int CELL_PIXEL_HEIGHT = 4 / SCREEN_CELL_RATIO;
    static const int RANDOM_FACTOR = 99999999;
    
    int activeElement = 1;
    int boundaryType = enums.INFINITE; // enums.BOUNDARIES // enums.DESTROY // INFINITE
    int activeCursorStyle = enums.CIRCULAR;
    Cursor cursor;
    
    
    /************************ INITIALIZATION FUNCTIONS ************************/
    
    void Seed () {
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                /*
                if (rand () % RANDOM_FACTOR == 0) {
                    canvas [i][j] = 1;
                }
                */
                
                int elementType = enums.EMPTY;
                // if the current cell is a boundary cell
                if (isBoundaryIndex (j, i)) {
                    switch (boundaryType) {
                        case enums.DESTROY:
                            elementType = enums.DARKNESS;
                            break;
                            
                        case enums.INFINITE:
                            break;
                            
                        case enums.BOUNDARIES:
                            elementType = enums.WALL;
                            break;
                            
                        default:
                            break;
                    }
                }
                canvas [i][j] = Particle (elementType, j, -i);
            }
        }
    }
    
    /************************ CURSOR FUNCTIONS ************************/
    
    void UpdateCursor () {
        cursor.Zero ();
        switch (activeCursorStyle) {
            case (enums.RECTANGULAR):
                cursor.FillRectangle ();
                break;
                
            case (enums.CIRCULAR):
                cursor.FillCircle ();
                break;
                
            default:
                break;
        }
    }
    void SetCursorStyle (int style) {
        activeCursorStyle = style;
    }
    
    
    /************************ DRAWING FUNCTIONS ************************/

    void DrawCursor (IntVector2 point) {
        int radius = cursor.getDiameter () / 2;
        point = IntVector2 (point.x / CELL_PIXEL_WIDTH, -point.y / CELL_PIXEL_HEIGHT);
        point = IntVector2 (point.x - radius, point.y - radius);
        IntVector2 size = cursor.getSize ();
        for (int i = 0; i < size.y; i++) {
            for (int j = 0; j < size.x; j++) {
                IntVector2 tilePos = IntVector2 (point.x + j, point.y + i);
                if (isWithinBounds (tilePos) && cursor.isTileOccupied (j, i)) {
                    Element* element = canvas [tilePos.y][tilePos.x].getElement ();
                    
                    if (false && element->state == enums.VOID) {
                        int color = LIGHTGRAY; // GRAY
                        LCD.SetFontColor (color);
                        
                        DrawCell (tilePos);
                    } else {
                        /*
                        int color = element->color;
                        int alphaColor = WHITE;
                        float opacity = 0.5;
                        
                        int newColor = AddColorAlpha (color, alphaColor, opacity);
                        LCD.SetFontColor (newColor);
                        */
                        int alphaColor = WHITE;
                        float opacity = 0.5;
                        
                        int color = element->color;
                        int newColor = InvertColor (color);
                        newColor = AddColorAlpha (newColor, alphaColor, opacity);
                        LCD.SetFontColor (newColor);
                        
                        DrawCell (tilePos);
                    }
                }
            }
        }
    }
    void DrawCell (IntVector2 pos) {
        Vector2 point = Vector2 (pos.x * CELL_PIXEL_WIDTH, -pos.y * CELL_PIXEL_HEIGHT);
        DrawBox (Box (point, CELL_PIXEL_WIDTH, CELL_PIXEL_HEIGHT));
    }
    void Draw () {
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                Element* element = canvas [i][j].getElement ();
                if (element->state != 0) {
                    int color = element->color;
                    LCD.SetFontColor (color);
                    
                    Vector2 point = Vector2 (j * CELL_PIXEL_WIDTH, -i * CELL_PIXEL_HEIGHT);
                    DrawBox (Box (point, CELL_PIXEL_WIDTH, CELL_PIXEL_HEIGHT));
                }
            }
        }
    }
    void TrueDraw () {
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                Particle *particle = &canvas [i][j];
                Element *element = particle->getElement ();
                if (element->state != 0) {
                    int color = element->color;
                    // LCD.SetFontColor (color);
                    LCD.SetFontColor (RED);
                    
                    float radius = 1;
                    // Vector2 point = Vector2 (j * CELL_PIXEL_WIDTH, -i * CELL_PIXEL_HEIGHT);
                    Vector2 point = Vector2 (particle->pos.x * CELL_PIXEL_WIDTH, particle->pos.y * CELL_PIXEL_HEIGHT);
                    // DrawBox (Box (point, CELL_PIXEL_WIDTH, CELL_PIXEL_HEIGHT));
                    DrawCircle (Circle (point, radius));
                    // DrawPixel (point);
                    
                    float scalar = 35;
                    DrawVector (point, particle->debugVect, scalar);
                    DrawClampedVector (point, particle->debugVect, scalar);
                }
            }
        }
    }
    
    
    /************************ BOOL FUNCTIONS ************************/
    
    bool isBoundaryIndex (int j, int i) {
        bool result = false;
        if (i == 0 || j == 0 || i == HEIGHT - 1 || j == WIDTH - 1) {
            result = true;
        }
        return result;
    }
    bool isWithinBounds (IntVector2 point) {
        bool result = false;
        
        if (point.x < WIDTH && point.x >= 0   &&   point.y < HEIGHT && point.y >= 0) {
            result = true;
        }
        
        return result;
    }
    
    
    /************************ DEBUG FUNCTIONS ************************/
    
    // print the float positions of each particle
    void PrintPositions () {
        cout << "     ";
        int widthLimit = 5;
        int heightLimit = 10;
        for (int k = 0; k < WIDTH && k < widthLimit; k++) {
            cout << k % 10 << "                     ";
        }
        cout << endl;
        for (int i = 0; i < HEIGHT && i < heightLimit; i++) {
            cout << i << ":  ";
            if (i < 10) {
                cout << " ";
            }
            for (int j = 0; j < WIDTH && j < widthLimit; j++) {
                Particle* particle = &canvas [i][j];
                Element* element = particle->getElement ();
                Vector2 point = Vector2 (j, -i);
                cout << "(" << particle->pos.toString () << ") ";
                if (i == 0) {
                    cout << " ";
                }
            }
            cout << endl;
        }
    }
    // print the int positions of each particle
    void PrintPositionsInt () {
        cout << "     ";
        int widthLimit = 10;
        int heightLimit = 10;
        for (int k = 0; k < WIDTH && k < widthLimit; k++) {
            cout << k % 10 << "       ";
        }
        cout << endl;
        for (int i = 0; i < HEIGHT && i < heightLimit; i++) {
            cout << i << ":  ";
            if (i < 10) {
                cout << " ";
            }
            for (int j = 0; j < WIDTH && j < widthLimit; j++) {
                Particle* particle = &canvas [i][j];
                Element* element = particle->getElement ();
                Vector2 point = Vector2 (j, -i);
                cout << "(" << particle->pos.toIntVector2 ().toString () << ") ";
            }
            cout << endl;
        }
    }
    
    
    /************************ CELL-CREATION FUNCTIONS ************************/
    
    void BirthCell (IntVector2 point) {
        int radius = cursor.getDiameter () / 2;
        point = IntVector2 (point.x / CELL_PIXEL_WIDTH, -point.y / CELL_PIXEL_HEIGHT);
        point = IntVector2 (point.x - radius, point.y - radius);
        IntVector2 size = cursor.getSize ();
        for (int i = 0; i < size.y; i++) {
            for (int j = 0; j < size.x; j++) {
                IntVector2 tilePos = IntVector2 (point.x + j, point.y + i);
                if (cursor.isTileOccupied (j, i)) {
                    Birth (tilePos);
                }
            }
        }
    }
    void Birth (IntVector2 point) {
        point = IntVector2 (point.x, point.y);
        IntVector2 newPoint = IntVector2 (0, 0);
        if (point.x < WIDTH   &&  point.x >= 0) {
            newPoint.x = point.x;
            if (point.y < HEIGHT  &&  point.y >= 0) {
                newPoint.y = point.y;
                if (canvas [newPoint.y][newPoint.x].getElement ()->state == enums.VOID) {
                    canvas [newPoint.y][newPoint.x] = Particle (activeElement, newPoint.x, -newPoint.y); // +
                }
            }
        }
    }
    void KillCell (IntVector2 point) {
        int radius = cursor.getDiameter () / 2;
        point = IntVector2 (point.x / CELL_PIXEL_WIDTH, -point.y / CELL_PIXEL_HEIGHT);
        point = IntVector2 (point.x - radius, point.y - radius);
        IntVector2 size = cursor.getSize ();
        for (int i = 0; i < size.y; i++) {
            for (int j = 0; j < size.x; j++) {
                IntVector2 tilePos = IntVector2 (point.x + j, point.y + i);
                if (cursor.isTileOccupied (j, i)) {
                    Kill (tilePos);
                }
            }
        }
    }
    void Kill (IntVector2 point) {
        point = IntVector2 (point.x, point.y);
        IntVector2 newPoint = IntVector2 (0, 0);
        if (point.x < WIDTH   &&  point.x >= 0) {
            newPoint.x = point.x;
            if (point.y < HEIGHT  &&  point.y >= 0) {
                newPoint.y = point.y;
                if (boundaryType == enums.BoundarySetting::INFINITE  ||  !isBoundaryIndex (newPoint.x, newPoint.y)) {
                    canvas [newPoint.y][newPoint.x] = Particle (enums.EMPTY, newPoint.x, -newPoint.y);
                }
            }
        }
    }
    
    
    
    
    /************************************************************************ MAIN FUNCTION ************************************************************************/
    
    
    void Next () {
        // make next canvas equal to canvas
        Particle nextCanvas [HEIGHT][WIDTH];
        for (int i = 0; i < HEIGHT; i++) { // fight me
            for (int j = 0; j < WIDTH; j++) {
                nextCanvas [i][j] = Particle (0, j, -i);
            }
        }
        // PrintPositions ();
        // calculate next positions of the particles
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                IntVector2 point = IntVector2 (j, i);
                Particle* particle = &canvas [i][j];
                Element* element = particle->getElement ();
            
                switch (element->state) {
                    case enums.VOID: { // empty
                        break;
                    }
                        
                    case enums.POWDER: { // powder
                        // do physics returns an updated version of the particle, and does not augment the original array of particles
                        nextCanvas [i][j] = DoPhysics (particle);
                        break;
                    }
                    
                    case enums.DESTROYER:
                    case enums.SOLID: { // solid
                        nextCanvas [i][j] = Particle (&canvas [i][j]);
                        // nextCanvas [i][j] = Particle (particle->elementID, j, -i);
                        break;
                    }
                        
                    default:
                        break;
                }
                
                // cout << "disp: " << disp.toString () << endl;
                 
                // nextCanvas [i][j] = canvas [i][j];
            }
        }
        // flip flop
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                canvas [i][j] = nextCanvas [i][j];
            }
        }
        for (int i = 0; i < HEIGHT; i++) { // fight me
            for (int j = 0; j < WIDTH; j++) {
                nextCanvas [i][j] = Particle (0, j, -i);
            }
        }
        // populate the next canvas based on the particle's float positions
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                IntVector2 point = IntVector2 (j, i);
                Particle* particle = &canvas [i][j];
                Element* element = particle->getElement ();
                
                switch (element->state) {
                    case enums.VOID: { // empty
                        break;
                    }
                        
                    case enums.POWDER: { // powder
                        // get particle position
                        Vector2 floatPos = particle->pos;
                        // set the particle's float position vector to an int position vector
                        IntVector2 intPos = CapPoint (IntVector2 (floatPos.x, -floatPos.y));
                        
                        Particle *canvasNewParticle = &canvas [intPos.y][intPos.x];
                        Particle *canvasCurrentParticle = &canvas [i][j];
                        Particle *nextCanvasNewParticle = &nextCanvas [intPos.y][intPos.x];
                        Particle *nextCanvasCurrentParticle = &nextCanvas [i][j];
                        
                        /*
                        if ((canvasNewParticle->getElement()->state == enums.VOID && nextCanvasNewParticle->getElement()->state == enums.VOID) || (canvasNewParticle == particle)) {
                            // put the particle with its new position at the corresponding location within next canvas
                            nextCanvas [intPos.y][intPos.x] = *particle;
                        } else if (nextCanvasNewParticle->getElement()->state != enums.VOID) {
                            int MAX_RAND_NUM = 1;
                            int randNum = rand () % MAX_RAND_NUM;
                            
                            if (randNum == 0) {
                                // switch the particles
                                Particle tempParticle = *nextCanvasNewParticle;
                                tempParticle.SetPosition (Vector2 (j, -i));
                                
                                nextCanvas [intPos.y][intPos.x] = *particle;
                                nextCanvas [i][j] = tempParticle;
                            }
                        } else { // otherwise it is moving into element that is not void // or the particle has not moved at all
                            // this chunk prevents particles from passing through other particles (usually solid ones) and from being deleted entirely
                            particle->SetPosition (Vector2 (j, -i));
                            nextCanvas [i][j] = *particle;
                        }
                        */
                        
                        if ((canvasNewParticle->getElement()->state == enums.VOID && nextCanvasNewParticle->getElement()->state == enums.VOID) || (canvasNewParticle == particle)) {
                            // put the particle with its new position at the corresponding location within next canvas
                            nextCanvas [intPos.y][intPos.x] = *particle;
                        } else { // otherwise it is moving into element that is not void // or the particle has not moved at all
                            // particle->vel = Vector2 (0, 0); // Vector2 (-0.1, 0.2);
                            // this chunk prevents particles from passing through other particles (usually solid ones) and from being deleted entirely
                            particle->SetPosition (Vector2 (j, -i));
                            nextCanvas [i][j] = *particle;
                        }
                        
                        /*
                        if ((canvas [intPos.y][intPos.x].getElement()->state == enums.VOID && nextCanvas [intPos.y][intPos.x].getElement()->state == enums.VOID) || (&canvas [intPos.y][intPos.x] == particle)) {
                            // put the particle with its new position at the corresponding location within next canvas
                            nextCanvas [intPos.y][intPos.x] = *particle;
                        } else { // otherwise it is moving into element that is not void // or the particle has not moved at all
                            // particle->vel = Vector2 (0, 0); // Vector2 (-0.1, 0.2);
                            // this chunk prevents particles from passing through other particles (usually solid ones) and from being deleted entirely
                            particle->SetPosition (Vector2 (j, -i));
                            nextCanvas [i][j] = *particle;
                        }
                        */
                        break;
                    }
                        
                    case enums.DESTROYER:
                    case enums.SOLID: { // solid
                        if (nextCanvas [i][j].getElement()->state == enums.POWDER) {
                            // cout << "oi";
                        }
                        nextCanvas [i][j] = *particle;
                        break;
                    }
                        
                    default:
                        break;
                }
                
            }
        }
        // make canvas equal to next canvas
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                canvas [i][j] = nextCanvas [i][j];
            }
        }
    }
    
    
    
    
    
    /************************************************************************ PHYSICS FUNCTIONS ************************************************************************/
    
    
    /************************ COLLISION-DETECTION FUNCTIONS ************************/
    
    void CheckAndApplyCollision (Particle *particle) {
        IntVector2 pos = particle->pos.toIntVector2 ();
        pos.y = pos.y * -1;
        
        int radius = 1;
        float collisionDistance = 10; // 10
        // for (int i = 0; i <= radius; i++) {
            // for (int j = 0; j <= radius; j++) {
        for (int i = -radius; i <= radius; i++) {
            for (int j = -radius; j <= radius; j++) {
                if (!(i == 0 && j == 0)) {
                    IntVector2 otherParticleIndex = CapPoint (IntVector2 (pos.x + j, pos.y + i));
                    Particle *otherParticle = &canvas [otherParticleIndex.y][otherParticleIndex.x];
                    if (otherParticle->getElement ()->state != enums.VOID) {
                        otherParticle->SetPosition (CapPoint (otherParticle->pos)); // could be optimized
                        float distance = Vector2::Distance(particle->pos, otherParticle->pos);
                        
                        if (distance <= collisionDistance) {
                            if (particle->getElement ()->attributes == enums.WHAT || otherParticle->getElement ()->attributes == enums.WHAT) {
                                OldCollidePowder (particle, otherParticle);
                            } else if (otherParticle->getElement ()->state == enums.POWDER) {
                                CollidePowder (particle, otherParticle);
                            } else if (otherParticle->getElement ()->state == enums.SOLID) {
                                // CollideSolid (particle, otherParticle);
                                OldCollidePowder (particle, otherParticle);
                            } else if (otherParticle->getElement ()->state == enums.DESTROYER) {
                                CollideDarkness (particle, otherParticle);
                            }
                        }
                        
                    }
                }
            }
        }
    }
    
    
    /************************ PHYSICS CALCULATIONS FUNCTIONS ************************/
    
    // simulate a collision between the given two particles by updating their velocities
    static void CollidePowder (Particle *particle, Particle *otherParticle) {
        float magn = particle->vel.getMagnitude ();
        float otherMagn = otherParticle->vel.getMagnitude ();
        float minSleepVelocity = 0.0; // minimum velocity for the particle to not be considered sleeping
        
        if (magn < minSleepVelocity  &&  otherMagn < minSleepVelocity) { // && distMagn < .05 // this is suppose to detect whether the object should go to sleep but it needs to be seriously improved
            particle->vel = Vector2 (0, 0);
            otherParticle->vel = Vector2 (0, 0);
        } else {
            
            // float distance = Vector2::Distance(particle->pos, otherParticle->pos); // may not want to calculate this twice...
            Vector2 deltaDistance = Vector2 (otherParticle->pos.x - particle->pos.x, otherParticle->pos.y - particle->pos.y);
            
            
            // the calculate the normal of the collision reference to the first particle
            Vector2 collisionNormal = Vector2 (otherParticle->pos.x - particle->pos.x, otherParticle->pos.y - particle->pos.y).getUnitVector ();
            Vector2 otherCollisionNormal = Vector2 (particle->pos.x - otherParticle->pos.x, particle->pos.y - otherParticle->pos.y).getUnitVector ();
            Vector2 unitNormalVector = Vector2 (collisionNormal.x - otherCollisionNormal.x, collisionNormal.y - otherCollisionNormal.y).getUnitVector ();
            
            
            /* new stuff */
            
            Vector2 norm = Vector2 (-collisionNormal.x, -collisionNormal.y);
            Vector2 dir = Vector2 (norm.x, norm.y);
            dir.RotateLeft ();
            
            Vector2 velP1 = particle->vel;
            Vector2 velP2 = otherParticle->vel;
            
            Vector2 U_S1 = Vector2::Proj (dir, velP1); // unchangedVelocityP1 (s = same)
            Vector2 U_S2 = Vector2::Proj (dir, velP2); // unchangedVelocityP2 (s = same)
            
            Vector2 U_R1 = Vector2::Proj (norm, velP1); // relevantInitialVelocityP1
            Vector2 U_R2 = Vector2::Proj (norm, velP2); // relevantInitialVelocityP2
            
            float m1 = particle->elem->mass;
            float m2 = otherParticle->elem->mass;
            float totalMass = m1 + m2;
            float massFactor1 = (m1 - m2) / totalMass;
            float massFactor2 = (2 * m2) / totalMass;
            
            // massFactor1 = 1;
            // massFactor2 = 1;
            
            Vector2 V_R1 = Vector2 (U_R1.x * massFactor1  +  U_R2.x * massFactor2,   U_R1.y * massFactor1  +  U_R2.y * massFactor2); // relevantFinalVelocityP1
            
            float PMR = 0.8;
            V_R1 = Vector2 (V_R1.x * PMR, V_R1.y * PMR);
            
            Vector2 netVelocity = Vector2 (V_R1.x + 0, V_R1.y + 0);
            // Vector2 netVelocity = Vector2 (V_R1.x + U_S1.x, V_R1.y + U_S1.y);
            // particle->SetVelocity (netVelocity);
            particle->Accelerate (netVelocity);
            
            
            /* debugging */
            
            // particle->debugVect = unitNormalVector;
            float debugScalar = 1;
            // particle->debugVect = Vector2 (netVelocity.x * debugScalar, netVelocity.y * debugScalar);
            particle->debugVect = norm;
        }
    }
    static void OldCollidePowder (Particle *particle, Particle *otherParticle) {
        float magn = particle->vel.getMagnitude ();
        float otherMagn = otherParticle->vel.getMagnitude ();
        float minSleepVelocity = 0.0; // minimum velocity for the particle to not be considered sleeping
        
        if (magn < minSleepVelocity  &&  otherMagn < minSleepVelocity) { // && distMagn < .05 // this is suppose to detect whether the object should go to sleep but it needs to be seriously improved
            particle->vel = Vector2 (0, 0);
            otherParticle->vel = Vector2 (0, 0);
        } else {
            
            // float distance = Vector2::Distance(particle->pos, otherParticle->pos); // may not want to calculate this twice...
            Vector2 deltaDistance = Vector2 (otherParticle->pos.x - particle->pos.x, otherParticle->pos.y - particle->pos.y);
            
            
            // the calculate the normal of the collision reference to the first particle
            Vector2 collisionNormal = Vector2 (otherParticle->pos.x - particle->pos.x, otherParticle->pos.y - particle->pos.y).getUnitVector ();
            Vector2 otherCollisionNormal = Vector2 (particle->pos.x - otherParticle->pos.x, particle->pos.y - otherParticle->pos.y).getUnitVector ();
            Vector2 unitNormalVector = Vector2 (collisionNormal.x - otherCollisionNormal.x, collisionNormal.y - otherCollisionNormal.y).getUnitVector ();
            // cout << "unitNormalVector: " << unitNormalVector.toString () << endl;
            
            float PMR = 0.2; // percent momentum retained // 0.8
            float K = .3; // .3
            
            float factor = -pow (K * particle->elem->mass, 0.5) * PMR;
            Vector2 distance = Vector2 (abs (deltaDistance.x), abs (deltaDistance.y));
            Vector2 finalVel = Vector2 (distance.x * factor * unitNormalVector.x,  distance.y * factor * unitNormalVector.y); // v = sqrt (k*x^2)
            particle->Accelerate (finalVel);
            
            // particle->debugVect = unitNormalVector;
            float debugScalar = factor;
            particle->debugVect = Vector2 (unitNormalVector.x * debugScalar, unitNormalVector.y * debugScalar);
        }
    }
    // simulate a collision between the given two particles by updating their velocities
    static void CollideSolid (Particle *particle, Particle *otherParticle) {
        // float distance = Vector2::Distance(particle->pos, otherParticle->pos); // may not want to calculate this twice...
        
        // particle->vel = Vector2 (-particle->vel.x, -particle->vel.y);
        particle->vel = Vector2 ();
    }
    static void CollideDarkness (Particle *particle, Particle *otherParticle) {
        particle->SetElement (enums.VOID);
        particle->Reset ();
    }
    Particle DoPhysics (Particle *newParticle) {
        Particle particleNotPtr = Particle (newParticle);
        Particle *particle = &particleNotPtr;
        // Particle *particle = new Particle (newParticle); // memory leak?
        // Particle *particle = newParticle;
        
        // CheckAndApplyCollision (particle);
        
        particle->ApplyAirFriction ();
        particle->Accelerate (Vector2 (0, -0.5)); // gravity // (0.5, -0.8) // (0.1, -0.2)
        
        CheckAndApplyCollision (particle);
        particle->UpdatePosition ();
        
        return particleNotPtr; // *particle
    }
    
    
    /************************ MISC FUNCTIONS ************************/
    
    IntVector2 CapPoint (IntVector2 pos) {
        IntVector2 newPoint = IntVector2 (Vector2::MathMod (pos.x, WIDTH), Vector2::MathMod (pos.y, HEIGHT));
        return newPoint;
    }
    Vector2 CapPoint (Vector2 pos) {
        // Vector2 newPoint = Vector2 (Vector2::MathMod (pos.x, WIDTH), Vector2::MathMod (pos.y, HEIGHT));
        Vector2 newPoint = Vector2 (Vector2::MathMod (pos.x, WIDTH), -Vector2::MathMod (-pos.y, HEIGHT));
        return newPoint;
    }
    /*
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
                    if (canvas [pos.y + i + disp.y][pos.x + j + disp.x] == 1) {
                        neighborCount++;
                    }
                }
            }
        }
        return neighborCount;
    }
    */
    void SetActiveElement (int ID) {
        activeElement = ID;
    }
private:
};



/************************ FUNCTION DECLARATIONS ************************/

void NextElement ();
void PreviousElement ();
void NextCursor ();
void DecrementCursorRadius ();
void IncrementCursorRadius ();


/************************ MISCELLANEOUS VARIABLES ************************/

Vector2 touch = Vector2 ();
bool touchState = false;
float timeSinceLastFrameUpdate;
float timeWhenSimulationUpdated;
#define SIMULATION_UPDATE_RATE 0.01 // 0.05

Vectors Vector;
Simulation simulation;


/************************ MISCELLANEOUS VARIABLES ************************/

bool eraseMode;
bool isGoing;


/************************ GUI VARIABLES ************************/

// sample variables for button declaration
#define BUTT_WIDTH 100
#define BUTT_HEIGHT 30
#define BUTT_Y_POS 205 // 195
#define BUTT_X_POS 105 // 160
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
    // const double sqrt3 = pow (3.0, 0.5);
    eraseMode = false;
    isGoing = false;
    // int rightButtMargin = 15; // y-pos: -15, -60, -105, -150, -195
    
    // initialize key inputs arrays
    for (int i = 0; i < 10; i++) {
        numKeyInp [i] = false;
        numKeyDownInp [i] = false;
    }

    // initialize buttons
    char charPtr [100];
    strcpy (charPtr, "++"); // use charPtr to set the text of the button
    actionButt0 = Button (  Box ( Vector2 (BUTT_X_POS, -BUTT_Y_POS - BUTT_HEIGHT*0 - BUTT_Y_MARGIN*0), 45, BUTT_HEIGHT ), charPtr, 0  ); // -150
    strcpy (charPtr, "GO");
    actionButt1 = Button (  Box ( Vector2 (BUTT_X_POS + 55, -BUTT_Y_POS - BUTT_HEIGHT*0 - BUTT_Y_MARGIN*0), 45, BUTT_HEIGHT ), charPtr, 0  );
    strcpy (charPtr, "X");
    actionButt2 = Button (  Box ( Vector2 (BUTT_X_POS + 55*2, -BUTT_Y_POS - BUTT_HEIGHT*0 - BUTT_Y_MARGIN*0), 45, BUTT_HEIGHT ), charPtr, 0  );
    
    int activeElement = simulation.activeElement;
    Element *elem = ET.getElement (activeElement);
    strcpy (charPtr, elem->getSymbol ());
    // strcpy (charPtr, "ELEM");
    actionButt3 = Button (  Box ( Vector2 (BUTT_X_POS + 55*3, -BUTT_Y_POS - BUTT_HEIGHT*0 - BUTT_Y_MARGIN*0), 45, BUTT_HEIGHT ), charPtr, 0  );
    
    // create simulation
    simulation = Simulation ();
    simulation.Seed ();
    
    // NextElement ();
    
    timeWhenSimulationUpdated = TimeNow ();
    timeSinceLastFrameUpdate = TimeNow (); // initialize the time since the last screen/frame update
}


// draws everything; all drawing functions should go here
// It's important to put all LCD functions here. It's critical for the simulation to work properly and
// is good coding practice for graphical computing, especially when you have limited computing capactity
// like you do on the Proteus.
void DrawEverything () {
    LCD.Clear (BACKGROUNDCOLOR); // clear the screen (for animation purposes)
    
    // sample button drawing function implementation
    /*
    actionButt0.DrawButton();
    actionButt1.DrawButton();
    actionButt2.DrawButton();
    actionButt3.DrawButton();
    */
    
    simulation.Draw ();
    // simulation.TrueDraw ();
    simulation.DrawCursor (IntVector2 (touch.x, touch.y));

    actionButt0.DrawButton();
    actionButt1.DrawButton();
    actionButt2.DrawButton();
    actionButt3.DrawButton();
}


// do all of the stuff for the main game loop that gets repeated
void mainLoop () {
    touchState = LCD.Touch (&touch.x, &touch.y); // get the user's touch input coordinates, and store whether or not the user is touching the screen in the variable touchState
    touch = Vector2 (touch.x, -touch.y); // standardize the touch coordinates so they're effectively in the fourth quadrant

    if (touchState) {
        if (eraseMode) {
            simulation.KillCell (IntVector2 (touch.x, touch.y));
        } else {
            simulation.BirthCell (IntVector2 (touch.x, touch.y));
        }
    }
    if (isGoing) {
        if (TimeNow () - timeWhenSimulationUpdated > SIMULATION_UPDATE_RATE) {
            simulation.Next ();
            
            timeWhenSimulationUpdated = TimeNow ();
        }
    }
    
    if (actionButt0.WasPressed (touch, touchState)) { // checks if the button was pressed and updates the state of the button
        simulation.Next ();
    }
    if (actionButt1.WasPressed (touch, touchState) || spaceKeyDownInp) { // checks if the button was pressed and updates the state of the button
        isGoing = !isGoing;
    }
    if (actionButt2.WasPressed (touch, touchState) || numKeyDownInp [0]) { // checks if the button was pressed and updates the state of the button
        eraseMode = !eraseMode;
    }
    if (actionButt3.WasPressed (touch, touchState) || numKeyDownInp [2]) { // checks if the button was pressed and updates the state of the button
        NextElement ();
        char charPtr [100];
        int activeElement = simulation.activeElement;
        Element *elem = ET.getElement (activeElement);
        // printf (charPtr, "%s", elem->getSymbol ());
        // char symb [5] = elem->getSymbol ();
        // cout << "elem " << symb << endl;
        strcpy (charPtr, elem->getSymbol ());
        // strncpy (charPtr, elem->getSymbol (), 5);
        actionButt3.UpdateText (charPtr);
    }
    if (numKeyDownInp [1]) { // checks if the button was pressed and updates the state of the button
        PreviousElement ();
        char charPtr [100];
        int activeElement = simulation.activeElement;
        Element *elem = ET.getElement (activeElement);
        strcpy (charPtr, elem->getSymbol ());
        actionButt3.UpdateText (charPtr);
    }
    if (numKeyDownInp [3]) {
        DecrementCursorRadius ();
    }
    if (numKeyDownInp [4]) {
        IncrementCursorRadius ();
    }
    if (numKeyDownInp [5]) {
        NextCursor ();
    }
    
    // reset key down inputs
    for (int i = 0; i < 10; i++) {
        numKeyDownInp [i] = false;
    }
    spaceKeyDownInp = false;

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

void PreviousElement () {
    int length = ET.length;
    int activeElement = simulation.activeElement;
    int newElement = activeElement - 1;
    if (newElement <= 0) {
        newElement = length - 1;
    }
    simulation.SetActiveElement (newElement);
}
void NextElement () {
    int length = ET.length;
    int activeElement = simulation.activeElement;
    int newElement = activeElement + 1;
    if (newElement >= length) {
        newElement = 1;
    }
    simulation.SetActiveElement (newElement);
}
void NextCursor () {
    int length = 2;
    int activeCursor = simulation.activeCursorStyle;
    int newCursor = activeCursor + 1;
    if (newCursor >= length) {
        newCursor = 0;
    }
    simulation.SetCursorStyle (newCursor);
    simulation.UpdateCursor ();
}
void DecrementCursorRadius () {
    int diameter = simulation.cursor.getDiameter ();
    if (diameter > 2) {
        diameter -= 2;
        simulation.cursor.SetDiameter (diameter);
        simulation.UpdateCursor ();
    }
}
void IncrementCursorRadius () {
    int diameter = simulation.cursor.getDiameter ();
    // if (diameter + 2 < simulation.cursor.MAX_WIDTH) {
    if (diameter + 2 <= 32) {
        diameter += 2;
        // simulation.cursor.SetRectangle (diameter);
        simulation.cursor.SetDiameter (diameter);
        simulation.UpdateCursor ();
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

// draws vector given a starting position, a direction, and a scalar
void DrawVector (Vector2 start, Vector2 dir, float scale) {
    Vector2 end = Vector2 (start.x + dir.x * scale, start.y + dir.y * scale);
    Edge edge = Edge (start, end, 0);
    DrawEdge (edge);
}
// clamps the given vector to the magnitude of the given scalar
void DrawClampedVector (Vector2 start, Vector2 dir, float scale) {
    dir = dir.getUnitVector ();
    Vector2 end = Vector2 (start.x + dir.x * scale, start.y + dir.y * scale);
    Edge edge = Edge (start, end, 0);
    DrawEdge (edge);
}
