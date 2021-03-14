		.MODEL	Tiny
		.STACK	100h

		.DATA
	Msg	DB	'Hello.',13,10,'$'	; строковая переменная (Msg = "Hello.\n")

		.CODE
		mov	ax, @Data		; установить регистр DS
		mov	ds, ax			; на сегмент с данными

		mov	ah, 9			; функция DOS вывода строки
		mov	dx, OFFSET Msg		; ссылка на сообщение (Msg)
		int	21h			; вызов прерывания DOS

		mov	ax, 4C00h		; функция DOS завершения программы
		int	21h			; вызов DOS

		END