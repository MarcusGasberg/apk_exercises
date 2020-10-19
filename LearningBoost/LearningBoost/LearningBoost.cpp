//// LearningBoost.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//#include <iostream>
//#include <boost/signals2/signal.hpp>
//#include "MedianCombiner.h"
//
//void print_out(const std::string& sensor_name, double sensor_value);
//class SigFunctor
//{
//public:
//	void operator()(const std::string& sensor_name, double sensor_value) const {
//		std::cout << "Functor:: " << sensor_name << ": " << sensor_value << std::endl;
//	}
//};
//
//class SensorLogger
//{
//public:
//	void log(const std::string& sensor_name, double sensor_value)
//	{
//		std::cout << "Method:: " << sensor_name << ": " << sensor_value << std::endl;
//	}
//};
//
//int main()
//{
//	boost::signals2::signal<void(const std::string&, double)> sig;
//
//	const SigFunctor sigf;
//	SensorLogger logger;
//
//	sig.connect(&print_out);
//	sig.connect(sigf);
//	sig.connect([](auto name, auto val){
//		std::cout << "Lambda::" << name << ": " << val << std::endl;
//	});
//	sig.connect(boost::bind(&SensorLogger::log, boost::ref(logger), boost::placeholders::_1, boost::placeholders::_2));
//
//	sig("TEST", 10);
//}
//
//void print_out(const std::string& sensor_name, double sensor_value)
//{
//	std::cout << "Free Function::" << sensor_name << ": " << sensor_value << std::endl;
//}