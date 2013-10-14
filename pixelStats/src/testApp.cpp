#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    setupComplete = false;
    
    source.loadImage("SALVADOR-DALI-010.jpg");
    
    int w = source.getWidth();
    int h = source.getHeight();
    

    
    target.allocate(w, h, OF_IMAGE_COLOR);
    
//    unsigned char * pixels = source.getPixels();
    

    
    for ( int y = 1; y < h - 1; y++) {
        for ( int x = 1; x < w - 1; x++ ) {
            ofColor mainColor= getColorAt(x, y, source);
            
            vector<ofColor> neighbours;
            neighbours.push_back(getColorAt(x - 1, y - 1, source));
            neighbours.push_back(getColorAt(x, y - 1, source));
            neighbours.push_back(getColorAt(x + 1, y - 1, source));
            neighbours.push_back(getColorAt(x - 1, y, source));
            neighbours.push_back(getColorAt(x + 1, y, source));
            neighbours.push_back(getColorAt(x - 1, y + 1, source));
            neighbours.push_back(getColorAt(x, y + 1, source));
            neighbours.push_back(getColorAt(x + 1, y + 1, source));
            
            bool colorFound = false;
            int i = 0;
            while ( i < colorStats.size() && colorFound == false ) {
                cout << "Main color = " << ofToString(mainColor) << "colorStats[i].color = " << ofToString(colorStats[i].color) << endl;
                if (mainColor == colorStats[i].color) colorFound = true;
                if (!colorFound) i++;
            }
            
            if (colorFound) {
                int numRatios = colorStats[i].ratios.size();
                for (int n = 0; n < neighbours.size(); n++) {
                    for (int r = 0; r < numRatios; r++) {
                        if ( neighbours[n] == colorStats[i].ratios[r].color ) {
                            colorStats[i].ratios[r].pct++;
                        }
                        else {
                            colorRatio tempRatio;
                            tempRatio.color = neighbours[n];
                            tempRatio.pct = 1;
                            colorStats[i].ratios.push_back(tempRatio);
                            cout << "colorStats[" << i << "].ratios.size() = " << colorStats[i].ratios.size() << endl << "numRatios=" << numRatios << endl << endl;
                        }
                    }
                }
            }
            else {
                colorInfo tempInfo;
                tempInfo.color = mainColor;
                for (int n = 0; n < neighbours.size(); n++) {
                    colorRatio tempRatio;
                    tempRatio.color = neighbours[n];
                    tempRatio.pct = 1;
                    tempInfo.ratios.push_back(tempRatio);
                }
                colorStats.push_back(tempInfo);
            }
        }
    }

    colorIndex = 0;
    setupComplete = true;
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    if (setupComplete) {
        ofSetRectMode(OF_RECTMODE_CORNER);
        source.draw(0,0);
        ofSetRectMode(OF_RECTMODE_CENTER);
        ofSetColor(colorStats[colorIndex].color);
        ofRect(ofGetWidth()/2, 100, 200, 200);
        
        for (int r = 0; r < colorStats[colorIndex].ratios.size(); r++) {
            ofSetColor(colorStats[colorIndex].ratios[r].color);
            int size = ofGetWidth()/colorStats[colorIndex].ratios.size();
            ofRect(r * size + size/2, 400, size, size);
            ofSetColor(255);
            ofDrawBitmapString(ofToString(colorStats[colorIndex].ratios[r].pct), r * size + size/2, 410 + size);
        }
    }
    
}

//--------------------------------------------------------------
ofColor testApp::getColorAt(int x, int y, ofImage &img) {
    unsigned char * pixels = img.getPixels();
    int index = y * img.getWidth() * 3 + x * 3;
    ofColor color(pixels[index], pixels[index+1], pixels[index+2]);
    
    return color;
}


//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if ( key == OF_KEY_LEFT ) {
        colorIndex--;
        if (colorIndex < 0) colorIndex = 0;
    }
    
    if ( key == OF_KEY_RIGHT) {
        colorIndex++;
        if (colorIndex > colorStats.size()-1) colorIndex = colorStats.size()-1;
    }
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
