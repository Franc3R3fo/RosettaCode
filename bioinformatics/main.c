#include "bioinformatics.h"

int main() {
    time_t t;
    srand((unsigned) time(&t));
    char* genome = bioinformatics_generate_random_sequence(200);
    bioinformatics_pretty_print_base_count(genome);
    char*newgenome = bioinformatics_mutate_sequence(genome);
    bioinformatics_pretty_print_base_count(newgenome);
};