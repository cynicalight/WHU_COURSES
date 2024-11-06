assume cs:code,ds:data

temp segment
	     db 16 dup(0)
temp ends

code segment
	start:mov  ax,data
	      mov  ds,ax
	      mov  ax,0b800h
	      mov  es,ax
	      mov  di,(5-1)*00a0h+2*(3-1)
	      mov  bx,0
			
	      mov  cx,300
	s:    mov  si,0
	      push cx
	    	
	      mov  cx,5
	s2:   mov  al,ds:[bx+si]
	      cmp  al,ds:[5400+si]         	
	      jne  skip1
	      inc  si
	      loop s2
			
	      add  si,7
	      mov  ax,ds:[bx+si]
	      add  ax,ds:[bx+si+2]
	      cmp  ax,255                  	
	      jna  skip1
	      cmp  byte ptr ds:[bx+si+4],18	
	      jnb  skip1
	
	      push di
	      mov  si,0
	      mov  cx,12
	s1:   mov  al,ds:[bx+si]           	
	      mov  es:[di],al
	      mov  byte ptr es:[di+1],2
	      add  di,2
	      inc  si
	      loop s1
	   		
	      mov  byte ptr es:[di],' '
	      add  di,2
	   		
	      mov  cx,3
	s8:   mov  ax,ds:[bx+si]           	
	      push bx
	      push ds
	      push si
	      push cx
	      mov  bx,temp
	      mov  ds,bx
	      mov  si,0
	      mov  bl,10
	s9:   div  bl
	      add  ah,'0'
	      mov  ds:[si],ah
	      inc  si
	      mov  ah,0
	      cmp  al,0
	      je   skip6
	      jmp  short s9
	skip6:mov  cx,si
	
	s10:  dec  si                      	
	      mov  al,ds:[si]
	      mov  es:[di],al
	      mov  byte ptr es:[di+1],2
	      add  di,2
	      loop s10
	      mov  byte ptr es:[di],' '
	      add  di,2
	      pop  cx
	      pop  si
	      pop  ds
	      pop  bx
	      add  si,2
	      loop s8
	   		
	      pop  di
	      add  di,160
		
	skip1:pop  cx
	      add  bx,18
	      dec  cx
	      cmp  cx,0
	      je   skip2
	      jmp  near ptr s
			
	skip2:mov  ax,4c00h
	      int  21h
	   		
code ends

data segment
	     db "Hubei jie1  "
