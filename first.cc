#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool does_key_match(char *keywords, char *logline) {
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
        for (char **kw = keywords; **kw != NULL; kw++) {
            if (does_key_match(*kw, logline)) {
                cout << "(match: " << *kw << ")" << endl; 
            }
        }
        match_keywords_in_line(keywords, (++logline));
    }    
    return 0;
}

int main () {
    string line;
    clock_t begin = clock();
    char *list[] = {"2017110200002","20171102000025","278200484904386","2782004849043863","2782004849044767","\0"};
    char **keywords = list;
    
    ifstream myfile ("/home/tiaanvz/Downloads/test.log");
    if (myfile.is_open()) {
        while ( getline (myfile,line) ) {
            char *logline = &line[0u];
            match_keywords_in_line(keywords, logline);
        }
        myfile.close();
    }
    else cout << "Unable to open file"; 

    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout << elapsed_secs;

    return 0;
}
