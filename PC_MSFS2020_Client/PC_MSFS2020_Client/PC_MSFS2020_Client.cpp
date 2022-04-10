#include <windows.h>
#include <iostream>

#include "SimConnect.h"
#include <string>
#include <curl/curl.h>
#include <sstream>

int quit = 0;
HANDLE hSimConnect = NULL;


static enum DATA_DEFINE_ID {
	DEFINITION_1,
};

static enum DATA_REQUEST_ID {
	REQUEST_1,
	REQUEST_2,
};

struct SimResponse {
	//SIMCONNECT_DATA_LATLONALT simdata;
	double latitude;
	double longitude;
	//int64_t gps_altitude;
	double altitude;
	int32_t heading;
	int32_t speed;
	int32_t vertical_speed;
};


void sendTelemetry(SimResponse* pS) {
	CURLcode ret;
	CURL* hnd;
	struct curl_slist* slist1;
	//std::string jsonstr = "{\"username\":\"bob\",\"password\":\"12345\"}";

	std::ostringstream oss;
	oss << "{";
	oss << "\"model\":\"AIRBUS_A320\",";
	oss << "\"telemetry\":{";
	oss << "\"latitude\":\"" << pS->latitude << "\",";
	oss << "\"longitude\":\"" << pS->longitude << "\",";
	oss << "\"altitude\":\"" << pS->altitude << "\",";
	oss << "\"pitch\":\"" << 0 << "\",";
	oss << "\"bank\":\"" << 0 << "\",";
	oss << "\"trueHeading\":\"" << pS->heading << "\",";
	oss << "\"magneticHeading\":\"" << pS->heading << "\"";
	oss << "},";
	oss << "\"gearDown\":\"false\",";
	oss << "\"onGround\":\"false\"";
	oss << "}";
	std::string payload = oss.str();

	std::cout << payload;

	slist1 = NULL;
	slist1 = curl_slist_append(slist1, "Content-Type: application/json");

	hnd = curl_easy_init();
	curl_easy_setopt(hnd, CURLOPT_URL, "http://192.168.1.104:8080/user/telemetry");
	curl_easy_setopt(hnd, CURLOPT_NOPROGRESS, 1L);
	curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, payload.c_str());
	curl_easy_setopt(hnd, CURLOPT_USERAGENT, "curl/7.82.0");
	curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, slist1);
	curl_easy_setopt(hnd, CURLOPT_MAXREDIRS, 50L);
	curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "POST");
	curl_easy_setopt(hnd, CURLOPT_TCP_KEEPALIVE, 1L);

	ret = curl_easy_perform(hnd);

	curl_easy_cleanup(hnd);
	hnd = NULL;
	curl_slist_free_all(slist1);
	slist1 = NULL;
}


void CALLBACK MyDispatchProc1(SIMCONNECT_RECV* pData, DWORD cbData, void* pContext) {
	switch (pData->dwID)
	{

	case SIMCONNECT_RECV_ID_SIMOBJECT_DATA:
	{
		SIMCONNECT_RECV_SIMOBJECT_DATA* pObjData = (SIMCONNECT_RECV_SIMOBJECT_DATA*)pData;

		switch (pObjData->dwRequestID)
		{
		case REQUEST_1:

			SimResponse* pS = (SimResponse*)&pObjData->dwData;
			sendTelemetry(pS);

			std::cout

				<< "\nAltitude: " << pS->altitude
				<< " - Heading: " << pS->heading
				<< " - Speed (knots): " << pS->speed
				<< " - Vertical Speed: " << pS->vertical_speed
				<< " - Lat: " << pS->latitude
				<< " - Lon: " << pS->longitude
				<< std::flush;
			break;
		}
		break;
	}

	case SIMCONNECT_RECV_ID_QUIT:
	{
		quit = 1;
		break;
	}

	default:
		break;
	}
}

bool initSimEvents() {
	HRESULT hr;

	if (SUCCEEDED(SimConnect_Open(&hSimConnect, "Client Event Demo", NULL, 0, NULL, 0))) {
		std::cout << "\nConnected To Microsoft Flight Simulator 2020!\n";

		// DATA
		//hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "MIDDLE MARKER LATLONALT", "structure");
		hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "Plane Latitude", "degrees");
		hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "Plane Longitude", "degrees");
		//hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "GPS POSITION ALT", "degrees");
		hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "Indicated Altitude", "feet");
		hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "HEADING INDICATOR", "degrees", SIMCONNECT_DATATYPE_INT64);
		hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "Airspeed Indicated", "knots", SIMCONNECT_DATATYPE_INT64);
		hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "VERTICAL SPEED", "Feet per second", SIMCONNECT_DATATYPE_INT64);

		// EVERY SECOND REQUEST DATA FOR DEFINITION 1 ON THE CURRENT USER AIRCRAFT (SIMCONNECT_OBJECT_ID_USER)
		hr = SimConnect_RequestDataOnSimObject(hSimConnect, REQUEST_1, DEFINITION_1, SIMCONNECT_OBJECT_ID_USER, SIMCONNECT_PERIOD_SECOND);

		// Process incoming SimConnect Server messages
		while (quit == 0) {
			// Continuously call SimConnect_CallDispatch until quit - MyDispatchProc1 will handle simulation events
			SimConnect_CallDispatch(hSimConnect, MyDispatchProc1, NULL);
			Sleep(1);
		}

		hr = SimConnect_Close(hSimConnect);
		return true;
	}
	else {
		std::cout << "\nFailed to Connect!!!!\n";
		return false;
	}
}

int main() {
	initSimEvents();

	return 0;
}