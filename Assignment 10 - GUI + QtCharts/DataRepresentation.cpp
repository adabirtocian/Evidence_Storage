#include "DataRepresentation.h"

#include <QtCharts/QChartGlobal>
#include <QtCharts/qchartview.h>
#include <QtCharts/qpieseries.h>
#include <QtCharts/qpieslice.h>
#include <QTCharts/QPieSeries>
#include <QtCharts/qbarset.h>
#include <QtCharts/qbarseries.h>
#include <QtCharts/qbarcategoryaxis.h>
#include <QtCharts/qvalueaxis.h>
#include <QHBoxLayout>
#include <qformlayout.h>
#include <qlineedit.h>

using namespace std;
using namespace QtCharts;

DataRepresentation::DataRepresentation(Service& service): service{service}
{
	this->initializeGUI();
}

void DataRepresentation::initializeGUI()
{
	this->setWindowTitle("Graphic data representation :)");
	QHBoxLayout* mainLayout = new QHBoxLayout{ this };

	vector<Evidence> evidences = this->service.getAllEvidence();
	vector<string> measurements;
	vector<double> quantityPerMeasurement;

	for (int i = 0; i < evidences.size(); ++i)
	{
		int measurementTypeAdded = 1;
		for (int j = 0; j < measurements.size(); ++j)
			if (measurements[j] == evidences[i].getMeasurement()) measurementTypeAdded = 0;

		if (measurementTypeAdded == 1) measurements.push_back(evidences[i].getMeasurement());
	}

	// Pie Chart - measurement distribution

	QPieSeries* pieSeriesMeasurement = new QPieSeries();
	vector<QPieSlice*> slicesVectorMeasurement;

	double maximumQuantity = 0;
	for (int i = 0; i < measurements.size(); ++i)
	{
		int numberPerType = 0;
		double quantityOneMeasurement = 0;
		for (int j = 0; j < evidences.size(); ++j)
			if (evidences[j].getMeasurement() == measurements[i])
			{
				numberPerType++;
				quantityOneMeasurement += evidences[j].getQuantity();

				
			}
		quantityPerMeasurement.push_back(quantityOneMeasurement);
		if (quantityOneMeasurement > maximumQuantity)
			maximumQuantity = quantityOneMeasurement;

		string typeAndNumber = measurements[i] + " : " + to_string(numberPerType);
		pieSeriesMeasurement->append(typeAndNumber.c_str(), numberPerType);
		slicesVectorMeasurement.push_back(pieSeriesMeasurement->slices().at(i));
		slicesVectorMeasurement[i]->setLabelVisible();
	}

	QChart* chartMeasurementTypes = new QChart();
	chartMeasurementTypes->setTheme(chartMeasurementTypes->ChartThemeBlueIcy);
	chartMeasurementTypes->addSeries(pieSeriesMeasurement);
	chartMeasurementTypes->setTitle("Evidence statistics by measurement");

	QChartView* chartViewMeasurementTypes = new QChartView(chartMeasurementTypes);
	chartViewMeasurementTypes->setMinimumWidth(600);
	chartViewMeasurementTypes->setMinimumHeight(500);
	chartViewMeasurementTypes->setRenderHint(QPainter::Antialiasing);

	mainLayout->addWidget(chartViewMeasurementTypes);

	QStringList categories;
	QBarSet* barSetMeasurement = new QBarSet("Quantity");

	for (int i = 0; i < measurements.size(); ++i)
	{
		*barSetMeasurement << quantityPerMeasurement[i];
		categories << QString::fromStdString(measurements[i]);
	}

	//Bar chart - total quantity per each measurement

	QBarSeries* barSeriesQuantity = new QBarSeries();
	barSeriesQuantity->append(barSetMeasurement);
	
	QChart* chartMeasurementQuantity = new QChart();
	chartMeasurementQuantity->addSeries(barSeriesQuantity);
	chartMeasurementQuantity->setTitle("Bar chart");
	chartMeasurementQuantity->setAnimationOptions(QChart::SeriesAnimations);

	QBarCategoryAxis* axisMeasurement = new QBarCategoryAxis();
	axisMeasurement->append(categories);
	chartMeasurementQuantity->addAxis(axisMeasurement, Qt::AlignBottom);
	barSeriesQuantity->attachAxis(axisMeasurement);

	QValueAxis* axisQuantity = new QValueAxis();
	axisQuantity->setRange(0, maximumQuantity);
	chartMeasurementQuantity->addAxis(axisQuantity, Qt::AlignLeft);
	barSeriesQuantity->attachAxis(axisQuantity);

	chartMeasurementQuantity->legend()->setVisible(true);
	chartMeasurementQuantity->legend()->setAlignment(Qt::AlignBottom);

	QChartView* chartViewMeasurementQuantity = new QChartView(chartMeasurementQuantity);
	chartViewMeasurementQuantity->setRenderHint(QPainter::Antialiasing);
	chartViewMeasurementQuantity->setMinimumHeight(500);
	chartViewMeasurementQuantity->setMinimumWidth(600);
	
	mainLayout->addWidget(chartViewMeasurementQuantity);
	
}