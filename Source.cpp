#include "csv.h"
#include "csv.cpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Eigen\Dense"
#include "Eigen\Geometry"

using namespace std;
using namespace Eigen;

const int number_of_sensor = 3;

/*int main()
{
	ifstream in("calibration_normal_walking.csv");
	vector<string> header;
	vector<vector<double>> fields;
	if (in) {
		string line;
		bool isheader = true;
		while (getline(in, line)) {
			stringstream sep(line);
			string field;
			if (!isheader)
			{
				fields.push_back(vector<double>());
				while (getline(sep, field, ',')) {
					fields.back().push_back(stod(field));
				}
			}
			else
			{
				while (getline(sep, field, ','))
				{
					header.push_back(field);
				}
				isheader = false;
			}
		}
	}
	for (auto row : fields) {
		for (auto field : row) {
			cout << field << ' ';
		}
		cout << '\n';
	}
	for (auto it = header.begin(); it != header.end(); ++it) {
		cout << *it;
	
	}
}*/

int main()
{
	//csv<float> lpms_data("calibration_normal_walking.csv");
	csv<float> lpms_data("../../../lpms_datasets_0728/wip_neutral.csv");
	//csv<double> write_data("write_data.csv");
	

	// csvread
	lpms_data.setquietMode(true);
	lpms_data.read();
	cout << " << read data" << endl;
	vector<vector<float>> data = lpms_data.getfields();
	cout << " << read header" << endl;
	vector<string> header = lpms_data.getheader();

	int colSize = header.size();
	int rowSize = data.size();
	cout << "Column size : " << colSize << endl;
	cout << "Row size : " << rowSize << endl;

/* column headers
00 SensorId, TimeStamp, FrameNumber, AccX (g), AccY (g), AccZ (g), GyroX (deg/s),
07 GyroY (deg/s), GyroZ (deg/s), MagX (uT), MagY (uT), MagZ (uT), EulerX (deg),
13 EulerY (deg), EulerZ (deg), QuatW, QuatX, QuatY, QuatZ, LinAccX (g), LinAccY (g),
21 LinAccZ (g), Pressure (kPa), Altitude (m), Temperature (degC), HeaveMotion (m)*/

	vector<float> lpms_TimeStamp[number_of_sensor];
	vector<int> lpms_FrameNumber[number_of_sensor];
	vector<Vector3f> lpms_Acc[number_of_sensor];
	vector<Vector3f> lpms_Gyro[number_of_sensor];
	vector<Quaternionf> lpms_Quat[number_of_sensor];
	vector<Vector3f> lpms_LinAcc[number_of_sensor];

	for (int i = 0; i < rowSize; i++)
	{
		int SensorId = (int)data[i][0];
		int idx = SensorId - 1;
		lpms_TimeStamp[idx].push_back(data[i][1]);
		lpms_FrameNumber[idx].push_back((int)data[i][2]);
		lpms_Acc[idx].push_back(Vector3f(data[i][3], data[i][4], data[i][5]));
		lpms_Gyro[idx].push_back(Vector3f(data[i][6], data[i][7], data[i][8]));
		lpms_Quat[idx].push_back(Quaternionf(data[i][15], data[i][16], data[i][17], data[i][18]));
		lpms_LinAcc[idx].push_back(Vector3f(data[i][19], data[i][20], data[i][21]));
	}

	cout << "Parsing done!" << endl;
	
	// csvwrite
	/*vector<string> header = { "Col1", "Col2", "Col3" };
	vector<vector<double>> fields = { { 1.1, 2.2, 3.3 },{ 4.4, 5.5, 6.6 },{ 7.7, 8.8, 9.9 } };
	write_data.write(header, fields);
	cout << "csv write" << endl;*/

	return 0;
}