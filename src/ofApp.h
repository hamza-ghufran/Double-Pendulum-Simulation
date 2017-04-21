#pragma once

#include "ofMain.h"
class Bob {

public:
	float angularVelocity;
	float angle;
	float angularAcceleration;
	float mass;
	float gravity;

	ofVec2f location;
	
	Bob(float _mass);
	void display();
	void update(float calculatedAcceleration, ofVec2f origin, float length);
	

};

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
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
};
