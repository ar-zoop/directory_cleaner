#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <chrono>  
#include<queue>
#include <map>
#include <cctype>
using namespace std;

queue<string> links_unvisited;
map <string,int>links_visited;

string extension(string filename){
    string ext="";
    
    stack<char>holder;
    int n=filename.length();
    for(int i=n-1; filename[i]!='.'; i--){
        holder.push(filename[i]);
    }
    
    while(!holder.empty()){
        ext+=holder.top();
        holder.pop();    
    }
    
    return ext;
}

string trim(string word){
    int n=word.length();
    string ret;
    int i=0,j=n-1;
    int idxs=-1, idxe=-1;
    while(i<j){
        if((word[i] =='\"'|| word[i] =='\'')&&idxs==-1){
            idxs=i+1;
        }
        if((word[j] =='\"'|| word[j] =='\'')&&idxe==-1){
            idxe=j-1;
            
        }
        else if(idxe!=-1 && idxs!=-1 ){
            break;
        }
        else{
            i++;
            j--;
        }
    }

    ret.assign(word, idxs, idxe-idxs+1);
    return ret;
}


void traverse(string file, string domain){
    cout<<file<<endl;
    string word;
    ifstream readfile(file);
    if (!readfile.is_open()) return;
    stack<string> stack;    
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
                    
                    readfile >> word;
                    
                    if((word.find("\"")!=-1 || word.find("'")!=-1) && word.find("?>")){
                        word=trim(word);
                        if(links_visited.find(word)==links_visited.end()){
                            links_unvisited.push(word);                        
                            links_visited[word]=1;
                        }
                      
                        if(stack.top()=="<?php"){
                        stack.pop();  
                        break;
                        }
                    }
                    else if(word.find("\"")!=-1 || word.find("'")!=-1){
                        word=trim(word);
                        if(links_visited.find(word)==links_visited.end()){
                            links_unvisited.push(word);                        
                            links_visited[word]=1;
                        }
                    }
                }
            }
        }  
        //Test case 2: make a queue of all the desired urls
        else if(word.find("src=")!=-1){
            word=trim(word);
            if(links_visited.find(word)==links_visited.end()){
                links_unvisited.push(word);                        
                links_visited[word]=1;
            }
        }
       else if(word.find("href=")!=-1){
            word=trim(word);
            if(links_visited.find(word)==links_visited.end()){
                links_unvisited.push(word);                        
                links_visited[word]=1;
            }
        }
        
    }
    readfile.close();
    return;
}

int main(){
    string filename="index.php";
    string domain="mindpowerindia.com";
    links_visited[filename]=1;
    traverse(filename, domain);        
    while(!links_unvisited.empty()){   
        string ext=extension(links_unvisited.front());        
        // cout<<links_unvisited.front()<<endl;
        for(int i=0 ;i<ext.length(); i++){
            if(isalpha(ext[i]))ext[i]=tolower(ext[i]);
        }
        // cout<<ext<<endl;
        if(ext!="png" && ext!="jpg" && ext!="jpeg" && ext!="css" &&ext!="js")        
            traverse(links_unvisited.front(), domain);
        links_unvisited.pop();
    }
    return 0;
}

