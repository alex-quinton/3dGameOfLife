//
//  preset.hpp
//  shadersketch
//
//  Created by Alex Q on 5/1/18.
//

#ifndef preset_hpp
#define preset_hpp

#include <stdio.h>
#include <vector>

using std::vector;

class Preset
{
    vector<vector<int>> cells_;
    vector<bool> rules_;
    
public:
    explicit Preset();
    explicit Preset(vector<vector<int>> cells, vector<bool> rules);
    
    vector<vector<int>> get_cells();
    
    vector<bool> get_rules();
};

#endif /* preset_hpp */
