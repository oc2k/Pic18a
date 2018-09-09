Pic18a1(f67j60)TCPIP__180907a
====
# recoder (TOP LATEST)

- ...</br>

- //09SEP2018b release *Pic18a1(f67j60)TCPIP__180907a.hex* </br>
- //09SEP2018b *add c018 startup debug trace* procedure </br>
	1. copy c018.c from mcc18 relevant folder (mcc18\src\traditional\startup\) and change name to c018oc2k.c
	2. add the file to mcp project
	3. right click and select compiler
	4. copy "c018oc2k.o" file from output Objects folder into "mcc18\Objects"
	5. add library new search parts, the mcp file would be change to "dir_lib=..\..\mcc18\Objects"
	6. build all
	7. after compile finish, debug trace will be point to "_asm goto _startup _endasm" in _entry of c018oc2k.c file
  </br>
		/mcc18</br>
		//- src</br>
		///+ traditional</br>
		////*startup*</br>
  </br>

- //09SEP2018a organize tcpip full version as preparing tcp branch</br>
	1. Fixed " _DATE_ " for easily check hex file
	2. add "mcc18" folder directory see below
	3. move lkr file to /mcc18/bin/lkr
	4. add "..\..\mcc18\h" as new "dir_inc" directory change mcp file
  </br>
		/mcc18</br>
		//- bin</br>
		///+ lkr</br>
		//- h</br>
		//- src</br>
		///+ traditional</br>
		////* startup</br>
		////* stdclib</br>
  </br>
- //07SEP2018 skel v0,1 -> Pic18a1
----
# skeleton revision
+ -- skeleton (revision v0,2 as simple process)
+		-- skeleton (v0,1 as first revision from download TCP/IP Stack 5.42)
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
