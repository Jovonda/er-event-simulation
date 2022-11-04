# Build Instructions
## CMake Build and Compile
```
cmake -B build
cmake --build build
```
## Alternate Direct Compilation
```
gcc base_station.c simlib.c -o build/base_station -lm
```
## Notes
CMake is recommended to build and compile this project.
Both methods generate a mm1 binary in the build directory.

---
# Executable Files
## File List
*   run_simulation.py
*   build/base_station
*   cleanup.sh
## Run Options
```
./build/base_station [mean_call_arrival] [mean_handoff_arrival] [mean_service_rate] [sim_time_duration]
```
## About
run_simulation.py executes the batch of simulations
<br/>
base_station runs a single simulation
<br/>
cleanup.sh cleans out the build and out directories

---
# Simulation Instructions
## Setup   
Write initial simulation conditions into base_station.in. Each line represents one simulation. There should be four values each line: mean_call_arrival, mean_handoff_arrival, mean_service_rate, and sim_time_duration. The first specifies the average number of calls per second. The second specifies the average number of handoff calls that come in per second. The thrid specifies how many calls a channel can handle per second. The fourth specifies how long the simulation will run for in simulation time. The number of channels is defined to be 100. This can be changed if desired in base_station.c.
## Run Simulation
```Python
python3 run_simulation.py
```
