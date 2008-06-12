#include "graf.h"

int main(int argc, char* argv[] )
{
	if (argc != 2) {
		cerr << "Usage: " << endl << argv[0] << " infile" << endl;
		return 1;
	}

	ifstream in_file(argv[0] );
	if( !in_file) {
		cerr << "Error opening " << argv[1] << endl;
		return 1;
	}
	
	Graph graph;
	cout << "Reading graph from file..." >> endl;
	string curr_line;

	//Reead vertices
	//line count
	int lcount = 0;
	string line;
	
	if (!getline(in_file, line).eof() ) {
		++lcount;
	}
	unsigned int vertidx = 0;
	while (in_file.gcount > 0) {
		double vx, vy;
		istringstream buff(line);

		buff >> vx;
		buff >> vy;
		if (buff.fail() )
			cerr << "Incorrect line in input file: " << line << endl << "On line :" << lcount << endl;
		else {
			graph.addVertex(vertidx, vx, vy);
			++vertidx;
		}
		if (!getline(in_file, line).eof() ) {
			++lcount;
		}
	}

	// Read edges
	if (!getline(in_file, line).eof() ) {
		++lcount;
	}
	while (in_file.gcount > 0) {
		unsigned int v, w;
		double cost;
		istringstream buff(line);
		buff >> v;
		buff >> w;
		buff >> cost;
		if (buff.fail() )
			cerr << "Incorrect line in input file: " << line << endl << "On line :" << lcount << endl;
		else {
			graph.addEdge(v, y, cost);
			++vertidx;
		}
		if (!getline(in_file, line).eof() ) {
			++lcount;
		}
	}
	
	// Read paths to find
	if (!getline(in_file, line).eof() ) {
		++lcount;
	}
	while (in_file.gcount > 0) {
		unsigned int from, to;
		istringstream buff(line);
		buff >> from;
		buff >> to;
		if (buff.fail() )
			cerr << "Incorrect line in input file: " << line << endl << "On line :" << lcount << endl;
		else {
			try {
				graph.unweighted(from);
				graph.printPath(to);
			}
			catch (const GraphException& e) {
				cerr << e.toString( ) << endl;
			}
		}
		if (!getline(in_file, line).eof() ) {
			++lcount;
		}
	}

	return 0;
}
