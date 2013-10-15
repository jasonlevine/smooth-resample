#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    setupComplete = false;
    
    source.loadImage("SALVADOR-DALI-010.jpg");
    
    int w = source.getWidth();
    int h = source.getHeight();
    
    bool colah = ofColor(0,0,0) < ofColor(0,1,0);
    
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
            
            
            if (colorStats.find(mainColor) != colorStats.end()) {
                for (int n = 0; n < neighbours.size(); n++) {
                    if (colorStats[mainColor].find(neighbours[n]) != colorStats[mainColor].end()) {
                        colorStats[mainColor][neighbours[n]]++;
                    }
                    else {
                        colorStats[mainColor][neighbours[n]] = 1;
                    }
                }
            }
            else {
                for (int n = 0; n < neighbours.size(); n++) {
                    colorStats[mainColor][neighbours[n]] = 1;
                }
            }
            
            /*
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
            }*/
        }
    }
    cout << "colorStats " << colorStats.size() << endl << "numPixels " << source.getWidth() * source.getHeight() ;
    
    map<ofColor, map < ofColor, int > >::iterator mainColor = colorStats.begin();
    mainColor++;
    for(map < ofColor, int >::iterator subColor=mainColor->second.begin();
        subColor!=mainColor->second.end(); ++subColor){
        cout << (*subColor).first << "  " << (*subColor).second << endl;
    }
    
    colorIndex = 0;
    setupComplete = true;
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

    
    
//    for ( subColor = mainColor-> .begin();
//         mainColor != colorStats.end();  // say let's stop when we get to the end aMap
//         ++it) {            // increment the iterator
//    }
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
