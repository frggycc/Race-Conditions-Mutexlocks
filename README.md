# Mutex Locks - Race Conditions
## Race Condition
This program was initially presented as a simple program that performed stack functions to a single stack. 

The task was to create 200 thread workers that would all modify the same stack, with each thread doing three push and three pop operations 500 times. When this was done, however, a race condition was created because 200 threads were modifying a single resource in no particular order.

Below are some of the errors that was ran into:

![Screenshot from 2024-10-31 16-40-08](https://github.com/user-attachments/assets/fd8a8b18-e00e-4ec2-b414-d6543ab6bbf7)

## Solution
The solution to avoiding these errors was to create a mutex lock that would only allow a single thread to hold onto the shared stack until it was finished with its pop or push operation. 

When applied, running the program multiple times did not incur any errors, as shown below when mutex locks were in place:

![Screenshot from 2024-10-31 16-50-56](https://github.com/user-attachments/assets/48d8dbd8-95d5-4d0a-9266-885397a0bfbc)
