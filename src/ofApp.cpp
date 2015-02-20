#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    w = ofGetScreenWidth(); h = ofGetScreenHeight();
    ofSetWindowShape(w, h);
    ofSetFullscreen(true);
    
    browserW = 600; browserH = 400;
    browser.setup(browserW,browserH);
    browserPos = ofVec2f(w/2 - browser.getWidth()/2,h/2 - browser.getHeight()/2);
    browser.loadURL("http://partsparts.parts");
    
    m1.loadImage("1.png"); m2.loadImage("2.png");
    m3.loadImage("3.png"); m4.loadImage("4.png");
    
    int mScale = 3;
    
    m1.resize(m1.getWidth()*mScale, m1.getHeight()*mScale);
    m2.resize(m2.getWidth()*mScale, m2.getHeight()*mScale);
    m3.resize(m3.getWidth()*mScale, m3.getHeight()*mScale);
    m4.resize(m4.getWidth()*mScale, m4.getHeight()*mScale);
    
    camW = 640; camH = 480;
    cam.setDeviceID(1);
    cam.initGrabber(camW, camH);
    
    artk.setup(camW, camH);
    threshold = 85;
    artk.setThreshold(threshold);
}

//--------------------------------------------------------------
void ofApp::update(){
    ofxAwesomium::updateCore();
    browser.update();
    
    cam.update();
    if(cam.isFrameNew()) {
        colorImage.setFromPixels(cam.getPixels(), camW, camH);
        grayImage = colorImage;
        grayImage.threshold(mouseX);
        //TODO: threshold image
        artk.update(grayImage.getPixels());
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    //===========================================================
    // BROWSER
    //===========================================================
    ofBackground(255);
    ofSetColor(255);
    m1.draw(browserPos.x - m1.getWidth()/2, browserPos.y - m1.getHeight());
    m2.draw(browserPos.x + browserW - m1.getWidth()/2, browserPos.y - m2.getHeight());
    m3.draw(browserPos.x - m3.getWidth()/2, browserPos.y + browserH);
    m4.draw(browserPos.x + browserW - m1.getWidth()/2, browserPos.y + browserH);
    
    browser.draw(browserPos.x, browserPos.y);
    
    //===========================================================
    // ARTK
    //===========================================================
    ofSetColor(255);
    grayImage.draw(0, 0, camW/2, camH/2);
    ofSetHexColor(0x666666);
    ofDrawBitmapString(ofToString(artk.getNumDetectedMarkers()) + " marker(s) found", 10, 20);
    artk.draw(0, 0, camW/2, camH/2);
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
