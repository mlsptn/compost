#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxARToolkitPlus.h"

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
		
        int camW = 640;
        int camH = 480;
        int w, h;
        int iw, ih;
        ofImage img;
        ofImage m1, m2, m3, m4;
    
        ofVideoGrabber cam;
        ofxARToolkitPlus artk;
        int threshold;

        ofxCvColorImage colorImage;
        ofxCvGrayscaleImage grayImage;
};
