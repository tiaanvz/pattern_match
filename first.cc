#include <iostream>
#include <fstream>
#include <string>

using namespace std;



bool does_key_match(char *keywords, char *logline) {
    //cout << " kw: " << *kw;
    
    if (*keywords == *logline) {
        while ((*keywords == *logline) && (*keywords != NULL) && (*logline != NULL)) {
            keywords++;
            logline++;
        }
        if (*keywords == NULL) {
            return true;
        }
    }
    return false;
}


int match_keywords_in_line(char **keywords, char *logline) {
    if (*logline != NULL) {
        //cout << '|' << *logline;
        for (char **kw = keywords; **kw != NULL; kw++) {
            if (does_key_match(*kw, logline)) {
                cout << "(match: " << *kw << ")" << endl; 
            }
        }

        //logline++;
        match_keywords_in_line(keywords, (++logline));
    }    
    return 0;
}


int main () {
    using namespace std;
    clock_t begin = clock();

    //using clock = std::chrono::steady_clock;     
    //clock::time_point start = clock::now();    
    // A long task...   
    string line;
    char *list[] = {"2017110200002","20171102000025","278200484904386","2782004849043863","2782004849044767","\0"};
    
    //char *list[] = {"Line", "hope", "Third", "\0"};
    char **keywords = list;
    
    ifstream myfile ("/home/tiaanvz/Downloads/test.log");
    if (myfile.is_open()) {
        while ( getline (myfile,line) ) {
            char *logline = &line[0u];
            //cout << match_keywords_in_line(keywords, logline) << endl;
            match_keywords_in_line(keywords, logline);
        }
        myfile.close();
    }
    else cout << "Unable to open file"; 

    //clock::time_point end = clock::now();
    //clock::duration execution_time = end - start;
    //cout << execution_time;
    //
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout << elapsed_secs;

    //for (char **phrase = newlist; **phrase != NULL; *phrase++) { 
    //        cout << *phrase << endl;
    //}

    return 0;
}
