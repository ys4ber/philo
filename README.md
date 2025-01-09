# 🍝 Philosophers

<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/8/81/Dining_philosophers_diagram.jpg/220px-Dining_philosophers_diagram.jpg" alt="Philosophers dining table illustration" />

## 🎯 Project Overview

The Philosophers project is a challenge that deals with the classic dining philosophers problem, teaching the fundamentals of threading and processes. It emphasizes resource sharing, deadlock prevention, and concurrent programming concepts.

## 🧮 The Problem

The problem consists of philosophers sitting at a round table performing three actions:
- Eating 🍽️
- Thinking 🤔
- Sleeping 😴

Each philosopher needs two forks to eat, and there's only one fork between each philosopher. The challenge is to design a solution where no philosopher will starve, avoiding deadlocks and optimizing resource use.

## 🛠️ Prerequisites

To compile and run this project, you will need:

- GCC compiler
- Make
- pthread library
- Unix-based operating system (Linux/Mac)

## 📚 Concepts Covered

- Threads
- Mutexes
- Data races
- Deadlocks
- Resource sharing
- Process synchronization

## 🏗️ Project Structure

```
philosophers/
├── philo/
    ├── src/
    │   ├── main.c
    │   ├── init.c
    │   ├── utils.c
    │   ├── routines.c
    │   └── monitoring.c
    ├── includes/
    │   └── philosophers.h
    └── Makefile

```

## 🚀 Getting Started

1. Clone the repository:
```bash
git clone <your-repo-url> philosophers
```

2. Navigate to the project directory:
```bash
cd philosophers/philo
```

3. Compile the project:
```bash
make
```

4. Run the program:
```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

Example:
```bash
./philo 5 800 200 200 7
```

## 🎮 Program Arguments

- `number_of_philosophers`: The number of philosophers and forks
- `time_to_die`: Time in milliseconds until a philosopher dies from starvation
- `time_to_eat`: Time in milliseconds it takes to eat
- `time_to_sleep`: Time in milliseconds to sleep
- `number_of_times_each_philosopher_must_eat` (optional): Program stops when all philosophers eat this many times

## 🎯 Expected Output

The program will output the state changes of philosophers in the following format:
```
timestamp_in_ms X has taken a fork
timestamp_in_ms X is eating
timestamp_in_ms X is sleeping
timestamp_in_ms X is thinking
timestamp_in_ms X died
```
Where X is the philosopher number.

## ⚠️ Common Issues and Solutions

1. **Data Races**
   - Use mutexes to protect shared resources
   - Implement proper locking mechanisms
   - Avoid global variables when possible

2. **Deadlocks**
   - Implement resource hierarchy
   - Use timeout mechanisms
   - Ensure proper fork allocation

3. **Performance**
   - Minimize critical sections
   - Avoid busy waiting
   - Optimize mutex usage

## 🔍 Testing

Test your program with various scenarios:

```bash
# Basic test
./philo 4 410 200 200

# Test with optional meals
./philo 5 800 200 200 7

# Edge cases
./philo 1 800 200 200
./philo 4 310 200 100
```

## 💡 Tips

- Create a custom timing function instead of using usleep() directly - the system's sleep function isn't precise enough for accurate death detection
- Remember to protect all shared resources with mutexes
- Implement a monitoring system to check for deaths
- Time calculations should be precise
- Clean up all resources properly

## 🔗 Useful Resources

- [POSIX Threads Programming](https://computing.llnl.gov/tutorials/pthreads/)
- [Dining Philosophers Problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [Mutex Tutorial](https://www.geeksforgeeks.org/mutex-lock-for-linux-thread-synchronization/)

## 📝 Evaluation Sheet

Key points that will be checked during evaluation:

- [ ] No data races
- [ ] No memory leaks
- [ ] Proper error handling
- [ ] Correct implementation of death detection
- [ ] Resource cleanup on exit
- [ ] Proper use of mutexes/semaphores
- [ ] Accurate timing management

## ⚖️ License

This project is part of 42 School curriculum. For more information about license, please contact 42.

---

Good luck with your Philosophers project! Remember, the key to success is understanding the synchronization mechanisms and properly managing shared resources. 🚀
