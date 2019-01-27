#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // Shaders derived from SimpleColorQuad example
    
//#ifdef TARGET_OPENGLES
//    shader.load("shadersES2/shader");
//#else
//    if(ofIsGLProgrammableRenderer()){
//        shader.load("shadersGL3/shader");
//    }else{
//        shader.load("shadersGL2/shader");
//    }
//#endif
    
    ofEnableLighting();
    light.setup();
    
    presets.setup();
    presets.setSize(260, 19);
    
    rules.setup();
    rules.setPosition(0, 195);
    
    light.setPosition(-200,200,200);
    ofSetVerticalSync(true);
    cam.setDistance(16);
    
    mat.setAmbientColor(ofColor::gray);
    mat.setDiffuseColor(ofColor(150, 150, 150));
    mat.setSpecularColor(ofColor::white);
    mat.setShininess(128);
    
    /*
     * Rules are applied to a cell based on how many adjacent cells are full. The first int in a rule the number of adjacent cells that are present when the rule is applied, and the second int (which is either 1 and 0) represents whether the cell should turn on or off based on that number of adjacent cells. For example, <2, 0> means if a cell has exactly 2 adjacent full cells, then it turns off. Likewise, <5, 1> means a cell turns on if it has 5 adjacent full cells.
     */
    
    rules.add(live_rules_0.setup("live rule 0", false));
    rules.add(live_rules_1.setup("live rule 1", false));
    rules.add(live_rules_2.setup("live rule 2", true));
    rules.add(live_rules_3.setup("live rule 3", true));
    rules.add(live_rules_4.setup("live rule 4", false));
    rules.add(live_rules_5.setup("live rule 5", false));
    rules.add(live_rules_6.setup("live rule 6", false));
    rules.add(live_rules_7.setup("live rule 7", false));
    rules.add(live_rules_8.setup("live rule 8", false));

    rules.add(dead_rules_0.setup("dead rule 0", false));
    rules.add(dead_rules_1.setup("dead rule 1", false));
    rules.add(dead_rules_2.setup("dead rule 2", false));
    rules.add(dead_rules_3.setup("dead rule 3", true));
    rules.add(dead_rules_4.setup("dead rule 4", false));
    rules.add(dead_rules_5.setup("dead rule 5", false));
    rules.add(dead_rules_6.setup("dead rule 6", false));
    rules.add(dead_rules_7.setup("dead rule 7", false));
    rules.add(dead_rules_8.setup("dead rule 8", false));
    
    presets.add(isRunning.setup("run app", false));
    presets.add(gol_rpentonimo_btn.setup("Game of Life - R pentonimo"));
    presets.add(gol_quadblinker_btn.setup("Game of Life - Quad Blinker"));
    presets.add(gol_glider_btn.setup("Game of Life - Diagonal Glider"));
    presets.add(gol_tenrow_btn.setup("Game of Life - Row of 10"));
    presets.add(fast_rpentonimo_btn.setup("Fast expansion - R pentonimo"));
    presets.add(fast_tenrow_btn.setup("Fast expansion - Row of 10"));
    presets.add(fast_diagonal_btn.setup("Fast expansion - Diagonal line"));
    
    isRunning.setSize(265, 19);
    gol_rpentonimo_btn.setSize(265, 19);
    gol_quadblinker_btn.setSize(265, 19);
    gol_glider_btn.setSize(265, 19);
    gol_tenrow_btn.setSize(265, 19);
    fast_rpentonimo_btn.setSize(265, 19);
    fast_tenrow_btn.setSize(265, 19);
    fast_diagonal_btn.setSize(265, 19);
    
    cam_pos = cam.getGlobalPosition();
    
    // Default preset
    Preset blank_default(
    {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},// middle
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},},
     {false, false, true, true, false, false, false, false, false, // Live rules
         false, false, false, true, false, false, false, false, false}); // Dead rules)
    select_preset(blank_default);
    
    // Create the presets the user can select from
    gol_rpentonimo = Preset(
    {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0},// middle
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},},
    {false, false, true, true, false, false, false, false, false, // Live rules
        false, false, false, true, false, false, false, false, false}); // Dead rules
    
    gol_quadblinker = Preset(
    {
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0},// middle
      {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},},
  {false, false, true, true, false, false, false, false, false, // Live rules
      false, false, false, true, false, false, false, false, false}); // Dead rules
    
    gol_glider = Preset(
    {
       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},// middle
       {0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},},
    {false, false, true, true, false, false, false, false, false, // Live rules
       false, false, false, true, false, false, false, false, false}); // Dead rules
    
    gol_tenrow = Preset(
    {
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},// middle
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},},
  {false, false, true, true, false, false, false, false, false, // Live rules
      false, false, false, true, false, false, false, false, false}); // Dead rules
    
    fast_rpentonimo = Preset(
    {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0},// middle
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},},
    {false, false, false, false, false, false, false, false, false, // Live rules
        false, false, true, true, false, false, false, false, false}); // Dead rules
    
    fast_tenrow = Preset(
    {
         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
         {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},// middle
         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},},
     {false, false, false, false, false, false, false, false, false, // Live rules
         false, false, true, true, false, false, false, false, false}); // Dead rules
    
    fast_diagonal = Preset(
    {
         {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},// middle
         {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},},
     {false, false, false, false, false, false, false, false, false, // Live rules
         false, false, true, true, false, false, false, false, false}); // Dead rules
    
}

