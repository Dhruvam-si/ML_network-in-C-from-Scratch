# Neural Network From Scratch in C++

A fully connected feed-forward neural network implemented entirely from scratch in modern C++ without using any machine learning libraries.

This project was built to understand every mathematical and engineering component behind neural networks rather than relying on frameworks.

---

## Project Status

This repo contains two implementations:

- **`xor.cpp`** — the original hardcoded 2→2→1 network. Complete, trained, and working (see results below).
- **`matrix.h` + `xor2.cpp`** — a generalized rewrite using a from-scratch `Matrix` class, designed to support arbitrary layer counts and sizes instead of hardcoded neurons. Currently in progress: matrix operations, forward pass, and cost function are complete; backpropagation is being built out.

---

## Features (xor.cpp)

- Feed Forward Neural Network (2 → 2 → 1)
- Sigmoid Activation Function
- Mean Squared Error (MSE) Loss
- Manual Backpropagation
- Gradient Descent
- Multi-Epoch Training
- Random Weight Initialization
- Model Save & Load (`xor.nn`)
- XOR Dataset Training

---

## Network Architecture

```
Input Layer
    x
    y
     │
     ▼
Hidden Layer
  Neuron 1
  Neuron 2
     │
     ▼
Output Layer
  Neuron
```

Activation Function:

- Sigmoid

Loss Function:

- Mean Squared Error (MSE)

Optimizer:

- Gradient Descent

---

## Project Structure

```
.
├── main.cpp
├── matrix.h        # Custom Matrix class (add, subtract, hadamard, transpose, multiply, applyFunction)
├── xor.cpp         # Original hardcoded implementation
├── xor2.cpp        # Generalized, matrix-based implementation (in progress)
├── xor.nn          # Saved model parameters
└── README.md
```

---

## Matrix Class (`matrix.h`)

A from-scratch `Matrix` class built to generalize the network beyond fixed neuron counts. Implements:

- Addition, Subtraction, Hadamard (elementwise) product
- Transpose
- Matrix multiplication (dot-product based)
- `applyFunction` — applies any `double(double)` function elementwise (e.g. sigmoid)

Used as the foundation for a `Network` class that stores weights and biases as `vector<Matrix>`, so the number of layers is no longer hardcoded — architecture is defined by a single `layer_sizes` list (e.g. `{2, 2, 1}`).

---

## Model Persistence

The neural network stores its learned parameters inside a model file.

```
Program Start
        │
        ▼
Load xor.nn
        │
        ▼
Forward Pass
        │
        ▼
Training
        │
        ▼
Save xor.nn
```

The model file contains:

- Learning Rate
- Hidden Layer Weights
- Hidden Layer Biases
- Output Layer Weights
- Output Layer Bias

Example:

```
LearningRate
0.55

HiddenNeuron1
w1 ...
w2 ...
b1 ...

HiddenNeuron2
w3 ...
w4 ...
b2 ...

OutputNeuron
w5 ...
w6 ...
b3 ...
```

---

## Training

The network is trained on the XOR truth table.

| x | y | Expected |
|---|---|----------|
|0|0|0|
|0|1|1|
|1|0|1|
|1|1|0|

---

## Sample Result (xor.cpp)

```
Epoch: 10000
Cost: 0.000184
```

Predictions

```
0 XOR 0 → 0.0148
0 XOR 1 → 0.9844
1 XOR 0 → 0.9845
1 XOR 1 → 0.0192
```

---

## Mathematical Concepts Implemented

- Forward Propagation
- Sigmoid Derivative
- Chain Rule
- Hidden Layer Backpropagation
- Output Layer Backpropagation
- Gradient Descent
- Weight Updates
- Bias Updates

---

## Future Improvements

- Complete backpropagation for the generalized `Network` class
- Weight/bias updates and full training loop for `xor2.cpp`
- Multiple hidden layers, arbitrary depth
- Softmax output
- Cross-Entropy loss
- Mini-batch Gradient Descent
- MNIST Digit Recognition
- Model checkpoints (architecture + weights, not just weights)

---

## Built Without

- TensorFlow
- PyTorch
- Eigen
- Any Machine Learning Library

Everything, including matrix operations, forward propagation, backpropagation, gradient computation, gradient descent, and model serialization, is implemented manually in C++.

---

## License

MIT License
