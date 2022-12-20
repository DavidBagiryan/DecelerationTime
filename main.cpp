#include "CalculateTD.h"
#include "CalculateVTD.h"

#include <Windows.h>

using namespace std::literals;

// Список комманд
enum class CommandMain {
    ZERO,
    END,
    ONE,
    TWO
};

// обработка команды
CommandMain EnterCommand(const std::string& command) {
    // удаление пробелов
    std::string command_process = domain::EraseSpace(command);

    if (command_process == "end"s) return CommandMain::END;
    if (command_process == "1"s) return CommandMain::ONE;
    if (command_process == "2"s) return CommandMain::TWO;

    std::cout << domain::error_command__ << '\n' << domain::line__ << std::endl;
    return CommandMain::ZERO;
}

int main() {
    SetConsoleCP(1251);         // устанавливает вывод данных в кодировку 1251 - +русский язык
    SetConsoleOutputCP(1251);   // устанавливает ввод данных в кодировку 1251 - +русский язык

    do {
        std::cout << "- выберите решаему задачу из списка:\n"s <<
            "1) расчет времени торможения автомобиля;\n"s <<
            "2) расчет времени восстановления равновесного состояния.\n"s <<
            "введите номер задачи или end, чтобы выйти из программы\n"s <<
            domain::line__  << std::endl;
        CommandMain task = EnterCommand(domain::ReadLine());

        switch (task)
        {
        case CommandMain::ZERO:
            continue;
        case CommandMain::END:
            break;
        case CommandMain::ONE:
        {
            td::CalculateTD process;
            process.Start();
            continue;
        }
        break; 
        case CommandMain::TWO:
        {
            vtd::CalculateVTD process;
            process.Start();
            continue;
        }
        default:
            continue;
        }
        break;
    } while (true);
}