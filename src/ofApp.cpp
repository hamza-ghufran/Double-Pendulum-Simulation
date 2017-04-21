#include "ofApp.h"

Bob Upperbob(10);
Bob Lowerbob(10);

Bob::Bob(float _mass) {
	//Initialize the location
	//initial angle, angularVelocity & angularAcceleration
	angle = PI / 1.1;
	angularVelocity = 0.0;
	angularAcceleration = 0.0;
	mass = _mass;
	gravity = 0.4;
}

void Bob::display() {

	ofColor(175, 20);
	ofDrawEllipse(location.x, location.y, 2 * mass, 2 * mass);
}

void Bob::update(float calculatedAcceleration, ofVec2f origin, float length) {

		angularAcceleration = calculatedAcceleration;
		angularVelocity += angularAcceleration;
		angle += angularVelocity;
	
	angularVelocity *= 0.993;
	//Polar to Cartesian (length=r)
	location.set(length*sin(angle), length*cos(angle));
	location += origin;
}

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(150);
	ofSetFrameRate(60);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
