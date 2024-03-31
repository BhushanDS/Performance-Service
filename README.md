# Performance Data Microservice

This C++ microservice provides a simple yet effective way to collect CPU and GPU memory usage data. 
It is designed to run in the background, suitable for continuous monitoring, and the collected data can be easily fed into a Grafana dashboard for visualization.

## Features

- **CPU Memory Usage:** Real-time collection of CPU memory usage data.
- **GPU Memory Usage:** Obtain GPU memory usage information.
- **Background Thread:** Runs as a background thread for continuous monitoring.
- **Grafana Integration:** Easily connect to a Grafana dashboard for data visualization. [To be ADD in future]

## Installation

### Prerequisites

- C++ compiler (e.g., GCC, Clang)
- CMake
- Libraries for GPU memory access (if applicable)
- Grafana setup for data visualization (optional but recommended) [TO be ADD in future]

### Building from Source

1. Clone the repository:

   ```sh
   git clone https://github.com/BhushanDS/Performance-Service.git
   cd Performance-Service
