#define IS_SIMULATION 1
#if IS_SIMULATION // if this is the simulation, then this chunck of code is used. Otherwise, this code is ignored.
/*



 SIMULATION only stuff



 */






// include statements

#ifndef Classes_hpp
#define Classes_hpp
#include <stdio.h>
#endif /* Classes_hpp */

#include "GFWLCD.hpp"
#include "GFWUtility.hpp"

#include <cstdlib>                      // standard definitions
#include <iostream>                     // C++ I/O
#include <cstdio>                       // C I/O (for sprintf)






#endif
#if !IS_SIMULATION // if this is not the simulation, then this chunck of code is used. Otherwise, this code is ignored.
/*



 NON-simulation only stuff



 */







#include <FEHLCD.h>
#include <FEHUtility.h>
#include <string.h>






#endif
/*



 SHARED simulation & non-simulation stuff



 */






// include statements

#include <cmath>                        // standard definitions
using namespace std;                    // make std accessible


// universal classes

#define M_PI 3.141592653589
const double DEGREES_TO_RADS = M_PI / 180;

class Vector2 {
public:
    Vector2 (float x0, float y0) {
        x = x0;
        y = y0;
    }
    Vector2 () {
        x = 0;
        y = 0;
    }
    float x;
    float y;

    // returns the magnitude of the vector
    float getMagnitude () {
        return sqrt (  pow (x, 2.0)  +  pow (y, 2.0)  );
    }
    // returns the vector converted into a unit vector
    Vector2 getUnitVector () {
        float magnitude = getMagnitude ();
        Vector2 unitVector;
        
        if (magnitude == 0) {
            unitVector = Vector2 (0, 0);
        } else {
            unitVector = Vector2 (x / magnitude, y / magnitude);
        }
        
        return unitVector;
    }
    // clamps the magnitude of the vector to maxLength
    void ClampMagnitude (float maxLength) {
        Vector2 unitVect = getUnitVector ();
        x = unitVect.x * maxLength;
        y = unitVect.y * maxLength;
    }
    // rotates vector counter-clockwise 90 degrees
    void RotateLeft () {
        int tempX = x;
        x = -y;
        y = tempX;
    }
    // rotates vector clockwise 90 degrees
    void RotateRight () {
        int tempX = x;
        x = y;
        y = -tempX;
    }
    // rotates vector by given degrees counter-clockwise about the origin
    void Rotate (float degrees) {
        float rads = degrees * DEGREES_TO_RADS;
        float tempX = x;
        float tempY = y;
        x = tempX * cos (rads) - tempY * sin (rads);
        y = tempX * sin (rads) + tempY * cos (rads);
    }
    void Rotate (Vector2 direction) {
        float degrees = direction.getAngle();
        Rotate (degrees);
    }
    // gets angle formed by the vector
    float getAngle () {
        float angle = -atan (x / y) / DEGREES_TO_RADS;
        if (y <= 0) {
            angle = angle + 180;
        }
        // cout << "Angle: " << angle << endl;
        return angle;
    }
    // returns a vector equivalent for the given angle
    static Vector2 DegreesToVector2 (float degrees) {
        Vector2 dir = Vector2 (1, tan (degrees * DEGREES_TO_RADS));
        return dir;
    }
};


class IntVector2 {
public:
    IntVector2 (int x0, int y0) {
        x = x0;
        y = y0;
    }
    IntVector2 () {
        x = 0;
        y = 0;
    }
    int x;
    int y;

    // rotates vector counter-clockwise 90 degrees
    void RotateLeft () {
        int tempX = x;
        x = -y;
        y = tempX;
    }
    // rotates vector clockwise 90 degrees
    void RotateRight () {
        int tempX = x;
        x = y;
        y = -tempX;
    }
    // returns whether the given vector equals this vector
    bool Equals (IntVector2 vect) {
        return (x == vect.x && y == vect.y);
    }
};


class Vectors {
public:
    Vectors () {
        right = Vector2 (1, 0);
        left = Vector2 (-1, 0);
        up = Vector2 (0, 1);
        down = Vector2 (0, -1);

        const double sqrt3 = sqrt (3.0);

        Bb = Vector2 (-sqrt3, 1).getUnitVector ();
        C = Vector2 (0, 1).getUnitVector ();
        D = Vector2 (sqrt3, 1).getUnitVector ();
        E = Vector2 (sqrt3, -1).getUnitVector ();
        F = Vector2 (0, -1).getUnitVector ();
        Aa = Vector2 (-sqrt3, -1).getUnitVector ();

        AB = getAverageUnitVector2 (Aa, Bb);
        BC = getAverageUnitVector2 (Bb, C);
        CD = getAverageUnitVector2 (C, D);
        DE = getAverageUnitVector2 (D, E);
        EF = getAverageUnitVector2 (E, F);
        FA = getAverageUnitVector2 (F, Aa);
    }
    Vector2 right;
    Vector2 left;
    Vector2 up;
    Vector2 down;

