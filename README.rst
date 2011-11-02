Thiao: fractional resource sharing experiment
---------------------------------------------

This is Thiao, an experiment for fractional resource management, the objective
is to use some well trusted software to do job management, in this case SLURM,
and also some cloud computing management software to manage the virtual machine
infrastructure for which I'm using OpenNebula.


Installing:
-----------

Note: this should work as long as you have a *WORKING* SLURM and OpenNebula
installation::

  sudo mkdir /opt/thiao
  sudo chmod 777 /opt/thiao
  cd /opt/thiao
  git clone git://github.com/scarmiglione/thiao.git .
  chmod 666 thiao.db
  ./bin/Setup

Set the *OneAuth* variable in *thiao.cfg* and make sure the user slurm can read
it (it's needed if you want SLURM to call the tclean.py script every time a job
finishes it's execution).


Optional: add /opt/thiao/bin to your PATH


First use case:
---------------

Use fsub.py to submit your jobs, fsub.py will forward the request to sbatch,
retrieve the job id, and launch the virtual machines in which the job will run.


