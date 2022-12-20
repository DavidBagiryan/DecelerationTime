#pragma once

#include "Domain.h"

namespace td {
	using namespace std::literals;

	// ��������� ��� �������� ������ �������
	struct TimeSum {
		// ����� ������� ��������
		double t_reaction = 0;
		// ����� ������������ �������
		double t_driveUnit = 0;
		// ����� ���������� ����������
		double t_decelerationBuildup = 0;
	};

	// ����� ������������ ������� ����������
	class CalculateTD {
	public:
		CalculateTD() = default;
		// ������ ������������
		void Start();

	private:
		double speedAuto_ = 0;
		double adhesionCoefficient_ = 0;
		TimeSum timeSum_;

		// ���� �������� ����������
		void AddSpeedAuto();
		// ���� ������� ������� ��������
		void AddTimeReaction();
		// ���� ������� ������������ �������
		void AddTimeDriveUnit();
		// ���� ������������ ���������
		void AddAdhesionCoefficient();
		// ���� ������� ���������� ����������
		void AddTimeDecelerationBuildup();

		// ���������� ������� ����������
		void ResultCalculate();
	};
}