    Vector2 Aa;
    Vector2 Bb;
    Vector2 C;
    Vector2 D;
    Vector2 E;
    Vector2 F;

    Vector2 AB;
    Vector2 BC;
    Vector2 CD;
    Vector2 DE;
    Vector2 EF;
    Vector2 FA;

    void AlignVehicleVectors (float degrees) {
        float degreesForAlignment = degrees;

        Aa.Rotate (degreesForAlignment);
        Bb.Rotate (degreesForAlignment);
        C.Rotate (degreesForAlignment);
        D.Rotate (degreesForAlignment);
        E.Rotate (degreesForAlignment);
        F.Rotate (degreesForAlignment);

        AB.Rotate (degreesForAlignment);
        BC.Rotate (degreesForAlignment);
        CD.Rotate (degreesForAlignment);
        DE.Rotate (degreesForAlignment);
        EF.Rotate (degreesForAlignment);
        FA.Rotate (degreesForAlignment);
    }
    Vector2 getAverageUnitVector2 (Vector2 a, Vector2 b) {
        Vector2 average = Vector2 (a.x + b.x, a.y + b.y);
        average = average.getUnitVector ();
        return average;
    }

private:
};


/*
class Shape {
public:
    Shape () {

    }

    // virtual void CoolBeans () = 0;
    virtual void CoolBeans () {
        cout << "this from shape" << endl;
    }
private:
public:
    Vector2 points[8];
    char type;
};
*/


class Edge {
// class Edge {
public:
    // creates edge object, taking as its parameters: its start point, its end point, its direction
    // where its direction is used exclusively for collision and a direction of 0 is down (collides with an object traveling upwards), 1 is left, 2 is up, 3 is right
    // (the start point should generally be above and to the left of the end point in order for the edge to work properly with the physics system)
    Edge (Vector2 v0, Vector2 v1, int direction) {
        // points = {Vector2 (), Vector2()};
        points [0] = v0;
        points [1] = v1;
        dir = direction;
        switch (dir) {
            case 0:
                norm = IntVector2 (0, -1);
                break;
            case 1:
                norm = IntVector2 (-1, 0);
                break;
            case 2:
                norm = IntVector2 (0, 1);
                break;
            case 3:
                norm = IntVector2 (1, 0);
                break;
            default:
                break;
        }
    }
    Edge (Vector2 v0, Vector2 v1, IntVector2 normal) {
        points [0] = v0;
        points [1] = v1;
        norm = normal;
        if (normal.x == 0) {
            if (normal.y == 1) {
                dir = 2;
            } else if (normal.y == -1) {
                dir = 0;
            }
        } else if (normal.y == 0) {
            if (normal.x == 1) {
                dir = 3;
            } else if (normal.x == -1) {
                dir = 1;
            }
        } else {
            dir = -1;
        }
    }
    Edge () {

    }
    Vector2 points[2];
    int dir;
    IntVector2 norm;
};


class Box { // notably, the screen is in the fourth quadrant
public:
    // creates box object, taking four verticies of type Vector2 as its parameters
    // where v0 is top left vertex, v1 is top right vertex, v2 is bottom left vertex, v3 is bottom right vertex // should be where v0 is top left vertex, v1 is top right vertex, v2 is bottom right vertex, v3 is bottom left vertex
    Box (Vector2 v0, Vector2 v1, Vector2 v2, Vector2 v3) {
        points [0] = v0;
        points [1] = v1;
        points [2] = v2;
        points [3] = v3;
        width = points [1].x - points [0].x;
        height = points [2].y - points [0].y;
    }
    // creates box object, taking as its parameters: its top left vertex, a width, a height
    Box (Vector2 v0, float wdth, float hght) {
        width = wdth;
        height = hght;
        points [0] = v0;
        points [1] = Vector2 (v0.x + width, v0.y);
        points [2] = Vector2 (v0.x, v0.y - height); // points [2] = Vector2 (v0.x + width, v0.y - height);
        points [3] = Vector2 (v0.x + width, v0.y - height); // points [3] = Vector2 (v0.x, v0.y - height);
    }
    Box () {

    }
    Vector2 points[4];
    float width;
    float height;

