# multi-lqr-yaml

A C++ library for calculating multiple linear quadratic regulator (LQR) controller gains from a YAML config file.

## Dependencies

1. [CMake](https://cmake.org/download/)

1. [Eigen 3.4.0](http://eigen.tuxfamily.org/index.php?title=Main_Page#Download)

1. [yaml-cpp](https://github.com/jbeder/yaml-cpp)

## Build & Run

1. Make sure you have installed the dependencies.

1. Open a new command line terminal. Clone the repository

    ```bash
    git clone https://github.com/BagaskaraPutra/multi-lqr-yaml.git
    ```

1. Build the project using CMake.

    ```bash
    cd multi-lqr-yaml
    mkdir build
    cd build
    cmake ..
    make
    ```

1. The example executable files will be generated in the `build/examples/` directory

1. Run the executable, for example:

    ```bash
    ./examples/multiLqr
    ```

## Tutorial

### Single Discrete-time LQR Gain

Let's say you want to calculate the gain matrix $\mathbf{K}$ of a single discrete-time LQR controller.  
However, you only have the continous-time linear time-invariant (LTI) state space:

$\dot{\mathbf{x}}(t)=\mathbf{A}\mathbf{x}(t) + \mathbf{B}\mathbf{u}(t)$

$\mathbf{y}(t)=\mathbf{C}\mathbf{x}(t)+\mathbf{D}\mathbf{u}(t)$

where the parameters $\mathbf{A}$, $\mathbf{B}$, $\mathbf{C}$, and $\mathbf{D}$ are defined in a YAML config file

```yaml
stateSpace:
    num_inputs: 1
    num_states: 2
    num_outputs: 2
    continuous:
        A: [0.05945,0.92220,
            -25.86632,-5.08911]
        B: [-0.13123,
            62.75906]
        C: [1,0,
            0,1]
        D: [0,
            0]
        samplingPeriod: 0.024
```

By setting the `samplingPeriod` parameter, the continuous-time system will be automatically discretized into its equivalent discrete-time model:

$\mathbf{x}[k+1]=\mathbf{A}_d\mathbf{x}[k] + \mathbf{B}_d\mathbf{u}[k]$

$\mathbf{y}[k]=\mathbf{C}_d\mathbf{x}[k]+\mathbf{D}_d\mathbf{u}[k]$

However, if you already have a discrete-time system parameters $\mathbf{A}_d$, $\mathbf{B}_d$, $\mathbf{C}_d$, and $\mathbf{D}_d$, just define it as the following YAML config:

```yaml
stateSpace:
    num_inputs: 1
    num_states: 2
    num_outputs: 2
    discrete:
        A: [0.99483,0.02080,
            -0.58350,0.87868]
        B: [0.01286,
            1.41565]
        C: [1,0,
            0,1]
        D: [0,
            0]
        samplingPeriod: 0.024
```

Set the state cost $\mathbf{Q}$ and input cost $\mathbf{R}$ weight matrices

```yaml
weights:
    Q: [40,0,
        0,1]
    R: [1]
```

### Multiple Discrete-time LQR Gains

You can also calculate the gains for multiple LQR controllers. First, define a YAML node named `LqrVariants:` to indicate that there will be multiple LQR configruations.  
Then define multiple nodes  for each LQR configuration.  
For example in the `config/multiLqr.yaml`, we define the configurations `Zero:`, `Medium:`, and `High:`.

```yaml
LqrVariants:
    Zero:
        stateSpace:
            ...
        weights:
            ...
    Medium:
        stateSpace:
            num_inputs: 1
            num_states: 2
            num_outputs: 2
            discrete:
                A: [0.99483, 0.02080,
                    -0.58350, 0.87868]
                B: [0.01286,
                    1.41565]
                C: [1,0,
                    0,1]
                D: [0,
                    0]
                samplingPeriod: 0.024
        weights:
            Q: [40,0,
                0,1]
            R: [1]   
    High:
        stateSpace:
            ...
        weights:
            ...
```
