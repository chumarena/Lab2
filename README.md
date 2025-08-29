# Cpp-Course

Это репозиторий для C++ курса у Григорьева. Одна из лабораторных работ будет требовать графику, рекомендован SDL. Поэтому тут будет инструкция, как безболезненно, одинаково у всех и быстро установить эту графику и писать под Linux в Docker контейнере.

## 1) Нужные программы:

- **[Docker Desktop](https://www.docker.com/products/docker-desktop/)** - сам непосредственно Docker  
- **[VSCode](https://code.visualstudio.com/download)** - в нём будет удобнее всего запускать контейнер, поэтому крайне рекомендую его использовать.
- Для запуска графики понадобится X server:
  - Для Windows - **[VcXsrv](https://sourceforge.net/projects/vcxsrv/)**
  - Для Mac - **[XQuartz](https://www.xquartz.org/)**
  - Для Linux ничего не надо, X server там встроенный.
- **[Git](https://git-scm.com/downloads)** - нужно установить и добавить переменную окружения с Git, погуглите, как это сделать на вашей платформе.

## 2) Расширения для VSCode:

Установите следующие расширения:
- [C/C++](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)
- [CMake Tools](https://marketplace.visualstudio.com/items?itemName=twxs.cmake)
- [Remote - Containers](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers)
- [Docker](https://marketplace.visualstudio.com/items?itemName=ms-azuretools.vscode-docker)

Эти дополнения нужно установить через вкладку с расширениями в боковом меню.

## 3) Инициализация репозитория:

1. Создайте папку, где будет ваш проект, и откройте её в VSCode.
2. Откройте терминал (верхнее меню) и в верхнем меню самого терминала откройте Git Bash консоль.
3. Введите команду:
   ```bash
   git clone https://github.com/Ftp-Glich/Cpp-Cource.git (если не работает ссылка скопируйте ссылку в зеленой кнопке code на главном экране)
   ```
4. Теперь у вас есть нужные файлы!
5. Откройте в VSCode именно папку из репозитория Cpp-Course.

## 4) Подготовка к развертыванию контейнера:

(Дальше гайд будет про Windows в основном, под Mac и Linux действия аналогичные, просто гуглите, как это сделать на вашей системе.)

1. Запустите свой вариант X server (VcXsrv или XQuartz). 
   - Для VcXsrv: запустите программу, не трогайте количество окон (-1 должно быть), выберите "No clients" и **ВАЖНО**: "Disable access control", чтобы разрешить другим устройствам использовать его.
   - На Windows в правом нижнем меню по стрелке должен быть значок X server. Также стоит проверить, разрешена ли эта программа в брандмауэре Windows; если её там нет, добавьте путь к исполняемому файлу vcxsrv.exe.
2. Запустите Docker Desktop.
3. В консоли выполните команду:
  ```bash
   ipconfig
  ```
   и запомните свой адрес IPv4 (он должен быть что-то вроде 192.168.x.x). Вставьте этот адрес в файлы .devcontainer/devcontainer.json, .devcontainer/dockerfile, .vscode/launch.json.

## 5) Развертывание контейнера:

1. Нажмите F1 и введите Dev Containers: Reopen In Container.
2. Если всё прошло хорошо, в левом нижнем углу будет название вашего нового контейнера.
3. В команндной паллете сверху пишите >Tasks: Run Task и выберете Configure CMake
4. Должна появиться папка build - значит все хорошо


## 6) Проверка:

В левом боковом меню выберите вкладку **Run and Debug** и выберите нужную конфигурацию - **Debug SDL App**, затем нажмите **Play**. После этого должно появиться синее окно - наша графика, значит всё получилось(добавлена автоматическая сборка при запуске дебага).
Так же можно просто запустить gcc main.cpp - выбрать сборку "(gdb)Launch" - она тоже с автоматической сборкой.

## 7) Фикс сборок:
если со сборкой cmake что-то идет не так, удалите папку build и в команндной паллете сверху пишите >Tasks: Run Task и выберете Configure CMake

Если есть вопросы, пишите в Telegram: [@ftpdog](https://t.me/ftpdog).

 
