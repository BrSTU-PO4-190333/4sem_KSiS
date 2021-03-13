		.MODEL	Tiny
		.STACK	100h

		.DATA
	Msg	DB 'Hello.',13,10,'$'

		.CODE
		mov ax, @Data		; установить регистр DS
		mov ds, ax			; на сегмент с данными

		mov ah, 9			; функция DOS вывода строки
		mov dx, OFFSET Msg	; ссылка на сообщение
		int 21h				; вызов DOS

		mov ax, 4C00h		; функция DOS завершения программы
		int 21h				; вызов DOS

		END