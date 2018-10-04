Pic18a1(f67j60)TCPIP__180923b
====
##### recoder (TOP LATEST)

----
>
> (branch:light) 
>

#### new tasks
*
* new task v: blank </br>
*

---------------
## processing task
- 181001a4, remove __C32**,__PIC24**,__PIC32
- 181001a3, remove __C30**
- 181001a2, remove HI_TECH_C
- 181001a1, remove "CFG_INCLUDE_PICDN2_ETH97" in mcp, output hex file no change
- permanent remove list
- -
	| remove macro|status|Remark|
	|---|---|---|
	| __C32*|Processed|exclude compiler.h
	| __PIC24*|Processed|exclude compiler.h
	| __PIC32*|Processed|exclude compiler.h
	| __dsPIC33*|Processed|exclude compiler.h
	| STACK_USE_MPFS2|181003a1PermanenceDelete|Keep uncomment permanence delete in TCPIP ***.h
	| STACK_USE_HTTP2_SERVER|181003b1PermanenceDelete|Keep uncomment permanence delete in TCPIP ***.h and undef HTTP_**
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

---------------
#### closed task record
- - copy processing </br>
- - 180920a2, to remove PingDemo.c </br>
- - 180920a1, to remove delay.c and DNSs.c </br>
- - 180918a, update c018i startup code instead of c018oc2k </br>
- - 180917a remove debug*,StructQueue*,timeDelay*,timer*, DynDNS*, FTP*, Hashes*, MPFS2* and regdef*, SPIRAM* and SPIEEPROM* </br>
- - 180914a,change maindemo to main (c,h) and remove BitInt* </br>
- - 180913a,remove smtp* (c,h); DHCP* (c,h) and AutoIP (c,h); HTTP* (c,h); ICMP_SERVER and no deleted is same, thus resume; FileSystem (c,h), MPFS2 (c,h), SNMP (c,h); TFTPc (c,h) -- that is Trivial File Transfer Protocol (TFTP) Client; ENCX24J600 (c,h) and more files </br>
- - 180912b,remove WF* (c,h) -- "WF_CS_TRIS"; Zeroconf* (c,h); ETHPIC32*.* (pic32 library file); </br>
- - ... </br>
-
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
> (branch:tcplite)
>


----
>
> (branch:tcp) deleted
>

----
>
> (branch:master)
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
