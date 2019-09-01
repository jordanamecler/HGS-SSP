# HGS-SSP

To compile, run:

* make

To execute, run:

* ./HGS_MTSP {instances_path} {instances_prefix} {solution_path} {seed} {number_of_individuals} {maximum_number_of_individuals} {number_elite_individuals} {number_close_individuals} {maximum_iterations_without_improvement_diversify}

For example, to run the first set of instances of Crama et al.:

* ./HGS_MTSP Instances/Crama/Tabela1 s1 solutions.txt 1 20 40 10 3 1000