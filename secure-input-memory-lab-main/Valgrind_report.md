# Memory Error Detection Report

## 1. Compilation

The project was compiled using strict compiler warnings and debugging symbols.

```bash
gcc -std=gnu89 -Wall -Wextra -Werror -pedantic -g src/*.c -o secure_input
```

## 2. Normal Input Test

**Test:** Executed the program using a normal-length username.

**Valgrind command:**

```bash
valgrind --leak-check=full \
--show-leak-kinds=all \
--track-origins=yes \
./secure_input
```

**Results:**

- Total errors: 14
- Error contexts: 6
- Invalid reads detected.
- Invalid free detected.
- No memory leaks reported.

### First reported error

```text
Invalid read of size 1
at strlen
by __vfprintf_internal
by printf (printf.c:33)
by main (main.c:31)
```

**Memory allocation and deallocation trace:**

- Allocated in `read_username()` – `user_input.c:13`.
- Freed in `session_destroy()` – `session.c:33`.
- Accessed again in `main()` – `main.c:31`.

**Classification:** Use-After-Free.

Another error was reported:

```text
Invalid free()
by main (main.c:33)
```

**Classification:** Double Free. The same memory block was freed previously in `session_destroy()`.

## 3. Boundary Input Test

**Test:** Executed the program using a longer-than-usual username.

**Results:**

- Total errors: 107
- Error contexts: 6
- Invalid reads detected.
- Invalid free detected.
- No memory leaks reported.

### First reported error

```text
Invalid read of size 1
at strlen
by __vfprintf_internal
by printf (printf.c:33)
by main (main.c:31)
```

The memory block was allocated in `read_username()` and subsequently freed in `session_destroy()` before being accessed again.

**Classification:** Use-After-Free.

An additional invalid free was reported at `main.c:33`, indicating a second attempt to free the same memory block.

**Classification:** Double Free.

## 4. Identified Memory Errors

| Error | Source file | Function | Line |
|---|---|---|---|
| Use-After-Free | main.c | main | 31 |
| First deallocation | session.c | session_destroy | 33 |
| Double Free | main.c | main | 33 |
| Original allocation | user_input.c | read_username | 13 |

## 5. Normal vs Boundary Input Comparison

Both test cases produced memory errors.

The normal input generated 14 errors, while the boundary input generated 107 errors. Both reported 6 error contexts.

The main identified problems were Use-After-Free and Double Free.

No memory leaks were reported in either test.

The increased number of errors with boundary input indicates that input length affects the observed error count. However, the supplied output does not establish a separate buffer overflow error.

## 6. Conclusion

Valgrind identified memory management problems involving invalid memory access and repeated deallocation.

The main issue is that the username memory is freed inside `session_destroy()` and subsequently accessed by `main()`. The program then attempts to free the same memory again.

Although no memory leaks were reported, the program is not memory-safe.

The results demonstrate that successful memory deallocation does not necessarily mean memory is being managed correctly.
