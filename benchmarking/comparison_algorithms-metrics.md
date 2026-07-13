# Algorithmic Efficiency Comparison

## 1

```
Naive algorithm result: 625025000
Naive algorithm time: 0.786158 seconds
Single-pass algorithm result: 25000
Single-pass algorithm time: 0.000031 seconds
```

## 2

```
Naive algorithm result: 625025000
Naive algorithm time: 0.784937 seconds
Single-pass algorithm result: 25000
Single-pass algorithm time: 0.000038 seconds
```

## 3

```
Naive algorithm result: 625025000
Naive algorithm time: 0.777397 seconds
Single-pass algorithm result: 25000
Single-pass algorithm time: 0.000031 seconds
```

## average execution time
<!--(0.786158 + 0.784937 + 0.777397) / 3 = 0.782831 seconds -->
<!--(0.000031 + 0.000038 + 0.000031) / 3 = 0.000033 seconds-->
- Naive algorithm: **0.782831 seconds**
- Single-pass algorithm: **0.000033 seconds**

## relative difference
<!--0.782831 / 0.000033333 ≈ 23,485-->
The naive implementation is  **23,485 times slower** than the single-pass implementation
