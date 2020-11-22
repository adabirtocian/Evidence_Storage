#pragma once
#include <qwidget.h>
#include "service.h"

class DataRepresentation : public QWidget
{
private:
	Service& service;
public:
	DataRepresentation(Service& service);
private:
	void initializeGUI();

};

