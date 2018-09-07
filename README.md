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

|Name      |Memory Layout|Thread Safety  |Zero-Copy Enqueue|
|----------|-------------|---------------|-----------------|
|queue1    |Linked List  |Locks          |no               |
|queue2    |Array        |Locks          |no               |
|queue3    |Linked List  |Memory Barriers|no               |
|queue4    |Array        |Memory Barriers|available        |
|queue5    |Array        |Memory Barriers|available        |
|moodycamel|Array        |Memory Barriers|available        |

### Queue Comparison

```bash
./comparison.sh <numa> <n> <b> <c1> <c2>
```

* `numa`: 0 to disable numa support, 1 to enable
* `n`: number of repetitions of experiment
* `b`: number of bytes to be passed for each element
* `c1`: number of elements to be passed in each experiment for queues 1,2,3
* `c2`: number of elements to be passed in each experiment for queues 4,5 and mc queue

*e.g.,* `./comparison.sh 0 5 32 1000000 25000000`

### Queue 5 Batching

```bash
./queue5_batch.sh <numa> <n> <b> <Bmax>
```

### Queue 5 Details

```bash
./queue5_detail.sh <numa> <n> <b> <c>
```

* `numa`: 0 to disable numa support, 1 to enable
* `n`: number of repetitions of experiment
* `b`: number of bytes to be passed for each element
* `c`: number of elements to be passed in each experiment

*e.g.,* `./queue5_detail.sh 0 5 32 25000000`
