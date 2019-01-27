//
//  test.cpp
//  shadersketch
//
//  Created by Alex Q on 5/1/18.
//

#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "test.hpp"

using std::vector;

TEST_CASE("Test cases")
{
    SECTION("conditional expansion, no expansion")
    {
        std::vector<std::vector<int>> cells =
        {
            {0, 0, 0},
            {0, 1, 0},
            {0, 0, 0}
        };
        vector<vector<int>> test_cells = conditional_expansion(cells);
        
        REQUIRE(test_cells == cells);
    }
    
    SECTION("conditional expansion, expected rightward expansion")
    {
        std::vector<std::vector<int>> cells =
        {
            {0, 0, 0},
            {0, 1, 1},
            {0, 0, 0}
        };
        
        std::vector<std::vector<int>> expected_cells =
        {
            {0, 0, 0, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0}
        };
        
        vector<vector<int>> test_cells = conditional_expansion(cells);
        
        REQUIRE(test_cells == expected_cells);
    }
    
    SECTION("conditional expansion, expected leftward expansion")
    {
        std::vector<std::vector<int>> cells =
        {
            {0, 0, 0},
            {1, 1, 0},
            {0, 0, 0}
        };
        
        std::vector<std::vector<int>> expected_cells =
        {
            {0, 0, 0, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0}
        };
        
        vector<vector<int>> test_cells = conditional_expansion(cells);
        
        REQUIRE(test_cells == expected_cells);
    }
    
    SECTION("count adjacent cells, no out of bounds")
    {
        std::vector<std::vector<int>> cells =
        {
            {0, 1, 0},
            {1, 1, 0},
            {0, 0, 0}
        };
        
        int adjacent_cells = count_adjacent_cells(cells, 1, 1);
        
        REQUIRE(adjacent_cells == 2);
    }
    
    SECTION("count adjacent cells, out of bounds")
    {
        std::vector<std::vector<int>> cells =
        {
            {0, 1, 0},
            {1, 1, 0},
            {0, 0, 0}
        };
        
        int adjacent_cells = count_adjacent_cells(cells, 0, 0);
        
        REQUIRE(adjacent_cells == 3);
    }
}

/**
 * Given a 2d vector and an index, returns the number of adjacent cells to that index that contain 1
 * @param cells The 2d vector to search through
 * @param x The x coordinate of the cell to search near
 * @param y The y coordinate of the cell to search near
 */
int count_adjacent_cells(vector<vector<int>> cells, int x, int y)
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
vector<vector<int>> conditional_expansion(std::vector<std::vector<int>> grid_to_expand)
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

    return expanded_grid;
}
