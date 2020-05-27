/*
�Q�lHP

�~�̐ڐ������߂����:https://mathtrain.jp/ennosessen
�G�N�Z����p�����~�ƒ����̌�_�v�Z:http://godfoot.world.coocan.jp/circle-line.htm


*/



#include "ofApp.h"
#include "ofMath.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//xe = ye / tan(arg * PI / 180);
	//n:�c���}�X�� d:�����Y���ʕ��܂ł̋��� bf:�����Y���ʕ�����̏œ_���� t:�����Y���� ys:���ˌ��J�ny 
	//ye,xe:���ˌ��̌�����y,x xc,yc:�����Y�~���Sx,y n1,n2,n3:���ܗ��@size:���ˌ��{���@stof:�X�^�[�g�I�t�Z�b�g
	ofBackground(0);
	ofEnableAntiAliasing();
	bSmooth = false;
	n = 700;
	d = 350;
	bf = 200;
	t = 50;
	ys = 0;
	ye = n/2;
	xe = d;
	xc = d+bf;
	yc = n / 2;
	n1 = 1.0003;
	n2 = 1.4585;
	n3 = 1.0003;
	size = 11;
	stof = 0;
	
}

//--------------------------------------------------------------
void ofApp::update(){
	for (int i = 0; i < size; i++) {
		ys = 20 * i+stof;
		ye = (n/2-5*5) + 5*i;
		L = sqrt((xe * xe) + ((ye - ys) * (ye - ys)));
		ex = xe / L;
		ey = (ye - ys) / L;
		a = ye - ys;
		b = -xe;
		c = -(b * ys);
		k = -(a * xc + yc * b + c) / (b * ex - a * ey);
		S = sqrt(((bf + t) * (bf + t)) - (k * k));
		xp = xc - k * ey;
		yp = yc + k * ex;

		x[i] = xp - S * ex;
		y[i] = yp - S * ey;
		//�~�Ɠ��ˌ��̐ړ_

		x2 = xp + S * ex;
		y2 = yp + S * ey;
		if (x2 < x[i]) {
			x[i] = x2;
			y[i] = y2;
		}

		xts = (((bf + t) * (bf + t)) - (y[i] - (n / 2)) * (0 - (n / 2))) / (x[i] - (d + bf)) + (d + bf);
		xte = (((bf + t) * (bf + t)) - (y[i] - (n / 2)) * (n - (n / 2))) / (x[i] - (d + bf)) + (d + bf);
		arg = PI / 2 - acos(abs(((ys - (n / 2)) * n) + (d * (xts - xte))) / (sqrt((ys - (n / 2)) * (ys - (n / 2)) + d * d) * sqrt(n * n + (xts - xte) * (xts - xte))));
		arg2 = asin(n1 / n2 * sin(arg));
		//arg2:�ڐ��̐���������̋��܌�̊p�x�A��C�����烌���Y��

		if (ys < n / 2) {
			argi = atan((ye - ys) / (double)(xe));
		}
		else {
			argi = atan((ys - ye) / (double)xe);
		}

		arga = argi - (arg - arg2);

		if (ys < n / 2) {
			yd[i] = y[i] + (d - x[i]) * tan(arga);
		}
		else {
			yd[i] = y[i] - (d - x[i]) * tan(arga);
		}

		//�ȉ��Aarg:�����Y�����C���ւ̓��ˊp arg2:���܊p
		if (yd[i]>=y[i]) {//�ォ��
			arg = atan((yd[i] - y[i]) / (double)(d - x[i]));
			arg2 = asin(n3 / n2 * sin(arg));
			yn[i] = yd[i] + (n - d) * tan(arg2);
		}

		if (yd[i] < y[i]) {//������
			arg = atan((y[i] - yd[i]) / (double)(d - x[i]));
			arg2 = asin(n3 /n2 * sin(arg));
			yn[i] = yd[i] - (n - d) * tan(arg2);
		}
		//printf("\n\nargtest:%lf\n\n",atan(3/20.0));



		if (x[i] > d) { //�����Y�O�ɓ��˂����ꍇ�̏���
			x[i] = NULL;
			y[i] = NULL;
			yd[i] = NULL;
			yn[i] = NULL;
		}
//		printf("\n");
//		printf("xs:0,ys:%lf\n", ys);
//		printf("x[i]:%lf,y[i]:%lf\n", x[i], y[i]);
//		printf("d:%lf,yd[i]:%lf\n", d, yd[i]);
//		printf("n:%lf,yn[i]:%lf\n", n, yn[i]);
//		printf("arg:%lf,arg2:%lf\n", arg, arg2);

//		printf("i:%d\n", i);
	}

	

}

//--------------------------------------------------------------
void ofApp::draw(){
	

	ofSetColor(0, 20, 255);
	ofCircle(d+bf, n/2, t+bf);
	ofSetColor(0, 0, 0);
	ofDrawRectangle(d, 0, d+bf, n);

	ofSetColor(255, 255, 255);
	ofDrawLine(1, 1, n, 1);
	ofDrawLine(1, 1, 1, n);
	ofDrawLine(1, n, n, n);
	ofDrawLine(n, 1, n, n);


	for (int i = 1; i < size; i++) {
		ys = 20 * i+stof;
		ofDrawLine(0, ys, x[i], y[i]);
		//ofDrawLine(xts, 0, xte, n);
		ofDrawLine(x[i], y[i], d, yd[i]);
		ofDrawLine(d,yd[i],n,yn[i]);
	}

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 's') {
		bSmooth = !bSmooth;
		if (bSmooth) {
			ofEnableAntiAliasing();
		}
		else {
			ofDisableAntiAliasing();
		}
	}

	if (key == 'n') {
		stof += 30;
		if (stof > 500) {
			stof = 0;
		}
	}


	//if (key == 'n') {
	//	ye += 5;
	//	if (ye > 315) {
	//		ye = 185;
	//	}
		
	//}
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