    void UpdatePosition (Vector2 pos) {
        points [0] = pos;
        Updatepoints ();
    }
    void Updatepoints () {
        points [1] = Vector2 (points [0].x + width, points [0].y);
        points [2] = Vector2 (points [0].x, points [0].y - height); // points [2] = Vector2 (v0.x + width, v0.y - height);
        points [3] = Vector2 (points [0].x + width, points [0].y - height); // points [3] = Vector2 (v0.x, v0.y - height);
    }
    bool IsWithinBounds (Vector2 point) {
        if (point.x >= points [0].x  &&  point.x <= points [0].x + width  &&  point.y <= points [0].y  &&  point.y >= points [0].y - height) {
            return true;
        } else {
            return false;
        }
    }
    bool IsWithinBounds (Box box) {
        // if the box is within this.box's X bounds  &&  Y bounds
        if (  box.points [0].x <= points [1].x  &&  box.points [1].x >= points [0].x   &&   box.points [3].y <= points [0].y  &&  box.points [0].y >= points [3].y) {
            return true;
        } else {
            return false;
        }
    }
    Vector2 getCenter () {
        return Vector2 (  points [0].x + width/2.0,  points [0].y - height/2.0  );
    }
    Edge getSouthEdge () {
        Edge southEdge = Edge (points[2], points[3], 0);
        return southEdge;
    }
    Edge getWestEdge () {
        Edge westEdge = Edge (points[0], points[2], 1);
        return westEdge;
    }
    Edge getNorthEdge () {
        Edge northEdge = Edge (points[0], points[1], 2);
        return northEdge;
    }
    Edge getEastEdge () {
        Edge eastEdge = Edge (points[1], points[3], 3);
        return eastEdge;
    }
};


class Circle { // notably, the screen is in the fourth quadrant
public:
    // creates box object, taking as its parameters: its top left vertex, a width, a height
    Circle (Vector2 v0, float rds) {
        radius = rds;
        points [0] = v0;
    }
    Circle () {

    }
    Vector2 points[1];
    float radius;

    void UpdatePosition (Vector2 pos) {
        points [0] = pos;
    }
    bool IsWithinBounds (Vector2 point) {
        return false;
    }
};


class Polygon {
public:
    Polygon (Vector2 pts[], int lngth) {
        length = lngth;
        for (int k = 0; k < length; k++) {
            points [k] = pts[k];
        }
    }
    // copies an existing polygon into a new one
    Polygon (Polygon *poly) {
        length = poly->length;
        for (int k = 0; k < length; k++) {
            points [k] = Vector2 (poly->points [k].x, poly->points [k].y);
        }
    }
    Polygon () {

    }
    int length;

    void Rotate (float degrees) {
        for (int k = 0; k < length; k++) {
            points [k].Rotate (degrees);
        }
    }
    void Rotate (Vector2 direction) {
        for (int k = 0; k < length; k++) {
            points [k].Rotate (direction);
        }
    }
    void Translate (Vector2 move) {
        for (int k = 0; k < length; k++) {
            points [k] = Vector2 (points [k].x + move.x, points [k].y + move.y);
        }
    }
private:
public:
    Vector2 points [8]; // flexible array has to go at the bottom for whatever reason
};



// graphics classes


class Button {
public:
    // creates a box object, taking as its parameters a box object representing its boundary, a character pointer to an array indicating the text
    // to be displayed on the object, and an an integer representing the type of button it is, where 0 is default menu button and 5 is arrow pad button
    Button (Box bounds, char txt[], int buttonType) {
        box = bounds;
        strcpy (text, txt);
        type = buttonType;
        BUTT_MARGIN = 5;
        pressStartedWithinBound = false;
    }
    Button (Box bounds) {
        box = bounds;
        type = 0;
        strcpy (text, "");
        BUTT_MARGIN = 5;
    }
    Button () {

    }
    Box box;
    int type;
    char text[100];
    bool isPressed; // button's state of being pressed or unpressed
    bool noPressLastTime;
    bool pressStartedWithinBound;
    int BUTT_MARGIN;
    // these may need to be moved / initialized elswhere in order to work on the proteus
    static const int dec = 5; // amount pixels to shrink the button by when its pressed
    static const int TEXT_HEIGHT = 10;

