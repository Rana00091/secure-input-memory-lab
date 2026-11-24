# Dangling Pointers & Memory Lifetime Analysis

## 1. Dynamic Memory Allocation

Identify all dynamic memory allocations.

| Source File | Function | Pointer | Allocation Size |
|---|---|---|---|
| user_input.c | read_username | username | strlen(buffer) + 1 |

## 2. Memory Deallocation

Identify where each allocation is freed.

| Source File | Function | Pointer | Line |
|---|---|---|---|
| session.c | session_destroy | session->username | 33 |
| main.c | main | username | 33 |

## 3. Pointer Propagation

Describe how the allocated pointer moves between functions and modules.

- Allocation function:
- Receiving function:
- Pointer passed to:
- Pointer stored in:

## 4. Ownership Analysis

- Is ownership clearly defined?
- Which function is responsible for freeing the allocation?
- Do multiple functions attempt to free the same allocation?
- Is ownership transferred explicitly or implicitly?

## 5. Memory Lifetime Analysis

Identify when the allocation becomes invalid.

- Allocation point:
- Deallocation point:
- First access after deallocation:
- Additional deallocation attempts:

## 6. Identified Memory Errors

| Error | Function | Source File | Evidence |
|---|---|---|---|
| Use-After-Free | main | main.c | Invalid read |
| Double Free | main | main.c | Invalid free |

## 7. Error Path Analysis

Explain whether different execution paths or function call orders could cause memory ownership problems.

## 8. Conclusion

Summarize the ownership problems, pointer lifetime issues, and memory errors identified in the program.

No source code modifications were made during this analysis.
