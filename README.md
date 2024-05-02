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

1. The example executable files will be generated in the `build/examples/` directory.

1. Run the executable, for example:

    ```bash
    ./examples/multiLqr
    ```

1. If you wish to run other YAML config files, add the file path after the executable. For example:

    ```bash
    ./examples/singleLqr ../config/singleLqrExample2.yaml
    ```

## Tutorial

### Single Discrete-time LQR Gain

Let's say you want to calculate the gain matrix $\mathbf{K}$ of a single discrete-time LQR controller for a discrete-time linear time-invariant (LTI) system given by:

$\mathbf{x}[k+1]=\mathbf{A}_d\mathbf{x}[k] + \mathbf{B}_d\mathbf{u}[k]$

$\mathbf{y}[k]=\mathbf{C}_d\mathbf{x}[k]+\mathbf{D}_d\mathbf{u}[k]$

Define the parameters $\mathbf{A}_d$, $\mathbf{B}_d$, $\mathbf{C}_d$, $\mathbf{D}_d$, and the sampling period (in unit of seconds) in the following YAML config:

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

However, what if you only know the continuous-time LTI state space:

$\dot{\mathbf{x}}(t)=\mathbf{A}\mathbf{x}(t) + \mathbf{B}\mathbf{u}(t)$

$\mathbf{y}(t)=\mathbf{C}\mathbf{x}(t)+\mathbf{D}\mathbf{u}(t)$

How would you design a discrete-time LQR controller for this system?

Just define the continuous-time parameters $\mathbf{A}$, $\mathbf{B}$, $\mathbf{C}$, and $\mathbf{D}$ in a YAML config file as:

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

Notice that by setting the `samplingPeriod` parameter, the continuous-time system will be automatically discretized into its equivalent discrete-time model.  
As of now, the default discretization method is the zero-order hold (ZOH).

Set the state cost $\mathbf{Q}$ and input cost $\mathbf{R}$ weight matrices:

```yaml
weights:
    Q: [40,0,
        0,1]
    R: [1]
```

Running the `./examples/singleLqr` example will result in a $\mathbf{K} \in \mathbb{R}^{1\times2}$ gain matrix of type Eigen::MatrixXd with the values:

```bash
[Dlqr] Finished loading config constructor: ../config/singleLqr.yaml

Single discrete-time LQR gain K: 
 2.74311 0.506378
```

### Multiple Discrete-time LQR Gains

You can also calculate the gains for multiple LQR controllers. First, define a YAML node named `LqrVariants:` to indicate that there will be multiple LQR configurations.  
Then define multiple nodes for each LQR configuration.  
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

Running the `./examples/multiLqr` example will result in a std::map where the keys are the configuration names and the values are the gain matrices:

```bash
[MultiLqrManager] Finished loading config constructor: ../config/multiLqr.yaml

Multiple discrete-time LQR gains: 
High Config Gain:  3.8063 0.52682
Medium Config Gain:  2.74306 0.506336
Zero Config Gain: 0 0
```