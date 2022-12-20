#include "CalculateTD.h"

#include <algorithm>
#include <iomanip>

// запуск калькулятора
void td::CalculateTD::Start() {
	std::cout << "[Запущено приложение: Калькулятор времени торможения автомобиля]\n"s <<
		domain::line__ << '\n' <<
		"Время торможение автомобиля вычислим из суммы {времени затраченного на реакцию водителя + времени срабатывания привода тормозного механизма + половины времени нарастания замедления} и {отношения скорости автомобиля к произведению коэффициента сцепления на ускорение свободного падения}\n"s  <<
		domain::line__ << std::endl;

	AddSpeedAuto();
	AddTimeReaction();
	AddTimeDriveUnit();
	AddAdhesionCoefficient();
	AddTimeDecelerationBuildup();

	ResultCalculate();

	std::cout << "[Закрыто приложение: Калькулятор времени торможения автомобиля]\n"s <<
		domain::line__ << std::endl;
}

// ввод скорости автомобиля
void td::CalculateTD::AddSpeedAuto() {
	do {
		std::cout << "- введите скорость автомобиля в [км/ч], не превышающую скорость света ("s <<
			std::fixed <<
			std::setprecision(1) <<
			domain::speed_of_light__ <<
			"[км/ч])"s << std::endl;
		std::string speed_auto_str = domain::EraseSpace(domain::ReadLine());
		if (domain::IsDigit(speed_auto_str)) {
			double speed_auto = std::stod(speed_auto_str);
			if (speed_auto < domain::speed_of_light__) {
				speedAuto_ = speed_auto;
				std::cout << domain::line__ << std::endl;
				break;
			}
		}
		std::cout << domain::error_command__ << '\n' << domain::line__ << std::endl;
	} while (true);
}

// ввод времени реакции водителя
void td::CalculateTD::AddTimeReaction() {
	do {
		std::cout << "- установим время реакции водителя (0,2–1,5с)\n"s <<
			"пусть данная величина зависит от возраста водителя, тогда обозначим:\n"s <<
			"1.\t18-29\t(0,2-0,4с)\n2.\t30-39\t(0,4-0,7с)\n3.\t40-49\t(0,7-1,0с)\n4.\t50-59\t(1,0-1,3с)\n5.\t60>\t(1,3-1,5с)\n"s <<
			"введите номер категории возраста водителя (временем будет выбрано случайное число в предложенном диапазоне) или нажмите [enter], чтобы выбрать случайное значение"s << std::endl;
		std::string age_category = domain::EraseSpace(domain::ReadLine());
		if (age_category.empty()) {
			timeSum_.t_reaction = domain::GetRandomNumberDouble(0.19, 1.51);
			break;
		}
		else if (age_category == "1"s) {
			timeSum_.t_reaction = domain::GetRandomNumberDouble(0.19, 0.41);
			break;
		}
		else if (age_category == "2"s) {
			timeSum_.t_reaction = domain::GetRandomNumberDouble(0.4, 0.71);
			break;
		}
		else if (age_category == "3"s) {
			timeSum_.t_reaction = domain::GetRandomNumberDouble(0.7, 1.01);
			break;
		}
		else if (age_category == "4"s) {
			timeSum_.t_reaction = domain::GetRandomNumberDouble(1.0, 1.31);
			break;
		}
		else if (age_category == "5"s) {
			timeSum_.t_reaction = domain::GetRandomNumberDouble(1.3, 1.51);
			break;
		}
		std::cout << domain::error_command__ << '\n' << domain::line__ << std::endl;
	} while (true);
	std::cout << "время реакции водителя - "s <<
		std::fixed <<
		std::setprecision(1) <<
		timeSum_.t_reaction << "с\n"s <<
		domain::line__ << std::endl;
}

