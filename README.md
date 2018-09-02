## Queue Performance Experiments

Oliver Michel, 2018,  *oliver dot michel at colorado dot edu*

### Compilation

*e.g., release build with GCC 8:*

```bash
    mkdir build && cd build
    cmake -DCMAKE_CXX_COMPILER=g++-8 -DCMAKE_BUILD_TYPE=Release ..
    make 
```

### Queue Implementations

|Name          |Memory Layout      |Thread Safety     |
|--------------|-------------------|------------------|
|queue1        |Linked List        |Locks             |
|queue2        |Array              |Locks             |
|queue3        |Linked List        |Atomic Variables  |
|queue4        |Array              |Atomic Variables  |
|queue5        |Array              |Atomic Variables  |
|moodycamel    |Array              |Atomic Variables  |

### Queue Comparison

```bash
    ./comparison.sh <numa> <queue_name> <n> <b> <c1> <c2>
```

* `numa`: 0 to disable numa support, 1 to enable
* `n`: number of repetitions of experiment
* `b`: number of bytes to be passed for each element
* `c1`: number of elements to be passed in each experiment for queue 1 and queue 2
* `c2`: number of elements to be passed in each experiment for queue 3 and mc queue

*e.g.,* `./comparison.sh 0 5 32 1000000 25000000`

### Queue 5 Details

```bash
    ./queue5_detail.sh <numa> <n> <b> <c>
```

* `numa`: 0 to disable numa support, 1 to enable
* `n`: number of repetitions of experiment
* `b`: number of bytes to be passed for each element
* `c`: number of elements to be passed in each experiment

*e.g.,* `./queue5_detail.sh 0 5 32 25000000`
