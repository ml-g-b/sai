#ifndef FUNCTION_H
#define FUNCTION_H

#include<stdlib.h>
#include<time.h>

#ifndef M_PI
#define M_PI 3.141592653589793
#endif

#define F_MIN(a, b) ((a < b) ? a : b)
#define F_MAX(a, b) ((a < b) ? b : a)

#define F_RANDINT(a ,b) (rand()%(b-a+1)+a)
#define F_RAND(a ,b) ((double)rand()*(F_MAX(a,b)-F_MIN(a,b))/(double)RAND_MAX + F_MIN(a,b))

#define F_POWINT(x, n) ({                       \
            long int i, b=x, a=x;               \
            for(i=1 ; i<n ; a*=b, i++);         \
            a;                                  \
        })

#define F_POW(x, n) ({                          \
            int i;                              \
            double b=x, a=x;                    \
            for(i=1 ; i<n ; a*=b, i++);         \
            a;                                  \
        })

#define F_LGR(a,b) ({                           \
            F_MAX(a,b)-F_MIN(a,b);              \
        })

#define F_SQRT(n) ({                            \
    int i;                                      \
    double s=n/2, tmp=0;                        \
    if(n<0)                                     \
        s=0;                                    \
    else if(n==1)                               \
        s=1;                                    \
    else for(i=0 ; i<100 && s!=tmp ; i++){      \
            tmp=s;                              \
            s=(n/tmp+tmp)/2;                    \
        }                                       \
    s;                                          \
        })
#define F_DISTANCE(x1,y1,x2,y2) ({                                      \
            F_SQRT((double)(F_POWER(F_LGR(x1,x2),2)+F_POWER(F_LGR(y1,y2),2))); \
        })


#endif