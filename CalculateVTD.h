#pragma once

#include "Domain.h"

namespace vtd {
	using namespace std::literals;

	// класс калькулятора времени восстановления равновесного состояния после торможения
	class CalculateVTD {
	public:
		CalculateVTD() = default;
		// запуск калькулятора
		void Start();

	private:
		double volume_pneumaticСavity_ = 0;

		// ввод объема газа в пневматиечской полости
		void AddVolumePneumaticСavity();

		// вычисление времени восстановления равновесного состояния после торможения
		void ResultCalculate();
	};
}