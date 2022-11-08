/* External definitions for emergency department using simlib. */

#include "simlib.h"             /* Required for use of simlib.c. */
#include <string.h>
#include <time.h>

#define EVENT_WALKIN_ARRIVAL          1  /* Event type walkin arrival */
#define EVENT_AMBULANCE_ARRIVAL       2  /* Event type ambulance arrival */
#define EVENT_TRIAGE_PATIENT          3  /* Event type triage patient */
#define EVENT_INITIAL_ASSESMENT       4  /* Event type intial assesment */
#define EVENT_RUN_TESTS               5  /* Event type run tests */
#define EVENT_FOLLOW_UP_ASSESSMENT    6  /* Event type follow-up assessment */
#define EVENT_PATIENT_ADMITTANCE      7  /* Event type patient admittance */
#define LIST_ACTIVE_PATIENTS          1  /* List number for tracking active patients */
#define LIST_ACTIVE_NURSES            2  /* List number for tracking active nurses */
#define LIST_ACTIVE_DOCTORS           3  /* List number for tracking active doctors */
#define AMBULANCE_SEVERITY         1.25  /* Ambulance severity multiplier */
#define MAX_NUM_PATIENTS	        100  /* Maximum number of patients in the ER */
#define FILENAME_LIMIT               50  /* Limit filename size */
#define MIN_DURATION                0.1  /* Minimum duration of any process */

/* Declare non-simlib global variables. */
int    RANDOM_STREAMS[8];
int    num_doctors, num_exam_rooms, num_nurses, num_labs, num_hospital_rooms, num_patients_simulated, goal_patients_simulated; 
float  mean_walkin_interarrival, mean_ambulance_interarrival, mean_triage_duration, 
       mean_initial_assessment_duration, mean_follow_up_assessment_duration, 
       mean_test_duration, mean_severity;
FILE*  outfile;
char   outfile_name[FILENAME_LIMIT];
char   error_msg[100];
time_t seconds;

/* Declare non-simlib functions. */
void try_input(float, char*);
void try_output(int);
void init_model(void);
void catch_exception(char*, int);
void report(void);

