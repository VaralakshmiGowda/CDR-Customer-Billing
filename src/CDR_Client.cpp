#include <myHeader.h>
#include <user.h>

string User::getPass(){
        return password;
}
string User::getUser(){
        return username;
}
//Assigning map 
map<string,User> users;
// using registers founction for registration 
int registers(){
        string u,p,g;
        cout <<"enter username"<<endl;
        cin >>u;
        cout <<"enter password"<<endl;
        cin >>p;
        cout <<"enter gender (M/F)"<<endl;
        cin >>g;
        int a;
        cout <<"enter age"<<endl;
        cin >>a;
        ofstream f;
        f.open("user.txt",ios::app);
        f <<u<<" "<<a<<" "<<g<<" "<<p<<endl;
        User u1(a,u,g,p);
        users[u]=u1;
        return 1;
}
// using login function for login
int login(){
        string u,p; 
        cout<<"enter username"<<endl; 
        cin >>u;
        cout <<"enter password"<<endl;
        cin >>p;
        if(users[u].getPass()!=p){       //comparing the registered password and the given password
        return 0;
        }
        return 1;
}
//assigning a variable pro with 0
int pro=0; 
int main()
{
    ifstream f("user.txt"); //storing the registration contents in user.txt file
    string li;
    if(!f)
    {
        cout<<"Unable to open file"<<endl;
    }
    else
    {
        string tm1,ta1[10];
        int j=0;
        while(getline(f,li))
        {
          stringstream X(li);
          while(getline(X,tm1,' '))
           {
                        ta1[j++]=tm1;
              }
                        j=0;
                        User u(stoi(ta1[1]),ta1[0],ta1[2],ta1[3]);
               
                        users[ta1[0]]=u;  
        }
        int log=0;
        int c=0,r=0,r1=0;
        while(1)
        {
                //system(" clear ");
                if(log==0)
                       {
                            cout<<"************** WELCOME TO MAIN MENU ******************"<<endl;
                            cout <<"Enter your choice \n1.Register\n2.login"<<endl;
                            cin >>c;
                switch(c)
                {
                    //Registration Part
                       case 1:r=registers();
                            if(r!=1)
                            cout <<"Unable to register"<<endl;
                        else
                            cout <<"Registered successfully"<<endl;
                        break;

                  //Login Part
                        case 2:r1=login();
                        if(r1!=1)
                                cout <<"Unable to login"<<endl;
                        else{
                            cout <<"Login successfully"<<endl;
                            log=1;
                            }
                        break;
                }
                        }
		       
                         else{
                                 
                                //Processing the file part
                               
                                 cout<<"************ PROCESSING MENU **********************"<<endl;
                                 cout <<"Enter your choice \n1.Process CDR\n2.Search\n3.Logout"<<endl;
                                 cin>>c;
                                 switch(c)
                                 {
                                        case 1:process_cdr();
                                        pro=1;
                                        break;
                                        case 2:if(pro==0)
                                        {
                                         process_cdr();
                                         pro=1;
                                         process_cdr();
                                         break;
                                        }
                                        else
                                        {
                                                process_cdr();
                                                break;
                                        }
                                        case 3:cout<<"Logged out:"<<endl; //Returns back to Main Menu
                                                log=0;
                                                break;
                                 }
                             }
                 }
        }
} 
// when the function process_cdr is called the process executes
int process_cdr()

{
    int sockfd, ret;

    struct sockaddr_in sAddr;

    char buff[10000];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
        {
            perror("socket() error");
            exit(1);
        }

        memset(&sAddr,'\0',sizeof(sAddr));

        sAddr.sin_family = AF_INET;
        sAddr.sin_port = htons(PORT);
        sAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

        ret = connect(sockfd, (struct sockaddr*)&sAddr, sizeof(sAddr));

        if(pro==0)
        {
           if(ret < 0)
              {
                   perror("connect() error");
                   exit(1);
              }
            char buff1[]="data.cdr";
            write(sockfd, buff1, strlen(buff1));
            bzero(buff, sizeof(buff));

           if(read(sockfd, buff, 10000) < 0)
                {
                    perror("read() error");
                    exit(1);
                }
                else
                    cout<<"Server: \t"<<buff<<endl;
        }
                else
                     {
                          char buff2[10];
                          cout<<"Enter Customer ID to search"<<endl;
                          cin>>buff2;
                          write(sockfd, buff2, strlen(buff2));
                           bzero(buff, sizeof(buff));
                         
                         if(read(sockfd, buff, 10000) < 0)
                         {
                                perror("read() error");
                                exit(1);
                         }
                         else
                         {
                                if(strcmp(buff,"Not")==0)
                                         cout <<"Not Able to find a Match"<<endl;
                                else
                                         cout<<buff<<endl;
                         }
                      }

        return EXIT_SUCCESS;

}