    // updates the text of the button
    void UpdateText (char txt[]) {
        strcpy (text, txt);
    }
    // returns whether the button had been pressed and updates the pressed-or-unpressed state of the button
    bool WasPressed (Vector2 touchPos, bool touchStatus) {
        bool result = false;
        if (touchStatus == false) { // if the screen is not currently touched
            if (isPressed == true && pressStartedWithinBound) { // check if the button had been touched the last time the method was called and that the initial touch was within the bounds of the button
                result = true; // if it was, then return that the button was pressed
                // *****
                //       this bit could not be working because LCD.Touch only updates the returned mouse position when the screen is first touched
                //       I can fix that in this 'emulation' but I don't know what the real behavior of LCD.Touch is on the actual proteus
                //       so if I fix this now it may cause problems with button input in the future
                // *****
                isPressed = false; // reset the button so no weird behaviors happen
                pressStartedWithinBound = false;
                noPressLastTime = true;
            } else { // if the screen had never been touched or if when the screen was no longer being touched the touch input was not within the bounds of the button
                result = false;
                noPressLastTime = true; // take note that there was no press during this iteration of the method's call
                pressStartedWithinBound = false;
            }
        } else { // if the screen is touched
            isPressed = IsWithinBounds (touchPos); // check if the touch input was in the bounds of the button
            // pressStartedWithinBound = true; // un-comment this line to make it so that it doesn't matter if the touch input initially started within the bounds of the button
            if (noPressLastTime && isPressed) { // if this is the first time there is a touch input on the screen and the input is within the bounds of the button
                pressStartedWithinBound = true; // take note of it
            } if (pressStartedWithinBound == false) { // if the initial press was not within the bounds of the button
                isPressed = false; // make it be so that the button is not pressed
            }
            result = false;
            noPressLastTime = false;
        }
        return result;
    }
    // returns whether the button is being pressed and updates the pressed-or-unpressed state of the button
    bool IsBeingPressed (Vector2 touchPos) {
        isPressed = IsWithinBounds (touchPos);
        return isPressed;
    }
    /*
    bool IsBeingPressed (Vector2 touchPos, bool touchStatus) {
        isPressed = IsWithinBounds (touchPos);
        return isPressed;
    }
    */
    // returns true if the touch position is within the position of the button boundaries and false otherwise
    bool IsWithinBounds (Vector2 touchPos) {
        if (touchPos.x > box.points [0].x  &&  touchPos.x < box.points [0].x + box.width  &&  touchPos.y < box.points [0].y  &&  touchPos.y > box.points [0].y - box.height) { // may have to adjust this based on where the origin is set
            return true;
        } else {
            return false;
        }
    }
    // draws pressed or unpressed button depending on the button's state
    void DrawButton () {
        if (isPressed) { // if the button is pressed
            DrawPressedButton ();
        } else {
            DrawUnpressedButton ();
        }
    }
private:
    // these may need to be moved / initialized elswhere in order to work on the proteus
    static const int ABYSS = 0x1a1a1a;
    static const int WALLCOLOR = ABYSS;
    static const int BUTTHIGHLIGHT = INDIANRED;

