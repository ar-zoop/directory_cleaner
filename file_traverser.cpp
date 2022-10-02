#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <chrono>  
#include<queue>
#include <map>
#include <cctype>
#include <direct.h>
#include <cstring>
// #include <filesystem>
using namespace std;
// namespace fs = std::filesystem;
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
    // cout<<file<<endl;
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

int make_directory(const char* name) {
  return (_mkdir(name));
}
void copy(FILE *source, FILE *target) 
{ 
	char ch; 
	system("cd D:"); 
	if(source != NULL) 
	{ 
		while((ch=fgetc(source))!=EOF) 
		{ 
			fputc(ch,target); 
		} 
		fclose(source); 
		fclose(target); 
		// printf("Copied successfully...\n"); 
	} 
	else 
	{ 
		fclose(source); 
		fclose(target); 
		printf("Press any key to exit...\n"); 
	} 
	 
} 

int main(){
    int verify;
    char path[100];
    cout<<"Enter the path of the new folder";
    cin>>path;
    // bool verify=create_directories(path);/
    // verify= _mkdir(path);
    make_directory(path);
    while(verify==-1){
        cout<<"Folder not created: try again: "<<endl;
        // cout<<"Error: "<<strerror(errno);
        cout<<"Enter the path of the new folder"<<endl;
        cin>>path;
        // verify= _mkdir(path);
        // bool verify=create_directories(path);
    }
    cout<<"Folder created"<<endl;
    string filename="index.php";
    string domain="mindpowerindia.com";
    links_visited[filename]=1;
    traverse(filename, domain);        
    while(!links_unvisited.empty()){   
        string ext=extension(links_unvisited.front()); //find out extensions of the files
        for(int i=0 ;i<ext.length(); i++){
            if(isalpha(ext[i]))ext[i]=tolower(ext[i]); //generalize the extension
        }
        if(ext!="png" && ext!="jpg" && ext!="jpeg" && ext!="css" &&ext!="js")     
            traverse(links_unvisited.front(), domain);
        links_unvisited.pop();
    }

    map <string,int>::iterator imp;
    cout<<"Copying has started. "<<endl;
    for(imp=links_visited.begin(); imp!=links_visited.end(); imp++){
        // cout<<imp->first<<endl;
        int n=(imp->first).length();
        string str=imp->first;
        char temp[n+1];
        strcpy(temp, str.c_str()); 
        FILE *source = fopen(temp,"r+"); 
        FILE *target = fopen(path,"a+");
        /*
        //converting from *char to LPCWSTR to use in CopyFile function
        const WCHAR *pwcsName;
        const WCHAR *pwcsName2;
        int size = MultiByteToWideChar(CP_ACP, 0, path, -1, NULL, 0);
        pwcsName = new WCHAR[100];
        pwcsName2 = new WCHAR[100];
        string temp=imp->first;
        char fName[1000];
        for(int i=0;temp[i]!='\0'; i++ ){
            fName[i]=temp[i];
        }
        MultiByteToWideChar(CP_ACP, 0, fName, -1, (LPWSTR)pwcsName2, size);
        MultiByteToWideChar(CP_ACP, 0, path, -1, (LPWSTR)pwcsName, size);
        
         //Conversion ends here

        CopyFile(pwcsName2, pwcsName, true);

        //deleting lpwstr objects
        delete [] pwcsName;
        delete [] pwcsName2;
        */
    }
    cout<<"Copying completed!"<<endl;
    return 0;
}

