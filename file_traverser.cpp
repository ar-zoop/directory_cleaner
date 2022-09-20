#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <chrono>  
#include<queue>
using namespace std;

string trim(string word){
    int n=word.length();
    string ret;
    int i=0,j=n-1;
    int idxs=-1, idxe=-1;
    while(i<j){
        if((word[i] =='\"'|| word[i] =='\'')&&idxs==-1){
            idxs=i;
        }
        if((word[j] =='\"'|| word[j] =='\'')&&idxe==-1){
            idxe=j;
            // cout<<"#";
        }
        else if(idxe!=-1 && idxs!=-1 ){
            break;
        }
        else{
            i++;
            j--;
        }
    }
    // cout<<word<<" ";
    // cout<<idxs<<" "<<idxe<<endl;
    ret.assign(word, idxs, idxe-idxs+1);
    return ret;
}

void printqueue(queue<string>queue){
    int count=0;
    while(!queue.empty()){
    cout<<queue.front()<<endl;
    queue.pop();
    count++;}
    cout<<count;
}

int main(){
    string word;
    string domain="mindpowerindia";
    ifstream readfile("index.php");
    stack<string> stack;
    queue<string> queue;
    while (readfile >> word) {
        //catch html comment and ignore operations on the code
        if(word.find("<!--")!=-1){      
            stack.push("<!--");            
        }
        
        else if(!stack.empty() && word.find("-->")!=-1 && stack.top()=="<!--") {            
            stack.pop();
        }
        
        else if(!stack.empty() &&  stack.top()=="<!--") {           
            continue;
        }
        
        //catch php opening tag
        else if(word=="<?php"){            
            stack.push("<?php");
            while(readfile>>word){                  
                if(!stack.empty() && stack.top()=="/*"){                   
                    while(readfile>>word){
                        if(word.find("*/")!=-1) {
                            stack.pop();
                            break;
                        }
                    }
                }
                else if(word.find("//")!=-1 || word.find("#")!=-1){                   
                    getline (readfile, word);
                    continue;
                }  
                else if(word.find("/*")!=-1)  {                    
                    stack.push("/*");
                }
                
                //catch php closing tag
                else if(word.find("?>")!=-1) {                 
                    if(stack.top()=="<?php"){
                        stack.pop();  
                        break;
                    }
                }   
                //catch php include
                else if(word=="include"){
                    //store the link
                    // cout<<"p1";
                    readfile >> word;
                    // cout<<"p2";
                    if((word.find("\"")!=-1 || word.find("'")!=-1) && word.find("?>")){
                        word=trim(word);
                        queue.push(word);                        
                      
                        if(stack.top()=="<?php"){
                        stack.pop();  
                        break;
                        }
                    }
                    else if(word.find("\"")!=-1 || word.find("'")!=-1){
                        word=trim(word);
                        queue.push(word);                        
                  
                    }
                }
            }
        }  
        //Test case 2: make a queue of all the desired urls
        else if(word.find("src=")!=-1){
            word=trim(word);
            queue.push(word);
        }
       else if(word.find("href=")!=-1){
            word=trim(word);
            queue.push(word);
        }
        
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