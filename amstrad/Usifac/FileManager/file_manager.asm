write"DIRECT_ROM.BIN"  
ORG &2900
data equ &2b00 
.txt_output equ &bb5a
.km_read_char equ &bb09	
	
	ld 	a,&FB 
        in 	a,(&De) 
	or	a
	jp	z,no_usb

;CATALOGUE A USB DIRECTORY

	call 	set_directory

	ld	bc,&fbd0
	call	clear_buffer
	call	usb_cmd

	ld	a,&2f
	out	(c),a
	
	ld	c,&d9
	ld 	a,1
	out	(c),a
	ld 	a,&FB 
        in 	a,(&D3) 
	or	a
	jp	nz,continue_man

	ld	c,&d0
	ld	a,"/"
	out	(c),a

continue_man:
	ld	bc,&fbd0
	ld	a,"*"
	out	(c),a
	ld	a,0
	out	(c),a
	call	usb_cmd
	ld	a,&32
	out	(c),a

	call	check_responce2
	ld 	A,&FB 
        in 	A,(&D0)  
	cp	&1d
	jp 	nz,error_4

	ld	hl,data
	ld	a,1
	ld	(hl),a

loop_mancatalogue:

	ld	bc,&fbd0
	call	clear_buffer
	call	usb_cmd
	ld	a,&27
	out	(c),a

	call	check_responce2
	ld 	A,&FB 
        in 	A,(&D0) 
	or	a	
	jp	z,ending_mancatalogue

	ld	b,8
	call	print_man_loop

	call	check_responce2
	ld 	A,&FB 
        in 	A,(&D0)  
	cp	&20
	jp	z,continue2_mancat
	
	ld	b,a
	ld	a,"."
	inc	hl
	ld	(hl),a
	ld	a,b
	inc	hl
	ld	(hl),a
continue2_mancat:
	ld	b,2
	call	print_man_loop

continue_mancat:

	call	check_responce2
	ld 	A,&FB 
        in 	A,(&D0)  
	cp	&10
	jr	nz,continue_manloop
	ld	a," "
	inc	hl
	ld	(hl),a
	ld	a,"<"
	inc	hl
	ld	(hl),a
	ld	a,"D"
	inc	hl
	ld	(hl),a
	ld	a,"I"
	inc	hl
	ld	(hl),a
	ld	a,"R"
	inc	hl
	ld	(hl),a
	ld	a,">"
	inc	hl
	ld	(hl),a

continue_manloop:
	ld	a,1
	inc	hl
	ld	(hl),a

	call	clear_buffer
	call	usb_cmd
	ld	a,&33
	out	(c),a

	call	check_responce2
	ld 	a,&FB 
        in 	a,(&D0)  
	cp	&1d
	jp	z,loop_mancatalogue

ending_mancatalogue:
	ld	a,2
	inc	hl
	ld	(hl),a
	ret

print_man_loop:		
	call	check_responce2
	ld 	A,&FB 
        in 	A,(&D0)  
	cp	&20
	jr	z,cont_print_man
	inc	hl
	ld	(hl),a

cont_print_man:
	djnz	,print_man_loop

	ret

no_usb:
	ld 	hl,message_no_usb_msg
	call	printmessage
	ret


;-----------------------------------------------------------------------------------------
set_directory:
add_sub_dirs2:	
	ld	bc,&fbd9
	ld 	a,1
	out	(c),a
	ld 	a,&FB 
        in 	a,(&D3) 
	cp	"/"		
	jp	nz,continue_usbcat

add_sub_dirs:		
				;Add sub dirs
	ld	bc,&fbd0
	call	clear_buffer
	call	usb_cmd	
	ld	a,&2f
	out	(c),a
	
	ld 	a,&FB 
        in 	a,(&D6) 
	CP	2
	jr	nz,dir_catname

	ld	a,"/"
	out	(c),a
		
dir_catname:
	ld 	a,&FB 
        in 	a,(&D3) 	
	cp	"/"
	jr	z,continue_subdir_loop
	or	a
	jr	z,continue_subdir_loop
	out	(c),a
	jr	dir_catname

continue_subdir_loop:
	ld	d,a
	ld	a,0
	out	(c),a
	call	clear_buffer
	call	usb_cmd
	ld	a,&32
	out	(c),a
	call	check_responce2

	ld 	A,&FB 
        in 	A,(&D0)  
	cp	&41
	jp	nz,error_ucd

	ld	a,d
	or	a
	jr	z,continue_usbcat
	jp	add_sub_dirs

continue_usbcat:
	ret
;-----------------------------------------------------------------------------------------
usb_cmd:
	ld	a,&57
	out	(c),a			
	ld	a,&ab
	out	(c),a
	ret
;-----------------------------

;---------------------------------------------------------------------------------------
check_responce2:	
        ld	a,&FB 
        in 	a,(&D1)  
        dec 	a
        jr z,check_responce2
	ret
clear_buffer:	
	inc	c				;clear buffer
	ld	a,1
	out	(c),a
	dec	c
	ret

;-----------------------------------------------------------------------------------------
error_4:
	ld	bc,&fbd1
	ld	a,9
	out	(c),a
	ld 	hl,error4_message
	call	printmessage
	ret
;-----------------------------------------------------------------------------------------
printmessage:
	ld 	a,(hl)
	or 	a
	ret	z
	call 	&bb5a
	inc 	hl
	jr 	printmessage
;-----------------------------------------------------------------------------------------
error_ucd:
	ei
	ld	hl,error3_message
	call 	printmessage
	ret

message_no_usb_msg:
defb "Usb Device not enabled!",13,10,0

error4_message:
defb "No File(s) or Dir(s) Found!",13,10,0

error3_message:
defb "Unexpected error!",13,10,0