// ввод времени срабатывания привода
void td::CalculateTD::AddTimeDriveUnit() {
	do {
		std::cout << "- установим время срабатывания привода тормозного механизма\n"s <<
			"в течение этого времени происходит перемещение деталей в приводе; промежуток этого времени зависит от технического состояния привода и его типа\n"s <<
			"для тормозных механизмов с гидравлическим приводом:\n1.\tдисковые тормоза\t(0,005—0,07с)\n2.\tбарабанные тормоза\t(0,15—0,2с)"s << std::endl;
		std::string drive_unit_category = domain::EraseSpace(domain::ReadLine());
		if (drive_unit_category == "1"s) {
			timeSum_.t_driveUnit = domain::GetRandomNumberDouble(0.00499, 0.07001);
			break;
		}
		else if (drive_unit_category == "2"s) {
			timeSum_.t_driveUnit = domain::GetRandomNumberDouble(0.14999, 0.20001);
			break;
		}
		std::cout << domain::error_command__ << '\n' << domain::line__ << std::endl;
	} while (true);
	std::cout << "время срабатывания привода - "s <<
		std::fixed <<
		std::setprecision(4) <<
		timeSum_.t_driveUnit << "с\n"s <<
		domain::line__ << std::endl;
}

// ввод коэффициента сцепления
void td::CalculateTD::AddAdhesionCoefficient() {
	do {
		std::cout << "- установим коэффициент сцепления в зависимости от дорожного покрытия и его влажности\n"s << 
			"/Дорожные условия/\t\t\t/Сухое покрытие/\t/Мокрое покрытие/\n"s <<
			"1.Асфальто- и цементобетонное покрытия\t(0,7-0,8)\t\t(0,4-0,5)\n"s <<
			"2.Гравийное покрытие\t\t\t(0,6-0,7)\t\t(0,3-0,4)\n"s <<
			"3.Грунтовая дорога\t\t\t(0,5-0,6)\t\t(0,2-0,4)\n"s <<
			"4.Дорога, покрытая укатанным снегом\t(0,2-0,3)\t\t(0,2-0,3)\n"s <<
			"5.Обледенелая дорога\t\t\t(0,1-0,2)\t\t(0,1-0,2)\n"s <<
			"выберите из таблицы выше номер подходящего покрытия (например a.b, где a - номер строки (1-5), b - номер столбца (1/2)); коэффициент будет случайным числом в предложенном диапазоне"s << std::endl;
		std::string adhesion_coefficient_number = domain::EraseSpace(domain::ReadLine());
		if (adhesion_coefficient_number.empty()) {
			std::cout << domain::error_command__ << '\n' << domain::line__ << std::endl;
			continue;
		}
		std::vector numbers = domain::SplitIntoWords(adhesion_coefficient_number, '.');
		if (numbers.size() != 2) {
			std::cout << domain::error_command__ << '\n' << domain::line__ << std::endl;
			continue;
		}
		int a = stoi(std::string(numbers[0])); int b = stoi(std::string(numbers[1]));
		if (a < 1 || a > 5 || b < 1 || b > 2) {
			std::cout << domain::error_command__ << '\n' << domain::line__ << std::endl;
			continue;
		}
		switch (b)
		{
		case 1: {
			switch (a)
			{
			case 1: {
				adhesionCoefficient_ = domain::GetRandomNumberDouble(0.7, 0.8);
				break;
			}
			case 2: {
				adhesionCoefficient_ = domain::GetRandomNumberDouble(0.6, 0.7);
				break;
			}
			case 3: {
				adhesionCoefficient_ = domain::GetRandomNumberDouble(0.5, 0.6);
				break;
			}
			case 4: {
				adhesionCoefficient_ = domain::GetRandomNumberDouble(0.2, 0.3);
				break;
			}
			case 5: {
				adhesionCoefficient_ = domain::GetRandomNumberDouble(0.1, 0.2);
				break;
			}
			default:
				std::cout << domain::error_command__ << '\n' << domain::line__ << std::endl;
				continue;
			}
			break;
		}
		case 2: {
			switch (a)
			{
			case 1: {
				adhesionCoefficient_ = domain::GetRandomNumberDouble(0.4, 0.5);
				break;
			}
			case 2: {
				adhesionCoefficient_ = domain::GetRandomNumberDouble(0.3, 0.4);
				break;
			}
			case 3: {
				adhesionCoefficient_ = domain::GetRandomNumberDouble(0.2, 0.4);
				break;
			}
			case 4: {
				adhesionCoefficient_ = domain::GetRandomNumberDouble(0.2, 0.3);
				break;
			}
			case 5: {
				adhesionCoefficient_ = domain::GetRandomNumberDouble(0.1, 0.2);
				break;
			}
			default:
				std::cout << domain::error_command__ << '\n' << domain::line__ << std::endl;
				continue;
			}
			break;
		}
		default:
			std::cout << domain::error_command__ << '\n' << domain::line__ << std::endl;
			continue;
		}
		break;
	} while(true);
	std::cout << "коэффициент сцепления - "s <<
		std::fixed <<
		std::setprecision(1) <<
		adhesionCoefficient_ << '\n' <<
		domain::line__ << std::endl;
}

