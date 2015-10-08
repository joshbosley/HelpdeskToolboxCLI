# HelpdeskToolboxCLI
*Our very own toolbox!*

## HDTB Usage ##

	./HelpdeskToolboxCLI
		- Will initiate the toolbox in human interface mode, where the 
		  user can interact with the prompt to accomplish tasks

	./HelpdeskToolboxCLI <filename>
		- Will initiate the toolbox in script mode which will read in 
		  the file line-by-line initiating each command. This is for
		  further automation of tasks.

## Adding your own module : ##

1. Create a module code in modules/framework/_modules/moduledirectory.h
    - Keep to naming scheme, and remember to ensure unique id

2. Write a new class file within modules/name_of_module/ using ModuleBase as
    the base class for your new module. For an example of how this
    is done, examine helpmodule.h, and helpmodule.cpp

3. Once the module class is written, insert the object into the
    core/modulebox.h structure. 

4. Add the module into the boxcore.moduleMap<CODE, ARG> within
    boxcore construction.
    Where the code is the module code entered in step 1,
    and the ARG is the argument used to call your module
    - Ensure that there are no duplicates

5. Edit boxcore::processRequest switch statement to handle 
    the new module by the module code entered in step 1

### Authors

* Josh Bosley
* Tyler Postma





 
