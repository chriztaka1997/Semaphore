# Semaphore

This is a simple programming assignment to give you experience with programmming semaphores and shared memory in Linux environment.

Four shared resources (e.g. account balances) are needed. Create a shared memory segment with 4 float variables, as the shared resources. Each resource is manipulated independently and concurrently by 10 processes. Initialize each variable to some non-zero value.

Each process iterates in a loop some fixed number of times. Each iteration through the loop, it generates a random value beta between -0.5 and 0.5, inclusive. It then selects one random shared variable (possibly a different variable on each loop iteration) and updates it by either adding or subtracting a fraction of its current value, according to the value of beta. Ignore arithmetic overflow or underflow.
