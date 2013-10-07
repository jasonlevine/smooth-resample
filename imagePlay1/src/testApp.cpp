#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    img.loadImage("SALVADOR-DALI-010.jpg");
    rows = 20;
    cols = 20;
    ofFill();
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
//    img.draw(0,0);
    
    unsigned char * pixels = img.getPixels();
    
    for ( float i = 0; i < rows; i++ ) {
        for ( float j = 0; j < cols; j++ ) {
            
            // xy = drawing...
            float x = float(i) / rows * ofGetWidth();
            float y = float(j) / cols * ofGetHeight();
            float w = (float)ofGetWidth() / (float)rows;
            float h = (float)ofGetHeight() / (float)cols;
            
            int xPix = ofMap(i, 0, rows-1, 0, img.getWidth()-1, true);
            int yPix = ofMap(j, 0, cols-1, 0, img.getHeight()-1, true);
            
            float red = 0;
            float green = 0;
            float blue = 0;
            
            int endX = (xPix + floor(w) < img.getWidth()) ? xPix + floor(w) : img.getWidth();
            int endY = (yPix + floor(h) < img.getHeight()) ? yPix + floor(h) : img.getHeight();
            
            for ( int k = xPix; k < endX; k++ ) {
                for ( int l = yPix; l < endY; l++ ) {
                    int index = (l * img.getWidth() + k) * 3;
                    red+= pixels[index];
                    green+= pixels[index+1];
                    blue+= pixels[index+2];
                }
            }
            
            red /= (w * h);
            green /= (w * h);
            blue /= (w * h);
            
//            ofSetColor(red, 0, 0);
//            ofRect(x, y, w/3, h);
//            
//            ofSetColor(0, green, 0);
//            ofRect(x+w/3, y, w/3, h);
//            
//            ofSetColor(0, 0, blue);
//            ofRect(x+(w/3*2), y, w/3, h);
            
            ofSetColor(red, green, 0);
            ofRect(x, y, w, h);
            
           
            ofPushMatrix();
            ofTranslate(x + w/2, y + h);
            ofRotateZ((int)(i*j + ofGetElapsedTimef() * 50) % 360);
            ofTranslate(-(x + w/2), -(y + h));
            ofSetColor(red, 0, blue);
            ofTriangle(x + w/2, y, x, y + h, x + w, y + h);
            ofPopMatrix();
            
            ofSetColor(0, green, blue);
            ofCircle(x + w/2, y+ h/2, (w + h) / 8);
    
            
            
            
//            int index = (yPix * img.getWidth() + xPix) * 3;
//            ofSetColor(pixels[index], pixels[index+1], pixels[index+2]);
            

        }
    }
   
    ofSetColor(255);
    ofDrawBitmapString("mousex=" + ofToString(mouseX) + " mousey=" + ofToString(mouseY), 100, 100);
                       
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
        rows = ofMap(x, 0, ofGetWidth(), 1, img.getWidth(), true);
        cols = ofMap(y, 0, ofGetHeight(), 1, img.getHeight(), true);

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
