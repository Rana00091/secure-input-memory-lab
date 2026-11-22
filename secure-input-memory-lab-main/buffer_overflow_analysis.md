# Unsafe Input & Buffer Overflow Analysis

## 1. Stack Buffer Identification

**File:** `user_input.c`

**Variable:**
```c
char buffer[32];
```

- Memory location: Stack
- Buffer capacity: 32 bytes
- Maximum input length: 31 characters, including space for the null terminator.

## 2. Input Handling

The program uses:

```c
scanf("%s", buffer);
```

The `%s` conversion does not enforce a maximum input width.

Therefore, user-controlled input can exceed the buffer capacity.

## 3. Numeric Overflow Boundary

Buffer capacity = 32 bytes.

Required memory = Input length + 1 byte for `\0`.

The overflow condition is:

`Input length + 1 > 32`

Therefore, an input of 32 characters or more can overflow the buffer.

## 4. Heap Allocation Analysis

The program subsequently uses:

```c
username = malloc(strlen(buffer) + 1);
```

This allocation does not protect the stack buffer because the input is written into the stack buffer before the heap allocation occurs.

An overflow may therefore happen before `malloc()` executes.

## 5. Missing Safety Invariants

- No enforced maximum input length.
- No guaranteed protection against writing beyond the stack buffer.
- No explicit input-boundary validation.
- Heap allocation occurs after the initial input operation.

## 6. Hardening Plan (No Code Changes)

- Enforce a maximum input length.
- Guarantee null termination.
- Validate input before using its length.
- Ensure allocation size matches the validated input length.
- Ensure copying never exceeds destination capacity.
- Test normal, boundary, and oversized inputs.

## 7. Conclusion

The main identified vulnerability is the unbounded input operation in `read_username()`.

The fixed-size stack buffer has a capacity of 32 bytes, but the input operation does not enforce this limit.

Consequently, oversized input can cause a stack buffer overflow before heap allocation takes place.
