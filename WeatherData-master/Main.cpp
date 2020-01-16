#include<chrono>
#include<string>
#include<iostream>
#include<fstream>
#include<vector>

using namespace std;
typedef std::chrono::high_resolution_clock Clock;

struct WeatherData {
	string date = "";
	float inAvgTemp, outAvgTemp;
	int moldIn, moldOut;
	float inAvgHum, outAvgHum;
	float minInAvgTemp, minOutAvgTemp, maxInAvgTemp, maxOutAvgTemp;
	float minInAvgHum, minOutAvgHum, maxInAvgHum, maxOutAvgHum;
};

//Change place for two memoryadresses
void swap(WeatherData* xp, WeatherData* yp){
	WeatherData temp = *xp;
	*xp = *yp;
	*yp = temp;
}

//Print function
void printVector(vector<WeatherData>& weather, int size){
	int i;
	for (i = 0; i < size; i++)
		cout << &weather[i] << " ";
	cout << endl;
}

//Search function
int search(vector<WeatherData>& weather, string x) {
	for (auto i = 0; i < weather.size(); i++)
		if (weather[i].date == x)
			return i;
	return -1;
}

//Sorts lowest to higest date
void DateLowToHigh(vector <WeatherData>& weather, int n){
	int i, j;
	for (i = 0; i < n - 1; i++)
		for (j = 0; j < n - i - 1; j++)
			if (weather[j].date > weather[j + 1].date)
				swap(&weather[j], &weather[j + 1]);
}

//Sort from warmest to coldest indoor
void IndoorAvgTempHotToCold(vector <WeatherData>& weather, int n){
	int i, j;
	for (i = 0; i < n - 1; i++)
		for (j = 0; j < n - i - 1; j++)
			if (weather[j].inAvgTemp < weather[j + 1].inAvgTemp)
				swap(&weather[j], &weather[j + 1]);
}

//Sort from coldest to warmest indoor
void IndoorAvgTempColdToHot(vector <WeatherData>& weather, int n){
	int i, j;
	for (i = 0; i < n - 1; i++)
		for (j = 0; j < n - i - 1; j++)
			if (weather[j].inAvgTemp > weather[j + 1].inAvgTemp)
				swap(&weather[j], &weather[j + 1]);
}

//Sort from warmest to coldest outdoor
void OutdoorAvgTempHotToCold(vector <WeatherData>& weather, int n){
	int i, j;
	for (i = 0; i < n - 1; i++)
		for (j = 0; j < n - i - 1; j++)
			if (weather[j].outAvgTemp < weather[j + 1].outAvgTemp)
				swap(&weather[j], &weather[j + 1]);
}

//Sort from coldest to warmest outdoor
void OutdoorAvgTempColdToHot(vector <WeatherData>& weather, int n){
	int i, j;
	for (i = 0; i < n - 1; i++)
		for (j = 0; j < n - i - 1; j++)
			if (weather[j].outAvgTemp > weather[j + 1].outAvgTemp)
				swap(&weather[j], &weather[j + 1]);
}

//Sort from driest to wettest indoor
void IndoorAvgHumDryToMoist(vector <WeatherData>& weather, int n){
	int i, j;
	for (i = 0; i < n - 1; i++)
		for (j = 0; j < n - i - 1; j++)
			if (weather[j].inAvgHum > weather[j + 1].inAvgHum)
				swap(&weather[j], &weather[j + 1]);
}

//Sort from the wettest to driest indoor
void IndoorAvgHumMoistToDry(vector <WeatherData>& weather, int n){
	int i, j;
	for (i = 0; i < n - 1; i++) 
		for (j = 0; j < n - i - 1; j++)
			if (weather[j].inAvgHum < weather[j + 1].inAvgHum)
				swap(&weather[j], &weather[j + 1]);
}

//Sort from driest to wettest outdoor
void OutdoorAvgHumDryToMoist(vector <WeatherData>& weather, int n){
	int i, j;
	for (i = 0; i < n - 1; i++) 
		for (j = 0; j < n - i - 1; j++)
			if (weather[j].outAvgHum > weather[j + 1].outAvgHum)
				swap(&weather[j], &weather[j + 1]);
}

