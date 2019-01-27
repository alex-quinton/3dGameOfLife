#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "preset.hpp"
#include<vector>
#include<map>

class ofApp : public ofBaseApp{
	public:
    
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    vector<vector<int>> conditional_expansion(vector<vector<int>> grid_to_expand);
    int count_adjacent_cells(vector<vector<int>> cells, int x, int y);
    void select_preset(Preset preset);

    ofShader shader;
    ofEasyCam cam;
    ofLight light;
    ofMaterial mat;
    
    Preset gol_rpentonimo;
    Preset gol_quadblinker;
    Preset gol_glider;
    Preset gol_tenrow;
    Preset fast_rpentonimo;
    Preset fast_tenrow;
    Preset fast_diagonal;
    
    ofxPanel rules;
    ofxToggle live_rules_0;
    ofxToggle live_rules_1;
    ofxToggle live_rules_2;
    ofxToggle live_rules_3;
    ofxToggle live_rules_4;
    ofxToggle live_rules_5;
    ofxToggle live_rules_6;
    ofxToggle live_rules_7;
    ofxToggle live_rules_8;
    
    ofxToggle dead_rules_0;
    ofxToggle dead_rules_1;
    ofxToggle dead_rules_2;
    ofxToggle dead_rules_3;
    ofxToggle dead_rules_4;
    ofxToggle dead_rules_5;
    ofxToggle dead_rules_6;
    ofxToggle dead_rules_7;
    ofxToggle dead_rules_8;
    
    ofxPanel presets;
    ofxToggle isRunning; // Not a preset, pauses/plays the app
    ofxButton gol_rpentonimo_btn;
    ofxButton gol_quadblinker_btn;
    ofxButton gol_glider_btn;
    ofxButton gol_tenrow_btn;
    ofxButton fast_rpentonimo_btn;
    ofxButton fast_tenrow_btn;
    ofxButton fast_diagonal_btn;
    
    std::map<int,int> live_rules;
    std::map<int,int> dead_rules;
    ofVec3f cam_pos;
    const int ticks_per_update = 10;
    const int initial_tick_delay = 0; // delays drawing process at startup
    const int max_possible_adjacent_cells = 8;
};
