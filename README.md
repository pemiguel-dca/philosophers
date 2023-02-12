This project is about learning how threads work by precisely timing a group of philosophers on when to pick up forks and eat spaghetti without dying from hunger.

**Example where all of them finished their meals**:

![image1](https://live.staticflickr.com/65535/52685145303_26e95e633d_b.jpg)

## Introduction

The  program takes the following arguments respectively:

- number_of_philosophers: The number of philosophers and also the number
of forks.

- time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die
milliseconds since the beginning of their last meal or the beginning of the simulation, they die.

- time_to_eat (in milliseconds): The time it takes for a philosopher to eat.
During that time, they will need to hold two forks.

- time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.

- number_of_times_each_philosopher_must_eat (optional argument): If all
philosophers have eaten at least number_of_times_each_philosopher_must_eat
times, the simulation stops. If not specified, the simulation stops when a
philosopher dies.

Each philosopher has a number ranging from 1 to **number_of_philosophers**.

Philosopher number 1 sits next to philosopher number **number_of_philosophers**.
Any other philosopher number N sits between philosopher number N - 1 and philosopher number N + 1

### Rules

The specific rules for the mandatory part are:
- Each philosopher should be a thread.
- There is one fork between each pair of philosophers. Therefore, if there are several
philosophers, each philosopher has a fork on their left side and a fork on their right
side. If there is only one philosopher, there should be only one fork on the table.

- To prevent philosophers from duplicating forks, you should protect the forks state
with a mutex for each of them.

## Clone

```bash
git clone https://github.com/pemiguel-dca/philosophers.git
```
When you have cloned the repo, you just need to run ```make``` inside of the 'src/philo', or for the bonus, 'src/philo_bonus'.

## Philo

To execute the program you have to follow the rules that I mention earlier, but here's an example:

```bash
./philo 2 400 100 50 3
```

If you wanna check if all messages are printing correctly you can try this way:

```bash
./philo 2 400 100 50 3 | grep "is eating 🍜" | wc -l
```

This way you will be able to see how many of them actually eat, and confirm if everything is working as expectedly.