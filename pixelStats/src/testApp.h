#pragma once

#include "ofMain.h"

struct colorRatio {
    ofColor color;
    float pct;
};

struct colorInfo {
    ofColor color;
    vector<colorRatio> ratios;
};

class testApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    
//    int getPixelIndex(int x, int y, int width) { return y * width * 3 + x * 3; };
//    ofColor getColorAt(int index, unsigned char * pixels) { return ofColor(pixels[index], pixels[index+1], pixels[index+2]); };
    
    ofColor getColorAt(int x, int y, ofImage &img);

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofImage source;
    ofImage target;
    
    vector<colorInfo> colorStats;
    
    int colorIndex;
    
    bool setupComplete;
		
};
