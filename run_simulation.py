#!/usr/bin/python3
import subprocess

INPUTFILE = "er_sim.in"
NUMARGS = 17
SIMPROGRAM = "build/er_sim"

simulations = []
with open(INPUTFILE, "r") as inputfile:
    for line in inputfile:
        simulations.append(line.strip().split())

for simulation in simulations:
    if len(simulation) == NUMARGS:
        simulation_init = [SIMPROGRAM]
        for arg in simulation:
            simulation_init.append(arg)
        subprocess.Popen(simulation_init)
