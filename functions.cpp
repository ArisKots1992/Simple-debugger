#include "header.h"


bool go(string path_,string name_,int trace_ct,bool block_mode, int trace_limit ,bool stdout_,bool stdin_,bool stderr_,string filename[]){
   
    /*  trace_category = 0 --> process-control
        trace_category = 1 --> file-management
        trace_category = 2 -- > both
    */
	const char* path = path_.c_str();
        const char* name = name_.c_str();

    int fd_out[2],fd_in[2],fd_err[2];		//for pipes
    int out_file,input_file,stderr_file;
    int status;
    pid_t child,out,in,derr;
    long orig_r_eax;
    long r_eax;


	if(stdout_ == true){
        	mode_t fdmode = S_IRUSR|S_IWUSR | S_IRGRP| S_IROTH;
       		if ( ( out_file = open(filename[1].c_str(), O_WRONLY | O_CREAT | O_TRUNC, fdmode ) ) == -1 ){
        		perror("open");
        		exit(1);
                }
                if(pipe(fd_out)==-1){
                	perror("pipe");
                	exit(1);
                }
		out = fork();
		if(out == 0){
			close(fd_out[READ]);
		}
		else{
                	close(fd_out[WRITE]);
			char reading[1];
	                while( read(fd_out[READ],reading,1) >0)
         	        	write(out_file,reading,1);
                	close(fd_out[READ]);
			exit(0);
		}
	}
        if(stdin_ == true){
                mode_t fdmode = S_IRUSR|S_IWUSR | S_IRGRP| S_IROTH;
                if ( ( input_file = open(filename[0].c_str(), O_RDONLY, fdmode ) ) == -1 ){
                        perror("open");
                        exit(1);
                }
                if(pipe(fd_in)==-1){
                        perror("pipe");
                        exit(1);
                }
                in = fork();
                if(in == 0){
                        close(fd_in[WRITE]);
                }
                else{
                        close(fd_in[READ]);
                        char reading[1];
			while( read(input_file,reading,1)>0)
				write(fd_in[WRITE],reading,1);
                        close(fd_in[WRITE]);
                        exit(0);
                }
        }
        if(stderr_ == true){
                mode_t fdmode = S_IRUSR|S_IWUSR | S_IRGRP| S_IROTH;
                if ( ( stderr_file = open(filename[2].c_str(), O_WRONLY | O_CREAT | O_TRUNC, fdmode ) ) == -1 ){
                        perror("open");
                        exit(1);
                }
                if(pipe(fd_err)==-1){
                        perror("pipe");
                        exit(1);
                }
                derr = fork();
                if(derr == 0){
                        close(fd_err[READ]);
                }
                else{
                        close(fd_err[WRITE]);
                        char reading[1];
                        while( read(fd_err[READ],reading,1) >0)
                                write(stderr_file,reading,1);
                        close(fd_err[READ]);
                        exit(0);
                }
        }




    child = fork();
    if(child == 0){

		if(stdout_ == true){
			dup2(fd_out[WRITE],1);
//			close(fd_out[WRITE]);
//			close(fd_out[READ]);
		}
		if(stdin_ == true){
			dup2(fd_in[READ],0);
//			close(fd_in[READ]);
//			close(fd_in[WRITE]);
		}
		if(stdout_ == true){
			dup2(fd_err[WRITE],2);
//			close(fd_err[WRITE]);
//			close(fd_err[READ]);
		}
	        ptrace(PTRACE_TRACEME, 0, NULL, NULL);


		execl(name,path, NULL);
		exit(0);
		}
    else {
			/* Care if i want to count ALL THE SYSCALLS and not two-two change all them to 0 */

		int writes=0;
		int reads=0;
		int forka=0;
		int waits=0;
		int opens=0;
		int closes=0;
		int ex=0;
		int kills=0;
		if (trace_limit == -5)
			trace_limit = NUM;
		while (1)
		{
			/* Wait for child status to change(syscalls etc..): */
			wait(&status);

			if (WIFEXITED(status)) {
				printf("Child exit with status %d\n", WEXITSTATUS(status));
			 	 	cout<<"Number of write:"<<writes/2<<endl;
					cout<<"Number of Read:"<<reads/2<<endl;
					cout<<"Number of Fork:"<<forka/2<<endl;
                	    		cout<<"Number of wait4:"<<waits/2<<endl;
               	     			cout<<"Number of open:"<<opens/2<<endl;
                   			cout<<"Number of close:"<<closes/2<<endl;
                  			cout<<"Number of Execve:(3)"<<ex<<endl;
                 			cout<<"Number of Kill:"<<kills/2<<endl;
					cout<<"FINAL"<<endl;
//					if( stdout_ == true)
//						close(fd_out[WRITE]);
//					if( stdin_ == true)
//						close(fd_in[READ]);
			return true;
			}

			if (!WIFSTOPPED(status)) {
				printf("wait() returned unhandled status 0x%x\n", status);
				exit(0);
			}
			bool entered = false;		/* that variable is for blocking mode */
			if (WSTOPSIG(status) == SIGTRAP) {
				/*
				*  1) syscall entry
				*  2) syscall exit
				*  3) child calls exec
				*/
				orig_r_eax = ptrace(PTRACE_PEEKUSER, child, ORIGIN_R_EAX, NULL);
				r_eax = ptrace(PTRACE_PEEKUSER, child, R_EAX, NULL);

				if(orig_r_eax == SYS_write && (trace_ct == 1 || trace_ct == 2) && writes<trace_limit*2){        /* Syscall write */
					writes++;
		                	if(writes%2 == 0){
						entered = true;
						cout<<"SYS_write"<<endl;
                		        	printf("ORIG_EAX %ld, EAX = %ld\n", orig_r_eax, r_eax);
						fflush(stdout);
					}
				}
				if(orig_r_eax == SYS_read && (trace_ct == 1 || trace_ct == 2) && reads<trace_limit*2){        /* Syscall read */
					reads++;
                    			if(reads%2 == 0){
						entered = true;
						cout<<"SYS_read"<<endl;
			                        printf("ORIG_EAX %ld, EAX = %ld\n", orig_r_eax, r_eax);
						fflush(stdout);
                			}
				}
				if(orig_r_eax == SYS_clone && (trace_ct == 0 || trace_ct == 2) && forka<trace_limit*2){        /* Syscall fork */
					forka++;
			        	if(forka%2 == 0){
						entered = true;
						cout<<"SYS_fork"<<endl;
                       				printf("ORIG_EAX %ld, EAX = %ld\n", orig_r_eax, r_eax);
                				fflush(stdout);
					}
				}
				if(orig_r_eax == SYS_wait4 && (trace_ct == 0 || trace_ct == 2) && waits<trace_limit*2){        /* Syscall wait4 */
					waits++;
		                	if(waits%2 == 0){
						entered = true;
						cout<<"SYS_wait4"<<endl;
                        			printf("ORIG_EAX %ld, EAX = %ld\n", orig_r_eax, r_eax);
						fflush(stdout);
                			}
				}
				if(orig_r_eax == SYS_execve && (trace_ct == 0 || trace_ct == 2) && ex<trace_limit*2){        /* Syscall execve */
					entered = true;
					ex++;
					cout<<"SYS_execve"<<endl;
                        		printf("ORIG_EAX %ld, EAX = %ld\n", orig_r_eax, r_eax);
                		}
				if(orig_r_eax == SYS_open && (trace_ct == 1 || trace_ct == 2) && opens<trace_limit*2){        /* Syscall open */
					opens++;
                    			if(opens%2 == 0){
						entered = true;
	                        		cout<<"SYS_open"<<endl;
						printf("ORIG_EAX %ld, EAX = %ld\n", orig_r_eax, r_eax);
						fflush(stdout);
					}
                		}
 				if(orig_r_eax == SYS_close && (trace_ct == 1 || trace_ct == 2) && closes<trace_limit*2){        /* Syscall close */
					closes++;
                    			if(closes%2 == 0){
						entered = true;
						cout<<"SYS_close"<<endl;
                        			printf("ORIG_EAX %ld, EAX = %ld\n", orig_r_eax, r_eax);
					}
                		}

 				if(orig_r_eax == SYS_kill && (trace_ct == 0 || trace_ct == 2) && kills<trace_limit*2){        /* Syscall kill */
					kills++;
                    			if(kills%2 == 0){
						entered = true;
						cout<<"SYS_kill"<<endl;
                        			printf("ORIG_EAX %ld, EAX = %ld\n", orig_r_eax, r_eax);
					}
                		}


			} else {
				//printf("Child stopped due to signal %d\n", WSTOPSIG(status));
			}
			fflush(stdout);


			ptrace(PTRACE_SYSCALL, child, NULL, NULL);
			/* freezing if blocking mode is on */

			if(block_mode == true && entered == true){
				string str;
				std::cin>>str;
				while(str.compare("y")!=0 && str.compare("n") ){
					cout<<"please press 'y' or 'n' "<<endl;
					cin>>str;
				}

				if(str.compare("n") == 0){
					return false;
				}
			}
   		 }
	}
}
