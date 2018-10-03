# WHAT IT MEANS
Rumors of what mbfree means:
* Mega Byte Free
* Memory Be Free
  
# WHAT IT DOES  
Mbfree allocates and frees a given amount of memory.  It is especially
helpful on systems that are over utilized that swap a lot.

# WHY MBFREE
A lot of OSs loose performance when their main memory is used and 
the OS is swapping.  Mbfree allows you to allocate a certain amount
of memory and free it.  In Linux the result is usually faster loading
of programs -- or successful loading of programs when they don't
load because there is not enough free memory.

# USES OF MBFREE (SERVER USES)
MBFREE can take memory that is currently in "swap" and in a "used" state
and put it into a free state.
  
# OTHER USES (DESKTOP USES)
If you have a browser crash or kill -9 a process, chances are there
is memory that is considered used but isn't anymore. Run "mbfree 256"
to free up memory.

