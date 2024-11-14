cmake_minimum_required(VERSION 3.15) # Проверка версии CMake.
									 # Если версия установленой программы
									 # старее указаной, произайдёт аварийный выход.

set(PROJECT_NAME ASD) # задать значение PROJECT_NAME		 
project("${PROJECT_NAME}")           # установить имя проекта

file(COPY "sorting.txt" DESTINATION "/")
file(COPY "words.txt" DESTINATION "/")

set(CMAKE_CXX_STANDARD 17)			 # устанавливаем 17 стандарт языка
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
include_directories("include/")		#Добавляем хедеры

# Сказать программе, что должен быть исполняемый файл
add_executable("${PROJECT_NAME}" main.cpp
								include/stack.hpp include/labs.hpp)

#Устанавливаем в качестве запускаемого проекта наш проект
set_property(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}" PROPERTY VS_STARTUP_PROJECT "${PROJECT_NAME}")