//Sort from wettest to driest outdoor
void OutdoorAvgHumMoistToDry(vector <WeatherData>& weather, int n){
	int i, j;
	for (i = 0; i < n - 1; i++)  
		for (j = 0; j < n - i - 1; j++)
			if (weather[j].outAvgHum < weather[j + 1].outAvgHum)
				swap(&weather[j], &weather[j + 1]);
}

//Sort from lowest risk of mold to highest indoor
void IndoorAvgMoldLowToHigh(vector <WeatherData>& weather, int n){
	int i, j;
	for (i = 0; i < n - 1; i++)  
		for (j = 0; j < n - i - 1; j++)
			if (weather[j].moldIn > weather[j + 1].moldIn)
				swap(&weather[j], &weather[j + 1]);
}

//Sort from highest to lowest mold risk indoor
void IndoorAvgMoldHighToLow(vector <WeatherData>& weather, int n){
	int i, j;
	for (i = 0; i < n - 1; i++)
		for (j = 0; j < n - i - 1; j++)
			if (weather[j].moldIn < weather[j + 1].moldIn)
				swap(&weather[j], &weather[j + 1]);
}

//Sort from the lowest to highest risk of mold outdoor
void OutdoorAvgMoldLowToHigh(vector <WeatherData>& weather, int n){
	int i, j;
	for (i = 0; i < n - 1; i++)
		for (j = 0; j < n - i - 1; j++)
			if (weather[j].moldOut > weather[j + 1].moldOut)
				swap(&weather[j], &weather[j + 1]);
}

//Sort from the highest to lowest risk of mold outdoor
void OutdoorAvgMoldHighToLow(vector <WeatherData>& weather, int n){
	int i, j;
	for (i = 0; i < n - 1; i++)
		for (j = 0; j < n - i - 1; j++)
			if (weather[j].moldOut < weather[j + 1].moldOut)
				swap(&weather[j], &weather[j + 1]);
}

