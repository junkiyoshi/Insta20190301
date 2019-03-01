#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);
	ofNoFill();
	ofSetLineWidth(3);

	this->font.loadFont("fonts/Kazesawa-Bold.ttf", 450, true, true, true);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	string word = "A";
	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	auto path_list = this->font.getStringAsPoints(word, true, false);
	for (int point_index = 0; point_index < path_list.size(); point_index++) {

		auto outline = path_list[point_index].getOutline();
		ofBeginShape();
		for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

			if (outline_index != 0) { ofNextContour(true); }

			outline[outline_index] = outline[outline_index].getResampledByCount(300);
			auto vertices = outline[outline_index].getVertices();
			for (int vertices_index = 0; vertices_index < vertices.size(); vertices_index++) {

				auto point = glm::vec2(vertices[vertices_index].x - this->font.stringWidth(word) * 0.5, vertices[vertices_index].y + this->font.stringHeight(word) * 0.5);
				auto noise_value = ofNoise(point.x * 0.03, point.y * 0.03, ofGetFrameNum() * 0.05);
				if (noise_value > 0.7) {

					noise_value = ofMap(noise_value, 0.7, 1.0, 1.0, 1.35);
				}
				else if (noise_value < 0.3) {

					noise_value = ofMap(noise_value, 0.0, 0.3, 0.65, 1.0);
				}
				else {

					noise_value = 1.0;
				}

				point *= noise_value;

				ofVertex(point);
			}
		}
		ofEndShape(true);
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}