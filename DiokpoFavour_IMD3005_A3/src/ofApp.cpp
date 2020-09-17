#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetRectMode(OF_RECTMODE_CENTER);

	m_device.connectEventHandler(&ofApp::onLeapFrame, this);
    m_background.loadImage("images/starbackground.png");

    
    //load images
	//m_man.load(ProjectConstants::IMG_PATH_SHIP);
    m_man.load(ProjectConstants::IMG_PATH_MAN);
    m_sunset.load(ProjectConstants::IMG_PATH_SUNSET);
    m_secret.load(ProjectConstants::IMG_PATH_SECRET);
    m_instruct.load(ProjectConstants::IMG_PATH_INSTRUCT);

    //background anchor point
    m_backgroundPos = ofVec2f(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
    m_sunsetPos = ofVec2f(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
    m_secretPos = ofVec2f(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
    m_instructPos = ofVec2f(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);

    //meteor load images
    m_meteorP.load(ProjectConstants::IMG_PATH_METEORP);
    m_meteorB.load(ProjectConstants::IMG_PATH_METEORB);
    m_meteorP1.load(ProjectConstants::IMG_PATH_METEORP);
    m_meteorB1.load(ProjectConstants::IMG_PATH_METEORB);
    m_meteorP2.load(ProjectConstants::IMG_PATH_METEORP);
    m_meteorB2.load(ProjectConstants::IMG_PATH_METEORB);


    //meteor load anchorpoint
    m_meteorBpos = ofVec2f(-15,-15);
    m_meteorPpos = ofVec2f(-15,-15);
    m_meteorB1pos = ofVec2f(-15,-15);
    m_meteorP1pos = ofVec2f(-15,-15);
    m_meteorB2pos = ofVec2f(-15,-15);
    m_meteorP2pos = ofVec2f(-15,-15);


	
	m_bgCol = ofFloatColor::white;		//make sure to initialize

	ofSetFrameRate(ProjectConstants::PROJ_DESIRED_FRAMERATE);
}



void ofApp::onLeapFrame(Leap::Frame frame)
{
	m_frame = frame;
}

//--------------------------------------------------------------
void ofApp::update()
{
	m_device.update();

	const Leap::HandList& hands = m_frame.hands();


	//	ofLogNotice( "OF_APP", "hand count: " + ofToString( hands.count() ) ); 

	for (int i = 0; i < hands.count(); ++i)
	{
        //make man bigger
		const Leap::Hand& hand = hands[i];
		const Leap::Vector palmPos			= hand.palmPosition();
		const ofVec3f ofPalmPos				= ofxLeapC::toVec3(hand.palmPosition());
		const ofVec3f ofStablizedPalmPos	= ofxLeapC::toVec3(hand.stabilizedPalmPosition());


		//get value of grab & pinch strength and grab angle (number between 0.0f and 1.0f)
		m_grabStrength	= hand.grabStrength();
		m_pinchStrength = hand.pinchStrength();
        m_grabAngle = hand.grabAngle();


		//get rotation from Leap data. Note that angles come in radians so we must convert
		m_palmRot = ofVec3f(
												ofRadToDeg( hand.direction().pitch() ),
												ofRadToDeg( hand.direction().yaw() ),
												ofRadToDeg( hand.direction().roll() )
											);

		//ofLogNotice("OF_APP", "ofPalmPos: "	+ ofToString(ofPalmPos));
		//ofLogNotice("OF_APP", "ofStablizedPalmPos: " + ofToString(ofStablizedPalmPos));
		//ofLogNotice("OF_APP", "ofPalmRot: " + ofToString(m_palmRot));

		cout << "pinchStrength: " << ofToString(m_pinchStrength) << ", grabStrength: " << ofToString(m_grabStrength) << ", grabAngle" << ofToString(m_grabAngle) << endl;

		//need to scale values. We do not use mapping as depending on the height of the hand teh boundaries change ( a frustum/come shape is visible to sensor so the lower the hand the less space to move in
		m_palmPos.x = ofPalmPos.x * 7.0f;
		m_palmPos.z = ofPalmPos.z * 5.0f;

		//now we need to set limits to screen so man can't disappear
		m_palmPos.x = ofClamp(m_palmPos.x, -(float)ProjectConstants::PROJ_WINDOW_RES_X / 2.0f, (float)ProjectConstants::PROJ_WINDOW_RES_X / 2.0f );
		m_palmPos.z = ofClamp(m_palmPos.z, -(float)ProjectConstants::PROJ_WINDOW_RES_Y / 2.0f, (float)ProjectConstants::PROJ_WINDOW_RES_Y / 2.0f);

		//now change coordinates to middle of screen
		//note how up and down is the Y-axis on Leap and in and out of screen is z-axis ... transposing from a 3D space to a 2D screen
		m_palmPos += ofVec3f((float)ProjectConstants::PROJ_WINDOW_RES_X / 2.0f, 0.0f, (float)ProjectConstants::PROJ_WINDOW_RES_Y / 2.0f);

		break; //only want one hand position so take the first detected as default ... perhaps a bit hacky. What is a better way?
	}
   
    //------------------------------------------------METEOR----------------------------------------------//

    m_meteorBpos.y += 6;
    m_meteorPpos.y += 2;
    m_meteorB1pos.y += 5;
    m_meteorP1pos.y += 8;
    m_meteorB2pos.y += 7;
    m_meteorP2pos.y += 4;


    if (m_grabStrength < 1) {
        m_meteorBpos.y = 0;
        m_meteorPpos.y = 0;
        m_meteorB1pos.y = 0;
        m_meteorP1pos.y = 0;
        m_meteorB2pos.y = 0;
        m_meteorP2pos.y = 0;

    }

  
}

//--------------------------------------------------------------
void ofApp::draw()
{
	//ofClear(oefFloatColor(m_grabStrength, 0.0f, 0.0f, 1.0f)); // when grabbing turn this color
    ofPushMatrix();
    ofTranslate(m_backgroundPos);
    m_background.draw(0.0f,0.0f);
    ofPopMatrix();


    //------------------------------------------------CHANGE BACKGROUND----------------------------------------------//   
    
    ofPushMatrix();
    if ((m_pinchStrength >= 1) ) {
        ofTranslate(m_sunsetPos);
        m_sunset.draw(0.0f, 0.0f);
    }
    else if (m_pinchStrength < 1) {
        ofTranslate(m_backgroundPos);
        m_background.draw(0.0f, 0.0f);
    }
    ofPopMatrix();

    ofPushMatrix();
    if ((m_grabAngle >= 2) && (m_pinchStrength < 0.2)) {
        ofTranslate(m_secretPos);
        m_secret.draw(0.0f, 0.0f);
    }
  
    ofPopMatrix();


    //------------------------------------------------METEOR SHOWER----------------------------------------------//

    ofPushMatrix();
    if ((m_grabStrength >= 1) ) {

        //draw pink meteor
        ofTranslate(m_meteorPpos);
        m_meteorP.draw(rand() % 805 + 13, 0.0f);

        ofTranslate(m_meteorP1pos);
        m_meteorP1.draw(rand() % 805 + 14, 0.0f);

        ofTranslate(m_meteorP2pos);
        m_meteorP2.draw(rand() % 805 + 15, 0.0f);


        //draw blue meteor 

        ofTranslate(m_meteorBpos);
        m_meteorB.draw(rand() % 805 + 10, 0.0f);

        ofTranslate(m_meteorB1pos);
        m_meteorB1.draw(rand() % 805 + 19, 0.0f);

        ofTranslate(m_meteorB2pos);
        m_meteorB2.draw(rand() % 805 + 20, 0.0f);
    }

        if (m_grabStrength < 1) {
            //remove pink meteor
            ofTranslate(m_meteorPpos);
            m_meteorP.draw(0.0f, 0.0f);

            ofTranslate(m_meteorP1pos);
            m_meteorP.draw(0.0f, 0.0f);

            ofTranslate(m_meteorP2pos);
            m_meteorP.draw(0.0f, 0.0f);


            //remove blue meteor 
            ofTranslate(m_meteorBpos);
            m_meteorB.draw(0.0f, 0.0f);

            ofTranslate(m_meteorB1pos);
            m_meteorB1.draw(0.0f, 0.0f);

            ofTranslate(m_meteorB2pos);
            m_meteorB2.draw(0.0f, 0.0f);

        }

        ofPopMatrix();

        //------------------------------------------------DRAW MAN----------------------------------------------//
    ofPushMatrix();

	ofTranslate(m_palmPos.x, m_palmPos.z);
	ofRotateZ(m_palmRot.y);
	ofScale(m_pinchStrength + 0.5f, m_pinchStrength + 0.5f, m_pinchStrength + 0.5f);
	m_man.draw(0.0f, 0.0f);

    ofPopMatrix();


    //print instruct
    ofPushMatrix();
    ofTranslate(m_instructPos);
    m_instruct.draw(0.0f, 0.0f);
    ofPopMatrix();
}
