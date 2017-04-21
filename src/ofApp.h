#pragma once

#include "ofMain.h"
#include "ofxGui.h"
class Bob {

public:
	float angularVelocity;
	float angle;
	float angularAcceleration;
	float mass;
	float gravity;
	bool dragging = false;
	float mx, my;

	ofVec2f location;
	vector<ofPoint> points;
	ofVec2f point;

	Bob(float _mass);
	void display();
	void update(float calculatedAcceleration, ofVec2f origin, float length);
	void trails();
	void changeinmass(float _slidermass);

	void check(float x, float y);
	void drag();
	void stopDrag();

};

//__________________________________________________________________________________________________________________________________________

class Pendulum {

public:
	float length;
	float gravity = 0.4;
	float damping = 0.999;
	ofVec2f origin;
	float upperLength;
	float lowerLength;


	Pendulum(float _upperlength, float _lowerlength);
	void go();
	void display();
	void update();
	void changeinlength(float _length1, float _length2);

	float UpperPendulumAcceleration();
	float LowerPendulumAcceleration();

};

//____________________________________________________________________________________________________________________________________________

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		
		ofxFloatSlider uppermass;
		ofxFloatSlider lowermass;
		ofxFloatSlider upperlength;
		ofxFloatSlider lowerlength;
		ofxPanel GUI;
		ofxToggle trail;
		ofxToggle airFriction;
		
};
