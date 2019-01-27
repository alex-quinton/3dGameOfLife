//
//  preset.cpp
//  shadersketch
//
//  Created by Alex Q on 5/1/18.
//

#include "preset.hpp"
using std::vector;

Preset::Preset()
{}

Preset::Preset(vector<vector<int>> cells, vector<bool> rules) : cells_(cells), rules_(rules)
{}

vector<vector<int>> Preset::get_cells()
{
    return cells_;
}

vector<bool> Preset::get_rules()
{
    return rules_;
}
