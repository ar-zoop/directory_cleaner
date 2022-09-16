#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <chrono>  
#include<queue>
using namespace std;

int main(){
    string word;
    string domain="mindpowerindia";
    ifstream readfile("view-source_https___mindpowerindia.com.html");
    stack<string> stack;
    queue<string> queue;
    while (readfile >> word) {
        //Testcase 1: catch comments        
        if((word=="*/" || word=="-->")&& !stack.empty() && stack.top()==word ){
            stack.pop();
        }
        else if(!stack.empty()) continue;
        else if( word=="/*" || word=="<! --"){
            if(word=="/*") stack.push("/*");
            else stack.push("<! --");
        }
        else if(word=="//" || word=="#"){
            getline (readfile, word);
        }
        
        //Testcase 2: make a queue of all the desired urls
        
        
    }
    readfile.close();
    return 0;
}

//it uses using namespace std::chrono;
//Before function call
//auto start = high_resolution_clock::now();
// After function call
// auto stop = high_resolution_clock::now();
//auto duration = duration_cast<microseconds>(stop - start)
//cout << duration.count() << endl;

//eg
/*     
// C++ program to find out execution time of
// of functions
#include <algorithm>
#include <chrono>
#include <iostream>
#include<vector>
using namespace std;
using namespace std::chrono;
 
// For demonstration purpose, we will fill up
// a vector with random integers and then sort
// them using sort function. We fill record
// and print the time required by sort function
int main()
{
 
    vector<int> values(10000);
 
    // Generate Random values
    auto f = []() -> int { return rand() % 10000; };
 
    // Fill up the vector
    generate(values.begin(), values.end(), f);
 
    // Get starting timepoint
    auto start = high_resolution_clock::now();
 
    // Call the function, here sort()
    sort(values.begin(), values.end());
 
    // Get ending timepoint
    auto stop = high_resolution_clock::now();
 
    // Get duration. Substart timepoints to
    // get duration. To cast it to proper unit
    // use duration cast method
    auto duration = duration_cast<microseconds>(stop - start);
 
    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl;
 
    return 0;
}
*/