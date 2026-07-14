# green_efficiency_analysis.md

## Green Efficiency Analysis

To evaluate the efficiency of the provided programs I used the benchmarking files without changing their algorithmic behavior. All source files were compiled using the required compiler flags and execution time was measured with the `clock()` function from the C standard library. The elapsed time was calculated by dividing the difference between the start and end clock values by `CLOCKS_PER_SEC`.
To reduce the effect of random timing variations I ran both the baseline program and the algorithm comparison program three consecutive times on the same machine. For the comparison benchmark I recorded the execution time of each implementation and calculated the average execution time. In the instrumentation experiment I added timing measurements around each processing phase to measure the time spent building the dataset processing it reducing it to a checksum and executing the entire program.

## Observed Performance Differences

The baseline benchmark produced very similar execution times across the three runs. The recorded times were **0.080281** **0.079081** and **0.078717** seconds. The small differences show that execution time was consistent across the runs even though slight variations are expected because of normal system activity.
The comparison benchmark showed a much larger difference between the two implementations. The naive algorithm took **0.786158** **0.784937** and **0.777397** seconds with an average execution time of **0.782831** seconds. The single-pass algorithm completed in **0.000031** **0.000038** and **0.000031** seconds with an average of about **0.000033** seconds.
Using these averages the naive implementation was about 23,485 times slower than the single-pass implementation. Although both implementations solved the same problem the naive version repeatedly processed values that had already been examined while the single-pass version visited each element only once. The execution times clearly show how algorithm design can have a major effect on performance.
The instrumentation experiment also helped identify where the program spent most of its time. The total execution time was **0.000819** seconds. The build phase took **0.000260** seconds the process phase took **0.000370** seconds and the reduce phase took **0.000181** seconds. The processing phase required the most time during execution.

## Relation Between Runtime and Energy Consumption

This project did not measure actual electrical power usage so it is not possible to calculate energy consumption directly. However execution time is still a useful indicator because a program that keeps the CPU busy for a longer period will usually consume more energy than one that completes the same work more quickly.
The results support this idea. The naive algorithm spent much more time executing than the single-pass implementation which suggests that it would also require more CPU activity. Improving algorithm efficiency reduces unnecessary computation and can make software more resource efficient especially when the same code runs repeatedly or processes large amounts of data.

## Limitations of the Experiment

One limitation of this experiment is that it measures only CPU execution time rather than actual power consumption. Other factors such as processor frequency memory usage operating system scheduling and background processes can also affect energy usage but were not measured.
Another limitation is that all tests were performed on a single machine using a fixed dataset size. Different hardware or larger datasets could produce different execution times even though the overall performance trend would probably remain the same.

## Practical Engineering Takeaway

This project showed the importance of measuring performance instead of making assumptions. Running each program several times and calculating average execution times produced more reliable results than relying on a single execution.
The experiments also demonstrated that choosing an efficient algorithm can greatly reduce execution time. In this case the single-pass implementation completed the same task much faster than the naive approach. Writing efficient code improves performance reduces unnecessary CPU usage and supports more sustainable software.