int main(int argc, char** argv)  /* Main function. */
{
    /* Verify correct number of arguments. */
    if (argc != 15)
    {
        printf("USAGE ERROR: Usage %s [mean_walkin_arrival] [mean_ambulance_arrival] [mean_triage_duration]\n\ 
[mean_initial_assessment_duration] [mean_test_duration] [mean_follow_up_assessment_duration]\n\ 
[mean_severity] [num_doctors] [num_nurses] [num_exam_rooms] [num_labs] [num_hospital_rooms]\n\ 
[min_patients_simulated] [output_file_name]\n", argv[0]);
        exit(1);
    }

    /* Read and validate input parameters. */
    try_input(mean_walkin_interarrival = atof(argv[1]), argv[1]);
    try_input(mean_ambulance_interarrival = atof(argv[2]), argv[2]);
    try_input(mean_triage_duration = atof(argv[3]), argv[3]);
    try_input(mean_initial_assessment_duration = atof(argv[4]), argv[4]);
    try_input(mean_test_duration = atof(argv[5]), argv[5]);
    try_input(mean_follow_up_assessment_duration = atof(argv[6]), argv[6]);
    try_input(mean_severity = atof(argv[7]), argv[7]);
    try_input((float)(num_doctors = atoi(argv[8])), argv[8]);
    try_input((float)(num_nurses = atoi(argv[9])), argv[9]);
    try_input((float)(num_exam_rooms = atoi(argv[10])), argv[10]);
    try_input((float)(num_labs = atoi(argv[11])), argv[11]);
    try_input((float)(num_hospital_rooms = atoi(argv[12])), argv[12]);
    try_input((float)(goal_patients_simulated = atoi(argv[13])), argv[13]);

    /* Calculate mean walk-in interarrival and mean ambulance interarrival time */
    mean_walkin_interarrival = 1.0 / mean_walkin_interarrival;
    mean_ambulance_interarrival = 1.0 / mean_ambulance_interarrival;

    /* Verify that outfile_name is within the FILENAME_LIMIT */
    if (strlen(argv[14]) + 8 >= FILENAME_LIMIT)
    {
        printf("FILENAME ERROR: Filename Too Long\n");
        exit(3);
    }
    strcpy(outfile_name, "out/");
    strcat(outfile_name, argv[14]);
    strcat(outfile_name, ".out");

    /* Open Output file. */
    outfile = fopen(outfile_name, "w");

    /* Verify the output file has been sucessfully opened. */
    if (outfile == NULL) {
        printf("FILE ERROR: Output File \"%s\" Cannot Be Opened\n", outfile_name);
        exit(4);
    }

    /* Write report heading and input parameters. */
    try_output(fprintf(outfile, "            Emergency Room Simulation using Simlib\n"));
    try_output(fprintf(outfile, "--------------------------------------------------------------\n\n"));
    try_output(fprintf(outfile, "[CONSTANTS]\n\n"));
    try_output(fprintf(outfile, "Ambulance severity multiplier:%20f\n\n", AMBULANCE_SEVERITY));
    try_output(fprintf(outfile, "Maximum capacity of ER:%20d\n\n", MAX_NUM_PATIENTS));
    try_output(fprintf(outfile, "Minimum duration of any process:%20.3f\n\n\n", MIN_DURATION));
    try_output(fprintf(outfile, "[INPUT PARAMETERS]\n\n"));
    try_output(fprintf(outfile, "Mean walk-in arrival rate:%20.3f patients per minute\n\n",
            1.0/mean_walkin_interarrival));
    try_output(fprintf(outfile, "Mean ambulance arrival rate:%20.3f patients per minute\n\n",
            1.0/mean_ambulance_interarrival));
    try_output(fprintf(outfile, "Mean walk-in arrival rate:%20.3f patients per minute\n\n",
            1.0/mean_walkin_interarrival));
    try_output(fprintf(outfile, "Mean triage duration:%20.3f minutes\n\n", mean_triage_duration));
    try_output(fprintf(outfile, "Mean initial assessment duration:%20.3f minutes\n\n", mean_initial_assessment_duration));
    try_output(fprintf(outfile, "Mean test duration:%20.3f minutes\n\n", mean_test_duration));
    try_output(fprintf(outfile, "Mean follow-up assessment duration:%20.3f minutes\n\n", mean_follow_up_assessment_duration));
    try_output(fprintf(outfile, "Mean patient severity:%20.3f\n\n", mean_severity));
    try_output(fprintf(outfile, "Number of doctors available:%20d\n\n", num_doctors));
    try_output(fprintf(outfile, "Number of nurses available:%20d\n\n", num_nurses));
    try_output(fprintf(outfile, "Number of exam rooms available:%20d\n\n", num_exam_rooms));
    try_output(fprintf(outfile, "Number of labs available:%20d\n\n", num_labs));
    try_output(fprintf(outfile, "Number of hospital rooms available:%20d\n\n", num_hospital_rooms));
    try_output(fprintf(outfile, "Number of patients to simulate:%20d\n\n", goal_patients_simulated));
    

    /* Initialize simlib */
    init_simlib();

    /* Set maxatr = max(maximum number of attributes per record, 4) */
    maxatr = 4;  /* NEVER SET maxatr TO BE SMALLER THAN 4. */

    /* Initialize the model. */
    init_model();

    /* Run the simulation while more calls are still needed. */
    while (num_patients_simulated < goal_patients_simulated) {

        /* Determine the next event. */
        timing();

        /* Invoke the appropriate event function. */
        switch (next_event_type) {
            case EVENT_WALKIN_ARRIVAL:
                /* Validate number of patients in the ER */
                if (list_size[LIST_ACTIVE_PATIENTS] >= MAX_NUM_PATIENTS) 
                {
                    sprintf(error_msg, "PATIENT VOLUME ERROR: Patients In ER Exceeded %d\n", MAX_NUM_PATIENTS);
                    catch_exception(error_msg, 6);
                }
                
                /* Add patient to list of active patients */
                list_file(FIRST, LIST_ACTIVE_PATIENTS);

                /* Schedule next walk-in patient */
                event_schedule(sim_time + expon(mean_walkin_interarrival, RANDOM_STREAMS[EVENT_WALKIN_ARRIVAL]),
                               EVENT_WALKIN_ARRIVAL);
                /* Schedule patient triage */
                event_schedule(sim_time + fmaxf(normal(mean_triage_duration, RANDOM_STREAMS[EVENT_TRIAGE_PATIENT]), MIN_DURATION), 
                               EVENT_TRIAGE_PATIENT);
                break;
            case EVENT_AMBULANCE_ARRIVAL:
                /* Validate number of patients in the ER */
                if (list_size[LIST_ACTIVE_PATIENTS] >= MAX_NUM_PATIENTS) 
                {
                    sprintf(error_msg, "PATIENT VOLUME ERROR: Patients In ER Exceeded %d\n", MAX_NUM_PATIENTS);
                    catch_exception(error_msg, 6);
                }

                /* Add patient to list of active patients */
                list_file(FIRST, LIST_ACTIVE_PATIENTS);

                /* Schedule next walk-in patient */
                event_schedule(sim_time + expon(mean_ambulance_interarrival, RANDOM_STREAMS[EVENT_AMBULANCE_ARRIVAL]),
                               EVENT_AMBULANCE_ARRIVAL);
                
                /* Add nurse to list of active nurses */
                list_file(FIRST, LIST_ACTIVE_NURSES);
                
                /* Schedule patient triage */
                event_schedule(sim_time + fmaxf(normal(mean_triage_duration, RANDOM_STREAMS[EVENT_TRIAGE_PATIENT]), MIN_DURATION), 
                               EVENT_TRIAGE_PATIENT);
                break;
            case EVENT_TRIAGE_PATIENT:
                /* Validate number of nurses in the ER */
                if (list_size[LIST_ACTIVE_NURSES] >= num_nurses)
                {
                    sprintf(error_msg, "NURSE ERROR: Number Of Active Nurses Exceeded %d\n", num_nurses);
                    catch_exception(error_msg, 7);
                }

                /* Remove nurse from list of active nurses */
                list_remove(FIRST, LIST_ACTIVE_NURSES);

                /* Add doctor to list of active doctors */
                list_file(FIRST, LIST_ACTIVE_DOCTORS);

                /* Schedule patient's initial assessment */
                event_schedule(sim_time + fmaxf(normal(mean_initial_assessment_duration, RANDOM_STREAMS[EVENT_INITIAL_ASSESMENT]), MIN_DURATION),
                               EVENT_INITIAL_ASSESMENT);
                break;
            case EVENT_INITIAL_ASSESMENT:
                
                break;
            case EVENT_RUN_TESTS:
                
                break;
            case EVENT_FOLLOW_UP_ASSESSMENT:
                
                break;
            case EVENT_PATIENT_ADMITTANCE:

                break;
        }
    }

    /* Invoke the report generator and end the simulation. */
    report();

    /* Close file and verify that is is successful */
    if (fclose(outfile) != 0) {
        printf("FILE ERROR: Output File \"%s\" Cannot Be Closed\n", outfile_name);
        exit(4);
    }

    return 0;
}


void init_model(void)  /* Initialization function. */
{
    /* Initialize non-simlib variables */

    /* Initialize random number streams */
    seconds = time(NULL);
    RANDOM_STREAMS[1] = 2 * seconds % 60;
    RANDOM_STREAMS[2] = 3 * seconds % 60;
    RANDOM_STREAMS[3] = 5 * seconds % 60;
    RANDOM_STREAMS[4] = 7 * seconds % 60;
    RANDOM_STREAMS[5] = 11 * seconds % 60;
    RANDOM_STREAMS[6] = 13 * seconds % 60;
    RANDOM_STREAMS[7] = 17 * seconds % 60;
    
    /* Schedule first new call and first handoff call */
    event_schedule(sim_time + expon(mean_walkin_interarrival, RANDOM_STREAMS[EVENT_WALKIN_ARRIVAL]),
                   EVENT_WALKIN_ARRIVAL);
    event_schedule(sim_time + expon(mean_ambulance_interarrival, RANDOM_STREAMS[EVENT_AMBULANCE_ARRIVAL]),
                   EVENT_AMBULANCE_ARRIVAL);
}


void report(void)  /* Report generator function. */
{
    /* Get and write out estimates of desired measures of performance. */
    // try_output(fprintf(outfile, "[PERFORMANCE METRICS]\n"));
    // try_output(fprintf(outfile, "\nBase Station Channel Utilization:%10.1f%%\n", 
    //            100.0 * filest(LIST_ACTIVE_CHANNELS) / MAX_CHANNELS));
    // try_output(fprintf(outfile, "\n(New) Call Block Probability:%14.1f%%\n", 
    //            100.0 * total_calls_rejected / (total_calls_connected + total_calls_rejected)));
    // try_output(fprintf(outfile, "\nHandoff Dropping Probability:%14.1f%%\n\n", 
    //            100.0 * total_handoffs_rejected / (total_handoffs_connected + total_handoffs_rejected)));
    // try_output(fprintf(outfile, "\n[TERMINATION METRICS]\n"));
    // try_output(fprintf(outfile, "\nTime simulation ended:%21.3f seconds\n", sim_time));
    // try_output(fprintf(outfile, "\nTotal calls simulated:%21d calls\n", 
    //            total_calls_connected + total_calls_rejected + total_handoffs_connected + total_handoffs_rejected));
}

void try_input(float input, char* input_str) /* Validate input or exit */
{
    if (input == 0)
    {
        printf("INPUT ERROR: \"%s\" Is Not A Valid Input\n", input_str);
        exit(2);
    }
}

void try_output(int status) /* Validate output or exit */
{
    if (status < 0)
    {
        printf("FILE ERROR: Output File \"%s\" Cannot Be Written To\n", outfile_name);
        if (fclose(outfile) != 0)
        {
            printf("FILE ERROR: Output File \"%s\" Cannot Be Closed\n", outfile_name);
        }
        exit(5);
    }
}

void catch_exception(char* error_msg, int error_type) /* General exception printer */
{
    printf("%s", error_msg);
    if (fclose(outfile) != 0)
    {
        printf("FILE ERROR: Output File \"%s\" Cannot Be Closed\n", outfile_name);
    }
    exit(error_type);
}

