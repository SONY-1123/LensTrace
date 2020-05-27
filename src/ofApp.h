#pragma once

#include "ofMain.h"
#include <vector>

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
		int i, size;
		double n, d, bf, t, ys, ye, xe,xc,yc,stof; 
		
		double arg,arg2,arg3,argi,arga;
		double L, ex, ey, S, k, a, b, c, xp, yp,x1,y1,x2,y2;
		double n1, n2, n3;
		double xts, xte;
		double x[11], y[11], yd[11];
		double yn[11];
		bool	bSmooth;
};
