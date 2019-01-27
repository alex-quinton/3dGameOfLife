//
//  test.hpp
//  shadersketch
//
//  Created by Alex Q on 5/1/18.
//

#ifndef test_hpp
#define test_hpp

#include <stdio.h>
#include <vector>
#include <iostream>

using std::vector;
vector<vector<int>> conditional_expansion(std::vector<std::vector<int>> grid_to_expand);
int count_adjacent_cells(vector<vector<int>> cells, int x, int y);

#endif /* test_hpp */
