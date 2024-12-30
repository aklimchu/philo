# Philosophers
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://opensource.org/licenses/GPL-3.0)
Solving famous "Dining philosophers problem"  One or more philosophers sit at a round table.
There is a large bowl of spaghetti in the middle of the table.
• The philosophers alternatively eat, think, or sleep.
While they are eating, they are not thinking nor sleeping;
while thinking, they are not eating nor sleeping;
and, of course, while sleeping, they are not eating nor thinking.
• There are also forks on the table. There are as many forks as philosophers.
• Because serving and eating spaghetti with only one fork is very inconvenient, a
philosopher takes their right and their left forks to eat, one in each hand.
• When a philosopher has finished eating, they put their forks back on the table and
start sleeping. Once awake, they start thinking again. The simulation stops when
a philosopher dies of starvation.

## ✨ Features
- Uses a thread for each philosopher
- Creates multiple mutexes to ensure that there are no data races
- A message announcing a philosopher died is be displayed no more than 10 ms after the actual death of the philosopher.

## 📚 Table of Contents
- [Installation](#-installation)
- [Building the Program](#️-build-the-program)
- [Running the Program](#-running-the-program)
- [Cleaning Up](#-cleaning-up)
- [License](#license)

## 🚀 Installation!

Clone the repository and navigate to the project directory:
```bash
git clone https://github.com/aklimchu/philo.git
cd philo/philo
```
## 🛠️ Build the Program!

### Use `make` command to create the program:
```bash
make
```

## 🎮 Running the Program

* #### Philosophers:
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep
[number_of_times_each_philosopher_must_eat]
```
*(number_of_philosophers):* The number of philosophers and also the number of forks.
*(time_to_die (in milliseconds):* If a philosopher didn’t start eating time_to_die
milliseconds since the beginning of their last meal or the beginning of the sim-
ulation, they die.
*(time_to_eat (in milliseconds):)* The time it takes for a philosopher to eat.
During that time, they will need to hold two forks.
*(time_to_sleep (in milliseconds):)* The time a philosopher will spend sleeping.
*(number_of_times_each_philosopher_must_eat (optional argument):)* If all
philosophers have eaten at least number_of_times_each_philosopher_must_eat
times, the simulation stops. If not specified, the simulation stops when a
philosopher dies.

## 🧹 Cleaning Up

To remove object files and libraries:
```bash
make fclean
```
## License

This project is licensed under the GNU GENERAL PUBLIC LICENSE - see the LICENSE.md file for details
