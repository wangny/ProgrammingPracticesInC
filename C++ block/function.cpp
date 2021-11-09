#include "function.h"

void Block::clockwise90()
{
     Block t;
     t = *this;
     int k = 0;
     for(int i = size-1; i>=0; i--){
        for(int j = 0; j<size; j++){
            buf[i+j*size]=t.buf[k];
            k++;
        }
     }
}

Block& Block::doublesize()
{
    Block t;
    t = *this;
    size = t.size*2;
    pattern = new char*[size];
    buf = new char[size*size];

    for (int i=0; i<(t.size)*(t.size) ; i++){
        int k = (i/t.size)*size*2;
        k = k+ i%t.size*2;
        //std::cout<<k<<std::endl;
        buf[k] = t.buf[i];
        buf[k+1] = t.buf[i];
        buf[k+size] = t.buf[i];
        buf[k+1+size] = t.buf[i];
    }
    for (int i=0; i<size; i++) {
            pattern[i] = (char*) &buf[i*size];
    }

}

bool equal(const Block& a, const Block& b)
{
    Block t=b;
    int tru=1;

    if(a.size != b.size)return false;
    else {
        for(int j=0; j<4; j++){
            for(int i=0; i<a.size*a.size; i++){
                if(a.buf[i]!=t.buf[i]){
                    tru=0;
                    break;
                }else{
                    tru=1;
                }
            }
            if(tru==1)return true;
            t.clockwise90();
        }
    }
    return false;
}