dw 149,149,20
db "Henan jie2  "
dw 120,110,17
db "Jilin jie3  "
dw 150,150,21
db "Hubei jie4  "
dw 149,149,20
db "Henan jie5  "
dw 120,110,17
db "Jilin jie6  "
dw 150,150,21
db "Hubei jie7  "
dw 149,149,20
db "Henan jie8  "
dw 120,110,17
db "Jilin jie9  "
dw 150,150,21
db "Hubei jie10 "
dw 149,149,20
db "Henan jie11 "
dw 120,110,17
db "Jilin jie12 "
dw 150,150,21
db "Hubei jie13 "
dw 149,149,20
db "Henan jie14 "
dw 120,110,17
db "Jilin jie15 "
dw 150,150,21
db "Hubei jie16 "
dw 149,149,20
db "Henan jie17 "
dw 120,110,17
db "Jilin jie18 "
dw 150,150,21
db "Hubei jie19 "
dw 149,149,20
db "Henan jie20 "
dw 120,110,17
db "Jilin jie21 "
dw 150,150,21
db "Hubei jie22 "
dw 149,149,20
db "Henan jie23 "
dw 120,110,17
db "Jilin jie24 "
dw 150,150,21
db "Hubei jie25 "
dw 149,149,20
db "Henan jie26 "
dw 120,110,17
db "Jilin jie27 "
dw 150,150,21
db "Hubei jie28 "
dw 149,149,20
db "Henan jie29 "
dw 120,110,17
db "Jilin jie30 "
dw 150,150,21
db "Hubei jie31 "
dw 149,149,20
db "Henan jie32 "
dw 120,110,17
db "Jilin jie33 "
dw 150,150,21
db "Hubei jie34 "
dw 149,149,20
db "Henan jie35 "
dw 120,110,17
db "Jilin jie36 "
dw 150,150,21
db "Hubei jie37 "
dw 149,149,20
db "Henan jie38 "
dw 120,110,17
db "Jilin jie39 "
dw 150,150,21
db "Hubei jie40 "
dw 149,149,20
db "Henan jie41 "
dw 120,110,17
db "Jilin jie42 "
dw 150,150,21
db "Hubei jie43 "
dw 149,149,20
db "Henan jie44 "
dw 120,110,17
db "Jilin jie45 "
dw 150,150,21
db "Hubei jie46 "
dw 149,149,20
db "Henan jie47 "
dw 120,110,17
db "Jilin jie48 "
dw 150,150,21
db "Hubei jie49 "
dw 149,149,20
db "Henan jie50 "
dw 120,110,17
db "Jilin jie51 "
dw 150,150,21
db "Hubei jie52 "
dw 149,149,20
db "Henan jie53 "
dw 120,110,17
db "Jilin jie54 "
dw 150,150,21
db "Hubei jie55 "
dw 149,149,20
db "Henan jie56 "
dw 120,110,17
db "Jilin jie57 "
dw 150,150,21
db "Hubei jie58 "
dw 149,149,20
db "Henan jie59 "
dw 120,110,17
db "Jilin jie60 "
dw 150,150,21
db "Hubei jie61 "
dw 149,149,20
db "Henan jie62 "
dw 120,110,17
db "Jilin jie63 "
dw 150,150,21
db "Hubei jie64 "
dw 149,149,20
db "Henan jie65 "
dw 120,110,17
db "Jilin jie66 "
dw 150,150,21
db "Hubei jie67 "
dw 149,149,20
db "Henan jie68 "
dw 120,110,17
db "Jilin jie69 "
dw 150,150,21
db "Hubei jie70 "
dw 149,149,20
db "Henan jie71 "
dw 120,110,17
db "Jilin jie72 "
dw 150,150,21
db "Hubei jie73 "
dw 149,149,20
db "Henan jie74 "
dw 120,110,17
db "Jilin jie75 "
dw 150,150,21
db "Hubei jie76 "
dw 149,149,20
db "Henan jie77 "
dw 120,110,17
db "Jilin jie78 "
dw 150,150,21
db "Hubei jie79 "
dw 149,149,20
db "Henan jie80 "
dw 120,110,17
db "Jilin jie81 "
dw 150,150,21
db "Hubei jie82 "
dw 149,149,20
db "Henan jie83 "
dw 120,110,17
db "Jilin jie84 "
dw 150,150,21
db "Hubei jie85 "
dw 149,149,20
db "Henan jie86 "
dw 120,110,17
db "Jilin jie87 "
dw 150,150,21
db "Hubei jie88 "
dw 149,149,20
db "Henan jie89 "
dw 120,110,17
db "Jilin jie90 "
dw 150,150,21
db "Hubei jie91 "
dw 149,149,20
db "Henan jie92 "
dw 120,110,17
db "Jilin jie93 "
dw 150,150,21
db "Hubei jie94 "
dw 149,149,20
db "Henan jie95 "
dw 120,110,17
db "Jilin jie96 "
dw 150,150,21
db "Hubei jie97 "
dw 149,149,20
db "Henan jie98 "
dw 120,110,17
db "Jilin jie99 "
dw 150,150,21
db "Hubei jie100"
dw 149,149,20
db "Henan jie101"
dw 120,110,17
db "Jilin jie102"
dw 150,150,21
db "Hubei jie103"
dw 149,149,20
db "Henan jie104"
dw 120,110,17
db "Jilin jie105"
dw 150,150,21
db "Hubei jie106"
dw 149,149,20
db "Henan jie107"
dw 120,110,17
db "Jilin jie108"
dw 150,150,21
db "Hubei jie109"
dw 149,149,20
db "Henan jie110"
dw 120,110,17
db "Jilin jie111"
dw 150,150,21
db "Hubei jie112"
dw 149,149,20
db "Henan jie113"
dw 120,110,17
db "Jilin jie114"
dw 150,150,21
db "Hubei jie115"
dw 149,149,20
db "Henan jie116"
dw 120,110,17
db "Jilin jie117"
dw 150,150,21
db "Hubei jie118"
dw 149,149,20
db "Henan jie119"
dw 120,110,17
db "Jilin jie120"
dw 150,150,21
db "Hubei jie121"
dw 149,149,20
db "Henan jie122"
dw 120,110,17
db "Jilin jie123"
dw 150,150,21
db "Hubei jie124"
dw 149,149,20
db "Henan jie125"
dw 120,110,17
db "Jilin jie126"
dw 150,150,21
db "Hubei jie127"
dw 149,149,20
db "Henan jie128"
dw 120,110,17
db "Jilin jie129"
dw 150,150,21
db "Hubei jie130"
dw 149,149,20
db "Henan jie131"
dw 120,110,17
db "Jilin jie132"
dw 150,150,21
db "Hubei jie133"
dw 149,149,20
db "Henan jie134"
dw 120,110,17
db "Jilin jie135"
dw 150,150,21
db "Hubei jie136"
dw 149,149,20
db "Henan jie137"
dw 120,110,17
db "Jilin jie138"
dw 150,150,21
db "Hubei jie139"
dw 149,149,20
db "Henan jie140"
dw 120,110,17
db "Jilin jie141"
dw 150,150,21
db "Hubei jie142"
dw 149,149,20
db "Henan jie143"
dw 120,110,17
db "Jilin jie144"
dw 150,150,21
db "Hubei jie145"
dw 149,149,20
db "Henan jie146"
dw 120,110,17
db "Jilin jie147"
dw 150,150,21
db "Hubei jie148"
dw 149,149,20
db "Henan jie149"
dw 120,110,17
db "Jilin jie150"
dw 150,150,21
db "Hubei jie151"
dw 149,149,20
db "Henan jie152"
dw 120,110,17
db "Jilin jie153"
dw 150,150,21
db "Hubei jie154"
dw 149,149,20
db "Henan jie155"
dw 120,110,17
db "Jilin jie156"
dw 150,150,21
db "Hubei jie157"
dw 149,149,20
db "Henan jie158"
dw 120,110,17
db "Jilin jie159"
dw 150,150,21
db "Hubei jie160"
dw 149,149,20
db "Henan jie161"
dw 120,110,17
db "Jilin jie162"
dw 150,150,21
db "Hubei jie163"
dw 149,149,20
db "Henan jie164"
dw 120,110,17
db "Jilin jie165"
dw 150,150,21
db "Hubei jie166"
dw 149,149,20
db "Henan jie167"
dw 120,110,17
db "Jilin jie168"
dw 150,150,21
db "Hubei jie169"
dw 149,149,20
db "Henan jie170"
dw 120,110,17
db "Jilin jie171"
dw 150,150,21
db "Hubei jie172"
dw 149,149,20
db "Henan jie173"
dw 120,110,17
db "Jilin jie174"
dw 150,150,21
db "Hubei jie175"
dw 149,149,20
db "Henan jie176"
dw 120,110,17
db "Jilin jie177"
dw 150,150,21
db "Hubei jie178"
dw 149,149,20
db "Henan jie179"
dw 120,110,17
db "Jilin jie180"
dw 150,150,21
db "Hubei jie181"
dw 149,149,20
db "Henan jie182"
dw 120,110,17
db "Jilin jie183"
dw 150,150,21
db "Hubei jie184"
dw 149,149,20
db "Henan jie185"
dw 120,110,17
db "Jilin jie186"
dw 150,150,21
db "Hubei jie187"
dw 149,149,20
db "Henan jie188"
dw 120,110,17
db "Jilin jie189"
dw 150,150,21
db "Hubei jie190"
dw 149,149,20
db "Henan jie191"
dw 120,110,17
db "Jilin jie192"
dw 150,150,21
db "Hubei jie193"
dw 149,149,20
db "Henan jie194"
dw 120,110,17
db "Jilin jie195"
dw 150,150,21
db "Hubei jie196"
dw 149,149,20
db "Henan jie197"
dw 120,110,17
db "Jilin jie198"
dw 150,150,21
db "Hubei jie199"
dw 149,149,20
db "Henan jie200"
dw 120,110,17
db "Jilin jie201"
dw 150,150,21
db "Hubei jie202"
dw 149,149,20
db "Henan jie203"
dw 120,110,17
db "Jilin jie204"
dw 150,150,21
db "Hubei jie205"
dw 149,149,20
db "Henan jie206"
dw 120,110,17
db "Jilin jie207"
dw 150,150,21
db "Hubei jie208"
dw 149,149,20
db "Henan jie209"
dw 120,110,17
db "Jilin jie210"
dw 150,150,21
db "Hubei jie211"
dw 149,149,20
db "Henan jie212"
dw 120,110,17
db "Jilin jie213"
dw 150,150,21
db "Hubei jie214"
dw 149,149,20
db "Henan jie215"
dw 120,110,17
db "Jilin jie216"
dw 150,150,21
db "Hubei jie217"
dw 149,149,20
db "Henan jie218"
dw 120,110,17
db "Jilin jie219"
dw 150,150,21
db "Hubei jie220"
dw 149,149,20
db "Henan jie221"
dw 120,110,17
db "Jilin jie222"
dw 150,150,21
db "Hubei jie223"
dw 149,149,20
db "Henan jie224"
dw 120,110,17
db "Jilin jie225"
dw 150,150,21
db "Hubei jie226"
dw 149,149,20
db "Henan jie227"
dw 120,110,17
db "Jilin jie228"
dw 150,150,21
db "Hubei jie229"
dw 149,149,20
db "Henan jie230"
dw 120,110,17
db "Jilin jie231"
dw 150,150,21
db "Hubei jie232"
dw 149,149,20
db "Henan jie233"
dw 120,110,17
db "Jilin jie234"
dw 150,150,21
db "Hubei jie235"
dw 149,149,20
db "Henan jie236"
dw 120,110,17
db "Jilin jie237"
dw 150,150,21
db "Hubei jie238"
dw 149,149,20
db "Henan jie239"
dw 120,110,17
db "Jilin jie240"
dw 150,150,21
db "Hubei jie241"
dw 149,149,20
db "Henan jie242"
dw 120,110,17
db "Jilin jie243"
dw 150,150,21
db "Hubei jie244"
dw 149,149,20
db "Henan jie245"
dw 120,110,17
db "Jilin jie246"
dw 150,150,21
db "Hubei jie247"
dw 149,149,20
db "Henan jie248"
dw 120,110,17
db "Jilin jie249"
dw 150,150,21
db "Hubei jie250"
dw 149,149,20
db "Henan jie251"
dw 120,110,17
db "Jilin jie252"
dw 150,150,21
db "Hubei jie253"
dw 149,149,20
db "Henan jie254"
dw 120,110,17
db "Jilin jie255"
dw 150,150,21
db "Hubei jie256"
dw 149,149,20
db "Henan jie257"
dw 120,110,17
db "Jilin jie258"
dw 150,150,21
db "Hubei jie259"
dw 149,149,20
db "Henan jie260"
dw 120,110,17
db "Jilin jie261"
dw 150,150,21
db "Hubei jie262"
dw 149,149,20
db "Henan jie263"
dw 120,110,17
db "Jilin jie264"
dw 150,150,21
db "Hubei jie265"
dw 149,149,20
db "Henan jie266"
dw 120,110,17
db "Jilin jie267"
dw 150,150,21
db "Hubei jie268"
dw 149,149,20
db "Henan jie269"
dw 120,110,17
db "Jilin jie270"
dw 150,150,21
db "Hubei jie271"
dw 149,149,20
db "Henan jie272"
dw 120,110,17
db "Jilin jie273"
dw 150,150,21
db "Hubei jie274"
dw 149,149,20
db "Henan jie275"
dw 120,110,17
db "Jilin jie276"
dw 150,150,21
db "Hubei jie277"
dw 149,149,20
db "Henan jie278"
dw 120,110,17
db "Jilin jie279"
dw 150,150,21
db "Hubei jie280"
dw 149,149,20
db "Henan jie281"
dw 120,110,17
db "Jilin jie282"
dw 150,150,21
db "Hubei jie283"
dw 149,149,20
db "Henan jie284"
dw 120,110,17
db "Jilin jie285"
dw 150,150,21
db "Hubei jie286"
dw 149,149,20
db "Henan jie287"
dw 120,110,17
db "Jilin jie288"
dw 150,150,21
db "Hubei jie289"
dw 149,149,20
db "Henan jie290"
dw 120,110,17
db "Jilin jie291"
dw 150,150,21
db "Hubei jie292"
dw 149,149,20
db "Henan jie293"
dw 120,110,17
db "Jilin jie294"
dw 150,150,21
db "Hubei jie295"
dw 149,149,15
db "Henan jie296"
dw 120,110,17
db "Jilin jie297"
dw 150,150,21
db "Hubei jie298"
dw 149,149,15
db "Henan jie299"
dw 120,110,17
db "Jilin jie300"
dw 150,150,15
db "Hubei",0,0,0
data ends

end start
