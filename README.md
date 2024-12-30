# philo
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://opensource.org/licenses/GPL-3.0)
Solving famous "Dining philosophers problem" using threads and mutexes

## ✨ Features
- Supports standard UNIX pipes for chaining commands
- Handles multiple pipes
- Accepts user input through `here_doc`

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
cd pipex
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
*(the program accepts positive numbers as input values)*

* ##### number_of_philosophers: The number of philosophers and also the number of forks.
* ##### time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die
milliseconds since the beginning of their last meal or the beginning of the sim-
ulation, they die.
* ##### time_to_eat (in milliseconds): The time it takes for a philosopher to eat.
During that time, they will need to hold two forks.
* ##### time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.
* ##### number_of_times_each_philosopher_must_eat (optional argument): If all
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
