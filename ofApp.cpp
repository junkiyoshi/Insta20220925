#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->mesh.clear();

	int span = 2;

	for (int z = 0; z >= -60; z -= 20) {

		for (int x = -360; x <= 360; x += span) {

			for (int y = -360; y <= 360; y += span) {

				auto noise_value = ofNoise(x * 0.005, y * 0.005 + ofGetFrameNum() * 0.02, z * 0.0015 + ofGetFrameNum() * 0.02);
				if (noise_value < 0.47 || noise_value > 0.53) { continue; }

				this->mesh.addVertex(glm::vec3(x, y, z));
				this->mesh.addVertex(glm::vec3(x + span, y, z));
				this->mesh.addVertex(glm::vec3(x + span, y + span, z));
				this->mesh.addVertex(glm::vec3(x, y + span, z));

				this->mesh.addIndex(this->mesh.getNumVertices() - 1); this->mesh.addIndex(this->mesh.getNumVertices() - 4); this->mesh.addIndex(this->mesh.getNumVertices() - 3);
				this->mesh.addIndex(this->mesh.getNumVertices() - 1); this->mesh.addIndex(this->mesh.getNumVertices() - 2); this->mesh.addIndex(this->mesh.getNumVertices() - 3);

				for (int i = 0; i < 4; i++) { this->mesh.addColor(ofColor(ofMap(z, -60, 0, 255, 32))); }
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);
	ofRotateX(180);

	this->mesh.draw();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}