# Neural-Network
## How to Run (via windows 11)
Start by downloading the MNIST data set, move the following files into the root folder
```
train-images.idx3-ubyte
train-labels.idx1-ubyte
t10k-images.idx3-ubyte
t10k-labels.idx1-ubyte
```
Then run the command `make`  
This should make the file `Ner.exe`  
which when run will:  
1) Create a new network based on the variable `a` in Network.cc and assing the weights random values between 1 and -1
   1) Ie `int a[] = {784, 16 ,10};`
   2) The first number must be 784 and the last 10 for the MNIST set
2) Train the network once on the train MNIST set
3) Check how accurate the network is against the t10k MNIST set