bool draw_help_message = false;
vector<vector<int>> cells;
vector<vector<vector<int>>> boxes_to_draw;
int tick = 0; //Used to change how often updates happen
bool hasWaited = false; // Used to delay the beginning of the drawing process

// Used to account for coordinate changes when expanding the array
int x_offset = 0;
int y_offset = 0;
vector<int> x_offsets;
vector<int> y_offsets;

//--------------------------------------------------------------
void ofApp::update(){
    if (!hasWaited && tick > initial_tick_delay)
    {
        hasWaited = true;
        tick = 0;
    }
    
    // Set rules based on the toggles
    live_rules[0] = live_rules_0;
    live_rules[1] = live_rules_1;
    live_rules[2] = live_rules_2;
    live_rules[3] = live_rules_3;
    live_rules[4] = live_rules_4;
    live_rules[5] = live_rules_5;
    live_rules[6] = live_rules_6;
    live_rules[7] = live_rules_7;
    live_rules[8] = live_rules_8;

    dead_rules[0] = dead_rules_0;
    dead_rules[1] = dead_rules_1;
    dead_rules[2] = dead_rules_2;
    dead_rules[3] = dead_rules_3;
    dead_rules[4] = dead_rules_4;
    dead_rules[5] = dead_rules_5;
    dead_rules[6] = dead_rules_6;
    dead_rules[7] = dead_rules_7;
    dead_rules[8] = dead_rules_8;
    
    // Check preset buttons
    if (gol_rpentonimo_btn) select_preset(gol_rpentonimo);
    if (gol_quadblinker_btn) select_preset(gol_quadblinker);
    if (gol_glider_btn) select_preset(gol_glider);
    if (gol_tenrow_btn) select_preset(gol_tenrow);
    if (fast_rpentonimo_btn) select_preset(fast_rpentonimo);
    if (fast_tenrow_btn) select_preset(fast_tenrow);
    if (fast_diagonal_btn) select_preset(fast_diagonal);
    
    // Advance one generation
    if (tick >= ticks_per_update && hasWaited && isRunning){
        tick = 0;
        boxes_to_draw.push_back(cells);
        cells = conditional_expansion(cells);
        
        // This will store the cells after all the rules have been applied
        vector<vector<int>> new_cells(cells);
        
        // Iterate over every cell in the array
        for (int x = 0; x < cells.size(); x++)
        {
            for (int y = 0; y < cells[x].size(); y++)
            {
                int adjacent_cells = count_adjacent_cells(cells, x, y);
                
                // Apply rules based on number of adjacent cells
                if (cells[x][y] == 1){
                    new_cells[x][y] = live_rules[adjacent_cells];
                    
                    if(x == 0)
                    {
                        for (int i = 0; i < cells[x].size(); i++)
                        {
                            cells[x].insert(cells[x].begin(), 0);
                        }
                    }
                    
                }
                if (cells[x][y] == 0){
                    new_cells[x][y] = dead_rules[adjacent_cells];
                }
            }
        }
        
        cells = new_cells;
        
        // use this in order to look at the layers one at a time
//        if (boxes_to_draw.size() > 1)
//            boxes_to_draw.erase(boxes_to_draw.begin());
    }
    
    tick ++;
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.setGlobalPosition(cam_pos);
    
    ofEnableDepthTest();
    light.enable();
    cam.begin();
    mat.begin();

    // Draws each of the cells in the "boxes_to_draw" array
    for (int z = 0; z < boxes_to_draw.size(); z++)
    {
        for (int x = 0; x < boxes_to_draw[z].size(); x++)
        {
            for (int y = 0; y < boxes_to_draw[z][x].size(); y++)
            {
                if(boxes_to_draw[z][x][y] == 1)
                {
                    ofDrawBox((y + y_offsets[z]), -(x + x_offsets[z]), z, 1, 1, 1);
                    std::cout << x << ", " << y << ", " << z << "\n";
                }
            }
        }
    }

    mat.end();
    cam.end();
    light.disable();
    ofDisableDepthTest();
    
    presets.draw();
    rules.draw();
    
    if (!draw_help_message)
    {
        ofDrawBitmapString("Press \'h\' for instructions", 16, 750);
    } else {
        ofDrawBitmapString("The upper pannel contains buttons that set the game to a certain preset state.\nThey fill parts of the grid, and set the rules.\nEach of the rules are named after whether they apply to live or dead cells, \nas well as how many adjacent cells there need to be for that rule to be applied.\nFor example, dead rule 6 applies to dead cells with 6 adjacent cells.\nWhether the box is checked determines whether cells under that rule will become live or dead.\nSo if you check the dead rule 6 box, dead cells with 6 adjacent live cells will become live.", 16, 670);
    }
}

