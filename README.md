# Neural-Network

This repository is a personal project I started to gain a better understanding of how simple (and complex) neural network systems work. I hope to add more to this repository in the future.  
  
I originally wrote the basic network by following [3Blue1Brown's Neural Network Video](https://www.youtube.com/watch?v=aircAruvnKk)
## How to Run
***Work on my PC***  
1. Start by downloading the MNIST data set, move the following files into the root folder
```
train-images.idx3-ubyte
train-labels.idx1-ubyte
t10k-images.idx3-ubyte
t10k-labels.idx1-ubyte
```
2. Then run the command `make`  
3. This should make a `Run.exe` file  
4. Running the `Run.exe` file will execute main in the `Driver.cc` file

## Notes
- On average, I see an accuracy of just above 89% (on the BasicNetwork)
- BitNetwork is a WIP (an Idea after I saw [this research paper](https://arxiv.org/abs/2402.17764))
  - Untested and probably not made correct (if I have even started on it, which I have not at time of writting)
- The Matrix class is garbage (I'm not sorry; it does what I want it to)
- The `bias` variable exists... but I never implemented it