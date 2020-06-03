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
    
    if (n<maxValues) {
        n++;
        dynamicIsValid = false;
    } else {
        dynamicIsValid = true;
    }

    meanX = meanX + (x/maxValues) - meanX/maxValues;
    meanX2 = meanX2 + ((x*x)/maxValues) - meanX2/maxValues;
    varX = meanX2 - (meanX*meanX);

    meanY = meanY + (y/maxValues) - meanY/maxValues;
    meanY2 = meanY2 + ((y*y)/maxValues) - meanY2/maxValues;
    varY = meanY2 - (meanY*meanY);

    meanXY = meanXY + ((x*y)/n) - meanXY/maxValues;

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
    
    if (n<maxValues) {
        n++;
        dynamicIsValid = false;
    } else {
        dynamicIsValid = true;
    }
    
    mmX[mmli] = x;
    mmY[mmli] = y;
    mmli++;
    if (mmli>= maxN) mmli = 0;

    meanX = meanX + (x/maxValues) - mmX[mmli]/maxValues;
    meanX2 = meanX2 + ((x*x)/maxValues) - mmX[mmli]*mmX[mmli]/maxValues;
    varX = meanX2 - (meanX*meanX);

    meanY = meanY + (y/maxValues) - mmY[mmli]/maxValues;
    meanY2 = meanY2 + ((y*y)/maxValues) - mmY[mmli]*mmY[mmli]/maxValues;
    varY = meanY2 - (meanY*meanY);

    meanXY = meanXY + ((x*y)/maxValues) - mmX[mmli]*mmY[mmli]/maxValues;

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

void LinearRegression::getSlope(){
    return m;
}

void LinearRegression::reset(){
    for (i=0;i<maxValues;i++){
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
