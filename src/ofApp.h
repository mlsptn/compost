#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxARToolkitPlus.h"
#include "ofxAwesomium.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        int camW;
        int camH;
        int w,h;
        int browserW, browserH;
        int threshold;
    
        ofVec2f browserPos;
        ofxAwesomium browser;
    
        ofVideoGrabber cam;
        ofxARToolkitPlus artk;
    
        ofImage m1, m2, m3, m4;
    
        ofxCvColorImage colorImage;
        ofxCvGrayscaleImage grayImage;
		
};
