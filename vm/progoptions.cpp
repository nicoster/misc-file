#include <string> 
#include <iostream> 
#include <boost/program_options.hpp> 
using namespace std; 
 
namespace po=boost::program_options;

int main (int ac, char* av[]) 
{ 
  po::options_description options("command line options"); 
  options.add_options() ("help,h", "Use -h or --help to list all arguments") 
                    ("file", po::value<vector<string> >( ), 
                         "Provide input file name"); 
  po::variables_map vmap; 
  po::store( 
      po::parse_command_line(ac, av, options), vmap); 
  po::notify(vmap); 
 
  if (vmap.count("help")) { 
      cout << options << endl; 
  } 
 
  if (vmap.count("file")) { 
      vector<string> ifiles(vmap["file"].as< vector<string> > ()); 
      vector<string>::iterator vI; 
      cout << "Number of input files: " << ifiles.size() << endl; 
      cout << "Input file list: " << endl; 
      for(vI = ifiles.begin(); vI != ifiles.end(); ++vI) 
          cout << "\t" << *vI << endl; 
  } else { 
      cout << "No file specified\n"; 
  } 
 
  return 0; 
}