#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetFrameRate(60);
    ofSetBackgroundColor(ofColor(255));
    
    sineTime = 0;
    noiseTime = 0;
    numWaveVertices = 200;
}

//--------------------------------------------------------------
void ofApp::update() {
    sineTime += 0.005;
    noiseTime += 0.01;
}

//--------------------------------------------------------------
void ofApp::draw() {
    float sine = sin(sineTime);
    float colorTransition = ofMap(sine,-1,1,0,1);
    
    ofColor firstBgColor = ofColor(33, 32, 56);
    ofColor secondBgColor = ofColor(24, 23, 68);
    ofColor thirdBgColor = ofColor(67, 66, 89);
    ofColor yellowWave = ofColor(248, 252, 184, 240);
    ofColor fog = ofColor(231, 232, 211, 240);
    
    // Background
    ofSetColor(firstBgColor.getLerped(secondBgColor, colorTransition));
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    
    // Waves
    ofPushMatrix();
    ofPushStyle();
    
    float mainWaveX = 0;
    float mainWaveDepth = 520;
    float mainWaveY = ofGetHeight() - mainWaveDepth;
    
    float altWaveX = 0;
    float altWaveDepth = 400;
    float altWaveY = ofGetHeight() - altWaveDepth;
    
    // Fog Wave
    ofSetColor(fog);
    waveGenerator(0, 365, 100, 300, 0.03, 400);

    // Yellow Wave
    ofSetColor(yellowWave);
    waveGenerator(mainWaveX, mainWaveY - 90, 600, mainWaveDepth, 0.04, 800);
    
    // Purple Wave
    ofSetColor(thirdBgColor.getLerped(ofColor(48, 46, 77), colorTransition));
    waveGenerator(altWaveX, altWaveY, 100, altWaveDepth, 0.03, 200);
    
    // Fog Wave
    ofSetColor(fog);
    waveGenerator(mainWaveX, ofGetHeight() - 255, 100, 300, 0.03, 200);
   
    // Blue Wave
    ofSetColor(184, 248, 240, 240);
    waveGenerator(mainWaveX, mainWaveY + 170, 300, altWaveDepth, 0.05, 800);
   
    // Dark Blue Wave
    ofSetColor(firstBgColor.getLerped(ofColor(24, 23, 38), colorTransition));
    waveGenerator(mainWaveX, ofGetHeight() - 250, 100, altWaveDepth, 0.03, 400);
    
    // Blue Overlay Wave
    ofSetColor(39, 69, 204, 80);
    waveGenerator(mainWaveX, mainWaveY - 50, 100, mainWaveDepth + 100, .08, 50);
    
    // Red Overlay Wave
    ofSetColor(223, 39, 24, 80);
    waveGenerator(mainWaveX, ofGetHeight() - 160, 100, mainWaveDepth + 100, .08, 900);
    
    ofPopStyle();
    ofPopMatrix();

    
    // Moon
    float waveHeight = 100;
    float noiseOffset = 500;
    float noiseResolution = 0.15;
    float value = noiseResolution + noiseOffset;
    float noise = ofNoise(value + noiseTime) * waveHeight;

    ofSetCircleResolution(12);
    ofSetColor(82, 64, 112, 100);
    ofDrawCircle(120, noise + 80, 50);
    
    ofSetColor(82, 64, 112, 120);
    ofDrawCircle(120, noise + 80, 45);
    
    ofNoFill();
    ofSetColor(52, 47, 74, 240);
    ofDrawCircle(120, noise + 80, 52);
    
    ofFill();
    ofSetColor(163, 49, 102, 20);
    ofDrawCircle(120, noise + 78, 38);
    
    ofSetColor(183, 49, 152, 30);
    ofDrawCircle(128, noise + 70, 20);
    
    ofSetColor(183, 49, 152, 30);
    ofDrawCircle(135, noise + 65, 5);
}

void ofApp::waveGenerator(int x, int y, float waveHeight, float shapeDepth, float noiseResolution, float noiseOffset) {
    ofPushMatrix();
    ofTranslate(x,y);

    float stepSize = ofGetWidth() / float(numWaveVertices);

    ofBeginShape();
    ofVertex(0, shapeDepth);
    for (int i=0; i<=numWaveVertices; i++)
    {
        float value = i*noiseResolution+noiseOffset;
        float noise = ofNoise(value+noiseTime) * waveHeight;
        ofVertex(i*stepSize,noise);
    }
    ofVertex(ofGetWidth(), shapeDepth);
    ofEndShape();
    ofPopMatrix();
}
