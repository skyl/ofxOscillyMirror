#pragma once

#define WEBCAM

#include "ofMain.h"

class ofApp : public ofBaseApp{
public:

    void setup();
    void update();
    void draw();

    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    void audioIn(ofSoundBuffer & input);
    void audioOut(ofSoundBuffer & input);

	// ofShader shader;
    ofVideoGrabber camera;
    // ofFbo fbo;
    ofPixels videoInverted;
    ofTexture videoTexture;

    ofSoundStream soundStream;
    ofSoundBuffer sb;
    vector <float> left;
    vector <float> right;
    vector <float> mono;

    bool toggle0;
    bool toggle1;
    bool toggle2;
};
