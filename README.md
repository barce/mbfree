# What does it stand for?
Rumors of what mbfree means:
* Mega Byte Free
* Memory Be Free
  
# What does mbfree do?
Mbfree allocates and frees a given amount of memory.  It is especially
helpful on systems that are over utilized that swap a lot.

# Why should I use mbfree?
A lot of OSs loose performance when their main memory is used and 
the OS is swapping.  Mbfree allows you to allocate a certain amount
of memory and free it.  In Linux the result is usually faster loading
of programs -- or successful loading of programs when they don't
load because there is not enough free memory.

# Install
`./configure && make && make install`
See INSTALL file for more info

# Uses of mbfree (server uses)
MBFREE can take memory that is currently in "swap" and in a "used" state
and put it into a free state.
  
# Other uses (desktop / laptop uses)
If you have a browser crash or kill -9 a process, chances are there
is memory that is considered used but isn't anymore. Run "mbfree 256"
to free up memory.

