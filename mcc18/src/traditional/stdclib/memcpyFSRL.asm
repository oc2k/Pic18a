; $Id: memcpyFSRL.asm,v 2.1 2015/09/30 Jian'an $ __>>memcpy.asm,v 1.1 2003/12/09 22:53:20 GrosbaJ Exp $

#include "P18CXXX.INC"
#include "P18MACRO.INC"

; -------------------------------------
; Trace 3rd number: df4D0913DDEQE0BLOCKrewporq
; Trace 4th number: 1
; -------------------------------------
; Rev01a
; -------------------------------------
; @name memcpy
;``The {\bf memcpy} funciton copies {\bf n} characters from the object
;pointed to by {\bf s2} into the object pointed to by {\bf s1}. If
;copying takes place between objects that overlap, the behaviour is
;undefined.''
;Stack usage: 8 bytes. Re-entrant.
;@param s1 pointer to destination
;@param s2 pointer to source
;@param n count of bytes to copy
;@return ``The {\bf memcpy} function returns the value of {\bf s1}.''
;
; void *memcpyFSRL (void *s1, const void *s2, size_t n);


STRING CODE
memcpyFSRL
  global memcpyFSRL

; Proceedure: Use offset from top of stack to test 'n' for zero and decrement
;         it. Use FSR0 for 'dest' and FSR2 for 'src' 


  ; Save FSR2 on the stack. 

          Stk2PushFromReg FSR2L

  ; Load FSR2 with the 'src' pointer

          Stk2CpyToReg -6,FSR2L

  ; Load FSR0 with the 'dest' pointer

          Stk2CpyToReg -4,FSR0L

  ; Make a copy for the return value
	  movff FSR0L, PRODL
	  movff FSR0H, PRODH


jLoop:

  ; Test n for zero

          Stk2TestForZero -8,jEnd

  ; Decrement n 

          Stk2Dec   -8

          movff     INDF2, INDF0; Rev2.1__>>Rev1.1, movff     POSTINC2, POSTINC0
		  incf      FSR2L, f	; Rev2.1 add
		  incf      FSR0L, f	; Rev2.1 add
          bra       jLoop

jEnd

  ; Restore stack frame for return: restore FSR2
          Stk2PopToReg FSR2L

  ; Restore FSR0
	  movff PRODL, FSR0L
	  movff PRODH, FSR0H

          return
  end
