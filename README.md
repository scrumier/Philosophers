
# Philosophers Project 🧘‍♂️🍴

This project is an implementation of the **Dining Philosophers Problem**—a classic synchronization problem that demonstrates challenges in concurrent programming and resource allocation.

## Overview
In the **Dining Philosophers Problem**, multiple philosophers sit at a table with a fork between each pair. Philosophers alternate between thinking and eating but need both forks on either side to eat. The goal is to prevent deadlock and starvation while ensuring each philosopher eats eventually.

## Getting Started

### Prerequisites
- **Compiler**: Ensure you have `gcc` or a compatible C compiler installed.
- **Make**: This project uses `make` for building the executable.

### Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/scrumier/philosophers.git
   cd philosophers
   ```
2. Build the project using `make`:
   ```bash
   make
   ```

## Usage

To run the **Philosophers** program, use the following command:
```bash
./philosophers <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

### Arguments
- `<number_of_philosophers>`: The number of philosophers and forks.
- `<time_to_die>`: Time in milliseconds after which a philosopher dies without eating.
- `<time_to_eat>`: Time in milliseconds for a philosopher to eat.
- `<time_to_sleep>`: Time in milliseconds for a philosopher to sleep.
- `[number_of_times_each_philosopher_must_eat]` (optional): The number of times each philosopher should eat before the simulation ends.

### Example
```bash
./philosophers 5 800 200 200
```

This command starts the simulation with 5 philosophers who must eat within 800ms intervals, taking 200ms to eat and 200ms to sleep.

## Features
- **Deadlock Prevention**: Implements a solution to avoid deadlock, ensuring all philosophers get opportunities to eat.
- **Thread Synchronization**: Utilizes mutexes for safe resource sharing.

## Contributing
Feel free to open issues or submit pull requests for improvements or bug fixes.

## License
This project is open source. See the [LICENSE](LICENSE) file for details.

---

Happy coding and dining! 🍜
