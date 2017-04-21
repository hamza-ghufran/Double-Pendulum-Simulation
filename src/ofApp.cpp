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



Pendulum::Pendulum(float _upperLength, float _lowerLength) {

	upperLength = _upperLength;
	lowerLength = _lowerLength;
	origin.set(640 / 2, 75);
}

void Pendulum::go() {

	display();
	update();
	
}

void Pendulum::display() {
	Upperbob.display();
	Lowerbob.display();

	ofDrawLine(origin.x, origin.y, Upperbob.location.x, Upperbob.location.y);
	ofDrawLine(Upperbob.location.x, Upperbob.location.y, Lowerbob.location.x, Lowerbob.location.y);
}

void Pendulum::update() {

	Upperbob.update(UpperPendulumAcceleration(), origin, upperLength);
	//since the lower bob is connected to the center of the upperbob
	// location of upper bob is passed as the origin
	Lowerbob.update(LowerPendulumAcceleration(), Upperbob.location, lowerLength);
}
void Pendulum::changeinlength(float _length1, float _length2) {

	upperLength = _length1;
	lowerLength = _length2;
}

float Pendulum::UpperPendulumAcceleration() {

	// derivative of angle with respect to time gives angular velocity
	// derivative of angular velocity with respect to time gives angular acceleration
	// high school physics, PFF

	// https://www.myphysicslab.com/pendulum/double-pendulum/double-pendulum-en.html 
	// Understanding The math behind the simulation. Above link.
	// With Runge Kutta method

	//Numerator of the equation
	//gravity taken as 0.4

	float NUM = -1 * 0.4*(2 * Upperbob.mass + Lowerbob.mass)*sin(Upperbob.angle) - Lowerbob.mass*0.4*sin(Upperbob.angle - (2 * Lowerbob.angle)) - 2 * (sin(Upperbob.angle - Lowerbob.angle))*Lowerbob.mass*((Lowerbob.angularVelocity*Lowerbob.angularVelocity)*lowerLength + (Upperbob.angularVelocity*Upperbob.angularVelocity)*upperLength*cos(Upperbob.angle - Lowerbob.angle));
	//Denominator
	float DENOM = upperLength*(2 * Upperbob.mass + Lowerbob.mass - Lowerbob.mass*cos(2 * Upperbob.angle - 2 * Lowerbob.angle));

	return (NUM / DENOM);
}

float Pendulum::LowerPendulumAcceleration() {

	float NUM = 2 * sin(Upperbob.angle - Lowerbob.angle)*((Upperbob.angularVelocity*Upperbob.angularVelocity)*upperLength*(Upperbob.mass + Lowerbob.mass) + 0.4*(Upperbob.mass + Lowerbob.mass)*cos(Upperbob.angle) + (Lowerbob.angularVelocity*Lowerbob.angularVelocity)*lowerLength*Lowerbob.mass*cos(Upperbob.angle - Lowerbob.angle));

	float DENOM = lowerLength*(2 * Upperbob.mass + Lowerbob.mass - Lowerbob.mass*cos(2 * Upperbob.angle - 2 * Lowerbob.angle));

	return (NUM / DENOM);
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
