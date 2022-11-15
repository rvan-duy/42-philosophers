# philosophers
![macOS/Ubuntu compile check](https://github.com/rvan-duy/42-philosophers/actions/workflows/build_philo.yml/badge.svg)
[![CodeFactor](https://www.codefactor.io/repository/github/rvan-duy/42-philosophers/badge/main)](https://www.codefactor.io/repository/github/rvan-duy/42-philosophers/overview/main)

This is the fractol project in 42's curriculum. A project which goal it is to explore the philosopher dining problem, using threads and mutexes.

## Features
- Simulate up to 200 philosopher threads
- Use different values for `time_to_die` `time_to_eat` `time_to_sleep`
- Set a minimum `number_of_times_each_philosopher_must_eat`

## Requirements
- A modern C compiler

## Clone and build the game
```
$ git clone https://github.com/rvan-duy/philosophers
$ cd philosophers
$ make
```

## To run the simulation
```
$ ./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```
