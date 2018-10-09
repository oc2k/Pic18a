Pic18a1(f67j60)TCPIP__181007a
====
##### recoder (TOP LATEST)

----
>
> (branch:light) 
>

#### new tasks
*
* new task v: halSCI </br>
*

---------------
## processing task
- 181009a, PURPOSE: add/set halA2D (c,h)
#### done record
- - 181008a, PURPOSE: clear main.c code (master branch can be do it)
- - 181007a, PURPOSE: added genSKEL (c,h) and define project fixed RAM/ROM parameter defines
- - 181006a, it is confirm to use **STACK_USE_TCP** due to define *STACK_USE_UART2TCP_BRIDGE* see TCPIP.h
-
- permanent remove list
	----
	| remove macro|status|Remark|
	|---|---|---|
	| __C32*|Processed|exclude compiler.h
	| __PIC24*|Processed|exclude compiler.h
	| __PIC32*|Processed|exclude compiler.h
	| __dsPIC33*|Processed|exclude compiler.h
	| STACK_USE_MPFS2|181003a1PermanenceDelete|Keep uncomment permanence delete in TCPIP ***.h
	| STACK_USE_HTTP2_SERVER|181003b1PermanenceDelete|Keep uncomment permanence delete in TCPIP ***.h and undef HTTP_..
	| STACK_USE_DHCP_SERVER|181003c1PermanenceDelete|see above
	| STACK_USE_DHCP_CLIENT|181003c2PermanenceDelete|see above
	| STACK_USE_AUTO_IP|181003d1PermanenceDelete|see above
	| STACK_USE_SMTP_CLIENT|181003e1PermanenceDelete|see above
	| STACK_USE_HTTP_EMAIL_DEMO|181003e2PermanenceDelete|see above
	| STACK_USE_GENERIC_TCP_CLIENT_EXAMPLE|181003f1PermanenceDelete|see above
	| STACK_USE_GENERIC_TCP_SERVER_EXAMPLE|181003f2PermanenceDelete|see above
	| STACK_USE_TELNET_SERVER|181003g1PermanenceDelete|see above
	| STACK_USE_REBOOT_SERVER|181003g2PermanenceDelete|see above
	| STACK_USE_SNTP_CLIENT|181003g3PermanenceDelete|see above
	| STACK_USE_TCP_PERFORMANCE_TEST|181003g4PermanenceDelete|see above
	| STACK_USE_UDP_PERFORMANCE_TEST|181003g5PermanenceDelete|see above
	| STACK_USE_SSL_SERVER|181003g6PermanenceDelete|see above
	| STACK_USE_SSL_CLIENT|181003g7PermanenceDelete|see above
	| STACK_USE_IP_GLEANING|181004a1PermanenceDelete|see above
	| STACK_USE_ICMP_SERVER||keep reason:STACK_USE_ICMP_CLIENT is still using
	| STACK_USE_FTP_SERVER|181004a2PermanenceDelete|see above
	| STACK_USE_SNMP_SERVER|181004a3PermanenceDelete|see above
	| STACK_USE_SNMPV3_SERVER|181004a4PermanenceDelete|see above
	| STACK_USE_TFTP_CLIENT|181004a5PermanenceDelete|see above
	| STACK_USE_DNS_SERVER|181004a6PermanenceDelete|see above
	| STACK_USE_DYNAMICDNS_CLIENT|181004a7PermanenceDelete|see above
	| STACK_USE_BERKELEY_API|181004a8PermanenceDelete|see above
	| STACK_USE_ZEROCONF_LINK_LOCAL|181004a9PermanenceDelete|see above
	| STACK_USE_ZEROCONF_MDNS_SD|181004a10PermanenceDelete|see above
	| STACK_USE_HTTP_MD5_DEMO|181006a5PermanenceDelete|see above
	| STACK_USE_HTTP_APP_RECONFIG|181006a5PermanenceDelete|see above
	

----
>
> (branch:master)
>

- - 180923a3: change mainDemo to main and remove like ETHPIC32*.* pic32 library and relevant library files </br>
- - 180923a2, update c018i startup code instead of c018oc2k </br>
- - 180923a1, back to master and planning </br>
- - back to master </br>

| remove defines|remove file|Remark|
|---|---|---|
|| AES*
|| ArcFOUR*
|| ETHPIC32*,BigInt_helper_PIC32.S
|| eth_pic32*
|| timer*
|| regdef* [MIPS Quick Tutorial](http://logos.cs.uic.edu/366/notes/mips%20quick%20tutorial.htm)

----
>
> (branch:tcplite) deleted
>


----
>
> (branch:tcp) deleted
>

----
>
> (branch:master) keeping
>

----
- *add c018 startup debug trace* procedure </br>
	1. copy c018i.c from mcc18 relevant folder (mcc18\src\traditional\startup\)
	2. add the file to mcp project
	3. right click and select compiler
	4. copy "c018i.o" file from output Objects folder into "mcc18\Objects"
	5. remove c018i.c from mcp project
	6. add library new search parts, the mcp file would be change to "dir_lib=..\..\mcc18\Objects"
	7. build all
-	*effect*: after build all, debug trace will be point to "_asm goto _startup _endasm" in _entry of c018i.c file
>
- //09SEP2018a organize tcpip full version as preparing tcp branch</br>
	1. Fixed " __DATE__ " for easily check hex file (note: no change actually)
	2. add "mcc18" folder directory see below
	3. move lkr file to /mcc18/bin/lkr
	4. add "..\..\mcc18\h" as new "dir_inc" directory change mcp file
- //07SEP2018 skel v0,1 -> Pic18a1

----
- folder directory


| Pic18a1|1|2|3|4|
|---|---|---|---|---|
||mcc18 |||
|||  bin
||||   lkr
|||  h
|||  src
||||   traditional
|||||     startup
|||||     stdclib
||Microchip
|||  Include
||||   TCPIP Stack
|||  TCPIP Stack
|| TCPIP
|||  **App** (main.c)
||||||

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
# discussion about the compiler
*
* 	- [LINK1 from sonsivri.to](http://www.sonsivri.to/forum/index.php?topic=43664.0)
*
****
