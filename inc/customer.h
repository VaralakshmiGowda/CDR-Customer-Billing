#pragma once
#include <myHeader.h>
class Customer
{
        public:
                Customer(){}
                Customer(long c,string b,long s1,long s2,long d1,long d2,long s3,long s4,long d3,long d4,long d,long u){
                cId=c;
                name=b;
                s_inc=s1;
                s_out=s2;
                d_inc=d1;
                d_out=d2;
                s_imsg=s3;
                s_omsg=s4;
                d_imsg=d3;
                d_omsg=d4;
                down=d;
                up=u;
                }
       ~Customer(){}
                long getCid();
                void setCid(long);
                string getName();
                long getSinc();
                long getSout();
                long getDinc();
                long getDout();
                long getSimsg();
                long getSomsg();
                long getDimsg();
                long getDomsg();
                long getDown();
                long getUp();

  private:
                long cId;
                string name;
                long s_inc;
                long s_out;
                long d_inc;
                long d_out;
                long s_imsg;
                long s_omsg;
                long d_imsg;
                long d_omsg;
                long down;
                long up;
};
