Thiao: fractional resource sharing experiment
---------------------------------------------

This is Thiao, an experiment for fractional resource management, the objective
is to use some well trusted software to do job management, in this case SLURM,
and also some cloud computing management software to manage the virtual machine
infrastructure for which I'm using OpenNebula.


Installing:
-----------

Note: this should work as long as you have a *WORKING* SLURM and OpenNebula
installation.

Copy everything to /opt/thiao
Make sure /opt/thiao/thiao.df is writable for anyone using Thiao
Optional: add /opt/thiao/bin to your PATH


Simplest use case:
------------------

Use fsub.py to submit your jobs, fsub.py will forward the request to sbatch,
retrieve the job id, and launch the virtual machines in which the job will run.


