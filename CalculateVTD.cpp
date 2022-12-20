#include "CalculateVTD.h"

#include <iomanip>
#include <math.h>

// запуск калькулятора
void vtd::CalculateVTD::Start() {
	std::cout << "[Запущено приложение: Калькулятор времени восстановления равновесного состояния после торможения]\n"s <<
		domain::line__ << '\n' <<
		"Время восстановления равновесного состояния после торможения вычислим из отношения объема газа в пневматиечской полости к максимальному количеству выделяемой теплоты (Qmax = "s << std::setprecision(0) << domain::qmax__ <<")\n"s <<
		domain::line__ << std::endl;

	AddVolumePneumaticСavity();

	ResultCalculate();

	std::cout << "[Закрыто приложение: Калькулятор времени восстановления равновесного состояния после торможения]\n"s <<
		domain::line__ << std::endl;
}

// ввод объема газа в пневматиечской полости
void vtd::CalculateVTD::AddVolumePneumaticСavity() {
	do {
		std::cout << "- введите объема газа в пневматиечской полости в [м^3], не превышающую 5 * 10 ^ 8 [м^3]"s << std::endl;
		std::string volume_str = domain::EraseSpace(domain::ReadLine());
		if (domain::IsDigit(volume_str)) {
			double volume = std::stod(volume_str);
			if (volume > 0 && volume < 5 * pow(10, 8)) {
				volume_pneumaticСavity_ = volume;
				std::cout << domain::line__ << std::endl;
				break;
			}
		}
		std::cout << domain::error_command__ << '\n' << domain::line__ << std::endl;
	} while (true);
}

// вычисление времени восстановления равновесного состояния после торможения
void vtd::CalculateVTD::ResultCalculate() {
	double result = - (volume_pneumaticСavity_ / domain::qmax__);
	result = abs(result);
	std::cout << "- рассчитаем время восстановления равновесного состояния после торможения\n"s <<
		"объем газа в пневматиечской полости амортизатора = "s << volume_pneumaticСavity_ << "[м^3]\n"s <<
		"максимальное количество выделяемой теплоты = "s << domain::qmax__ << "Дж\n"s  << std::setprecision(4) <<
		"[РЕЗУЛЬТАТ]:\t"s << result << "\n"s << domain::line__ << std::endl;
}