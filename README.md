# LinearRegressino 

Library to calculate linear regression in arduino ( [Better use Regressino a new library with linear regression and more](https://github.com/cubiwan/Regressino) )
You can use it on live data to calculate a mobile Linear regression on the last n samples


### Create

```c
LinearRegression lr = LinearRegression();
```

```c
LinearRegression lr = LinearRegression(0,100);
```

### Methods
```c
LinearRegression();  
```

Initializes object 

```c
LinearRegression(int min, int max);  
```

Initializes the object with limits to the value of X
* min: min value of X
* max: max value of X

```c
void learn(int x, int y);  
```

Learns one example.
* x: value of X
* y: value of Y

```c
double calculate(int x);  
```

Estimates value of Y for X
* x: value of x 

```c
double correlation();  
```

Return actual correlation value

```c
void reset();  
```

Reset values. Start learning since zero.

```c
void getValues(double values[]);
```

Returns parameters of the linear regression
* values[0] = m;
* values[1] = b;
* values[2] = n;

**Y = m*X + b**   

**n** is the number of examples
