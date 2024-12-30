# Philosophers  
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://opensource.org/licenses/GPL-3.0)

This project solves the famous "Dining Philosophers Problem," which is a classic synchronization problem in computer science. The simulation models philosophers sitting at a round table, where they alternately eat, think, and sleep.

### Problem Overview:
- Philosophers sit at a table with a large bowl of spaghetti in the center.
- There are forks placed between each philosopher; each philosopher needs two forks to eat.
- Philosophers alternate between eating, thinking, and sleeping.
- A philosopher eats using both the fork on their right and the fork on their left.
- Philosophers die of starvation if they don’t eat within a specified time frame.

## ✨ Features
- **Thread-based Simulation**: Each philosopher is represented by a separate thread.
- **Mutexes**: Multiple mutexes are used to prevent data races and ensure synchronization.
- **Event logging**: The program tracks time in milliseconds, printing a message for each event with a corresponding timestamp.

## 📚 Table of Contents
- [Installation](#-installation)
- [Building the Program](#️-build-the-program)
- [Running the Program](#-running-the-program)
- [Cleaning Up](#-cleaning-up)
- [License](#license)

## 🚀 Installation

Clone the repository and navigate to the project directory:

```bash
git clone https://github.com/aklimchu/philo.git
cd philo/philo
```
## 🛠️ Build the Program

### Use `make` command to create the program:
```bash
make
```

## 🎮 Running the Program

To run the simulation, execute the following command:
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep
[number_of_times_each_philosopher_must_eat]
```
### Arguments:
- **`number_of_philosophers`**: The number of philosophers (and forks) at the table.
- **`time_to_die`** (in milliseconds): The time after which a philosopher dies if they haven’t eaten.
- **`time_to_eat`** (in milliseconds): The time it takes for a philosopher to eat.
- **`time_to_sleep`** (in milliseconds): The time a philosopher will sleep between meals.
- **`number_of_times_each_philosopher_must_eat`** (optional): The number of times each philosopher must eat before the simulation stops. If not specified, the simulation stops when a philosopher dies.

## 🧹 Cleaning Up

To remove object files and libraries:
```bash
make fclean
```
## License

This project is licensed under the GNU GENERAL PUBLIC LICENSE - see the LICENSE.md file for details
