## README

- [English](README.md)
- [Русский](README-ru.md)

## Дерево проекта

```
tree --charset ascii

.
|-- README*.md      // инструкции
|-- Debug
|   `-- *.exe       // исполняемый файл
|-- Release
|   `-- *.exe       // исполняемый файл
|-- *
|   `-- App         // папка с исходным кодом С++
`-- *.sln           // открыть проект Visual Studio
```

## Как скомпилировать проект

Проект написан в IDE `Visual Studio 2019`.

Чтобы открыть проект - запускаем файл `*.sln`.

В IDE `Visual Studio 2019` есть зелёная кнопка стрелка `|> Local Windows Debugger` - создается в папке `Release` или в папке `Debug` исполняемый файл `*.exe`.
