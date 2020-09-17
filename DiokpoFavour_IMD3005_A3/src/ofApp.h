#pragma once

//May want to look here: https://developer.leapmotion.com/documentation/v4/group___structs.html#struct_l_e_a_p___h_a_n_d 

#include "ofMain.h"
#include "ofxLeapC.h"
#include <stdlib.h>
#include <time.h> 
#include "Laser.h"
#include "ProjectConstants.h"



class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void onLeapFrame(Leap::Frame frame);

		ofxLeapC::Device		m_device;
		Leap::Frame				m_frame;

		ofVec3f					m_palmPos;
		ofVec3f					m_palmRot;
		float					m_pinchStrength;
		float					m_grabStrength;
        float					m_grabAngle;
		ofImage					m_ship;
        ofImage					m_man;

        ofImage                 m_background;
        ofVec2f                 m_backgroundPos;

        ofImage                 m_sunset;
        ofVec2f                 m_sunsetPos;

        ofImage                 m_secret;
        ofVec2f                 m_secretPos;

        ofImage                 m_instruct;
        ofVec2f                 m_instructPos;

        ofImage                 m_meteorB;
        ofImage                 m_meteorP;
        ofImage                 m_meteorB1;
        ofImage                 m_meteorP1;
        ofImage                 m_meteorB2;
        ofImage                 m_meteorP2;


        ofVec2f                 m_meteorBpos;
        ofVec2f                 m_meteorPpos;
        ofVec2f                 m_meteorB1pos;
        ofVec2f                 m_meteorP1pos;
        ofVec2f                 m_meteorB2pos;
        ofVec2f                 m_meteorP2pos;


		ofFloatColor			m_bgCol;
};
