# Build Instructions
## CMake Build and Compile
```
cmake -B build
cmake --build build
```
## Alternate Direct Compilation
```
gcc er_sim.c simlib.c -o build/er_sim -lm
```
## Notes
CMake is recommended to build and compile this project.
Both methods generate a er_sim binary in the build directory.

---
# Executable Files
## File List
*   run_simulation.py
*   build/base_station
*   cleanup.sh
## Run Options
```
./build/er_sim [mean_walkin_arrival] [mean_ambulance_arrival] [mean_triage_duration] 
[mean_initial_assessment_duration] [mean_test_duration] [mean_follow_up_assessment_duration] 
[mean_severity] [num_doctors] [num_nurses] [num_exam_rooms] [num_labs] [num_hospital_rooms] 
[min_patients_simulated]
```
## About
run_simulation.py executes the batch of simulations
<br/>
er_sim runs a single simulation
<br/>
cleanup.sh cleans out the build and out directories

---
# Simulation Instructions
## Setup   
<!-- Write initial simulation conditions into er_sim.in. Each line represents one simulation. There should be thirteen values each line: mean_call_arrival, mean_handoff_arrival, mean_service_rate, and sim_time_duration. The first specifies the average number of calls per second. The second specifies the average number of handoff calls that come in per second. The thrid specifies how many calls a channel can handle per second. The fourth specifies how long the simulation will run for in simulation time. The number of channels is defined to be 100. This can be changed if desired in base_station.c. --> TODO
## Run Simulation
```Python
python3 run_simulation.py
```
