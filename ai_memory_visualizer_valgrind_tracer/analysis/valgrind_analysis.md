# Valgrind Analysis

## heap_example.c

### Valgrind Warning

Memory Leak

### Explanation

The program creates two `Person` objects: Alice and Bob.

Bob is freed correctly:

```c
free(bob->name);
free(bob);
```

Alice is not freed correctly.

The function

```c
person_free_partial(alice);
```

only calls:

```c
free(alice);
```

The memory for `alice->name` is never freed.

This causes a memory leak because the program loses the pointer to the string before freeing it.

---

## aliasing_example.c

### Valgrind Warning

Invalid Read (Use-After-Free)

### Explanation

The program creates an array and stores its address in `a`.

Then:

```c
b = a;
```

Now both pointers point to the same memory.

Later the program calls:

```c
free(a);
```

The heap memory is released.

After that, the program reads:

```c
b[2]
```

This is a **use-after-free** because `b` still points to memory that has already been freed.

---

### Valgrind Warning

Invalid Write (Use-After-Free)

### Explanation

After the memory is freed, the program writes:

```c
b[3] = 1234;
```

This writes to memory that no longer belongs to the program.

Valgrind reports this as an Invalid Write.

---

## stack_example.c

### Valgrind Result

No memory errors are expected.

### Explanation

This program only uses stack variables.

It does not use `malloc()` or `free()`.

All local variables are removed automatically when each function returns.

---

# AI Review

The AI said that after calling:

```c
free(a);
```

pointer `b` becomes `NULL`.

This is not correct.

`free()` only releases the heap memory.

It does not change any pointer.

After `free(a)`, both `a` and `b` still contain the same address, but that address is no longer valid.

Both pointers become **dangling pointers**, and using them causes **use-after-free**.

---

# Summary

| Program | Valgrind Result | Reason |
|---------|-----------------|--------|
| stack_example.c | No errors | Only stack memory is used. |
| heap_example.c | Memory Leak | `alice->name` is never freed. |
| aliasing_example.c | Invalid Read | Reading memory after `free()`. |
| aliasing_example.c | Invalid Write | Writing to memory after `free()`. |
