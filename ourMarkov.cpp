#include <ctime>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class markov {
public:
    void create( string file ) {
        ifstream f( file.c_str(), ios_base::in );
        fileBuffer = string( ( istreambuf_iterator<char>( f ) ), istreambuf_iterator<char>() );
        f.close();
        if( fileBuffer.length() < 1 ){
        	cout << "Error: File not found or unreadable." << endl;
        	return;
        }
        prepareString();
        createDictionary();
        createText();
    }
private:
    string createText(){
	string key = "", appendix, output = "";
	int numChar = 280, charCheck;
	size_t keyPos = 0;

	map<string, vector<string> >::iterator it = dictionary.begin();
	do{
	it = dictionary.begin();
	advance(it, rand() % dictionary.size());

	key = (*it).first;
	output.append(key);
	numChar -= key.size();
	}
	while(dictionary[key].size() == 0);
	
	while(dictionary[key].size() != 0){

			appendix = dictionary[key][rand() % (dictionary[key].size())];
			charCheck = numChar - appendix.size();
			if(charCheck < 0){
				break;
			}
	
			output.append(appendix);
			keyPos = output.find_first_of(32, keyPos+1 );
			key = output.substr(keyPos+1);
	
			numChar -= appendix.size();
			if(numChar <= 0){
				break;
			}
		}
		output[0] = toupper(output[0]);
		cout << output << endl;
		return output;

    }
    void createDictionary() {
    	string sub, key, element;
    	size_t keyPos = 0, midPos = 0, nextPos = 0, farPos = 0, subSpaceTemp=0, subSpacePos = 0;
    	
    	
    	while( (farPos+1) != fileBuffer.size() ){
    		keyPos = fileBuffer.find_first_not_of(32, midPos);
    
    		midPos = fileBuffer.find_first_of(32, keyPos);
    
    		nextPos = fileBuffer.find_first_of(32, midPos+1);
    
    		farPos = fileBuffer.find_first_of(32, nextPos+1);
    
    		sub = fileBuffer.substr(keyPos, (farPos-keyPos)+1);
    
    		subSpaceTemp = sub.find_first_of(32, 0);
    		subSpacePos = sub.find_first_of(32, subSpaceTemp+1);
    		key = sub.substr(0, subSpacePos+1);
    		element = sub.substr(subSpacePos+1);
    
    		dictionary[key].push_back(element);
    
    	}
    }
    
    void prepareString(){
    	string nl = "\n";
	
		size_t lastNl = 0, firstNl = 0;
	
		while( true ){
			firstNl = fileBuffer.find(nl, lastNl+1);
			if(firstNl >= fileBuffer.size()){
				break;
			}
			lastNl = fileBuffer.find_first_not_of(nl, firstNl+1)-1;
	
			fileBuffer = fileBuffer.replace(firstNl, (lastNl-firstNl)+1, " ");
	
		}
	
		if( *fileBuffer.rbegin() != ' '){
			fileBuffer.append(" ");
		}
    }
    
    string fileBuffer;
    map<string, vector<string> > dictionary;
};

int main( int argc, char* argv[] ) {
    srand( unsigned( time( 0 ) ) );
    string input = "alice_oz.txt";
    if(argc > 1){
    	input = string( argv[1] );
    }
    markov m;
    m.create( input );
    return 0;
}