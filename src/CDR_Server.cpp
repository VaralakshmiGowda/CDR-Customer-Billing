#include <myHeader.h>
#include <customer.h>
#include <sstream>
//using namespace std;
   //setter and getter functions
                long Customer :: getCid()
                {
                return cId;
                }
                void Customer :: setCid(long c)
                {
                cId=c;
                }
                string Customer :: getName()
                {
                return name;
                }
                long Customer :: getSinc()
                {
                return s_inc;
                }
                long Customer :: getSout()
                {
                return s_out;
                }
                long Customer :: getDinc()
                {
                return s_inc;
                }
                long Customer :: getDout()
                {
                return d_out;
                }
                long Customer :: getSimsg()
                {
                return s_imsg;
                }
                long Customer :: getSomsg()
                {
                return s_omsg;
                }
                long Customer :: getDimsg()
                {
                return d_imsg;
                }
                long Customer :: getDomsg()
                {
                return d_omsg;
                }
                long Customer :: getDown()
                {
                return down;
                }
                long Customer :: getUp()
                {
                return up;
                }


long j=0;

string t,ta[10];
//Assigning the map to store the output for searching 
map<long,Customer> mp;

void process_customer(string line)
{
        stringstream X(line);
        while(getline(X,t,'|'))
             {
                ta[j++]=t;
             }
        j=0;
        long l=stol(ta[0]);  //converting string type to long type
        long l1=stol(ta[2]);
        long l2=stol(ta[4]);
        long l3=stol(ta[5]);
        long l4=stol(ta[6]);
        long t1=0;
        long t2=1;

//Logic of the code 
        if(ta[3]=="MTC"){        //checking wheather coloum 3 is incoming voice call
                if(ta[2]==ta[8])
                {
                        Customer c(l,ta[1],l2,t1,t1,t1,t1,t1,t1,t1,t1,t1);
                        mp[l]=c;
                }
                else
                {
                        Customer c(l,ta[1],t1,t1,l2,t1,t1,t1,t1,t1,t1,t1);
                        mp[l]=c;
                }
        }
        else if(ta[3]=="MOC") // checking whether column 3 is outgoing voice call
        {
                if(ta[2]==ta[8])
                {
                        Customer c(l,ta[1],t1,l2,t1,t1,t1,t1,t1,t1,t1,t1);
                        mp[l]=c;
                }
                else
                {
                        Customer c(l,ta[1],t1,t1,t1,l2,t1,t1,t1,t1,t1,t1);
                        mp[l]=c;
                }
        }

        else if(ta[3]=="GPRS")   //checking whether column 3 is the uploaded or downloaded data
        {
                Customer c(l,ta[1],t1,t1,t1,t1,t1,t1,t1,t1,l3,l4);
                mp[l]=c;
        }
        else if(ta[3]=="SMS-MT")  //checking whether the column 3 is incoming message 
        {
                if(ta[2]==ta[8])
                {
                        Customer c(l,ta[1],t1,t1,t1,t1,t2,t1,t1,t1,t1,t1);
                        mp[l]=c;
                }
                else
                
                {
                        Customer c(l,ta[1],t1,l2,t1,t1,t1,t1,t2,t1,t1,t1);
                        mp[l]=c;
                }
        }
        else
        {
                if(ta[2]==ta[8]) 
                {
                        Customer c(l,ta[1],t1,t1,t1,t1,t1,t2,t1,t1,t1,t1);
                        mp[l]=c;
                }
                else
                {
                        Customer c(l,ta[1],t1,l2,t1,t1,t1,t1,t1,t2,t1,t1);
                        mp[l]=c;
                }
        }
} 

