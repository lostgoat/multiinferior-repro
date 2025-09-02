# multiinferior-repro

Steps to repro:
  * Open this git repor as a folder
  * Set a breakpoint on the "parent exiting" line
  * Start the "(gdb) Launch" debug task

Expectation:
  * The breakpoint is hit

Observed behaviour:
  * When the child exits, the debug session stops

