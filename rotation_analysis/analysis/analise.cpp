#include "../src/DataAnalysis.cpp"
#include <string>
#include <vector>

using namespace std;

int main(int argc, char** argv){

	/*
	CHANGE THE DIRECTORY OF THE SIMULATIONS HERE
	n_terminals IS THE NUMBER OS TABS THAT WILL BE RAN AT THE SAME TIME
	AFTER FINISHED RUNNING, CHECK EVERY FILE AT directory/plots/ AND DELETE
		THE ONES THAT ARE TRASH
	*/

	string directory = "../outputs/Data/"; // INCLUDE LAST SLASH
	int n_terminals = 6;

	system("g++ -o2 single_analise.cpp -lm -o single_analise `root-config --cflags --glibs`");

	int n_files;
	string *files;
	char plot[64], log[64], cmd[516];

	sprintf(cmd, "rm -rvf %splots", directory.c_str());
	system(cmd);
	sprintf(cmd, "rm -rvf %slogs", directory.c_str());
	system(cmd);

	files = list_dir(directory.c_str(), &n_files);

	sprintf(cmd, "mkdir %splots", directory.c_str());
	system(cmd);
	sprintf(cmd, "mkdir %slogs", directory.c_str());
	system(cmd);

	for(int i = 0; i < n_files; i++){
		sprintf(plot, "%splots/plot%s.png", directory.c_str(), files[i].substr(string(directory).size(), 8).c_str());
		sprintf(log , "%slogs/log%s.txt"  , directory.c_str(), files[i].substr(string(directory).size(), 8).c_str());
		if(i % n_terminals == 0){
			sprintf(cmd, "./single_analise %s %s %s; sleep 1", files[i].c_str(), plot, log);
			system(cmd);
		}else{
			sprintf(cmd, "gnome-terminal --tab -- bash -ic './single_analise %s %s %s'", files[i].c_str(), plot, log);
			system(cmd);
		}
	}

	return 0;

}