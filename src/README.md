### Part 1. Настройка **gitlab-runner**

##### Подними виртуальную машину *Ubuntu Server 22.04 LTS*.

![Alt text](images/LTS_22.04.png)

##### Скачал и установил на виртуальную машину **gitlab-runner**.

![Alt text](images/install_runner.png)

##### Запустил **gitlab-runner** и зарегистрировал его для использования в текущем проекте

![alt text](images/on_gitlab_run.png)

### Part 2. Сборка

#### Написал этап для **CI** по сборке приложений из проекта *C2_SimpleBashUtils*, а так же файлы, полученные после сборки, сохранил в произвольную директорию со сроком хранения 30 дней.

![alt text](images/buld_script.png)

##### Проверям pipline

![alt text](images/check_buld.png)


### Part 3. Тест кодстайла

#### Написал этап для **CI**, который запускает скрипт кодстайла (*clang-format*).

![alt text](images/style_script.png)

##### Если кодстайл не прошел, то «зафейлил» пайплайн.

![alt text](images/style_test_mistake.png)


### Part 4. Интеграционные тесты

**== Задание ==**

#### Написал этап для **CI**, который запускает интеграционные тесты из того же проекта.

![alt text](images/test_script2.png)

##### Если тесты не прошли, то пайплайн будет зафейлен.

![alt text](images/test_fail.png)


### Part 5. Этап деплоя


##### Поднял вторую виртуальную машину *Ubuntu Server 22.04 LTS*.

![alt text](images/cd.png)

#### Написал этап для **CD**, который «разворачивает» проект на другой виртуальной машине.

![alt text](images/add_run_bash.png)


##### Написал bash-скрипт, который при помощи **ssh** и **scp** копирует файлы, полученные после сборки (артефакты), в директорию */usr/local/bin* второй виртуальной машины.

![alt text](images/CD_script.png)

- результат скрипта
![alt text](images/RESULT_bash_script.png)

- pipline выполнен

![alt text](images/зшз5.png)

### Part 6. Дополнительно. Уведомления

##### Настроил уведомления об успешном/неуспешном выполнении пайплайна через бота с именем "theiajar DO6 CI/CD» в *Telegram*.

 - скрипт
![alt text](images/Telega_script.png)

- результат

![alt text](images/telega_result.png)