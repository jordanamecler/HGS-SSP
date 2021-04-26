# HGS-SSP

This work was published in one of the best journals in the area of operations research, [Computers & Operations Research](https://www.journals.elsevier.com/computers-and-operations-research).  
The paper is available in <https://www.sciencedirect.com/science/article/abs/pii/S0305054820302707>.

To compile, run:

* make

To execute, run:

* ./HGS_SSP {instance_path} {instance_name} {solution_path} {seed}

For example, to run the first instance of Crama et al.:

* ./HGS_SSP Instances/Crama/Tabela1 s1n001 solutions.txt 1

The output will be in the form:

* {best_solution_found},{CPU time}
