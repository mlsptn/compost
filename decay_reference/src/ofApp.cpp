#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    w = ofGetScreenWidth(); h = ofGetScreenHeight();
    ofSetWindowShape(w, h);
    
    img.loadImage("test.png");
    img.resize(img.getWidth()/2,img.getHeight()/2);
    iw = img.getWidth(); ih = img.getHeight();
    
    m1.loadImage("1.png"); m2.loadImage("2.png");
    m3.loadImage("3.png"); m4.loadImage("4.png");

    int mScale = 3;
    
    m1.resize(m1.getWidth()*mScale, m1.getHeight()*mScale);
    m2.resize(m2.getWidth()*mScale, m2.getHeight()*mScale);
    m3.resize(m3.getWidth()*mScale, m3.getHeight()*mScale);
    m4.resize(m4.getWidth()*mScale, m4.getHeight()*mScale);
    
    cam.initGrabber(camW, camH);
    
    artk.setup(camW, camH);
    threshold = 85;
    artk.setThreshold(threshold);
}

//--------------------------------------------------------------
void ofApp::update(){
    cam.update();
    if(cam.isFrameNew()) {
        colorImage.setFromPixels(cam.getPixels(), camW, camH);
        grayImage = colorImage;
        grayImage.mirror(false, true);
        artk.update(grayImage.getPixels());
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofBackground(255);
    
    ofPushMatrix();
        ofTranslate(280,0);
        ofSetHexColor(0xffffff);
        ofVec2f imgPos = ofVec2f(w/2-iw/2, h/3-ih/2);
        
        m1.draw(imgPos.x - m1.getWidth()/2, imgPos.y - m1.getHeight());
        m2.draw(imgPos.x + iw - m1.getWidth()/2, imgPos.y - m2.getHeight());
        m3.draw(imgPos.x - m3.getWidth()/2, imgPos.y + ih);
        m4.draw(imgPos.x + iw - m1.getWidth()/2, imgPos.y + ih);
        
        img.draw(imgPos.x, imgPos.y);
    ofPopMatrix();
    
    //===========================================================
    
    
	// Threshold image
	ofSetHexColor(0xffffff);
	grayImage.draw(0, 0);
	ofSetHexColor(0x666666);
    ofDrawBitmapString(ofToString(artk.getNumDetectedMarkers()) + " marker(s) found", 10, 20);
    artk.draw(0, 0);

    //===========================================================

    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
