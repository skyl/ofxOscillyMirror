#include "ofApp.h"

void ofApp::setup(){

	int camWidth = ofGetWidth();
	int camHeight = ofGetHeight();
	camera.initGrabber(camWidth, camHeight);

	videoInverted.allocate(camWidth, camHeight, OF_PIXELS_RGB);
	videoTexture.allocate(videoInverted);
	ofSetVerticalSync(true);

	int bufferSize = 512;
	int sampleRate = 44100;

	left.assign(bufferSize, 0.0);
	right.assign(bufferSize, 0.0);
	mono.assign(bufferSize, 0.0);

	ofSoundStreamSettings settings;
	// or by name
	auto devices = soundStream.getMatchingDevices("default");
	if(!devices.empty()){
		settings.setInDevice(devices[0]);
		settings.setOutDevice(devices[0]);
	}
	settings.setInListener(this);
	settings.setOutListener(this);
	settings.sampleRate = sampleRate;
	settings.numOutputChannels = 2;
	settings.numInputChannels = 2;
	settings.bufferSize = bufferSize;
	soundStream.setup(settings);

}

//--------------------------------------------------------------
void ofApp::update(){
	camera.update();

	int width = camera.getWidth();
	int height = camera.getHeight();



	// if(camera.isFrameNew()){
	ofPixels & pixels = camera.getPixels();
	for(int i = 0; i < pixels.size(); i++){

		int x = (i / 3) % width;
		int y = (i / 3) / width;

		float monoAtY = mono[ofMap(y, 0, height, 0, 512)];
		// color of pixel monoAtY displaced on x from this pixel
		int diffX = x - ofClamp(x + (width * monoAtY), 0, width);

		// if ((x > width / 2) && (y > height / 2)) {
		//     videoInverted[i] = 255 - pixels[i];
		// } else {
		// 	videoInverted[i] = pixels[i];
		// }
		if (
			(toggle0 && i % 3 == 0) ||
			(toggle1 && i % 3 == 1) ||
			(toggle2 && i % 3 == 2)
		) {
			videoInverted[i] = pixels[i + (diffX * 3)];
		} else {
			videoInverted[i] = pixels[i];
		}
	}



	//load the inverted pixels
	videoTexture.loadData(videoInverted);
	// }
}

//--------------------------------------------------------------
void ofApp::draw(){
	videoTexture.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::audioIn(ofSoundBuffer & input){
	sb = input;
	for (int i = 0; i < input.getNumFrames(); i++){
		left[i] = input[i*2];
		right[i] = input[i*2+1];
		mono[i] = (left[i] + right[i]) / 2;
	}
}

//--------------------------------------------------------------
void ofApp::audioOut(ofSoundBuffer & buffer){
	// route sound to the output
	// buffer = sb;
}



//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if( key == 'f' ){
		int mode = ofGetWindowMode();

		if (mode == OF_WINDOW) {
		    ofSetFullscreen(1);
		} else if (mode == OF_FULLSCREEN){
			ofSetFullscreen(0);
		}
	}

	if( key == '1' ){
		toggle0 = !toggle0;
	}
	if( key == '2'){
		toggle1 = !toggle1;
	}
	if( key == '3' ){
		toggle2 = !toggle2;
	}
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
