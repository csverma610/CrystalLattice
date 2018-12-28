#include "CrystalLattice.hpp"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
void CrystalLattice :: simple_lattice()
{
    assert( dim[0] >= 2 && dim[1] >= 2  &&  dim[2] >= 2);

    if( celllength ) {
        dim[0] = length[0]/celllength + 1;
        dim[1] = length[1]/celllength + 1;
        dim[2] = length[2]/celllength + 1;
    }

    double dx = length[0]/(double)(dim[0]-1);
    double dy = length[1]/(double)(dim[1]-1);
    double dz = length[2]/(double)(dim[2]-1);

    graph.nodes.clear();
    graph.nodes.reserve(dim[0]*dim[1]*dim[2]);

    Array3D xyz;
    for( int k = 0; k < dim[2]; k++) {
        for( int j = 0; j < dim[1]; j++) {
            for( int i = 0; i < dim[0]; i++) {
                xyz[0] = origin[0] + i*dx;
                xyz[1] = origin[1] + j*dy;
                xyz[2] = origin[2] + k*dz;
                graph.nodes.push_back(xyz);
            }
        }
    }
    graph.edges.clear();

    int offset;
    for( int k = 0; k < dim[2]; k++) {
        for( int j = 0; j < dim[1]; j++) {
            for( int i = 0; i < dim[0]; i++) {
                offset = k*dim[0]*dim[1] + j*dim[0] + i;
                if( i < dim[0]-1) graph.edges.push_back( { offset, offset+1} );
                if( j < dim[1]-1) graph.edges.push_back( { offset, offset+dim[0]} );
                if( k < dim[2]-1) graph.edges.push_back( { offset, offset + dim[0]*dim[1]} );
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
void CrystalLattice :: bodycentered_lattice()
{
    simple_lattice();
    double dx = length[0]/(double)(dim[0]-1);
    double dy = length[1]/(double)(dim[1]-1);
    double dz = length[2]/(double)(dim[2]-1);

    Array3D xyz;
    int offset, newid = dim[0]*dim[1]*dim[2];
    for( int k = 0; k < dim[2]-1; k++) {
        for( int j = 0; j < dim[1]-1; j++) {
            for( int i = 0; i < dim[0]-1; i++) {
                xyz[0] = origin[0] + (i+0.5)*dx;
                xyz[1] = origin[1] + (j+0.5)*dy;
                xyz[2] = origin[2] + (k+0.5)*dz;
                graph.nodes.push_back(xyz);
                offset = k*dim[0]*dim[1] + j*dim[0] + i;
                graph.edges.push_back( { newid, offset} );
                graph.edges.push_back( { newid, offset+1} );
                graph.edges.push_back( { newid, offset+dim[0]} );
                graph.edges.push_back( { newid, offset+dim[0]+1} );
                offset += dim[0]*dim[1];
                graph.edges.push_back( { newid, offset} );
                graph.edges.push_back( { newid, offset+1} );
                graph.edges.push_back( { newid, offset+dim[0]} );
                graph.edges.push_back( { newid, offset+dim[0]+1} );
                newid++;
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
void CrystalLattice :: facecentered_lattice()
{
    simple_lattice();

    double dx = length[0]/(double)(dim[0]-1);
    double dy = length[1]/(double)(dim[1]-1);
    double dz = length[2]/(double)(dim[2]-1);

    Array3D xyz;
    int offset, newid = dim[0]*dim[1]*dim[2];
    int n0, n1, n2, n3;
    for( int k = 0; k < dim[2]-1; k++) {
        for( int j = 0; j < dim[1]-1; j++) {
            for( int i = 0; i < dim[0]-1; i++) {
                offset = k*dim[0]*dim[1] + j*dim[0] + i;
                //Add X faces ...
                xyz[0] = origin[0] + i*dx;
                xyz[1] = origin[1] + (j+0.5)*dy;
                xyz[2] = origin[2] + (k+0.5)*dz;
                graph.nodes.push_back(xyz);
                n0 = offset;
                n1 = n0 + dim[0]*dim[1];
                n2 = n1 + dim[0];
                n3 = n0 + dim[0];
                graph.edges.push_back( { newid, n0} );
                graph.edges.push_back( { newid, n1} );
                graph.edges.push_back( { newid, n2} );
                graph.edges.push_back( { newid, n3} );
                newid++;

                if( i == dim[0]-2) {
                    xyz[0] = origin[0] + (i+1)*dx;
                    xyz[1] = origin[1] + (j+0.5)*dy;
                    xyz[2] = origin[2] + (k+0.5)*dz;
                    graph.nodes.push_back(xyz);
                    n0 = offset+1;
                    n1 = n0 + dim[0]*dim[1];
                    n2 = n1 + dim[0];
                    n3 = n0 + dim[0];

                    graph.edges.push_back( { newid, n0} );
                    graph.edges.push_back( { newid, n1} );
                    graph.edges.push_back( { newid, n2} );
                    graph.edges.push_back( { newid, n3} );
                    newid++;
                }

                //Add Y faces ...
                xyz[0] = origin[0] + (i+0.5)*dx;
                xyz[1] = origin[1] + j*dy;
                xyz[2] = origin[2] + (k+0.5)*dz;
                graph.nodes.push_back(xyz);
                n0 = offset;
                n1 = n0 + 1;
                n2 = n0 + dim[0]*dim[1];
                n3 = n2 + 1;

                graph.edges.push_back( { newid, n0} );
                graph.edges.push_back( { newid, n1} );
                graph.edges.push_back( { newid, n2} );
                graph.edges.push_back( { newid, n3} );
                newid++;

                if( j == dim[0]-2) {
                    xyz[0] = origin[0] + (i+0.5)*dx;
                    xyz[1] = origin[1] + (j+1.0)*dy;
                    xyz[2] = origin[2] + (k+0.5)*dz;
                    graph.nodes.push_back(xyz);
                    n0 = offset+dim[0];
                    n1 = n0 + 1;
                    n2 = n0 + dim[0]*dim[1];
                    n3 = n2 + 1;

                    graph.edges.push_back( { newid, n0} );
                    graph.edges.push_back( { newid, n1} );
                    graph.edges.push_back( { newid, n2} );
                    graph.edges.push_back( { newid, n3} );
                    newid++;
                }

                //Add Z faces ...
                xyz[0] = origin[0] + (i+0.5)*dx;
                xyz[1] = origin[1] + (j+0.5)*dy;
                xyz[2] = origin[2] + k*dz;
                graph.nodes.push_back(xyz);
                n0 = offset;
                n1 = n0 + 1;
                n2 = n0 + dim[0];
                n3 = n2 + 1;

                graph.edges.push_back( { newid, n0} );
                graph.edges.push_back( { newid, n1} );
                graph.edges.push_back( { newid, n2} );
                graph.edges.push_back( { newid, n3} );
                newid++;

                if( k == dim[0]-2) {
                    xyz[0] = origin[0] + (i+0.5)*dx;
                    xyz[1] = origin[1] + (j+0.5)*dy;
                    xyz[2] = origin[2] + (k+1.0)*dz;
                    graph.nodes.push_back(xyz);
                    n0 = offset+dim[0]*dim[1];
                    n1 = n0 + 1;
                    n2 = n0 + dim[0];
                    n3 = n2 + 1;

                    graph.edges.push_back( { newid, n0} );
                    graph.edges.push_back( { newid, n1} );
                    graph.edges.push_back( { newid, n2} );
                    graph.edges.push_back( { newid, n3} );
                    newid++;
                }

            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
void CrystalLattice :: generate( int ltype) 
{

     if( ltype == (int)LatticeType::CUBE) simple_lattice();
     if( ltype == (int)LatticeType::BODY_CENTERED) bodycentered_lattice();
     if( ltype == (int)LatticeType::FACE_CENTERED) facecentered_lattice();
}

///////////////////////////////////////////////////////////////////////////////

void CrystalLattice :: saveAs( const string &filename) const
{
    ofstream ofile(filename.c_str(), ios::out);
    ofile << "OFF" << endl;
    ofile << graph.nodes.size() << "  0 " << graph.edges.size() << endl;

    for(auto v : graph.nodes) ofile << v[0] << " " << v[1] << " " << v[2] << endl;
    for(auto e : graph.edges) ofile << e[0] << " " << e[1] << endl;
}

///////////////////////////////////////////////////////////////////////////////
