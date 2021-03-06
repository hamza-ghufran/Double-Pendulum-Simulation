#include "ofApp.h"

Bob Upperbob(10);
Bob Lowerbob(10);

//--------------------------------------------------------------

Bob::Bob(float _mass) {
	//Initialize the location
	//Initial angle, angularVelocity & angularAcceleration
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
	if (!dragging) {
		angularAcceleration = calculatedAcceleration;
		angularVelocity += angularAcceleration;
		angle += angularVelocity;
	}

	//Polar to Cartesian (length=r)

	location.set(length*sin(angle), length*cos(angle));
	location += origin;
}

void Bob::check(float x, float y) {

	float difference = ofDist(x, y, location.x, location.y);
	if (difference< mass) {
		dragging = true;
	}
}
void Bob::drag() {    
					  //While dragging we calculate the angle between the 
					  // pendulum location and mouse positio 	  
					  // we then convert from Cartesian to Polar 
	if (dragging) {
		ofVec2f mouse(mx, my);
		//ofVec2f diff = location - mouse;   // Difference between 2 points
		//issue here
		angle =mouse.angleRad(location);
		//angle= atan2(-1 * diff.y, diff.x) - ofDegToRad(90);// Angle relative to vertical axis
	}
}

void Bob::stopDrag() {
	angularVelocity = 0; // No velocity once you let go
	dragging = false;
}

void Bob::changeinmass(float _slidermass) {
	mass = _slidermass;
}

void Bob::trails() {
	//x,y location stored in a vector array
	points.push_back(location);

	for (int i = 0; i <= points.size(); i++) {
		point = points[i];
		ofDrawCircle(point.x, point.y, 1, 1);
	}
}

//--------------------------------------------------------------

Pendulum::Pendulum(float _upperLength, float _lowerLength) {

	upperLength = _upperLength;
	lowerLength = _lowerLength;
	origin.set(640/2, 150);
	
}

void Pendulum::go() {
	display();
	update();
	Upperbob.drag();
	
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
//Pass in length of Pendulum
Pendulum pendulum(50, 70);

void ofApp::setup(){
	ofBackground(150);
	ofSetFrameRate(60);

	
	GUI.setup();
	GUI.add(uppermass.setup("Upper Bob Mass", 10, 10, 40));
	GUI.add(lowermass.setup("Lower Bob Mass", 10, 2, 40));
	GUI.add(upperlength.setup("Upper String Length", 100, 20, 500));
	GUI.add(lowerlength.setup("Lower String Length", 60, 20, 500));

	GUI.add(trail.setup("TRAILS", true));
	GUI.add(airFriction.setup("Air Friction", false));
}

//--------------------------------------------------------------
void ofApp::update(){

	Lowerbob.changeinmass(lowermass);
	Upperbob.changeinmass(uppermass);
	pendulum.changeinlength(upperlength, lowerlength);
}

//--------------------------------------------------------------
void ofApp::draw(){

	ofDrawLine(640 / 2 - 20, 150, 640 / 2 + 20,150);
	

	GUI.draw();
	pendulum.go();
	if (trail == true) Lowerbob.trails();
	if (airFriction == true) { Lowerbob.angularVelocity *= 0.993; Upperbob.angularVelocity *= 0.993; }
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	Upperbob.mx = x;
	Upperbob.my = y;
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	Upperbob.check(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	Upperbob.stopDrag();
	Lowerbob.stopDrag();
}