    // draws unpressed button
    void DrawUnpressedButton () {
        switch (type) {
            case 5:
                LCD.SetFontColor (WHITE);
                LCD.WriteAt ( text, (int)(box.points[0].x+BUTT_MARGIN), -(int)(box.points[0].y - box.height / 2.0 + TEXT_HEIGHT / 2.0) );
                LCD.DrawRectangle ( (int)(box.points[0].x), -(int)(box.points[0].y), box.width, box.height );
                break;
            case 6:
                LCD.SetFontColor (ABYSS);
                LCD.SetBackgroundColor (ABYSS);
                LCD.FillRectangle ( (int)(box.points[0].x), -(int)(box.points[0].y), box.width, box.height );
                LCD.SetFontColor (WHITE);
                LCD.WriteAt ( text, (int)(box.points[0].x+BUTT_MARGIN), -(int)(box.points[0].y - box.height / 2.0 + TEXT_HEIGHT / 2.0) );
                LCD.DrawRectangle ( (int)(box.points[0].x), -(int)(box.points[0].y), box.width, box.height );
                break;
            case 0:
            default:
                // LCD.FillRectangle ( (int)(box.points[0].x), -(int)(box.points[0].y), box.width, box.height);
                // effectively erase the button before drawing the un-pressed version
                LCD.SetFontColor (WALLCOLOR);
                LCD.FillRectangle ( (int)(box.points[0].x), -(int)(box.points[0].y) - 1, box.width + 1, box.height + 1 );
                // draw the actual button
                LCD.SetFontColor (WHITE);
                LCD.SetBackgroundColor (WALLCOLOR);
                LCD.WriteAt ( text, (int)(box.points[0].x+BUTT_MARGIN), -(int)(box.points[0].y - box.height / 2.0 + TEXT_HEIGHT / 2.0) );
                LCD.DrawRectangle ( (int)(box.points[0].x), -(int)(box.points[0].y), box.width, box.height );
                break;
        }
    }
    // draws pressed version of button
    void DrawPressedButton () {
        switch (type) {
            case 5:
                LCD.SetFontColor (RED);
                LCD.WriteAt ( text, (int)(box.points[0].x+BUTT_MARGIN), -(int)(box.points[0].y - box.height / 2.0 + TEXT_HEIGHT / 2.0) );
                // LCD.DrawRectangle ( (int)(box.points[0].x + dec / 2.0), -(int)(box.points[0].y - dec / 2.0), box.width - dec, box.height - dec );
                LCD.DrawRectangle ( (int)(box.points[0].x), -(int)(box.points[0].y), box.width, box.height );
                break;
            case 6:
                LCD.SetFontColor (RED);
                LCD.WriteAt ( text, (int)(box.points[0].x+BUTT_MARGIN), -(int)(box.points[0].y - box.height / 2.0 + TEXT_HEIGHT / 2.0) );
                break;
            case 0:
            default:
                // effectively erase the button before drawing the pressed version
                LCD.SetFontColor (WALLCOLOR);
                LCD.FillRectangle ( (int)(box.points[0].x), -(int)(box.points[0].y) - 1, box.width + 1, box.height + 1 ); // erase button
                LCD.SetFontColor (BUTTHIGHLIGHT);
                LCD.SetBackgroundColor (BUTTHIGHLIGHT);
                LCD.FillRectangle ( (int)(box.points[0].x + dec / 2.0), -(int)(box.points[0].y - dec / 2.0), box.width - dec, box.height - dec );
                LCD.SetFontColor (WHITE);
                LCD.WriteAt ( text, (int)(box.points[0].x+BUTT_MARGIN), -(int)(box.points[0].y - box.height / 2.0 + TEXT_HEIGHT / 2.0));
                LCD.DrawRectangle ( (int)(box.points[0].x + dec / 2.0), -(int)(box.points[0].y - dec / 2.0), box.width - dec, box.height - dec );
                LCD.SetBackgroundColor (BLACK);
                break;
        }
    }
};


class StateIndicator {
public:
    // creates a box object, taking as its parameters a box object representing its boundary, a character pointer to an array indicating the text
    // to be displayed on the object, // and an an integer representing the type of indicator it is
    StateIndicator (Box bounds, char txt[]) {
        box = bounds;
        strcpy (text, txt);
        type = 0;
        BUTT_MARGIN = 5;
        
        backgroundColor = ABYSS;
        borderColor = WHITE;
        textColor = WHITE;
    }
    StateIndicator () {
        
    }
    Box box;
    int type;
    char text[100];
    int BUTT_MARGIN;
    static const int TEXT_HEIGHT = 10;
    int backgroundColor;
    int borderColor;
    int textColor;
    
    // updates the text of the indicator
    void UpdateText (char txt[]) {
        strcpy (text, txt);
    }
    // updates the color of the indicator, given a background color, border color, and text color
    void UpdateColors (int background, int border, int textC) {
        backgroundColor = background;
        borderColor = border;
        textColor = textC;
    }
    // updates the color of the indicator, given a background color and border color
    void UpdateColors (int background, int border) {
        backgroundColor = background;
        borderColor = border;
    }
    // updates the color of the indicator, given a background color
    void UpdateColors (int background) {
        backgroundColor = background;
    }
    // draws the indicator
    void Draw () {
        DrawIndicator (); // this method is kinda redundant
    }
private:
    static const int ABYSS = 0x1a1a1a;
    
    // actually draws indicator
    void DrawIndicator () {
        // effectively erase the button before drawing the un-pressed version
        LCD.SetFontColor (backgroundColor);
        LCD.FillRectangle ( (int)(box.points[0].x), -(int)(box.points[0].y), box.width, box.height );
        // draw the actual button
        LCD.SetFontColor (textColor);
        LCD.SetBackgroundColor (backgroundColor);
        LCD.WriteAt ( text, (int)(box.points[0].x+BUTT_MARGIN), -(int)(box.points[0].y - box.height / 2.0 + TEXT_HEIGHT / 2.0) );
        LCD.SetFontColor (borderColor);
        LCD.DrawRectangle ( (int)(box.points[0].x), -(int)(box.points[0].y), box.width, box.height );
    }
};
