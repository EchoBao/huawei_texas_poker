This file mainly reveals the role of each file or derectory!
Hulu:
	The directory hulu contains a derectory demos, and demos include seven playe
 	programs which offered by Huawei to play with our own designed program. We 
	can use these play programs to compete with our own program to check the bquality of our program.

server: 
	contains "gameseerver" derectory.

works:
	The most important directory of this project.
	It mainly contains the following file or directory:
	1.libs:
		include the program needed library files.
	2.makeproject:
		include the makefile of project.
	3.target:
		include the excuteable file created
	4.source:
		program sourcefile.
		
		game.c:
			include the main function.
		sendmsg.c:
			send message to the server.
		decode.c:
			decoded message received from the server
		debug.c:
			print some imformation helping debugging
		estimate.c:
			make decision according to algrithm.
dist_check_and_run.sh:
		shell script which offered by Huawei.
