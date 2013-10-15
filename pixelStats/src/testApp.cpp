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
            
        }
    }
    
//    cout << "colorStats " << colorStats.size() << endl << "numPixels " << source.getWidth() * source.getHeight() << endl;
    int numEmpty = 0;
    
    for(map<ofColor, map < ofColor, float > >::iterator mainColor = colorStats.begin(); mainColor!=colorStats.end(); ++mainColor){
        
        cout << (*mainColor).second.size() << endl;
        
        float totalOccurences = 0;
        for(map < ofColor, float >::iterator subColor = mainColor->second.begin();
            subColor!=mainColor->second.end(); ++subColor){
            totalOccurences += (*subColor).second;
        }
        
        for(map < ofColor, float >::iterator subColor = mainColor->second.begin();
            subColor!=mainColor->second.end(); ++subColor){
            (*subColor).second /= totalOccurences;
        }
        
        float lastVal = 0;
        for(map < ofColor, float >::iterator subColor = mainColor->second.begin();
            subColor!=mainColor->second.end(); ++subColor){
            (*subColor).second += lastVal;
            lastVal = (*subColor).second;
        }
        
        

    }
    
//    cout << "numEmpty = " << numEmpty << endl;
    ofColor mainColor(0, 21, 40);
   for(map < ofColor, float >::iterator subColor = colorStats[mainColor].begin(); subColor!=colorStats[mainColor].end(); ++subColor){
//        cout << (*subColor).first << "  " << (*subColor).second << endl;
    }
    
    colorIndex = 0;
    setupComplete = true;
    
//    cout << "color 144, 89, 0 ->" << endl;
//    for(map < ofColor, float >::iterator subColor = colorStats[ofColor(3,3,3)].begin();
//        subColor!=colorStats[ofColor(144, 89, 0)].end(); ++subColor){
//        cout << (*subColor).first << " " << (*subColor).second << endl;
//    }
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    source.draw(0,0);
//    target.update();
    target.draw(source.getWidth(), 0);

}

//--------------------------------------------------------------
ofColor testApp::getColorAt(int x, int y, ofImage &img) {
    unsigned char * pixels = img.getPixels();
    int index = y * img.getWidth() * 3 + x * 3;
    ofColor color(pixels[index], pixels[index+1], pixels[index+2]);
    
    return color;
}


//--------------------------------------------------------------
void testApp::generateImage(int xPos, int yPos){
    
    unsigned char * srcPixels = source.getPixels();
    unsigned char * tgtPixels = target.getPixels();
    
    // assign edges of source image to target to avoid edge cases
    /*for (int x = 0; x < source.getWidth(); x++) {
        int index = getPixelIndex(x, 0, source.getWidth());
        tgtPixels[index] = srcPixels[index];
        tgtPixels[index+1] = srcPixels[index+1];
        tgtPixels[index+2] = srcPixels[index+2];
        
        index = getPixelIndex(x, source.getHeight()-1, source.getWidth());
        tgtPixels[index] = srcPixels[index];
        tgtPixels[index+1] = srcPixels[index+1];
        tgtPixels[index+2] = srcPixels[index+2];
    }
    
    for (int y = 1; y < source.getHeight()-1; y++) {
        int index = getPixelIndex(0, y, source.getWidth());
        tgtPixels[index] = srcPixels[index];
        tgtPixels[index+1] = srcPixels[index+1];
        tgtPixels[index+2] = srcPixels[index+2];
        
        index = getPixelIndex(source.getHeight(), y, source.getWidth());
        tgtPixels[index] = srcPixels[index];
        tgtPixels[index+1] = srcPixels[index+1];
        tgtPixels[index+2] = srcPixels[index+2];
    }*/
    
    
    
    int index = getPixelIndex(xPos, yPos, source.getWidth());
    ofColor mainColor(srcPixels[index], srcPixels[index+1], srcPixels[index+2]);
    ofColor selectedColor(0,0,0);
    
    
    for (int y = 0; y < target.getHeight(); y++) {
        for (int x = 0; x < target.getWidth(); x++) {

//            bool colorFits = false;
//            while (!colorFits) {
            
                float diceRoll = ofRandomf();
                bool colorFound = false;
            
                
                for(map < ofColor, float >::iterator subColor = colorStats[mainColor].begin(); subColor!=colorStats[mainColor].end(); ++subColor){
                    
                    if ( (*subColor).second > diceRoll && !colorFound) {
                        selectedColor = (*subColor--).first;
                        colorFound = true;
                        int index = y * target.getWidth() * 3 + x * 3;
                        tgtPixels[index] = selectedColor.r;
                        tgtPixels[index+1] = selectedColor.g;
                        tgtPixels[index+2] = selectedColor.b;
                    }
                }
                
            mainColor = selectedColor;
            
//                if ( selectedColor) {
//                    int index = y * target.getWidth() * 3 + x * 3;
//                    tgtPixels[index] = selectedColor.r;
//                    tgtPixels[index+1] = selectedColor.g;
//                    tgtPixels[index+2] = selectedColor.b;
//                    colorFits = true;
//                }
//            }
            
        }
        cout << "y " << y << "mainColor " << mainColor << endl;
        
    }
    
    target.update();
    
}


//--------------------------------------------------------------
void testApp::keyPressed(int key){

    
//    if (key == 'g') generateImage();
    
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
    if ( x < source.getWidth() && y < source.getHeight() ) {
        generateImage(x, y);
    }
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
