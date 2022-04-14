#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

        float sineTime;
        float noiseTime;
        int numWaveVertices;
        
    void waveGenerator(int x, int y, float waveHeight, float shapeDepth, float noiseResolution, float noiseOffset);
};
