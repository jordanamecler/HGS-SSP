# HGS-SSP

To compile, run:

* make

To execute, run:

* ./HGS_MTSP {instances_path} {instances_prefix} {solution_path} {seed} {number_of_individuals} {maximum_number_of_individuals} {number_elite_individuals} {number_close_individuals} {maximum_iterations_without_improvement_diversify}

For example, to run the first set of instances of Crama et al.:

* ./HGS_MTSP Instances/Crama/Tabela1 s1 solutions.txt 1 20 40 10 3 1000

The output will be in the form:

* {best_solution} {average solution over 10 runs} {average time over 10 runs}
* Each line but the last referes to a particular instance (e.g. for the previous example of Crama/Tabela1 s1, each line will refer to one of the 10 instances with prefix s1 (s1n001, s1n002, ..., s1n010)
* The last line is the average over all instances (average of the previous lines)
