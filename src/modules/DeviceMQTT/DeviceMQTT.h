#ifndef MQTT_H
#define MQTT_H

#include <Arduino.h>
#include <Streaming.h>
#include <WiFi.h>
#include <MQTTClient.h>
#include <ArduinoJson.h>
#include "Board.h"
#include "Params.h"
#include "ParamsRTOS.h"

// ------------ callbacks ------------
typedef void (*IOTMessageCallback)(String topic, String payload);
typedef void (*IOTCallback)();

extern IOTMessageCallback onIOTMessageReceivedCallback;
extern IOTMessageCallback onIOTMessagePublishedCallback;
extern IOTCallback onIOTConnectedCallback;
extern IOTCallback onIOTDisconnectedCallback;
// ------------------------------------

#include "RobotButterfly.h"

void initMQTT();
void updateMQTT();
void Task_MQTT_code(void * pvParameters);
void setMQTTTaskPriority(uint8_t p);

static WiFiClient net;
static MQTTClient mqtt;

struct DeviceMQTT {

	String wifi_ssid;
	String wifi_pass;
	String mqtt_server;
	String mqtt_port;
	String mqtt_user;
	String mqtt_pass;
	String mqtt_id;
	String robot_name;
	String robot_namespace;
	String robot_set;
	String robot_team;

};

extern struct DeviceMQTT device_mqtt;

void connect();
void defaultSubscribeMQTT();
void conductorSubscribeMQTT();
void subscribeMQTT(String topic);
void defaultPublishMQTT();
void publishMQTT();
void messageReceivedMQTT(String &topic, String &payload);
String getMacAddress();
void publishMQTTMessage(String topic, String payload);

static bool done_connecting;
static bool done_disconnecting;
static bool mqtt_task_enabled;
static bool time_to_publish;

// ---------- rtos ------------
static TaskHandle_t Task_MQTT;
static SemaphoreHandle_t Mutex_MQTT;
static long last_mqtt_rtos_print;
// -------------------------------

#endif