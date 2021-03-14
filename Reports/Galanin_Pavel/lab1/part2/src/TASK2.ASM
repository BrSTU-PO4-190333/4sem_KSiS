		.MODEL Tiny
		.STACK 100h

		.DATA
	Surname		DB	'Galanin',13,10,'$'	; строковая переменная (Surname = "Galanin\n")
	EmptyString	DB	13,10,'$'		; строковая переменная (EmptyString = "\n")
	N		DW	5			; целочисленная переменная (N = 12)

		.CODE
		mov	ax, @Data			; установить регистр DS
		mov	ds, ax				; на сегмент с данными


							; Задание (вывести N символов со строки)


		mov	dx, OFFSET Surname		; ссылка на сообщение (Surname)
		mov	bx, 1				; информация будет отображена на экране
		mov	cx, N				; количество букв (N)
		mov	ah, 40h				; функция вывода строки
		int	21h				; вызов прерывания DOS


							; вывод пустой строки


		mov	dx, OFFSET EmptyString		; ссылка на сообщение (EmptyString)
		mov	ah, 9h				; функция DOS вывода строки
		int	21h				; вызов прерывания DOS


							; = = = = = > Задание (вывести циклически строку N-1 раз)


		sub	N, 1				; разность N и 1 (N = N - 1)

		mov	dx, OFFSET Surname		; ссылка на сообщение (Surname)

		mov	cx, N				; количество проходов цикла (N-1)
		NextLoop:				; метка для перехода
							; ------------------ тело цикла
			mov	ah, 9h			; функция DOS вывода строки
			int	21h			; вызов прерывания DOS
							; ------------------ конец тела цикла
		loop	NextLoop			; повторить CX раз от метки NextLoop


		mov		ax, 4C00h		; функция DOS завершения программы
		int		21h			; вызов прерывания DOS

		END