const int CAM_SPEED = 5;

// Used to control camera
void ofApp::keyPressed(int key){
    if (key == OF_KEY_RIGHT)
    {
        cam_pos.x += CAM_SPEED;
    }
    
    if (key == OF_KEY_LEFT)
    {
        cam_pos.x -= CAM_SPEED;
    }
    
    if (key == OF_KEY_UP)
    {
        cam_pos.z -= CAM_SPEED;
    }
    
    if (key == OF_KEY_DOWN)
    {
        cam_pos.z += CAM_SPEED;
    }
    
    if (key == 122)
    {
        cam_pos.y += CAM_SPEED;
    }
    
    if (key == 120)
    {
        cam_pos.y -= CAM_SPEED;
    }
    
    if (key == 'h')
    {
        draw_help_message = !draw_help_message;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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

/**
 * Given a certain Preset object, sets the cells vector and rule toggles to the settings described by the preset's private variables.
 @param preset The preset whose settings are to be read
 */
void ofApp::select_preset(Preset preset)
{
    boxes_to_draw.clear();
    cells = preset.get_cells();
    
    live_rules_0 = preset.get_rules()[0];
    live_rules_1 = preset.get_rules()[1];
    live_rules_2 = preset.get_rules()[2];
    live_rules_3 = preset.get_rules()[3];
    live_rules_4 = preset.get_rules()[4];
    live_rules_5 = preset.get_rules()[5];
    live_rules_6 = preset.get_rules()[6];
    live_rules_7 = preset.get_rules()[7];
    live_rules_8 = preset.get_rules()[8];
    
    dead_rules_0 = preset.get_rules()[9];
    dead_rules_1 = preset.get_rules()[10];
    dead_rules_2 = preset.get_rules()[11];
    dead_rules_3 = preset.get_rules()[12];
    dead_rules_4 = preset.get_rules()[13];
    dead_rules_5 = preset.get_rules()[14];
    dead_rules_6 = preset.get_rules()[15];
    dead_rules_7 = preset.get_rules()[16];
    dead_rules_8 = preset.get_rules()[17];
}

/**
 * Given a 2d vector and an index, returns the number of adjacent cells to that index that contain 1
 * @param cells The 2d vector to search through
 * @param x The x coordinate of the cell to search near
 * @param y The y coordinate of the cell to search near
 */
int ofApp::count_adjacent_cells(vector<vector<int>> cells, int x, int y)
{
    int sum = 0;
    
    // Iterate to the up, down, left, right of the given cell and count each live cell
    for(int i = x - 1; i < x + 2; i++){
        for(int j = y - 1; j < y + 2; j++){
            
            // Check to see if cell being checked is out of bounds
            if (!(i == x && j == y) &&
                !( (i) < 0
                  || (j) < 0
                  || (i) >= cells.size()
                  || (j) >= cells[0].size())
                && (cells[i][j] == 1) )
            {
                sum++;
            }
            
        }
    }
    
    return sum;
}

/**
 Given a 2d vector,check to see if it needs to be expanded in order to accomodate new cells, based on whether there are live cells on the borders if the vector.
 @param grid_to_expand vector to check for expansion
 */
vector<vector<int>> ofApp::conditional_expansion(vector<vector<int>> grid_to_expand)
{
    bool has_expanded_top = false;
    bool has_expanded_bottom = false;
    bool has_expanded_left = false;
    bool has_expanded_right = false;
    
    vector<vector<int>> expanded_grid(grid_to_expand);
    
    // Check the top/bottom borders for live cells
    for (int i = 0; i < grid_to_expand.size(); i++)
    {
        // If any of the border cells at the bottom is live
        if (expanded_grid[i][expanded_grid[0].size() - 1] == 1
            && !has_expanded_bottom)
        {
            std::cout << "expanded bottom" << "\n";
            // Expand each element of expanded_grid by one (at front)
            for (int k = 0; k < expanded_grid.size(); k++)
            {
                expanded_grid[k].push_back(0);
            }
            has_expanded_bottom = true;
        }
        
        // If any of the border cells at the top is live
        if (expanded_grid[i][0] == 1 && !has_expanded_top)
        {
            std::cout << "expanded top" << "\n";
            // Expand each element of expanded_grid by one (at front)
            for (int k = 0; k < expanded_grid.size(); k++)
            {
                expanded_grid[k].insert(expanded_grid[k].begin(), 0);
            }
            has_expanded_top = true;
            y_offset --;
        }
    }
    
    // Check the left borders for live cells
    for (int j = 0; j < expanded_grid[0].size(); j++)
    {
        // If any of the border cells at the left are live
        if(expanded_grid[0][j] == 1 && !has_expanded_left)
        {
            std::cout << "expanded left" << "\n";
            // Append an empty vector to the left side
            expanded_grid.insert(expanded_grid.begin(), vector<int>(expanded_grid[0].size()));
            
            has_expanded_left = true;
            x_offset --;
            std::cout << x_offset << "\n";
        }
    }
    
    // Check the right borders for live cells
    for (int j = 0; j < expanded_grid[expanded_grid.size() - 1].size(); j++)
    {
        // If any of the border cells at the right are live
        if(expanded_grid[expanded_grid.size() - 1][j] == 1 && !has_expanded_right)
        {
            std::cout << "expanded right" << "\n";
            // Append an empty vector to the right side
            expanded_grid.push_back(
                                    vector<int>(expanded_grid[expanded_grid.size() - 1].size()));
            has_expanded_right = true;
        }
    }
    
    x_offsets.push_back(x_offset);
    y_offsets.push_back(y_offset);
    
    return expanded_grid;
}
