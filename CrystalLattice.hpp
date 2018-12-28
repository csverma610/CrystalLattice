#include <stdio.h>
#include <iostream>
#include <fstream>

#include <array>
#include <vector>
#include <cassert>
#include <string>

enum class LatticeType
{
    CUBE, BODY_CENTERED, FACE_CENTERED, DELAUNAY, VORONOI
};

typedef std::array<double,3> Array3D;
typedef std::array<int,2>    Array2I;
typedef std::array<int,3>    Array3I;

struct Graph
{
    std::vector<Array3D> nodes;
    std::vector<Array2I> edges;
};

class CrystalLattice
{
public:
    void setOrigin( double ox, double oy, double oz) {
        origin[0]  = ox;
        origin[1]  = oy;
        origin[2]  = oz;
    }

    void setCellLength( const double &l) {
	    celllength = l; 
    }


    void setModelLength( double lx, double ly, double lz) {
        length[0] = lx;
        length[1] = ly;
        length[2] = lz;
    }

    void generate(int t);

    Graph getGraph() const { return graph; }

    void saveAs( const std::string &f) const;

private:
    Array3I dim     = {2, 2, 2};
    Array3D length  = {1.0, 1.0, 1.0};
    Array3D origin  = {0.0, 0.0, 0.0};

    double celllength = 0.0;

    Graph graph;

    void simple_lattice();
    void bodycentered_lattice();
    void facecentered_lattice();

};

