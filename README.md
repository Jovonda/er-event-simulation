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
./build/er_sim [mean_walkin_arrival] [mean_ambulance_arrival] [mean_triage_duration] [mean_initial_assessment_duration] [mean_test_duration] [mean_follow_up_assessment_duration] [mean_hospital_duration] [mean_severity] [num_doctors] [num_nurses] [num_exam_rooms] [num_labs] [num_hospital_rooms] [addmittance_chance] [specialist_chance] [goal_patients_simulated] [output_file_name]
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
Write initial simulation conditions into er_sim.in. Each line represents one simulation. There should be seventeen values each line. The specific inputs are mentioned in the run options section above. Once a line has been correcly filled in, run_simulation.py will execute the simulation.
## Run Simulation
```Python
python3 run_simulation.py
```
