#include "header.h"


int main(int argc, char *argv[]) {

	bool block_mode = false,block_input = false;
	bool stdout_=false,stderr_=false,stdin_=false;
	string filename[3];
	int trace_category = -1,blocking = 0;
	bool trace_management = false;
	bool trace_process = false;
	bool allow = true;
	int limit_trace = -5;
	if(argc !=2 )
		return -1;

	string path = argv[1];
	int end = path.length()-1;

	string program_name;
	for(int i=end; i>=0; i--){
		if(path[i] != '/')
			program_name+=path[i];
		else
			break;
	}

	program_name = string ( program_name.rbegin(), program_name.rend() );

	char x[256];
	string name;
	bool quit = false;

	signal(SIGINT,f1);		//singal handler
        signal(SIGHUP,f2);               //singal handler
        signal(SIGTERM,f3);               //singal handler


	while(1){
		allow = true;
		cout << "\033[1;35m "<<">"<<"\033[0m" ;
		cin.getline (x,256);
		name = string(x);
		if( words(name) < 1|| words(name) > 3)
			cout<<"Wrong Input!"<<endl;
		else{
			if(words(name) == 1){
				/*	help	*/
				if( name.length() == 1 && name[0] == 'h')
					help();
				else if(name.length() > 1 && name[0] =='h' && name[1] == ' ')
					help();
				else if( equal(name,"help") )
					help();
				/*	quit	*/
                                else if( name.length() == 1 && name[0] == 'q'){
                                        quit = true;
					break;
				}
                                else if(name.length() > 1 && name[0] =='q' && name[1] == ' '){
                                        quit = true;
					break;
				}
                                else if( equal(name,"quit") ){
                                        quit = true;
					break;
				}
                                /*      go    */
                                else if( name.length() == 1 && name[0] == 'g'){
					if(trace_category == -1 )
						cout<<"Please enter trace <category>!"<<endl;
					if(block_input == false )
						cout<<"Please enter blocking-mode <mode>!"<<endl;
					if(stdout_ == false && stdin_ == true){
						cout<<"please redirect stdout,thx!"<<endl;
						allow = false;
					}
                                        if(trace_category != -1 && block_input == true && allow == true)
						go(path,program_name,trace_category,block_mode,limit_trace,stdout_,stdin_,stderr_,filename);
                                }
                                else if(name.length() > 1 && name[0] =='g' && name[1] == ' '){
                                        if(trace_category == -1 )
                                                cout<<"Please enter trace <category>!"<<endl;
                                        if(block_input == false )
                                                cout<<"Please enter blocking-mode <mode>!"<<endl;
                                        if(stdout_ == false && stdin_ == true){
                                                cout<<"please redirect stdout,thx!"<<endl;
                                                allow = false;
                                        }
                                        if(trace_category != -1 && block_input == true && allow == true)
                                                go(path,program_name,trace_category,block_mode,limit_trace,stdout_,stdin_,stderr_,filename);
                                }
                                else if( equal(name,"go") ){
                                        if(trace_category == -1 )
                                                cout<<"Please enter trace <category>!"<<endl;
                                        if(block_input == false )
                                                cout<<"Please enter blocking-mode <mode>!"<<endl;
                                        if(stdout_ == false && stdin_ == true){
                                                cout<<"please redirect stdout,thx!"<<endl;
                                                allow = false;
                                        }
                                        if(trace_category != -1 && block_input == true && allow == true)
                                                go(path,program_name,trace_category,block_mode,limit_trace,stdout_,stdin_,stderr_,filename);
                                }

			}
			else if(words(name) == 2){
				/*	trace	*/
				int temp;
				temp = trace_test(name);
				if(temp != -1){
					trace_category = temp;
					if( trace_category == 1)
						trace_management = true;
					if( trace_category == 0)
						trace_process = true;
					if( trace_process == true && trace_management == true)
						trace_category = 2;
					}

				/*	block	*/
				int tmp;
				tmp = block(name);
				if( tmp != -1){
					blocking = tmp;
					block_input = true;
				}
				if(blocking == 1)
					block_mode = true;
				else if(blocking == 0)
					block_mode = false;

				/*	limit-trace	*/
				int tmp2 = limit(name);
				if(tmp2 != -1)
					limit_trace = tmp2;

				if(temp == -1 && tmp == -1 && tmp2 == -1)
                                	cout<<"Wrong Input!"<<endl;
			}
			else if(words(name) == 3){
				/*	redirect	*/
				int tmp;

				tmp = redirect(name,filename);
				if(tmp != -1){
					if(tmp == 1)
						stdout_ = true;
					else if(tmp == 2)
						stderr_ = true;
					else
						stdin_ = true;
				}
				if(tmp == -1)
					cout<<"Wrong Input!"<<endl;
			}
		}


	}


return 0;
}



/* SIGINT handler */

void f1(int signum){

cout<<"You just requested my termination!"<<endl;

	kill(getpid(),SIGKILL);
//  kill(getpid(),SIGKILL);


}

void f2(int signum){

cout<<"You just requested my termination!"<<endl;

        kill(getpid(),SIGTERM);
//  kill(getpid(),SIGKILL);


}
void f3(int signum){

cout<<"You just requested my termination!"<<endl;

        kill(getpid(),SIGTERM);
//  kill(getpid(),SIGKILL);


}