int main()
{
        ostringstream a;
        int sockfd, ret ;             

        struct sockaddr_in sAddr, newAddr;

        socklen_t addr_size, newSockfd;         //creation of new socket

        char buff[100000];
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

        ret = bind(sockfd,(struct sockaddr*)&sAddr,sizeof(sAddr));

        if(ret < 0)
        {
                perror("bind() error");
                exit(1);
        }

        cout<<"[+]Bind to the port: "<<PORT<<endl;


        if(listen(sockfd,10) == 0)
                cout<<"[+]Listening....."<<endl;
        else
                cout<<"[-]Error in binding"<<endl;
        while(1)
        {
                memset(&buff,'\0',sizeof(buff));
                newSockfd = accept(sockfd,(struct sockaddr*) &newAddr, &addr_size);
                if(newSockfd < 0)
                {
                        perror("accept() error");
                        exit(1);
                }
                  if(fork() == 0)
                  {

                        while(1)
                        {
                        bzero(buff, sizeof(buff));
                        read(newSockfd, buff, 10000);
                        cout<<buff<<endl;
                       
                        if(strcmp(buff,"")==0)
                        {
                                                   
                        perror("disconnected");
                        exit(1);

                        }
                        if(strcmp(buff,"data.cdr") != 0)
                        {
                            long f=stol(buff);
                            if(!mp.count(f))
			    {
	                    char buff3[]="Not";
	                    write(newSockfd, buff3, strlen(buff3));
                            }
                               else
                                {
                                   a<< "Customer ID: " << mp[f].getName() << " ("<<mp[f].getCid()<< ")\n\t* Services within the mobile operator *\n\tIncoming voice call durations: "<<mp[f].getSinc()<<"\n\tOutgoing voice call durations: "<<mp[f].getSout()<<"\n\tIncoming SMS messages: "<<mp[f].getSimsg()<<"\n\tOutgoing SMS messages: "<<mp[f].getSomsg()<<"\n\t* Services outside the mobile operator *\n\tIncoming voice call durations: "<<mp[f].getDinc()<<"\n\tOutgoing voice call durations: "<<mp[f].getDout()<<"\n\tIncoming SMS messages: "<<mp[f].getDimsg()<<"\n\tOutgoing SMS messages: "<<mp[f].getDomsg()<<"\n\t* Internet use *\n\tMB downloaded: "<<mp[f].getDown()<<" | MB uploaded: "<<mp[f].getUp()<<endl; 
                                   string output=a.str();                                               
                                   char buff4[10000]="Found data";
                                   strcpy(buff4,output.c_str());
                                   write(newSockfd, buff4, strlen(buff4));
                                 }
                            break;
                        }
                        else
                        {
                            cout<<"File from Client"<<buff<<endl;
                            ifstream f1(buff);
                            string l;
                            if(!f1)
                                {
                                        cout<<"Unable to open"<<endl;
                                        char buff2[]="Unable to find cdr file";
                                        write(newSockfd, buff2, strlen(buff2));
                                }
                            else
                                {
                                    cout <<"Proccessing Data"<<endl;
                                    while(getline(f1,l))
                                    {
                                        process_customer(l);
                                    }
                                        cout <<"Processed Data"<<endl;
                                }
                                ofstream f2;
                                if(!f2)
                                { 
                                      cout<<"Unable to open the processed file "  <<endl;
                                }
                                f2.open("result.txt",ios::in|ios::out);

                                         map<long,Customer>::iterator itr;

                                         for(itr=mp.begin();itr!=mp.end();++itr)
                                         {
                                         f2<< "Customer ID: "<<itr->first << " (" <<(itr->second).getName()<<")\n\t* Services within the mobile operator *\n\tIncoming voice call durations: "<<(itr->second).getSinc()<<"\n\tOutgoing voice call durations: "<<(itr->second).getSout()<<"\n\tIncoming SMS messages: "<<(itr->second).getSimsg()<<"\n\tOutgoing SMS messages: "<<(itr->second).getSomsg()<<"\n\t* Services outside the mobile operator *\n\tIncoming voice call durations: "<<(itr->second).getDinc()<<"\n\tOutgoing voice call durations: "<<(itr->second).getDout()<<"\n\tIncoming SMS messages: "<<(itr->second).getDimsg()<<"\n\tOutgoing SMS messages: "<<(itr->second).getDomsg()<<"\n\t* Internet use *\n\tMB downloaded: "<<(itr->second).getDown()<<" | MB uploaded: "<<(itr->second).getUp()<<endl;
                                         }

                                f2.close();
                                char buff1[]="Processed the cdr file and created result.txt file";
                                write(newSockfd, buff1, strlen(buff1));
                                bzero(buff, sizeof(buff));
                                bzero(buff1, sizeof(buff1));
                               
                                break;
                        }
                    }
                }
                else
                {
                   close(sockfd);
                  
                   wait(0);
                }

        }

        close(newSockfd);

        return EXIT_SUCCESS;

}
