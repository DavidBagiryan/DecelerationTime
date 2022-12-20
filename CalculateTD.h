#pragma once

#include "Domain.h"

namespace td {
	using namespace std::literals;

	// структура для хранения данных времени
	struct TimeSum {
		// время реакции водителя
		double t_reaction = 0;
		// время срабатывания привода
		double t_driveUnit = 0;
		// время нарастания замедления
		double t_decelerationBuildup = 0;
	};

	// класс калькулятора времени торможения
	class CalculateTD {
	public:
		CalculateTD() = default;
		// запуск калькулятора
		void Start();

	private:
		double speedAuto_ = 0;
		double adhesionCoefficient_ = 0;
		TimeSum timeSum_;

		// ввод скорости автомобиля
		void AddSpeedAuto();
		// ввод времени реакции водителя
		void AddTimeReaction();
		// ввод времени срабатывания привода
		void AddTimeDriveUnit();
		// ввод коэффициента сцепления
		void AddAdhesionCoefficient();
		// ввод времени нарастания замедления
		void AddTimeDecelerationBuildup();

		// вычисление времени торможения
		void ResultCalculate();
	};
}