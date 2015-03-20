#include "header.h"

int words(string name){
	bool flag;
	int word=0,size;
	size = name.length();
	if(size == 0)
		return 0;
	for(int i=0;i<size;i++){
		if(name[i] != ' ')
			flag = true;
		else{
			if(flag == true){
				word++;
				flag=false;
			}
		}
	}
	if(flag == true)
		return word+1;
	else
		return word;
}

bool equal(string x,string y){
	string z;

	for(int i=0; i<x.length(); i++){
		if(x[i] != ' ')
			z+=x[i];

	}

	if(y.compare(z) == 0)
		return true;
	else
		return false;

}
void help(){

        cout<<"\033[1;35m"<<"----------------------------------------------------------------------------------"<<"\033[0m"<<endl;

	cout<<"\033[1;37m"<<"      ** Menu **"<<"\033[0m"<<endl;
	cout<<endl<<"...watch system calls..."<<endl;
	cout<<"\033[1;33m"<<"trace <category> :"<<"\033[0m"<<endl;
	cout<<"\033[1;33m"<<"			<category> "<<"\033[0m"<<"= 'process-control' (execve,fork,wait4,kill)"<<endl;
        cout<<"\033[1;33m"<<"			<category> "<<"\033[0m"<<"= 'file-management' (read,write,open,close)"<<endl;
	cout<<"\033[1;33m"<<"			<category> "<<"\033[0m"<<"= 'all' (process-controll & file-managment)"<<endl;
	cout<<endl<<"...redirect sreams..."<<endl;
	cout<<"\033[1;33m"<<"redirect <stream> <filename>:"<<"\033[0m"<<endl;
	cout<<"				   <stream> = 'stdin','stdout','stderr'"<<endl;
	cout<<endl<<"...freezing the program in each system call..."<<endl;
	cout<<"\033[1;33m"<<"blocking-mode <mode>:"<<"\033[0m"<<endl;
	cout<<"\033[1;33m"<<"			   <mode> "<<"\033[0m"<<"= 'on'(user must press 'y' to continue or 'n' to stop)"<<endl;
	cout<<"\033[1;33m"<<"			   <mode> "<<"\033[0m"<<"= 'of'(executing without interruption)"<<endl;
	cout<<endl<<"...numbers of system calls in each category..."<<endl;
	cout<<"\033[1;33m"<<"limit-trace <number>:"<<"\033[0m"<<endl;
	cout<<"\033[1;33m"<<"			   <number>"<<"\033[0m"<<" = N>0 (number of syscalls)"<<endl;
	cout<<endl<<"...executing the program..."<<endl;
	cout<<"\033[1;33m"<<"go"<<"\033[0m"<<endl;
	cout<<endl<<"...press that for exit..."<<endl;
	cout<<"\033[1;33m"<<"quit"<<"\033[0m"<<endl;
	cout<<endl<<"...press that for help"<<endl;
	cout<<"\033[1;33m"<<"help"<<"\033[0m"<<endl;
        cout<<"\033[1;35m"<<"----------------------------------------------------------------------------------"<<"\033[0m"<<endl;


}
int trace_test(string name){

	string first,second;
	bool second_word = false;
        for(int i=0; i<name.length(); i++){
                if(name[i] != ' ' && second_word == false)
                        first += name[i];
		if(name[i] == ' ')
			second_word = true;
		if(name[i] != ' ' && second_word == true)
			second += name[i];

        }

	if(first.compare("trace") == 0 || first.compare("t") == 0){
		if(second.compare("process-control") == 0)
			return 0;
		else if(second.compare("file-management") == 0)
			return 1;
		else if(second.compare("all") == 0)
			return 2;
		else
			return -1;

	}
	else
		return -1;

}

int block(string name){

        string first,second;
        bool second_word = false;
	for(int i=0; i<name.length(); i++){
                if(name[i] != ' ' && second_word == false)
                        first += name[i];
                if(name[i] == ' ')
                        second_word = true;
                if(name[i] != ' ' && second_word == true)
                        second += name[i];

        }

	if(first.compare("blocking-mode") == 0 || first.compare("b") == 0){
                if(second.compare("on") == 0)
                        return 1;
                else if(second.compare("off") == 0)
                        return 0;
		else{
			return -1;
		}
        }
        else
                return -1;



}
bool isInt(string s){
  bool isInt = true;
    for(int i = 0; i < s.length(); i++){
      if(!isdigit(s[i]))
        isInt = false;
    }
  return isInt;
}

int limit(string name){
        string first,second;
        bool second_word = false;
        for(int i=0; i<name.length(); i++){
                if(name[i] != ' ' && second_word == false)
                        first += name[i];
                if(name[i] == ' ')
                        second_word = true;
                if(name[i] != ' ' && second_word == true)
                        second += name[i];

        }
	if(first.compare("limit-trace") == 0 || first.compare("l") == 0){
		if( isInt(second) )
			return atoi(second.c_str());
		else
			return -1;

	}
	else
		return -1;

}
int redirect(string name, string filename[]){
	string first,second,third;
	bool second_word = false;
	bool third_word = false;
	bool bike = false;

        for(int i=0; i<name.length(); i++){
                if(name[i] != ' ' && second_word == false)
                        first += name[i];
                if(name[i] == ' ')
                        second_word = true;
                if(name[i] != ' ' && second_word == true && third_word == false){
                        second += name[i];
			bike = true;
		}
		if(name[i] == ' ' && bike == true)
			third_word = true;
		if(name[i] != ' ' && third_word == true)
			third+=name[i];
        }
	if(first.compare("redirect") == 0 || first.compare("r") == 0){
		if(second.compare("stdout") == 0){
			filename[1] = third;
			return 1;
		}
		else if( second.compare("stderr") == 0){
			filename[2] = third;
			return 2;
		}
		else if(second.compare("stdin") == 0){
			filename[0] = third;
			return 0;
		}
		else
			return -1;
	}
	else
		return -1;

}
