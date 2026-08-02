# Memory Maps

## stack_example.c

### Step 1

The program starts in `main()`.

Only the `main()` stack frame exists.

```
Stack
+------------+
| main()     |
+------------+

Heap
(empty)
```

There is no heap memory in this program.

---

### Step 2

`main()` calls `walk_stack()`.

A new stack frame is created.

Variables:

- depth
- max_depth
- marker

```
Stack

+------------------+
| walk_stack()     |
| marker           |
+------------------+
| main()           |
+------------------+
```

`marker` exists only while the function is running.

---

### Step 3

`walk_stack()` calls `dump_frame()`.

A new stack frame is added.

Variables:

- local_int
- local_buf
- p_local

`p_local` points to `local_int`.

```
p_local
   |
   v
local_int
```

---

### Step 4

The function calls itself again.

Each recursive call creates a new stack frame.

Each frame has its own copy of the local variables.

---

### Step 5

When a function returns, its stack frame is removed.

All local variables disappear.

There is no heap allocation in this program.

---

## heap_example.c

### Step 1

The program creates two people:

- Alice
- Bob

Each person has:

- a `Person` structure
- a `name` string

Both are allocated on the heap.

```
alice ---> Person ---> "Alice"

bob -----> Person ---> "Bob"
```

---

### Step 2

Bob is freed correctly.

```
free(bob->name);
free(bob);
```

Both allocations are released.

---

### Step 3

Alice is not freed correctly.

The program calls:

```c
person_free_partial(alice);
```

This function only does:

```c
free(alice);
```

The string `"Alice"` is never freed.

This causes a memory leak.

---

### Ownership

`alice` owns:

- the Person structure
- the name string

Both should be freed.

---

## aliasing_example.c

### Step 1

Memory is allocated.

```
a
 |
 v

Heap

[0][11][22][33][44]
```

---

### Step 2

The program does:

```c
b = a;
```

Now both pointers point to the same memory.

```
a ----+

      |

b ----+

      |

      v

Heap

[0][11][22][33][44]
```

This is called **pointer aliasing**.

---

### Step 3

The program calls:

```c
free(a);
```

The heap memory is released.

Both `a` and `b` now point to freed memory.

Both are dangling pointers.

---

### Step 4

The program reads:

```c
b[2]
```

This is an invalid read because the memory has already been freed.

---

### Step 5

The program writes:

```c
b[3] = 1234;
```

This is an invalid write.

Both operations are Undefined Behavior.

---

# AI Review

The AI said that after calling `free(a)`, pointer `b` becomes `NULL`.

This is not correct.

`free()` only releases the heap memory.

It does not change the value of any pointer.

After `free(a)`, both `a` and `b` still contain the same address, but that address is no longer valid.

Both pointers become dangling pointers, and using them causes Undefined Behavior.
