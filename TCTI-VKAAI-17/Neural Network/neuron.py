import random
random.seed(0)

from numpy import dot, exp
from typing import List


class Neuron:
    def __init__(self, n_weights : int) -> None:
        '''
            Initialize the Neuron.
                By default, allocate random weights and random bias
        '''
        self.weights = [random.uniform(-1,1) for _ in range(n_weights)] 
        self.bias =  random.uniform(-1,1)
        self.output = 0.0
        self.gradient = 0.0 
        self.weighted_sum = 0.0 
    
    def sigmoid(self, x : float) -> float:
        return 1 / (1 + exp(-x))
        
    def der_sigmoid(self, x : float) -> float:
        return self.sigmoid(x) * (1 - self.sigmoid(x))
    
    def activate(self, inputs : List[float]) -> float:
        # activation_func( weights * outputs of prev layer ) + bias
        self.weighted_sum = dot(self.weights, inputs) + self.bias
        return self.sigmoid(self.weighted_sum)
    
    def calc_gradient(self, x : float) -> float:
        return self.der_sigmoid(self.weighted_sum) * x
    
    def update_weight_bias(self, inputs : List[float], learning_rate : float ) -> None:
        # new_weight= old_weight + learning_rate * gradient * input of prev neuron
        for i in range(len(self.weights)):
            self.weights[i] += learning_rate * self.gradient * inputs[i]
        
        # new_bias = old_bias + learning_rate * gradient
        self.bias += learning_rate * self.gradient
            
 