int main() {
	auto t1 = Clock::now();
	//bunch of variables for later use
	string day, time, inOut, temperature, humidity, dates, searchDate,a;
	string currentDate = "", checkDate = "", input = "";
	int sizeIn, ptime, sizeOut, countIn = 0, countOut = 0, countTotal = 0;
	float tempInSum = 0, tempOutSum = 0, humInSum = 0, humOutSum = 0;

	//create 2 vectors, one for inside and one for outside so it will be easier to sort
	struct vector<WeatherData>weatherInside;
	struct vector<WeatherData>weatherOutside;
	struct WeatherData inside;
	struct WeatherData outside;

	//creates a stream to our txt file to read data from
	string inFileName = "tempdata4long.txt";
	ifstream inFile;
	inFile.open(inFileName);

	if (inFile.is_open()) {
		//While loop to go through every lines
		while (inFile) {
			getline(inFile, day, ' '), getline(inFile, time, ','), getline(inFile, inOut, ','), getline(inFile, temperature, ','), getline(inFile, humidity);
			dates = day.substr(0, 4) + day.substr(5, 2) + day.substr(8, 2);

			//Everything is calculated here to later get inserted into the vector
			if (dates == checkDate) {
				if (inOut == "Inne") {
					tempInSum += stof(temperature);
					humInSum += stof(humidity);
					currentDate = dates;
					countIn++;
				}
				else {
					tempOutSum += stof(temperature);
					humOutSum += stof(humidity);
					currentDate = dates;
					countOut++;
				} countTotal++;
			}
			else {
				checkDate = dates;
				//if it has found a date it will insert it into our inside and outside
				if (countTotal != 0) {
					inside.date = currentDate;
					inside.inAvgTemp = (tempInSum / countIn);
					inside.inAvgHum = (humInSum / countIn);

					outside.date = currentDate;
					outside.outAvgTemp = (tempOutSum / countOut);
					outside.outAvgHum = (humOutSum / countOut);

					//Calculates the mold indoor
					if ((inside.inAvgTemp >= 15 && inside.inAvgTemp < 50) && (inside.inAvgHum >= 78))
						inside.moldIn = (inside.inAvgHum - 78) / 0.22;
					else if ((inside.inAvgTemp >= 0 && inside.inAvgTemp < 15) && (inside.inAvgHum >= 78))
						inside.moldIn = ((inside.inAvgHum - 78) * (inside.inAvgTemp / 15)) / 0.22;
					else
						inside.moldIn = 0;

					//Calculates the mold outdoor
					if ((outside.outAvgTemp >= 15 && outside.outAvgTemp < 50) && (outside.outAvgHum >= 78))
						outside.moldOut = (outside.outAvgHum - 78) / 0.22;
					else if ((outside.outAvgTemp >= 0 && outside.outAvgTemp < 15) && (outside.outAvgHum >= 78))
						outside.moldOut = ((outside.outAvgHum - 78) * (outside.outAvgTemp / 15)) / 0.22;
					else
						outside.moldOut = 0;

					//pushes the inside and outside into our weatherinside and weatheroutside vectors
					weatherInside.push_back(inside);
					weatherOutside.push_back(outside);

					//resets all the variables to be used again for the next date
					tempInSum = 0, tempOutSum = 0, humInSum = 0, humOutSum = 0, countIn = 0, countOut = 0, countTotal = 0;
				}
			}if (!inFile)
				break;
		}
		sizeIn = weatherInside.size(), sizeOut = weatherOutside.size();
		
		//Prints how long it took for the program to start
		if (ptime = 1){
			auto t2 = Clock::now();
			cout << "The program took " << chrono::duration_cast <chrono::seconds> (t2 - t1).count() << " seconds to run\n\n";
			ptime = 2;
		}

		do {
			cout << "Enter 1 to search for specifik date" << endl;
			cout << "Enter 2 for the 5 warmest and coldest days, indoor" << endl;
			cout << "Enter 3 to get the 5 warmest and coldest days, outdoor " << endl;
			cout << "Enter 4 for the 5 driest and the days with highest humidity, indoor " << endl;
			cout << "Enter 5 for the 5 driest and the days with highest humidity, outdoor " << endl;
			cout << "Enter 6 for the 5 days with lesser and higher risk of mold, indoor " << endl;
			cout << "Enter 7 for the 5 days with low and high risk of mold, outdoor " << endl;
			cout << "Enter 8 for Winter and Fall \n" << endl;

			getline(cin, input);
			cout << endl;
			int inputCase = stoi(input);

			switch (inputCase){
			//Search for specific date
			case 1:{
				cout << "Enter Date with format 'yyyymmdd': " << endl;
				getline(cin, searchDate);
				int c = search(weatherInside, searchDate);
				int k = search(weatherOutside, searchDate);

				//Prints the indoor date - temp - hum - risk of mold
				cout << "\nIndoor" << endl;
				cout << "Date" << "\t\t" << "Temperature" << "\t" << "AirHumidity" << "\t" << "risk of molt Indoor" << endl;
				cout << weatherInside[c].date << "\t" << weatherInside[c].inAvgTemp << "\t\t" << weatherInside[c].inAvgHum << " \t" << weatherInside[c].moldIn << endl;
				
				//Prints the outdoor date - temp - hum - risk of mold
				cout << "\nOutdoor" << endl;
				cout << "Date" << "\t\t" << "Temperature" << "\t" << "AirHumidity" << "\t" << "risk of molt outdoor" << endl;
				cout << weatherOutside[k].date << "\t" << weatherOutside[k].outAvgTemp << "\t\t" << weatherOutside[k].outAvgHum << "\t\t" << weatherOutside[k].moldOut << endl;
				
				cout << "Press enter to continue" << endl;
				getline(cin, a);
				printf("\033c");
				break;
			}
			//Sort temperature inside
			case 2:{
				//Sort from warmest to coldest and prints the warmest days indoor
				IndoorAvgTempHotToCold(weatherInside, sizeIn);
				cout << "The 5 warmest days, indoor: " << endl;
				cout << "Date" << "\t\t" << "Temperature" << endl;

				for (int i = 0; i < 5; i++)
					cout << weatherInside[i].date << "\t" << weatherInside[i].inAvgTemp << endl;
				cout << endl;

				//Sort from coldest to warmest and prints the coldest days indoor
				IndoorAvgTempColdToHot(weatherInside, sizeIn);
				cout << "The 5 coldest days, indoor: " << endl;
				cout << "Date" << "\t\t" << "Temperature" << endl;
				
				for (int i = 0; i < 5; i++)
					cout << weatherInside[i].date << "\t" << weatherInside[i].inAvgTemp << endl;

				cout << "Press enter to continue" << endl;
				getline(cin, a);
				printf("\033c");
				break;
			}
			//Sort temperature outside
			case 3:{
				//Sort from warmest to coldest och prints the warmest outdoor
				OutdoorAvgTempHotToCold(weatherOutside, sizeOut);
				cout << "The 5 warmest days, outdoor: " << endl;
				cout << "Date" << "\t\t" << "Temperature" << endl;

				for (int i = 0; i < 5; i++)
					cout << weatherOutside[i].date << "\t" << weatherOutside[i].outAvgTemp << endl;
				cout << endl;

				//Sort from coldest to warmest and prints the coldest days outdoor
				OutdoorAvgTempColdToHot(weatherOutside, sizeOut);
				cout << "The 5 coldest days, outdoor: " << endl;
				cout << "Date" << "\t\t" << "Temperature" << endl;

				for (int i = 0; i < 5; i++)
					cout << weatherOutside[i].date << "\t" << weatherOutside[i].outAvgTemp << endl;

				cout << "Press enter to continue" << endl;
				getline(cin, a);
				printf("\033c");
				break;
			}
			//Sort humidity inside
			case 4:{
				//Sort from driest to wettest and prints the driest indoor
				IndoorAvgHumDryToMoist(weatherInside, sizeIn);
				cout << "The 5 driest days, indoor: " << endl;
				cout << "Date" << "\t\t" << "Humidity" << endl;

				for (int i = 0; i < 5; i++)
					cout << weatherInside[i].date << "\t" << weatherInside[i].inAvgHum << endl;
				cout << endl;

				//Sort from the wettest to driest and prints the wettest indoor
				IndoorAvgHumMoistToDry(weatherInside, sizeIn);
				cout << "The 5 days wettest days, indoor: " << endl;
				cout << "Date" << "\t\t" << "Humidity" << endl;

				for (int i = 0; i < 5; i++)
					cout << weatherInside[i].date << "\t" << weatherInside[i].inAvgHum << endl;

				cout << "Press enter to continue" << endl;
				getline(cin, a);
				printf("\033c");
				break;
			}
			//Sort humidity outside
			case 5:{
				//Sort from the driest to wettest and prints the driest days outdoor
				OutdoorAvgHumDryToMoist(weatherOutside, sizeOut);
				cout << "The 5 driest days, outdoor: " << endl;
				cout << "Date" << "\t\t" << "Humidity" << endl;

				for (int i = 0; i <= 5; i++)
					cout << weatherOutside[i].date << "\t" << weatherOutside[i].outAvgHum << endl;
				cout << endl;

				//Sort from the wettest to driest and prints the wettest days outdoor
				OutdoorAvgHumMoistToDry(weatherOutside, sizeOut);
				cout << "The 5 days with the highest humidity, outdoor: " << endl;
				cout << "Date" << "\t\t" << "Humidity" << endl;

				for (int i = 0; i < 5; i++)
					cout << weatherOutside[i].date << "\t" << weatherOutside[i].outAvgHum << endl;

				cout << "Press enter to continue" << endl;
				getline(cin, a);
				printf("\033c");
				break;
			}
			//Prints mouldindex inside
			case 6:{
				cout << "Scale from 0-100" << endl;

				//Sort from lowest to higest risk of mold and prints the days with lowest indoor
				IndoorAvgMoldHighToLow(weatherInside, sizeIn);
				cout << "Days with lesser risk of mold, indoor: " << endl;
				cout << "Date" << "\t\t" << "Mold" << endl;
				
				for (int i = 0; i < 5; i++)
					cout << weatherInside[i].date << "\t" << weatherInside[i].moldIn << endl;
				cout << endl;

				//Sort from higest to lowest risk of mold and prints the days with the higest indoor
				IndoorAvgMoldLowToHigh(weatherInside, sizeIn);
				cout << "Days with high risk of mold, indoor: " << endl;
				cout << "Date" << "\t\t" << "Mold" << endl;

				for (int i = 0; i < 5; i++)
					cout << weatherInside[i].date << "\t" << weatherInside[i].moldIn << endl;
				
				cout << "Press enter to continue" << endl;
				getline(cin, a);
				printf("\033c");
				break;
			}
			//Prints mouldindex outside
			case 7:{
				cout << "Scale from 0-100" << endl;

				//Sort from lowest to higest mold risk and prints the days with the lowest outdoor
				OutdoorAvgMoldHighToLow(weatherOutside, sizeOut);
				cout << "Days with low risk of mold, outdoor: " << endl;
				cout << "Date" << "\t\t" << "Mold" << endl;
				
				for (int i = 0; i < 5; i++)
					cout << weatherOutside[i].date << "\t" << weatherOutside[i].moldOut << endl;
				cout << endl;
				
				//Sort from higest to lowest mold risk and prints the days with the higest outdoor
				cout << "Days with high risk of mold, outdoor: " << endl;
				OutdoorAvgMoldLowToHigh(weatherOutside, sizeOut);
				cout << "Date" << "\t\t" << "Mold" << endl;
				
				for (int i = 0; i < 5; i++)
					cout << weatherOutside[i].date << "\t" << weatherOutside[i].moldOut << endl;

				cout << "Press enter to continue" << endl;
				getline(cin, a);
				printf("\033c");
				break;
			}
			//Date for winter and autumn
			case 8:{
				int winterCount = 0, fallCount1 = 0, fallCount = 0;
				DateLowToHigh(weatherOutside, sizeOut);

				//Winter
				for (int i = 0; i < sizeOut; i++)
					//Check if temp is bellow 0
					if (outside.outAvgTemp <= 0) {
						winterCount++;
						//if temp is bellow 0 5 times in a row winter has arrived
						if (winterCount == 5) { cout << "Winter arrived at: " << weatherOutside[i - 5].date << "\n" << endl;break; }
					}
					else winterCount = 0;
				//if no winter was found it will print no winter occurred
				if (winterCount == 0)cout << "No winter occurred" << "\n" << endl;


				//Autumn
				for (int i = 0; i < sizeOut; i++)
					//Check if temp outside is between zero and 10
					if (weatherOutside[i].outAvgTemp > 0 && weatherOutside[i].outAvgTemp < 10)
						//Check if the next day is colder than the day before, if it is colder 4 times in a row each time you have autumn
						if (weatherOutside[i].outAvgTemp <= weatherOutside[i - 1].outAvgTemp) {
							fallCount1++;
							if (fallCount1 == 4) { cout << "Autumn arrived at: " << weatherOutside[i - 4].date << endl;break; }
							//if one day is not colder than the one before reset the counter
						}else fallCount1 = 0;
				//if no autumn was found it will print no autumn occurred
				if (fallCount1 == 0)cout << "No Autumn occurred" << endl;
				
				cout << "Press enter to continue" << endl;
				getline(cin, a);
				printf("\033c");
			}
			default:
				break;
			}
			cout << endl;
			cin.clear();
		} while (true);
		inFile.close();
	}else
		cout << "Cannot open file " << inFileName << endl;
}
