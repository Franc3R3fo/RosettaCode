#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bioinformatics_pretty_print_base_count(char*genome);
char* bioinformatics_mutate_sequence(char*genome);
char* bioinformatics_generate_random_sequence(int minlen);