// ввод времени нарастания замедления
void td::CalculateTD::AddTimeDecelerationBuildup() {
	do {
		std::cout << "- установим время нарастания замедления (0,05-2с)\n"s <<
			"оно зависит от типа автомобиля, состояния дороги, дорожной ситуации, квалификации и состояния водителя, состояния тормозной системы; возрастает с увеличением силы тяжести автомобиля и уменьшением коэффициента сцепления\n"s <<
			"введите время или нажмите [enter], чтобы выбрать случайное значение в зависимости от коэффициента сцепления"s << std::endl;
		std::string time_deceleration_buildup_str = domain::EraseSpace(domain::ReadLine());
		if (time_deceleration_buildup_str.empty()) {
			if (adhesionCoefficient_ < 0.2) {
				timeSum_.t_decelerationBuildup = domain::GetRandomNumberDouble(1.76, 2.0);
				break;
			}
			else if (adhesionCoefficient_ < 0.3) {
				timeSum_.t_decelerationBuildup = domain::GetRandomNumberDouble(1.47, 1.76);
				break;
			}
			else if (adhesionCoefficient_ < 0.4) {
				timeSum_.t_decelerationBuildup = domain::GetRandomNumberDouble(1.19, 1.47);
				break;
			}
			else if (adhesionCoefficient_ < 0.5) {
				timeSum_.t_decelerationBuildup = domain::GetRandomNumberDouble(0.9, 1.19);
				break;
			}
			else if (adhesionCoefficient_ < 0.6) {
				timeSum_.t_decelerationBuildup = domain::GetRandomNumberDouble(0.62, 0.9);
				break;
			}
			else if (adhesionCoefficient_ < 0.7) {
				timeSum_.t_decelerationBuildup = domain::GetRandomNumberDouble(0.33, 0.62);
				break;
			}
			else if (adhesionCoefficient_ < 0.8) {
				timeSum_.t_decelerationBuildup = domain::GetRandomNumberDouble(0.05, 0.33);
				break;
			}
			std::cout << domain::error_command__ << '\n' << domain::line__ << std::endl;
			continue;
		}
		if (domain::IsDigit(time_deceleration_buildup_str)) {
			double time_deceleration_buildup = std::stod(time_deceleration_buildup_str);
			if (time_deceleration_buildup < 0.05 || time_deceleration_buildup > 2.0) {
				std::cout << domain::error_command__ << '\n' << domain::line__ << std::endl;
				continue;
			}
			timeSum_.t_decelerationBuildup = time_deceleration_buildup;
			break;
		}
		break;
	} while (true);
	std::cout << "время нарастания замедления - "s <<
		std::fixed <<
		std::setprecision(2) <<
		timeSum_.t_decelerationBuildup << "с\n"s <<
		domain::line__ << std::endl;
}

// вычисление времени торможения
void td::CalculateTD::ResultCalculate() {
	double speed_auto = speedAuto_ * 5 / 18;
	double result = (timeSum_.t_reaction + timeSum_.t_driveUnit + 0.5 * timeSum_.t_decelerationBuildup) + speed_auto / (adhesionCoefficient_ * domain::g__);
	std::cout << "- рассчитаем время торможения\n"s <<
		"время затраченное на реакцию водителя = "s << timeSum_.t_reaction << "с\n"s <<
		"время срабатывания привода тормозного механизма = "s << timeSum_.t_driveUnit << "с\n"s <<
		"время нарастания замедления = "s << timeSum_.t_decelerationBuildup << "с\n"s <<
		"скорость автомобиля = "s << speedAuto_ << "[км/ч] = "s << speed_auto << "[м/с]\n"s << 
		"коэффициент сцепления = "s << adhesionCoefficient_ << '\n' << 
		"ускорение свободного падения = "s << domain::g__ << "[м/с]\n"s << std::setprecision(3) <<
		"[РЕЗУЛЬТАТ]:\t"s << result << "с\n"s << domain::line__ << std::endl;
}