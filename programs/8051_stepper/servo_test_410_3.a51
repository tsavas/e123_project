; timer2_biflip.a51	use Timer2 to toggle LED, on interrupt by timer overflow

	$NOSYMBOLS													; keeps listing short
	$INCLUDE (C:\RIDE\INC\51\SILABS\c8051f410.inc)  

	$INCLUDE (C:\SiLabs\VECTORS320.INC)	; Tom's vectors definition file
	STACKBOT EQU 80h					; put stack at start of scratch
	DIV12 EQU 0DFh						; timer clock mask to div by 12, in CKCON

	GLOBALINTEN EQU EA				; global interrupt enable
	TIM2INTEN EQU IE.5
	TIM2_ENABLE EQU TMR2CN.2
	SOFTFLAG EQU 0						; software flag that ISR uses to talk to Main
	BLUE_LED EQU P0.0					; LED to toggle
	
	 HITIME SET 0FFh	; set start count close to the overflow val
	 LOTIME SET 0F0H	;  ...and this is the low byte

; port use:
; 	LED at P0.0
	
	ORG 0

          SJMP STARTUP
	
	ORG 80h
STARTUP: ACALL USUAL_SETUP
          ACALL TIMER_INITS
          ACALL INT_SETUP
	
STUCK:	SJMP STUCK	; await interrupts.  All the action is there
	
	
;------- INITIALIZATIONS

USUAL_SETUP: ANL   PCA0MD, #NOT(040h)        ; Disable the WDT.
                                             ; Clear Watchdog Enable bit
				; Configure the Oscillator
          ORL   OSCICN, #04h         ; sysclk = 24.5 Mhz / 8
					mov  P0MDOUT,   #001h

         ; Enable the Port I/O Crossbar
          MOV   XBR1, #40h           ; Enable Crossbar
          RET
						
TIMER_INITS:
          ANL CKCON, #DIV12		; set timer clock to system/12	

          MOV TMR2CN, #04h		; enable timer 2, and 16-bit auto-reload
	
          MOV TMR2H, #HITIME
          MOV TMR2L, #LOTIME
	
          MOV TMR2RLH, #0FFh		; reload values (at first, close to ovflw value)
          MOV TMR2RLL, #060h
          RET
	
; ----NOW ENABLE INTERRUPTS----
INT_SETUP:
          SETB TIM2INTEN		; timer-2 interrupt enable
          SETB GLOBALINTEN	; Global int 

					setb IT0		; make INT0 Edge-sensitive	(p. 22)
  				setb IT1		; ditto for INT1
					;  setb PX1		; you can try giving higher priority to INT1 (SFR "IP0", p. 25 of user's guide);
					;                   name is from RIDE list, "IP"...
  				setb EX0		; ...and enable INT0
  				setb EX1		; ...and INT1
					mov IT01CF, #75h	; SiLabs special: makes both interrupts active-low, places them at P0.7, P0.5
					;mov IT01CF, #01h
  				setb EA		; Global int enable        (pp.31-32)
	


          RET


; --- INTERRUPT RESPONSE ---
; ISR: JUST TOGGLE LED

	ORG TIMER2VECTOR

ISR:	CPL BLUE_LED
          CLR TF2H		; Clear timer-2 overflow flag (does this clear interrupt flag?)
          RETI	 

ORG INT0VECTOR				; this is defined in VECTORS3210.INC, included above.
									;  It is address 03h, the address to which micro hops
									;   in response to interrupt ZERO
ISR0:	
			PUSH ACC
			MOV A, TMR2RLL
			ADD A, #1Ah
			MOV TMR2RLL, A
			POP ACC

		RETI	


		  END						
						
