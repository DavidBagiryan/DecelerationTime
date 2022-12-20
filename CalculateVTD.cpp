#include "CalculateVTD.h"

#include <iomanip>
#include <math.h>

// ������ ������������
void vtd::CalculateVTD::Start() {
	std::cout << "[�������� ����������: ����������� ������� �������������� ������������ ��������� ����� ����������]\n"s <<
		domain::line__ << '\n' <<
		"����� �������������� ������������ ��������� ����� ���������� �������� �� ��������� ������ ���� � �������������� ������� � ������������� ���������� ���������� ������� (Qmax = "s << std::setprecision(0) << domain::qmax__ <<")\n"s <<
		domain::line__ << std::endl;

	AddVolumePneumatic�avity();

	ResultCalculate();

	std::cout << "[������� ����������: ����������� ������� �������������� ������������ ��������� ����� ����������]\n"s <<
		domain::line__ << std::endl;
}

// ���� ������ ���� � �������������� �������
void vtd::CalculateVTD::AddVolumePneumatic�avity() {
	do {
		std::cout << "- ������� ������ ���� � �������������� ������� � [�^3], �� ����������� 5 * 10 ^ 8 [�^3]"s << std::endl;
		std::string volume_str = domain::EraseSpace(domain::ReadLine());
		if (domain::IsDigit(volume_str)) {
			double volume = std::stod(volume_str);
			if (volume > 0 && volume < 5 * pow(10, 8)) {
				volume_pneumatic�avity_ = volume;
				std::cout << domain::line__ << std::endl;
				break;
			}
		}
		std::cout << domain::error_command__ << '\n' << domain::line__ << std::endl;
	} while (true);
}

// ���������� ������� �������������� ������������ ��������� ����� ����������
void vtd::CalculateVTD::ResultCalculate() {
	double result = - (volume_pneumatic�avity_ / domain::qmax__);
	result = abs(result);
	std::cout << "- ���������� ����� �������������� ������������ ��������� ����� ����������\n"s <<
		"����� ���� � �������������� ������� ������������ = "s << volume_pneumatic�avity_ << "[�^3]\n"s <<
		"������������ ���������� ���������� ������� = "s << domain::qmax__ << "��\n"s  << std::setprecision(4) <<
		"[���������]:\t"s << result << "\n"s << domain::line__ << std::endl;
}