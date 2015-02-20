#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    w = ofGetScreenWidth(); h = ofGetScreenHeight();
    ofSetWindowShape(w, h);
    ofSetFullscreen(true);
    
    browserW = 800; browserH = 600;
    browser.setup(browserW,browserH);
    browserPos = ofVec2f(w/2 - browser.getWidth()/2,h/2 - browser.getHeight()/2);
    browser.loadURL("http://www.facebook.com");
    
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
    
    resultImage.allocate(camW, camH);
    
    artk.setup(camW, camH);
    threshold = 85;
    artk.setThreshold(threshold);
    
    ofSetLogLevel(OF_LOG_NOTICE);
}

//--------------------------------------------------------------
void ofApp::update(){
    ofxAwesomium::updateCore();
    browser.update();
    
    cam.update();
    if(cam.isFrameNew()) {
        colorImage.setFromPixels(cam.getPixels(), camW, camH);
        grayImage = colorImage;
        
        //grayImage.mirror(false, true); //do this if using mirror
        grayImage.threshold(mouseX);
        artk.update(grayImage.getPixels());
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255);
    
    //===========================================================
    // ARTK + BROWSER
    //===========================================================
    int numMarkers = artk.getNumDetectedMarkers();
    
    ofSetColor(255);
    grayImage.draw(0, 0, camW/4, camH/4);
    ofSetHexColor(0x666666);
    ofDrawBitmapString(ofToString(numMarkers) + " marker(s) found", 10, 20);
    artk.draw(0, 0, camW/2, camH/2);
    
    ofSetColor(255);
    browser.draw(browserPos.x, browserPos.y);
    
    if(numMarkers == 4) {
        vector<cv::Point2f> centers;
        vector<cv::Point2f> orderedCenters;
        for(int i = 0; i < numMarkers; i++) {
            ofPoint pt = artk.getDetectedMarkerCenter(i);
            centers.push_back(cv::Point2f(pt.x,pt.y));
        }
        
        orderedCenters.push_back(centers[0]);
        orderedCenters.push_back(centers[1]);
        orderedCenters.push_back(centers[3]);
        orderedCenters.push_back(centers[2]);
        
        ofImage r; r.allocate(camW, camH, OF_IMAGE_COLOR);
        ofxCv::unwarpPerspective(colorImage, r, orderedCenters);
        resultImage.setFromPixels(r.getPixelsRef());
        resultImage.draw(w/2 - browserW/2,h/2 - browserH/2,browserW, browserH);
    }
    
    //===========================================================
    // MARKERS
    //===========================================================
    ofSetColor(255);
    ofSetRectMode(OF_RECTMODE_CENTER);
    float scale = 1.3;
    ofFill();
    ofRect(browserPos.x, browserPos.y,m1.getWidth()*scale, m1.getHeight()*scale);
    ofRect(browserPos.x+browserW, browserPos.y,m1.getWidth()*scale, m1.getHeight()*scale);
    ofRect(browserPos.x, browserPos.y+browserH,m1.getWidth()*scale, m1.getHeight()*scale);
    ofRect(browserPos.x+browserW, browserPos.y+browserH,m1.getWidth()*scale, m1.getHeight()*scale);
    
    
    if(mouseDown) ofEllipse(mouseX, mouseY, 50, 50);
    
    ofSetRectMode(OF_RECTMODE_CORNER);
    m1.draw(browserPos.x - m1.getWidth()/2, browserPos.y - m1.getHeight()/2);
    m2.draw(browserPos.x + browserW - m1.getWidth()/2, browserPos.y - m1.getHeight()/2);
    m3.draw(browserPos.x - m3.getWidth()/2, browserPos.y + browserH - m1.getHeight()/2);
    m4.draw(browserPos.x + browserW - m1.getWidth()/2, browserPos.y + browserH - m1.getHeight()/2);
    
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
    mouseDown = true;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    mouseDown = false;
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
