#include "Arduino.h"
#include "LinearRegression.h"

LinearRegression::LinearRegression(double min, double max){
    limits = true;
    minX = min;
    maxX = max;
    reset();
}

LinearRegression::LinearRegression(){
    limits = false;
    reset();
}

void LinearRegression::learn(double x, double y){
    if(limits){
        if(x < minX){
            return;
        } else if(x > maxX){
            return;
        }
    }
    n++;

    meanX = meanX + ((x-meanX)/n);
    meanX2 = meanX2 + (((x*x)-meanX2)/n);
    varX = meanX2 - (meanX*meanX);

    meanY = meanY + ((y-meanY)/n);
    meanY2 = meanY2 + (((y*y)-meanY2)/n);
    varY = meanY2 - (meanY*meanY);

    meanXY = meanXY + (((x*y)-meanXY)/n);

    covarXY = meanXY - (meanX*meanY);

    m = covarXY / varX;
    b = meanY-(m*meanX);
}

void LinearRegression::dynamicFilteredLearn(double x, double y){
    if(limits){
        if(x < minX){
            return;
        } else if(x > maxX){
            return;
        }
    }
    
    if (n<MAXVALUES) {
        n++;
        dynamicIsValid = false;
    } else {
        dynamicIsValid = true;
    }

    meanX = meanX + (x/MAXVALUES) - meanX/MAXVALUES;
    meanX2 = meanX2 + ((x*x)/MAXVALUES) - meanX2/MAXVALUES;
    varX = meanX2 - (meanX*meanX);

    meanY = meanY + (y/MAXVALUES) - meanY/MAXVALUES;
    meanY2 = meanY2 + ((y*y)/MAXVALUES) - meanY2/MAXVALUES;
    varY = meanY2 - (meanY*meanY);

    meanXY = meanXY + ((x*y)/n) - meanXY/MAXVALUES;

    covarXY = meanXY - (meanX*meanY);

    m = covarXY / varX;
    b = meanY-(m*meanX);
}

void LinearRegression::dynamicLearn(double x, double y){
    if(limits){
        if(x < minX){
            return;
        } else if(x > maxX){
            return;
        }
    }
    
    if (n<MAXVALUES) {
        n++;
        dynamicIsValid = false;
    } else {
        dynamicIsValid = true;
    }
    
    mmX[mmli] = x;
    mmY[mmli] = y;
    mmli++;
    if (mmli>= MAXVALUES) mmli = 0;

    meanX = meanX + (x/MAXVALUES) - mmX[mmli]/MAXVALUES;
    meanX2 = meanX2 + ((x*x)/MAXVALUES) - mmX[mmli]*mmX[mmli]/MAXVALUES;
    varX = meanX2 - (meanX*meanX);

    meanY = meanY + (y/MAXVALUES) - mmY[mmli]/MAXVALUES;
    meanY2 = meanY2 + ((y*y)/MAXVALUES) - mmY[mmli]*mmY[mmli]/MAXVALUES;
    varY = meanY2 - (meanY*meanY);

    meanXY = meanXY + ((x*y)/MAXVALUES) - mmX[mmli]*mmY[mmli]/MAXVALUES;

    covarXY = meanXY - (meanX*meanY);

    m = covarXY / varX;
    b = meanY-(m*meanX);
}

double LinearRegression::correlation() {
    double stdX = sqrt(varX);
    double stdY = sqrt(varY);
    double stdXstdY = stdX*stdY;
    double correlation;

    if(stdXstdY == 0){
        correlation = 1;
    } else {
        correlation = covarXY / stdXstdY;
    }
    return correlation;
}

double LinearRegression::calculate(double x) {
    return (m*x) + b;
}

void LinearRegression::getValues(double values[]){
    values[0] = m;
    values[1] = b;
    values[2] = n;
}

double LinearRegression::getIntercept(){
    return b;    
}

double LinearRegression::getSlope(){
    return m;
}

void LinearRegression::reset(){
    for (int i=0;i<MAXVALUES;i++){
        mmX[i]=0.0;
        mmY[i]=0.0;
    }
    meanX = 0;
    meanX2 = 0;
    varX = 0;
    meanY = 0;
    meanY2 = 0;
    varY = 0;
    meanXY = 0;
    covarXY = 0;
    n = 0;
    m = 0;
    b = 0;  
    dynamicIsValid = false; 

}