## Queue Performance Experiments

Oliver Michel, 2018,  *oliver dot michel at colorado dot edu*

### Queue Implementations

|Name          |Memory Layout      |Thread Safety     |
|--------------|-------------------|------------------|
|queue1        |Linked List        |Locks             |
|queue2        |Array              |Locks             |
|queue3        |Linked List        |Atomic Variables  |
|moodycamel    |Array              |Atomic Variables  |

### Run Basic Experiment

#### Run Experiment

    ./queue_comparison.sh <numa> <queue_name> <n> <b> <c1> <c2>


* `numa`: 0 to disable numa support, 1 to enable
* `n`: number of repetitions of experiment
* `b`: number of bytes to be passed for each element
* `c1`: number of elements (in millions) to be passed in each experiment for queue 1 and queue 2
* `c2`: number of elements (in millions) to be passed in each experiment for queue 3 and mc queue

for example `./queue_comparison 0 5 32 1 5`
