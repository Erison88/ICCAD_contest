#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm> // for find_if 
#include "readfile.h"
// #include "linesearch.h"
#include "BFS.h"

using namespace std;


// int main() {
//     vector<Block> blocks;
//     vector<Net> nets;
//     vector<Component> components;
//     vector<Region> regions;
//     int num_Comp = 0;
//     int UNITS_DISTANCE_MICRONS = 0;
//     DieArea diearea;
//     vector<OnlyBlock> onlyblocks;

    

//     // file path
//     string blockFilePath = "case4/case4_cfg.json";
//     string netFilePath = "case4/case4.json";
//     string defFilePath = "case4/case4_def/chip_top.def";

//     readJsonFiles(blockFilePath, netFilePath, blocks, nets);

//     readDefFile(defFilePath, components, regions, num_Comp, UNITS_DISTANCE_MICRONS, diearea);


//     // file path for individual DEF of component
//     vector<string> compFilePaths(num_Comp);
//     for (int i = 0; i < num_Comp; ++i) {
//         char filePath[50];
//         sprintf(filePath, "case4/case4_def/blk_%d.def", i);
//         compFilePaths[i] = string(filePath); 
//     }

    
//     for (const auto& path : compFilePaths) {
//         readCompFile(path, onlyblocks);
//         // std::cout << "File: " << path << std::endl;
//     }

//     for (const auto& block : onlyblocks) {
//         std::cout << "Block Name: " << block.name << std::endl;
//         for (const auto& pt : block.vertices) {
//             std::cout << "Vertex: (" << pt.x << ", " << pt.y << ")" << std::endl;
//         }
//         std::cout << std::endl;
    
//     }

// //////////////////////////////////////////////////////////////////////////
//     // for input parameters
//     vector<Block> blockList;

//     for (const auto& component : components) {
//         auto it = find_if(onlyblocks.begin(), onlyblocks.end(), [&](const OnlyBlock& ob) { return ob.name == component.name; });
//         if (it != onlyblocks.end()) {
//             Block block;
//             block.name = component.name;
//             block.position = {component.x, component.y};
//             block.vertices = transformVertices(it->vertices, block.position, component.orientation);
//             blockList.push_back(block);
//         }
//     }

//     // Print blockList for verification
//     for (const auto& block : blockList) {
//         cout << "Block: " << block.name << ", Position: (" << block.position.x << ", " << block.position.y << "), Vertices: ";
//         for (const auto& vertex : block.vertices) {
//             cout << "(" << vertex.x << ", " << vertex.y << ") ";
//         }
//         cout << endl;
//     }





//     // for BFS.cpp
//     // grid = vector<vector<int>>(rows, vector<int>(cols, 0));
//     //  1: obstacles, 0: can pass
//     // vector<vector<int>> grid;
//     // grid = {
//     //     {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
//     //     {0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
//     //     {0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
//     //     {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
//     //     {1, 1, 0, 0, 1, 0, 0, 0, 0, 0},
//     //     {0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
//     //     {0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
//     //     {0, 0, 0, 1, 0, 1, 1, 1, 0, 0},
//     //     {1, 1, 0, 0, 0, 0, 0, 1, 1, 1},
//     //     {0, 1, 0, 0, 0, 1, 0, 0, 0, 0}
//     // };
//     // // (1, 0) is downward, (0, 1) is go right 

//     // Point_2 start(0, 0);
//     // Point_2 goal(9, 9);

//     // vector<Point_2> path;
//     // path = BFS(start, goal, grid);
    

//     // cout << "Path: ";
//     // for (auto p : path) {
//     //     cout << "(" << p.x << "," << p.y << ") ";
//     // }
//     // cout << endl;

//     return 0;

// }

// function used in output of plotting csv file
string pointToString(const Point& point) {
    ostringstream oss;
    oss << point.x << ";" << point.y;
    return oss.str();
}


int main() {
    vector<Block> blocks;
    vector<Net> nets;
    vector<Component> components;
    vector<Region> regions;
    int num_Comp = 0;
    int UNITS_DISTANCE_MICRONS = 0;
    DieArea diearea;
    vector<OnlyBlock> onlyblocks;

    // File path
    string blockFilePath = "case4/case4_cfg.json";
    string netFilePath = "case4/case4.json";
    string defFilePath = "case4/case4_def/chip_top.def";

    readJsonFiles(blockFilePath, netFilePath, blocks, nets);
    readDefFile(defFilePath, components, regions, num_Comp, UNITS_DISTANCE_MICRONS, diearea);

    // File path for individual DEF of component
    vector<string> compFilePaths(num_Comp);
    for (int i = 0; i < num_Comp; ++i) {
        char filePath[50];
        sprintf(filePath, "case4/case4_def/blk_%d.def", i);
        compFilePaths[i] = string(filePath); 
    }

    for (const auto& path : compFilePaths) {
        readCompFile(path, onlyblocks);
    }

    for (const auto& block : onlyblocks) {
        std::cout << "Block Name: " << block.name << std::endl;
        for (const auto& pt : block.vertices) {
            std::cout << "Vertex: (" << pt.x << ", " << pt.y << ")" << std::endl;
        }
        std::cout << "(Width, Height): " << block.width << ", "<< block.height << std::endl;
        std::cout << std::endl;
    }

    // Print components for verification
    // cout << "Components:" << endl;
    // for (const auto& component : components) {
    //     cout << "Name: " << component.name 
    //          << ", Blocktype: " << component.blocktype 
    //          << ", X: " << component.x 
    //          << ", Y: " << component.y 
    //          << ", Orientation: " << component.orientation 
    //          << endl;
    // }


    // Build Block
    vector<Block> blockList;

    for (const auto& component : components) {
        auto it = find_if(onlyblocks.begin(), onlyblocks.end(), [&](const OnlyBlock& ob) { return ob.name == component.blocktype; });
        if (it != onlyblocks.end()) {
            Block block;
            block.block_name = component.name;
            block.position = {component.x, component.y};
            block.vertices = transformVertices(it->vertices, it->width, it->height, block.position, component.orientation);
            blockList.push_back(block);
        }
    }

    // Print blockList for verification
    for (const auto& block : blockList) {
        cout << "Block: " << block.block_name << ", Position: (" << block.position.x << ", " << block.position.y << "), Vertices: ";
        for (const auto& vertex : block.vertices) {
            cout << "(" << vertex.x << ", " << vertex.y << ") ";
        }
        cout << endl;
    }



    // Print onlyblocks for verification
    // cout << "OnlyBlocks:" << endl;
    // for (const auto& onlyblock : onlyblocks) {
    //     cout << "Name: " << onlyblock.name << ", Vertices: ";
    //     for (const auto& vertex : onlyblock.vertices) {
    //         cout << "(" << vertex.x << ", " << vertex.y << ") ";
    //     }
    //     cout << endl;
    // }




    // output plotting csv file, called "blocks.csv"
    ofstream file("blocks.csv");
    for (const auto& block : blockList) {
        file << block.block_name << ",";
        for (const auto& pt : block.vertices) {
            file << pointToString(pt);
            file << ",";
        }
        file << "\n";
    }
    file.close();


    return 0;
}


