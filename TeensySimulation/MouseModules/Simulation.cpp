/*
 * Simulation.cpp
 *
 *  Created on: 17 May 2021
 *      Author: David(Yong eel) Lee
 *      Cited from     Author: Mack / mackorone
 */
#include <Mice.h>
#include <BrainConfig.h>

#include <String.h>

#include <Simulation.h>

Simulation::Simulation() {
	// TODO Auto-generated constructor stub

}

Simulation::~Simulation() {
	// TODO Auto-generated destructor stub
}

// ----- API -----
void Simulation::log( char * message) {
 //   printf("log %s\n" , message );
    Serial.print("log " + String(message) + "\n");
}

int Simulation::mazeWidth() {
    return getInteger((char *) "mazeWidth");
}

int Simulation::mazeHeight() {
    return getInteger((char *) "mazeHeight");
}

bool Simulation::FrontWallFront(int halfStepsAway) {
	char buf[30];
	sprintf(buf, "wallFront %d", halfStepsAway);
    return getBoolean((char *) buf);
}

bool Simulation::FrontWallRight(int halfStepsAway) {
	char buf[30];
	sprintf(buf, "wallFrontRight %d", halfStepsAway);
    return getBoolean((char *) buf);
}

bool Simulation::FrontWallLeft(int halfStepsAway) {
	char buf[30];
	sprintf(buf, "wallFrontLeft %d", halfStepsAway);
    return getBoolean((char *) buf);
}

bool Simulation::wallFront() {
    return getBoolean((char *) "wallFront");
}

bool Simulation::wallRight() {
    return getBoolean((char *) "wallRight");
}

bool Simulation::wallLeft() {
    return getBoolean((char *) "wallLeft");
}

bool Simulation::BackWallBack(int halfStepsAway) {
	char buf[30];
	sprintf(buf, "wallBack %d", halfStepsAway);
    return getBoolean((char *) buf);
}

bool Simulation::BackWallRight(int halfStepsAway) {
	char buf[30];
	sprintf(buf, "wallBackRight %d", halfStepsAway);
    return getBoolean((char *) buf);
}

bool Simulation::BackWallLeft(int halfStepsAway) {
	char buf[30];
	sprintf(buf, "wallBackLeft %d", halfStepsAway);
    return getBoolean((char *) buf);
}

bool Simulation::moveFullForward(short distance) {
	char buf[30];
	if( distance == 0 ) return false;
	sprintf(buf, "moveForward %d", distance);
	getAck((char *) buf);
	return true;
}

bool Simulation::moveHalfForward(short numHalfSteps) {
	char buf[30];
	sprintf(buf, "moveForwardHalf %d", numHalfSteps);
	getAck((char *) buf);
    return true;
}

bool Simulation::moveEdgeForward(short numHalfSteps) {
	char buf[30];
	sprintf(buf, "moveForwardHalf %d", numHalfSteps);
	getAck((char *) buf);
    return	 true;
}

void Simulation::runRight() {
    getAck((char *) "curveTurnRight");
}

void Simulation::runLeft() {
    getAck((char *) "curveTurnLeft");
}

void Simulation::turnRight90() {
    getAck((char *) "turnRight90");
}

void Simulation::turnLeft90() {
    getAck((char *) "turnLeft90");
}

void Simulation::turnRight45() {
    getAck((char *) "turnRight45");
}

void Simulation::turnLeft45() {
    getAck((char *) "turnLeft45");
}

void Simulation::turnBack() {
    getAck((char *) "turnBack");
}

void Simulation::completeRun() {
    getAck((char *) "completeRun");
}

void Simulation::setWall(int x, int y, char direction) {
    //printf("setWall %d %d %c\n", x ,y, direction  );
    Serial.print(
        "setWall "
        + String(x) + " "
        + String(y) + " "
        + String(direction) + "\n"
    );    
}

void Simulation::clearWall(int x, int y, char direction) {
    //printf("clearWall %d %d %c\n", x ,y, direction  );
    Serial.print(
        "clearWall "
        + String(x) + " "
        + String(y) + " "
        + String(direction) + "\n"
    );    
}

void Simulation::setColor(int x, int y, char color) {
    //printf("setColor %d %d %c\n", x ,y, color  );
    Serial.print(
        "setColor "
        + String(x) + " "
        + String(y) + " "
        + String(color) + "\n"
    );    
}

void Simulation::clearColor(int x, int y) {
    //printf("clearColor %d %d\n", x ,y );
    Serial.print(
        "clearColor "
        + String(x) + " "
        + String(y) + "\n"
    );    
}

void Simulation::clearAllColor() {
    //printf("clearAllColor\n");
    Serial.print("clearAllColor\n");    
}

void Simulation::setText(int x, int y, char *text) {
  //  printf("setText %d %d %s\n", x ,y, (char *) text  );
    Serial.print(
        "setText "
        + String(x) + " "
        + String(y) + " "
        + String(text) + "\n"
    );    
}

void Simulation::clearText(int x, int y) {
    //printf("clearText %d %d\n", x ,y );
    Serial.print(
        "clearText "
        + String(x) + " "
        + String(y) + "\n"
    );    
}

void Simulation::clearAllText() {
    //printf("clearAllText\n");
    Serial.print("clearAllText\n");    
}

bool Simulation::wasReset() {
    return getBoolean((char *) "wasReset");
}

void Simulation::ackReset() {
    getAck((char *) "ackReset");
}

// ----- Helpers -----

char * Simulation::readline() {
//	static char buf[100];
//    scanf("%s", buf);
//    return (char *) &buf[0];

    String response = "";
    while (response == "") {
        response = Serial.readStringUntil('\n');
    }
    return (char *) response.c_str();
}

char * Simulation::communicate(char *command) {
    //printf("%s\n", (char *) command );
    Serial.print(String(command) + "\n");
    return readline();
}

bool Simulation::getAck( char * command) {
    char *response = communicate(command);
    return ( strcmp(response,"ack")  == 0 ? true : false );
}

bool Simulation::getBoolean( char * command) {
    char *response = communicate(command);
    return (strcmp(response, "true") == 0 ? true : false );
}

int Simulation::getInteger( char * command) {
    char *response = communicate(command);
    return atoi(response);
}
