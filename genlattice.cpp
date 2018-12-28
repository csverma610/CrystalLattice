#include "CrystalLattice.hpp"
#include <unistd.h>

using namespace std;

void Usage(const std::string &e)
{
}

int main(int argc, char **argv)
{
    CrystalLattice cl;

    double ox, oy, oz;
    double lx, ly, lz;
    double clength;
    int    pattern = 0;
    string outfilename = "lattice.off";

    int c;
    while ((c = getopt (argc, argv, "c:o:l:p:s:h")) != -1) {
        switch (c)
        {
        case 'c':
            clength = atof(optarg);
            cl.setCellLength(clength);
            break;
        case 'o':
            ox  = atof(argv[optind-1]);
            oy  = atof(argv[optind]);
            oz  = atof(argv[optind+1]);
            cl.setOrigin(ox, oy, oz);
            break;
        case 'l':
            lx  = atof(argv[optind-1]);
            ly  = atof(argv[optind]);
            lz  = atof(argv[optind+1]);
            cl.setModelLength(lx, ly, lz);
            break;
        case 'p':
             pattern = atoi(optarg);
             break;
        case 's':
             outfilename = optarg;
             break;
        case 'h':
            Usage( argv[0] );
            return 1;
        }
    }

    cl.generate(pattern);

    cl.saveAs(outfilename);
}
