Pic18a1(f67j60)TCPIP__180907a
====
# recoder (TOP LATEST)
- ...
|- //09SEP2018 organize tcpip full version as preparing tcp branch
|	1. Fixed " _DATE_ " for easily check hex file
|	2. add "mcc18" folder directory
|		/mcc18
|		//- bin
|		///+ lkr
|		//- h
|		//- src
|		///+ traditional
|		////* startup
|		////* stdclib
|	3. move lkr file to /mcc18/bin/lkr
|	4. add "..\..\mcc18\h" as new "dir_inc" directory change mcp file
|
|- //07SEP2018 skel v0,1 -> Pic18a1 (/)
----
# skeleton revision
+ -- skeleton (revision v0,2 as simple process)
+		-- skeleton (v0,1 as first revision from download TCP/IP Stack 5.24)
# standard build all procedure
*	1. build all
*	2. success
*	3. menu/file -> export
*	4. click OK and save as work folder, hex filename:#Pic18a1(f67j60)TCPIP__180907a.hex
*	5. commit
# mercurial untrace file list:
*	1. untitled.mcw
*	2. Objects/
*	3. Output/
*	and more, detailed see .hgignore
# development environment
*	- winxp
*	- Mercurial as pc version control tools
*	- mplabIDE v8.xx
*	- Mplabc18 compiler v3.41
*	- Mplabc18 compiler recommend location: c:\pic\mcc18
*	- work folder: c:\pic18a1
*	- assistance folder: c:\pic18a1ASS (include untitled.mcw, prebuild folder and more)
*	- microcontroller: pic18f67J60
*	- PIC-WEB (Rev.C)
****
