#pragma once

#include "Domain.h"

namespace vtd {
	using namespace std::literals;

	// ����� ������������ ������� �������������� ������������ ��������� ����� ����������
	class CalculateVTD {
	public:
		CalculateVTD() = default;
		// ������ ������������
		void Start();

	private:
		double volume_pneumatic�avity_ = 0;

		// ���� ������ ���� � �������������� �������
		void AddVolumePneumatic�avity();

		// ���������� ������� �������������� ������������ ��������� ����� ����������
		void ResultCalculate();
	};
}